#include <iostream>
#include <string>
#include <native/heap.h>
// #include <stdio.h>
#include "sysconfig.h"
#include "logger.h"
using namespace std;

#define SYS_TYPE 					32
#define SYS_BYTE_ORDER				1
#define SYS_VERSION					1
#define SYS_MACHINE					1

#define verify(exp, ecode, msg) {		\
	if(exp) {							\
		LOGGER_ERR(ecode,msg);			\
	}}								
#define SV_AXIS(i)			(sv_conf->axis_config[i])
#define RC_AXIS(i)			(rc_conf->axis[i])
#define RC_AXIS_DH(i)		(RC_AXIS(i).DH_p)
#define RC_AXIS_LIM(i)		(RC_AXIS(i).Lim_p)

RT_HEAP  	ioconf_heap;				/* I/O配置共享区描述符 */
RT_HEAP 	svconf_heap;				/* 伺服配置信息共享区描述符 */
RT_HEAP 	rcconf_heap;				/* RC配置信息共享区描述符*/
RT_HEAP		sv_heap_desc;				/* 伺服映像区堆描述符 */
RT_HEAP		rc_heap_desc;				/* RC与PLC共享内存区堆描述符 */

IOConfig 		*io_conf;				/* I/O配置信息共享区指针 */
ServoConfig 	*sv_conf;				/* 伺服配置信息共享区指针 */
RobotConfig 	*rc_conf;				/* 机器人配置信息共享区指针 */

IOMem 			io_shm;					/* I/O映像区(包含了分配堆描述符，和返回指针) */
SVMem			*sv_shm;				/* 伺服映像区指针 */
RCMem			*rc_shm;				/* RC与软PLC共享区指针 */

typedef struct{
	uint8_t type;						/* 控制器类型（32位、64位）*/
	uint8_t order;						/* 字节序 小端 大端 */
	uint8_t version;					/* 目标文件版本 */
	uint8_t target;						/* CPU 目标平台 */
}OBJHeader;

/**
  *	功能：加载配置文件头部信息，并判断是否符合要求
  * 返回值： 正常返回0
  */
static int verify_obj(TiXmlNode* node){
	TiXmlElement* configElm = node->FirstChildElement();
	TiXmlAttribute* attr = configElm->FirstAttribute();
	// 判断配置文件的正确性
	if(configElm->Value() == string("header")){
		OBJHeader header;
		for(; attr != NULL; attr = attr->Next()){
			std::string attrName = attr->Name();
			std::string attrValue = attr->Value();
			if(attrName == "type"){
				if(attrValue == "SYS_TYPE_32")			header.type = 32;
				else if(attrValue == "SYS_TYPE_64")		header.type = 64;
				verify(SYS_TYPE != header.type, E_SYS_TYPE, "");
			}
			else if(attrName == "order"){	
				if(attrValue == "BYTE_ORDER_LIT")		header.order = 1;
				else if(attrValue == "BYTE_ORDER_BIG")	header.order = 2;
				verify(SYS_BYTE_ORDER != header.order, E_BYTE_ORDER,"");
			}
			else if(attrName == "version"){
				header.version = atoi(attrValue.c_str());			
				verify(SYS_VERSION != header.version, E_SYS_VERSION, "");
			}
			else if(attrName == "target"){
				if(attrValue == "IPC")					header.target = 1;
				else if(attrValue == "MACH_CORTEX_A8")	header.target = 2;
				verify(SYS_MACHINE != header.target, E_SYS_MACHINE, "");
			}
		}
		LOGGER_DBG(DFLAG_LONG,
			"OBJHeader:\n .type = %d\n .order = %d\n .version = %d\n .machine = %d",
			header.type, header.order, header.version, header.target);
	}
	return 0;
}

/**
  *	功能：加载IO配置信息，并初始化IO映像区
  * 返回值： 正常返回0
  */
static int load_io_config(TiXmlNode* node, IOConfig *io_config){
	// IO 配置及IO初始 
	TiXmlNode* IONode = node->FirstChild("ios");
	TiXmlElement* configElm = IONode->ToElement();
	TiXmlAttribute* attr;
	// int io_count = 0;
	for(attr = configElm->FirstAttribute(); attr != NULL; attr = attr->Next()){
		std::string attrName = attr->Name();
		std::string attrValue = attr->Value();
		if(attrName == "period"){
			io_conf->update_interval = atoi(attrValue.c_str());
			verify(MIN_IO_INTERVAL > io_conf->update_interval, E_IO_INTERVAL, "");
		}
		else if(attrName == "count")
			io_conf->typecount = atoi(attrValue.c_str());
	}
	LOGGER_DBG(DFLAG_LONG,
				"IOConfig:\n .update_interval = %d\n .iotype_count = %d\n", io_conf->update_interval, io_conf->typecount);


	TiXmlNode* OneIONode = IONode->FirstChild();
	int dev_cnt = 0;
	for(;OneIONode != NULL; OneIONode = OneIONode->NextSibling("io"))
	{
		configElm = OneIONode->ToElement();
		for(attr = configElm->FirstAttribute(); attr != NULL; attr = attr->Next()){
			std::string attrName = attr->Name();
			std::string attrValue = attr->Value();
			if(attrName == "pid")			io_conf->io_map[dev_cnt].pid = atoi(attrValue.c_str());
			else if(attrName == "name")		strcpy(io_conf->io_map[dev_cnt].name,attrValue.c_str());
			else if(attrName == "iotype")
				if(attrValue == "input") 	io_conf->io_map[dev_cnt].iotype = INPUT_IO;
				else						io_conf->io_map[dev_cnt].iotype = OUTPUT_IO;
			else if(attrName == "datatype")
				if(attrValue == "digit")	io_conf->io_map[dev_cnt].datatype = DIGIT_IO;
				else						io_conf->io_map[dev_cnt].datatype = ANALOG_IO;
			else if(attrName == "size")		io_conf->io_map[dev_cnt].size = atoi(attrValue.c_str());		
		}

		// 数字I/O初始化
		if(DIGIT_IO == io_conf->io_map[dev_cnt].datatype){
			int unit_cnt = 0;
			TiXmlNode* UnitNode = OneIONode->FirstChild("group");
			for(;UnitNode != NULL; UnitNode = UnitNode->NextSibling()){
				configElm = UnitNode->ToElement();
				for(attr = configElm->FirstAttribute(); attr != NULL; attr = attr->Next()){
					std::string attrName = attr->Name();
					if(attrName == "id"){
						 io_conf->io_map[dev_cnt].id[unit_cnt] = attr->IntValue();
					}else if(attrName == "init"){
						char* addr = io_shm.base[io_conf->io_map[dev_cnt].iotype]+
									io_conf->io_map[dev_cnt].id[unit_cnt]*DIGITUNIT_SIZE;
						std::string attrValue = attr->Value();
						char val = 0;
						for(int i = 0; i < 8; ++i)
							val = (val << 1) + attrValue[i]-'0';
						*addr = val;
					}					
				}
				unit_cnt ++;
			}
			// 验证配置的IO个数与实际读取的IO个数是否相等
			//if(unit_cnt * 8 != io_conf->io_map[dev_cnt].size) { cout << "digit unit error" << endl;	return -1;}
			verify(unit_cnt*8 != io_conf->io_map[dev_cnt].size, E_LOAD_IO_CONFIG, "Digit unit error");
		}else{
			// 模拟IO初始化
			int unit_cnt = 0,port_cnt = 0;
			TiXmlNode* UnitNode = OneIONode->FirstChild("group");
			for(;UnitNode != NULL; UnitNode = UnitNode->NextSibling()){
				configElm = UnitNode->ToElement();
				attr = configElm->FirstAttribute();
				if(string(attr->Name()) == "id"){
					io_conf->io_map[dev_cnt].id[unit_cnt] = attr->IntValue();
					//cout << "id = " << (unsigned)io_conf->io_map[dev_cnt].id << endl;
				}
				TiXmlNode* PortNode = UnitNode->FirstChild("init");
				for(; PortNode != NULL; PortNode = PortNode->NextSibling()){
					TiXmlElement* elm = PortNode->ToElement();
					float AnaVal = atof(elm->GetText()); 
					float* addr = (float *)(io_shm.base[io_conf->io_map[dev_cnt].iotype] + DIGIT_SIZE + 
							(io_conf->io_map[dev_cnt].id[unit_cnt]-16)*ANALOGUNIT_SIZE + port_cnt * ANALOGPORT_SIZE);
					*addr = AnaVal;
					port_cnt ++;
				}
				unit_cnt++;
			}
			// if(unit_cnt * port_cnt != io_conf->io_map[dev_cnt].size) { cout << "analog unit error; portcnt = "  << port_cnt << endl; return -1; }
			verify(unit_cnt * port_cnt != io_conf->io_map[dev_cnt].size, E_LOAD_IO_CONFIG, "Analog unit error");
		} 
		

		if(io_conf->io_map[dev_cnt].datatype == DIGIT_IO){
			int index = io_conf->io_map[dev_cnt].iotype;
			LOGGER_DBG(DFLAG_SHORT, 	
				".IOMem Digit %s:", (index == INPUT_IO ? "Input":"Output"));
			int n = io_conf->io_map[dev_cnt].size/8;
			for(int i = 0; i < n; ++i){
				int ID = io_conf->io_map[dev_cnt].id[i];
				LOGGER_DBG(DFLAG_SHORT," Channel = %d  Value = 0x%x",ID,*(io_shm.base[index]+ID*DIGITUNIT_SIZE));
			}
		}else{
			int index = io_conf->io_map[dev_cnt].iotype;
			LOGGER_DBG(DFLAG_SHORT,
				".IOMem Analog %s", (index == INPUT_IO ? "Input":"Output"));
			int portsize = io_conf->io_map[dev_cnt].size;
			for(int i = 0; i < portsize; ++i){
				int channel = i/8;
				int ID = io_conf->io_map[dev_cnt].id[channel];
				int port = i-channel*8;
				LOGGER_DBG(DFLAG_SHORT," Channel = %d  Port = %d  Value = %f", ID,port,
						*(float *)(io_shm.base[index]+DIGIT_SIZE+ (ID-16)*ANALOGUNIT_SIZE + port*ANALOGPORT_SIZE));
			}
		}
		dev_cnt ++;
	}
	LOGGER_DBG(DFLAG_SHORT,"");
	return 0;
}

/**
  *	功能：加载配置文件中的伺服配置信息
  * 返回值： 正常返回0
  */
static int load_servo_config(TiXmlNode* node, ServoConfig *sv_conf){
	TiXmlNode* SerInfoNode = node->FirstChild("servos");
	TiXmlElement* configElm = SerInfoNode->ToElement();
	TiXmlAttribute* attr;
	for(attr = configElm->FirstAttribute(); attr != NULL; attr = attr->Next()){
		std::string attrName = attr->Name();
		if(attrName == "period") 		 sv_conf->update_interval = attr->IntValue();
		else if(attrName == "count")	 sv_conf->axis_count = attr->IntValue();
		else if(attrName == "opmode")	 sv_conf->opmode = attr->IntValue();		
	}
	LOGGER_DBG(DFLAG_LONG,
			"ServoConfig:\n .axis_count = %d\n .update_interval = %d\n .opmode = %d\n",
				sv_conf->axis_count, sv_conf->update_interval, sv_conf->opmode);

	// 伺服轴配置
	TiXmlNode* 	servoNode = SerInfoNode->FirstChild("servo");
	int axis_cnt = 0;
	for(; servoNode; servoNode = servoNode->NextSibling()){
		configElm = servoNode->ToElement();
		for(attr = configElm->FirstAttribute(); attr != NULL; attr = attr->Next())
		{
			std::string attrName = attr->Name();
			if(attrName == "pid") 			SV_AXIS(axis_cnt).pid = attr->IntValue();
			else if(attrName == "name") 	strcpy(SV_AXIS(axis_cnt).name, attr->Value());
			else if(attrName == "id")		SV_AXIS(axis_cnt).id = attr->IntValue();
			else if(attrName == "type")		SV_AXIS(axis_cnt).type = attr->IntValue();
			else if(attrName == "min_pos") 	SV_AXIS(axis_cnt).min_pos = attr->DoubleValue();
			else if(attrName == "max_pos")	SV_AXIS(axis_cnt).max_pos = attr->DoubleValue();
			else if(attrName == "ratio")	SV_AXIS(axis_cnt).ratio = attr->IntValue();
			else if(attrName == "encode")	SV_AXIS(axis_cnt).encode = attr->IntValue();
		}
		LOGGER_DBG(DFLAG_LONG,
			"AxisConfig:\n .name = %s\n .id = %d\n .type = %d\n .min_pos = %f\n .max_pos = %f\n .ratio = %d\n .encode = %d\n",
			SV_AXIS(axis_cnt).name, SV_AXIS(axis_cnt).id, SV_AXIS(axis_cnt).type, SV_AXIS(axis_cnt).min_pos, 
			SV_AXIS(axis_cnt).max_pos, SV_AXIS(axis_cnt).ratio, SV_AXIS(axis_cnt).encode);
		axis_cnt ++;
	}
	// if(axis_cnt != sv_conf->axis_count) { cout << "axis count error" << endl; return -1;}
	verify(axis_cnt != sv_conf->axis_count, E_AXIS_COUNT,"");
	return 0;
}

/**
  *	功能：加载配置文件中的机器人配置信息
  * 返回值： 正常返回0
  */
static int load_robot_config(TiXmlNode* node, RobotConfig* rc_conf){
	// 机器人参数配置
	TiXmlNode* RobotNode = node->FirstChild("robot");
	TiXmlElement* configElm = RobotNode->ToElement();
	TiXmlAttribute* attr;
	for(attr = configElm->FirstAttribute(); attr != NULL; attr = attr->Next()){
		std::string attrName = attr->Name();
		if(attrName == "name")				strcpy(rc_conf->name,attr->Value());
		else if(attrName == "type") 		rc_conf->robot_type = ROBOT_TYPE(attr->IntValue());
		else if(attrName == "count")		rc_conf->axis_count = attr->IntValue();
	}
	LOGGER_DBG(DFLAG_LONG,"Robot_parameter:\n .name = %s\n .type = %d\n .axis_count = %d\n",rc_conf->name, rc_conf->robot_type,rc_conf->axis_count);
	TiXmlElement* axisInfoElm = RobotNode->FirstChildElement("AXISINFO");
	
	int axis_cnt = 0;
	for(; axisInfoElm != NULL; axisInfoElm = axisInfoElm->NextSiblingElement()){
		TiXmlAttribute* axisAttr = axisInfoElm->FirstAttribute();
		for(;axisAttr != NULL; axisAttr = axisAttr->Next()){
			std::string attrName = axisAttr->Name();
			if(attrName == "name") 		strcpy(RC_AXIS(axis_cnt).name,axisAttr->Value());
			else if(attrName == "dir")  RC_AXIS(axis_cnt).dir = axisAttr->IntValue();
			else if(attrName == "offset") RC_AXIS(axis_cnt).offset = axisAttr->DoubleValue();
		}
		TiXmlElement* axisDHElm = axisInfoElm->FirstChildElement("DH");
		if(axisDHElm != NULL){
			TiXmlAttribute* DHAttr = axisDHElm->FirstAttribute();
			for(;DHAttr != NULL; DHAttr = DHAttr->Next()){
				std::string attrName = DHAttr->Name();
				if(attrName == "theta")   RC_AXIS_DH(axis_cnt).theta = DHAttr->DoubleValue();
				else if(attrName == "d")  RC_AXIS_DH(axis_cnt).d = DHAttr->DoubleValue();
				else if(attrName == "a")  RC_AXIS_DH(axis_cnt).a = DHAttr->DoubleValue();
				else if(attrName == "alpha") RC_AXIS_DH(axis_cnt).alpha = DHAttr->DoubleValue();
				else if(attrName == "offset") RC_AXIS_DH(axis_cnt).offset = DHAttr->DoubleValue();
			}
		}

		TiXmlElement* axisLimElm = axisInfoElm->FirstChildElement("LIM");
		if(axisLimElm != NULL){
			TiXmlAttribute* LimAttr = axisLimElm->FirstAttribute();
			for(; LimAttr != NULL; LimAttr = LimAttr->Next()){
				std::string attrName = LimAttr->Name();
				if(attrName == "max_pos")		RC_AXIS_LIM(axis_cnt).max_pos = LimAttr->DoubleValue();
				else if(attrName == "min_pos")	RC_AXIS_LIM(axis_cnt).min_pos = LimAttr->DoubleValue();
				else if(attrName == "max_vel")	RC_AXIS_LIM(axis_cnt).max_vel = LimAttr->DoubleValue();
				else if(attrName == "max_acc")	RC_AXIS_LIM(axis_cnt).max_acc = LimAttr->DoubleValue();	
				else if(attrName == "max_dec")  RC_AXIS_LIM(axis_cnt).max_dec = LimAttr->DoubleValue();
				else if(attrName == "max_jerk")	RC_AXIS_LIM(axis_cnt).max_jerk = LimAttr->DoubleValue();
			}
		}
		LOGGER_DBG(DFLAG_LONG,"AxisName: %s\t Direction: %d\t Offset: %f\n" 
		"DH_parameter:\n .theta = %f\n .d = %f\n .a = %f\n .alpha = %f\n offset = %f\n"
		"LIM_paramter:\n .max_pos = %f\n .min_pos = %f\n .max_vel = %f\n .max_acc = %f\n .max_dec = %f\n .max_jerk = %f\n",
		RC_AXIS(axis_cnt).name,RC_AXIS(axis_cnt).dir,RC_AXIS(axis_cnt).offset,
		RC_AXIS_DH(axis_cnt).theta, RC_AXIS_DH(axis_cnt).d, RC_AXIS_DH(axis_cnt).a, RC_AXIS_DH(axis_cnt).alpha,RC_AXIS_DH(axis_cnt).offset,
 		RC_AXIS_LIM(axis_cnt).max_pos, RC_AXIS_LIM(axis_cnt).min_pos, RC_AXIS_LIM(axis_cnt).max_vel,RC_AXIS_LIM(axis_cnt).max_acc,RC_AXIS_LIM(axis_cnt).max_dec,RC_AXIS_LIM(axis_cnt).max_jerk);
		axis_cnt ++;
	}
	return 0;
}

/**
 *	功能：加载系统配置文件，并填充各配置共享区
 *	返回值： 运行正常返回0
 */
int SystemConfig()
{
	TiXmlDocument doc("config.xml");
	bool loadOkay = doc.LoadFile();
	if(!loadOkay)	fprintf(stderr,"could not load system config file\n");

	// 创建配置共享区
	io_conf_create(&ioconf_heap,&io_conf); 
	sv_conf_create(&svconf_heap,&sv_conf);
	rc_conf_create(&rcconf_heap,&rc_conf);

	// 将配置文件中配置信息加载至以上共享区，创建并初始化IO映像区
	TiXmlNode* node = doc.FirstChild("config");
	verify_obj(node);
	// IO映像区需要先创建，加载配置文件时有初始化
	io_mem_create(&io_shm,M_SHARED);
	load_io_config(node,io_conf);
	load_servo_config(node,sv_conf);
	load_robot_config(node,rc_conf);

	//创建伺服映像区，RC/软PLC共享区并初始化
	sv_mem_create(&sv_heap_desc,&sv_shm);
	sv_mem_init(sv_shm,sv_conf);
	rc_mem_create(&rc_heap_desc,&rc_shm);
	rc_mem_init(rc_shm,rc_conf);
	return 0;
}