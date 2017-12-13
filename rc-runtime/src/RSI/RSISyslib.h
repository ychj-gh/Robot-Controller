
#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>
#include <unordered_map>

#include <memory.h>

#include <tinyxml.h>

#include "IValue.h"
#include "rc_exception.h"

#define MAX_SPOU_NAME_SIZE  50

#define RSI_DEBUG_PRINT

extern bool RSIStopFlag; /* THIS IS VERY IMPORTANT, WHICH CONTROL THE WHOLE LIFECYCLE OF RSI */
extern int sockfd;

#define RSI_STOP_CHECK() do{if(RSIStopFlag == true) return 0;}while(0);


#ifdef RSI_DEBUG_PRINT
extern std::unordered_map<int, std::string> rdataIndexMap;   // index --> var
#endif

class EntityBase;

typedef struct {
    char name[MAX_SPOU_NAME_SIZE];
    int in_count;
    int out_count;
    int (*pfun)(std::vector<int>&, EntityBase*, std::vector<IValue>&);
} RSILibEntry; /* System-level POU(Library) descriptor */

typedef enum{
	RSI_SUM = 0,
	RSI_SUB,
	RSI_MULTI,
	RSI_DIV,

	RSI_ABS,
	RSI_NORM,
	RSI_EXP,
	RSI_LOG,
	RSI_CEIL,
	RSI_FLOOR,
	RSI_ROUND,
	RSI_POW,

	RSI_SIN,
	RSI_COS,
	RSI_TAN,
	RSI_ASIN,
	RSI_ACOS,
	RSI_ATAN,
	RSI_ATAN2,

	RSI_INC,
	RSI_DEC,

	RSI_PRINT,

	RSI_EQ,
	RSI_GT,
	RSI_GE,
	RSI_LT,
	RSI_LE,

	RSI_AND,
	RSI_OR,
	RSI_XOR,
	RSI_NOT,

	RSI_P,
	RSI_PD,
	RSI_I,
	RSI_D,
	RSI_PI,
	RSI_PID,

	RSI_AXISCORR,
	RSI_POSCORR,
	RSI_TRANSFRAME,
	RSI_POSACT,
	RSI_AXISACT,
	RSI_GEARTORQUE,
	RSI_MOTORCURRENT,

	RSI_COMMUNICATION,
	RSI_PIDN,
	RSI_SETOFFSET,

}POUId;


inline int rsi_sum(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[params[2]] = addrspace[params[0]] + addrspace[params[1]];
	return 0;
}

inline int rsi_sub(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[2] = addrspace[params[0]] - addrspace[params[1]];
	return 0;
}

inline int rsi_multi(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[2] = addrspace[params[0]] * addrspace[params[1]];
	return 0;
}
inline int rsi_div(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[2] = addrspace[params[0]] / addrspace[params[1]];
	return 0;
}

inline int rsi_abs(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_norm(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_exp(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_log(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_ceil(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_floor(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_pow(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}

inline int rsi_sin(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_cos(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_tan(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_asin(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_acos(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_atan(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_atan2(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}

inline int rsi_inc(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[params[0]] += 1;
	return 0;
}
inline int rsi_dec(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[params[0]] -= 1;
	return 0;
}

inline int rsi_print(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
#ifdef RSI_DEBUG_PRINT
	std::cout << std::endl << "[DEBUG: " << rdataIndexMap[params[0]] << " --> " << addrspace[params[0]] << " ]" << std::endl;
#else
	std::cout << std::endl << "Macro RSI_DEBUG_PRINT not defined" << std::endl;
#endif
	return 0;
}


inline int rsi_eq(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[0] = addrspace[params[0]] == addrspace[params[1]] ? 1 : 0;
	return 0;
}

inline int rsi_gt(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[0] = addrspace[params[0]] > addrspace[params[1]] ? 1 : 0;
	return 0;
}

inline int rsi_ge(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[0] = addrspace[params[0]] >= addrspace[params[1]] ? 1 : 0;
	return 0;
}

inline int rsi_lt(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[0] = addrspace[params[0]] < addrspace[params[1]] ? 1 : 0;
	return 0;
}

inline int rsi_le(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[0] = addrspace[params[0]] <= addrspace[params[1]] ? 1 : 0;
	return 0;
}

inline int rsi_and(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	int cond1 = addrspace[params[0]].RSIint();
	int cond2 = addrspace[params[1]].RSIint();
	addrspace[0] = cond1 && cond2;

	return 0;
}

inline int rsi_or(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	int cond1 = addrspace[params[0]].RSIint();
	int cond2 = addrspace[params[1]].RSIint();
	addrspace[0] = cond1 || cond2;

	return 0;
}

inline int rsi_xor(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	int cond1 = addrspace[params[0]].RSIint();
	int cond2 = addrspace[params[1]].RSIint();
	if(cond1 == 0 && cond2 != 0 || cond1 != 0 && cond2 == 0){
		addrspace[0] = 1;
	} else {
		addrspace[0] = 0;
	}
	
	return 0;
}

inline int rsi_not(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	int cond1 = addrspace[params[0]].RSIint();
	addrspace[0] = (cond1 == 0 ? 1 : 0);
	return 0;
}

inline int rsi_p(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_pd(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_i(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_d(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_pi(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}

int rsi_pid(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) ;
int rsi_pidn(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace);
int rsi_setoffset(std::vector<int>&,EntityBase*,std::vector<IValue>&);

inline int rsi_timer(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_limit(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}

inline int rsi_min(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[params[2]] = addrspace[params[0]] < addrspace[params[1]] ? addrspace[params[0]] : addrspace[params[1]];
	return 0;
}

inline int rsi_max(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	addrspace[params[2]] = addrspace[params[0]] > addrspace[params[1]] ? addrspace[params[0]] : addrspace[params[1]];
	return 0;
}

inline int rsi_delay(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_monitor(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_stop(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {
	if(addrspace[params[0]] == IValue(1)) {
		close(sockfd);
		RSIStopFlag = true;
	}
}


int rsi_axiscorr(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) ;

int rsi_poscorr(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) ;

inline int rsi_transfame(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}

int rsi_posact(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) ;
int rsi_axisact(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) ;


inline int rsi_geartorque(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}
inline int rsi_motorcurrent(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace) {}

int rsi_comm_interface(std::vector<int>& params, EntityBase* config, std::vector<IValue>& addrspace);



#define VARIABLE_LEN 0

#define RSI_LIB_SIZE  53

/* ORDER SENSITIVE */
static const RSILibEntry libEntry[RSI_LIB_SIZE] = {
	{"SUM", 2, 1, rsi_sum},
	{"SUB", 2, 1, rsi_sub},
	{"MULTI", 2, 1, rsi_multi},
	{"DIV", 2, 1, rsi_div},

	{"ABS", 1, 0, rsi_abs},
	{"NORM", VARIABLE_LEN, 1, rsi_norm},
	{"EXP", 2, 1, rsi_exp},
	{"LOG", 2, 1, rsi_log},
	{"CEIL", 1, 1,rsi_ceil},
	{"FLOOR", 1, 1, rsi_floor},
	{"POW", 2, 1,rsi_pow},

	{"SIN", 1, 1,rsi_sin},
	{"COS", 1, 1,rsi_cos},
	{"TAN", 1, 1,rsi_tan},
	{"ASIN", 1, 1,rsi_asin},
	{"ACOS", 1, 1,rsi_acos},
	{"ATAN", 1, 1,rsi_atan},
	{"ATAN2", 1, 1,rsi_atan2},

	{"INC", 1, 0,rsi_inc},
	{"DEC", 1, 0,rsi_dec},

	{"PRINT", 1, 0,rsi_print},

	{"EQ", 2, 0,rsi_eq},
	{"GT", 2, 0,rsi_gt},
	{"GE", 2, 0,rsi_ge},
	{"LT", 2, 0,rsi_lt},
	{"LE", 2, 0,rsi_le},

	{"AND", 2, 0,rsi_and},
	{"OR", 2, 0,rsi_or},
	{"XOR", 2, 0,rsi_xor},
	{"NOT", 1, 0,rsi_not},

	{"P", 1, 0,rsi_p},
	{"PD", 1, 0,rsi_pd},
	{"I", 1, 0,rsi_i},
	{"D", 1, 0,rsi_d},
	{"PI", 1, 0,rsi_pi},
	{"PID", 1, 0,rsi_pid},

	{"TIMER", 1, 0,rsi_timer},
	{"LIMIT", 1, 0,rsi_limit},
	{"MIN", VARIABLE_LEN, 1, rsi_min},
	{"MAX", VARIABLE_LEN, 1,rsi_max},
	{"DELAY", 1, 0,rsi_delay},
	{"MONITOR", VARIABLE_LEN, 0,rsi_monitor},
	{"STOP", 1, 0,rsi_stop},

	{"AXISCORR", VARIABLE_LEN,0, rsi_axiscorr},
	{"POSCORR", VARIABLE_LEN, 0,rsi_poscorr},
	{"TRANSFRAME", VARIABLE_LEN,0, rsi_transfame},
	{"POSACT", VARIABLE_LEN, 0,rsi_posact},
	{"AXISACT", VARIABLE_LEN, 0,rsi_axisact},
	{"GEARTORQUE", VARIABLE_LEN, 0,rsi_geartorque},
	{"MOTORCURRENT", VARIABLE_LEN, 0,rsi_motorcurrent},

	{"COMMUNICATION", VARIABLE_LEN, 0,rsi_comm_interface},
	{"PIDN", VARIABLE_LEN, 0 ,rsi_pidn},
	{"SETOFFSET",VARIABLE_LEN, VARIABLE_LEN, rsi_setoffset},
};


/* ************** the Entity type of function block ***************** */
class EntityBase {
public:
	EntityBase(std::string f) : funcName(f) {}

	virtual int setConfig(std::string key, std::string value) = 0;

	virtual int printInfo() { std::cout << "[> EntityBase <]" << std::endl; }

public:
	std::string funcName;
};


class EntityDELAY : public EntityBase {
public:
	EntityDELAY() : EntityBase("DELAY"), T(0.0) {}

	virtual int setConfig(std::string key, std::string value) override {
		if(key == "T")  {
			T = stoival(RSIDOUBLE,value);
		} else {
			return -1;
		}
		return 0;
	}

	virtual int printInfo() override {
		std::cout << std::endl << "Type: " << funcName << " --> ";
		std::cout << "T=" << T << std::endl;
	}

public:
	IValue T;
};


enum SensorType{
	SENSOR = 0,
	PC
};

enum SensorMode{
	TRIG = 0,
	CYCLIC
};

class EntityComm : public EntityBase {
public:
	struct SendDataElem {  						// 与PC通信定义的发送数据数据结构
		std::string tag;
		std::vector<std::pair<std::string, int>> dataMap;
		std::pair<std::string, int> tagText;
	};

public:
	EntityComm() : EntityBase("COMMUNICATION"),cycflag(false),cfgruncnt(0) {
		memset(sendBuffer, 0, 4096);
		memset(recvBuffer, 0, 4096);
	}
	virtual int printInfo() override {
		std::cout << std::endl << "Type: " << funcName << " --> ";
		std::cout << "comm_type=" << comm_type << " ip=" << ip << " port=" << port << " rootNode=" << rootNode << std::endl;
		if(stype == SENSOR){
			std::cout << "Normal sensor in " << (smode == TRIG ? "TRIG":"CYCLIC") << "mode" << std::endl;
			std::cout << "config packages nums = " << cfgcmdcnt << std::endl;
			for(auto &row:cfgCmdData){
				for(auto el:row)
					std::cout << el << " ";
				std::cout << std::endl;
			}
			std::cout << "************************** recvcfg ****************************" << std::endl;
			for(size_t i = 0; i != recvtype.size(); ++i)
				std::cout << "ratio = " << dataratio[i] << "  type = " << (unsigned)recvtype[i] << std::endl;
		}else{
			std::cout << "\tPC" << std::endl;
			std::cout << "[> --- SENDDATAMAP --- <]" << std::endl;
			for(auto &e : sendDataMap) {
				std::cout << e.tag << std::endl;
				for(auto &elem : e.dataMap) {
					std::cout << elem.first << "<-->" << elem.second << " ";
				}
				std::cout << std::endl;
				if(e.tagText.first != "") {
					std::cout << e.tagText.first << "<-->" << e.tagText.second << std::endl;
				}
			}
			std::cout << "[> --- RECVDATAMAP --- <]" << std::endl;
			for(auto &e : recvDataMap) {
				std::cout << e.first << std::endl;
				for(auto &elem : e.second) {
					std::cout << elem.first << "<-->" << elem.second << " ";
				}
				std::cout << std::endl;
			}
		}
	}
public:
	// 与xml解析器交互
	virtual int setConfig(std::string key, std::string value) override {
		if(key == "COM_TYPE")  {
			comm_type = value;
		} else if(key == "IP"){
			ip = value;
		} else if(key == "PORT"){
			port = value;
		} else if(key == "ROOTNAME"){
			rootNode = value;
		}else if(key == "SENSORTYPE"){
			if(value == "SENSOR") stype = SENSOR;
			else if(value == "PC") stype = PC;
			else return -1;
		}else if(key == "SENSORMODE"){
			if(value == "TRIG") smode = TRIG;
			else if(key == "CYCLIC") smode = CYCLIC;
		}else if(key == "TOLERAT"){
			tolerattime = std::stoi(value);
		}else if(key == "CFGCMDCNT"){
			cfgcmdcnt = std::stoi(value);
		}else if(key == "RECVOFFSET"){
			recvoffset = std::stoi(value);
		}
		if(ip != "" && port != ""){
			sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
			struct timeval timeout = {0, tolerattime*1000};
    		setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval));
			bzero(&sensoraddr, sizeof(sensoraddr));
	    	sensoraddr.sin_family = AF_INET;
	    	sensoraddr.sin_port = htons(atoi(port.c_str()));
	    	sensoraddr.sin_addr.s_addr = inet_addr(ip.c_str());
			return 0;
		}
		return -1;
	}

	int setTypeCfg(std::string key,std::vector<std::string>& value){
		if(key == "CFGTYPE") 
			cfgtype = value;
		else if(key == "SENDTYPE")
			sendtype = value;
		return 0;
	}

	// 普通传感器设置配置与发送报文
	int setCfgPackages(std::vector<std::string>& value){
		std::vector<IValue> tmp;
		for(size_t i = 0; i != value.size(); ++i)
			tmp.push_back(stoival(RSI_typetable[cfgtype[i]],value[i]));
		cfgCmdData.push_back(tmp);
	}

	int setSendPackage(std::vector<std::string>& value){
		for(size_t i = 0; i!= value.size(); ++i)
			sendCmdData.push_back(stoival(RSI_typetable[sendtype[i]],value[i]));
	}

	int setRecvPackage(std::string& type, std::string& ratio, int varIndex){
		recvtype.push_back(RSI_typetable[type]);
		dataratio.push_back(IValue(RSIDOUBLE,std::stod(ratio)));
		recvDataIndex.push_back(varIndex);
	}

	// 与PC通信设置发送与接受报文格式
	int setSendDataMap(std::string &tagName, int varIndex);
	int setRecvDataMap(std::string &tagName, int varIndex);

public:
	// 与RSI执行器交互
	int genSendPackage(std::vector<IValue>& addrspace){
		if(stype == PC)
			return xmlGenerate(addrspace);
		else if(stype == SENSOR)
			if(cfgcmdcnt > cfgruncnt)	return cmdGenerate(cfgCmdData[cfgruncnt]);
			else if(smode == CYCLIC) 	return cmdGenerate(sendCmdData); 
		return 0;
	}

	int parseRecvPackage(std::vector<IValue>& addrspace){
		if(stype == PC)
			return xmlParse(addrspace);
		else 
			return dataParse(addrspace);
	}

private:
	// 与普通传感器通信发送数据产生函数 返回报文长度
	int cmdGenerate(std::vector<IValue>& data){
		size_t offset = 0;
		// std::cout << " generate cmd " << std::endl;
		for(size_t i = 0; i != data.size(); ++i){
			IValue tmp = data[i].htonival();
			memcpy((char*)&sendBuffer[offset],(const char*)&tmp,tmp.DataSize());
			offset += tmp.DataSize();
			// std::cout << "type = " << (unsigned)tmp.type << " " << tmp << " ";
		}
		std::cout << std::endl << "sendbuffer = ";
		// for(size_t i = 0; i < offset; ++i)
		// 	std::cout << std::hex << (unsigned char)sendBuffer[i] << " ";
		// std::cout << std::endl;
		return offset;
	}

	int dataParse(std::vector<IValue>& addrspace){
		int offset = recvoffset;
		// std::cout << "dataParse data:";
		for(size_t i = 0; i != recvtype.size(); ++i){
			IValue tmp(recvtype[i]);
			memcpy(&tmp,recvBuffer+offset,tmp.DataSize());
			// std::cout << "\ttype = " << (unsigned)tmp.type << " " << tmp.ntohival() * dataratio];
			addrspace[recvDataIndex[i]] = tmp.ntohival() * dataratio[i];
			offset += tmp.DataSize();
		}
		// std::cout << std::endl;
		return 0;
	}

	// 与PC周期通信时创建并发送给PC的xml文件
	int xmlGenerate(std::vector<IValue>& addrspace);
	// 解析RSI周期通信中PC发送给RSI的数据
	int xmlParse(std::vector<IValue>& addrspace);

public:
	bool cycflag;			
	struct sockaddr_in sensoraddr;		// 目标socket地址		
	char sendBuffer[4096];			
	char recvBuffer[4096];	

	int cfgruncnt;
	int cfgcmdcnt;						// 配置传感器时所需的报文数
	SensorType stype;					// 传感器类型		SENSOR | PC
	SensorMode smode;					// 传感器工作模式　TRIG | CYCLIC
private:
	/* 配置参数　*/
	std::string comm_type;				// TCP | UDP
	std::string ip;						// IP 地址
	std::string port;					// 端口号
	int tolerattime;					// 等待报文容忍时间

	std::string rootNode;				// xml文件根节点
	/* 与传感器通信时设置参数　*/
	std::vector<std::string> cfgtype;
	std::vector<std::string> sendtype;
	std::vector<std::vector<IValue>> cfgCmdData;
	std::vector<IValue> sendCmdData;	// 默认周期通信时传感器只需要一条命令
	size_t recvoffset;
	std::vector<uint8_t> recvtype;
	std::vector<IValue> dataratio;
	std::vector<int> recvDataIndex;
	/* 与PC通信时xml文件解析对应变量　*/
	std::unordered_map<std::string, std::unordered_map<std::string, int>>  recvDataMap; // indicate <tag, <property, index>>
	std::vector<SendDataElem> sendDataMap;		// 发送数据格式
};

inline 
int EntityComm::setSendDataMap(std::string &tagName, int varIndex) {
	int pos = 0;
	std::string tag;
	std::string key;

	if((pos = tagName.find(".")) != std::string::npos) {
		tag = tagName.substr(0, pos);
		key = tagName.substr(pos+1);
	} else {
		tag = tagName;
		key = tagName;
	}
	int index = 0;
	for(; index < sendDataMap.size(); index ++) 
		if(sendDataMap[index].tag == tag) 
			break;
	if(index == sendDataMap.size()) {
		SendDataElem tmp;
		tmp.tag = tag;
		if(tag != key) 
			tmp.dataMap.push_back(std::pair<std::string, int>(key, varIndex));
		else 
			tmp.tagText = std::pair<std::string, int>(key, varIndex);
		sendDataMap.push_back(tmp);
	} 
	else {
		if(tag != key)
			sendDataMap[index].dataMap.push_back(std::pair<std::string, int>(key, varIndex)); 
		else
			sendDataMap[index].tagText = std::pair<std::string, int>(key, varIndex);
	}
	return 0;
}

inline
int EntityComm::setRecvDataMap(std::string &tagName, int varIndex) {
	int pos = 0;
	std::string tag;
	std::string key;

	if((pos = tagName.find(".")) != std::string::npos) {
		tag = tagName.substr(0, pos);
		key = tagName.substr(pos+1);
	} else {
		tag = tagName;
		key = tagName;
	}

	if(recvDataMap.find(tag) != recvDataMap.end()) {
		recvDataMap[tag].insert(std::pair<std::string, int>(key, varIndex));
	} else {
		std::unordered_map<std::string, int> map;
		map.insert(std::pair<std::string, int>(key, varIndex));
		recvDataMap.insert(std::pair<std::string, std::unordered_map<std::string, int>>(tag, map));
	}
	return 0;
}

inline
int EntityComm::xmlGenerate(std::vector<IValue>& addrspace) {
	TiXmlDocument doc;
	TiXmlElement *rootEle = new TiXmlElement(rootNode);
	for(auto &e : sendDataMap) {
		TiXmlElement *tagEle = new TiXmlElement(e.tag);
		for(auto &elem : e.dataMap) {
			tagEle->SetAttribute(elem.first, addrspace[elem.second].RSIstring());
		}
		if(e.tagText.first != "") {
			tagEle->LinkEndChild(new TiXmlText(addrspace[e.tagText.second].RSIstring()));
		}
		rootEle->LinkEndChild(tagEle);
	}
	doc.LinkEndChild(rootEle);
	TiXmlPrinter printer;
	// printer.SetIndent( "\t" );
	doc.Accept( &printer );
	sprintf( sendBuffer, "%s", printer.CStr());
	return strlen(sendBuffer);
}

inline
int EntityComm::xmlParse(std::vector<IValue>& addrspace) {
	TiXmlDocument doc;
	doc.Parse(recvBuffer);
	TiXmlElement* rootEle = doc.RootElement();  
	if(rootEle != NULL && rootEle->Value() == rootNode) {
		TiXmlElement* dataEle = rootEle->FirstChildElement();
		for(; dataEle != NULL; dataEle = dataEle->NextSiblingElement()) {
			std::string tag = dataEle->Value();
			std::unordered_map<std::string, int> &mp = recvDataMap[tag];
			TiXmlAttribute* attr = dataEle->FirstAttribute();
			for(; attr != NULL; attr = attr->Next()) 
				addrspace[mp[attr->Name()]] = IValue(RSIDOUBLE,std::stod(attr->Value()));
			if(mp.find(tag) != mp.end()) 
				addrspace[mp[tag]] = IValue(RSIDOUBLE,std::stod(dataEle->GetText()));
		}
		return 0;
	} 
	else return -1;
}


class EntityPOSCORR : public EntityBase {
public:
	EntityPOSCORR() : EntityBase("POSCORR"), CorrType(0){}

	virtual int setConfig(std::string key, std::string value) override {
		if(key == "LowerLimX")  {
			LowerLimX = stoival(RSIDOUBLE,value);
		} else if(key == "LowerLimY") {
			LowerLimY = stoival(RSIDOUBLE,value);
		} else if(key == "LowerLimZ") {
			LowerLimZ = stoival(RSIDOUBLE,value);
		} else if(key == "UpperLimX") {
			UpperLimX = stoival(RSIDOUBLE,value);
		} else if(key == "UpperLimY") {
			UpperLimY = stoival(RSIDOUBLE,value);
		} else if(key == "UpperLimZ") {
			UpperLimZ = stoival(RSIDOUBLE,value);
		} else if(key == "MaxRotAngle") {
			MaxRotAngle = stoival(RSIDOUBLE,value);
 		} else if(key == "RefCorrSys") {
 			RefCorrSys = std::stoi(value);
 		} else if(key == "CorrType") {
 			CorrType = std::stoi(value);
 		} else if(key == "OverTransLim") {
 			OverTransLim = stoival(RSIDOUBLE,value);
 		} else if(key == "OverRotAngle") {
 			OverRotAngle = stoival(RSIDOUBLE,value);
 		} else {
 			return -1;
 		}
		return 0;
	}

	virtual int printInfo() override {
		std::cout << std::endl << "Type: " << funcName << " --> " << " CorrType=" << CorrType << std::endl;;
		std::cout << " LowerLimX=" << LowerLimX << " LowerLimY=" << LowerLimY << " LowerLimZ=" << LowerLimZ
				  << " UpperLimX=" << UpperLimX << " UpperLimY=" << UpperLimY << " UpperLimZ=" << UpperLimZ
				  << " MaxRotAngle=" << MaxRotAngle << " RefCorrSys=" << RefCorrSys 
				  << std::endl << " OverTransLim=" << OverTransLim << " OverRotAngle=" << OverRotAngle
				  << std::endl;
				  
	}

public:
	int    CorrType;	// 0: relative 1: absolute
	int    RefCorrSys;  // 0: axis 1: base 2: tool

	IValue LowerLimX;
	IValue LowerLimY;
	IValue LowerLimZ;
	IValue UpperLimX;
	IValue UpperLimY;
	IValue UpperLimZ;
	IValue MaxRotAngle;

	IValue OverTransLim;
	IValue OverRotAngle;

public:
	IValue overDeltaX;
	IValue overDeltaY;
	IValue overDeltaZ;
	IValue overDeltaA;
	IValue overDeltaB;
	IValue overDeltaC;	  
};


class EntityAXISCORR : public EntityBase {
public:
	EntityAXISCORR() : EntityBase("AXISCORR"), CorrType(0) {}

	virtual int setConfig(std::string key, std::string value) override {
		if(key == "LowerLimA1")  {
			LowerLimA1 = stoival(RSIDOUBLE,value);
		} else if(key == "LowerLimA2") {
			LowerLimA2 = stoival(RSIDOUBLE,value);
		} else if(key == "LowerLimA3") {
			LowerLimA3 = stoival(RSIDOUBLE,value);
		} else if(key == "LowerLimA4") {
			LowerLimA4 = stoival(RSIDOUBLE,value);
		} else if(key == "LowerLimA5") {
			LowerLimA5 = stoival(RSIDOUBLE,value);
		} else if(key == "LowerLimA6") {
			LowerLimA6 = stoival(RSIDOUBLE,value);
		} else if(key == "UpperLimA1") {
			UpperLimA1 = stoival(RSIDOUBLE,value);
		} else if(key == "UpperLimA2") {
			UpperLimA2 = stoival(RSIDOUBLE,value);
		} else if(key == "UpperLimA3") {
			UpperLimA3 = stoival(RSIDOUBLE,value);
		} else if(key == "UpperLimA4") {
			UpperLimA4 = stoival(RSIDOUBLE,value); 
		} else if(key == "UpperLimA5") {
			UpperLimA5 = stoival(RSIDOUBLE,value);
		} else if(key == "UpperLimA6") {
			UpperLimA6 = stoival(RSIDOUBLE,value);
		} else if(key == "CorrType") {
 			CorrType = std::stoi(value);
 		} else if(key == "OverLimA1") {
 			OverLimA1 = stoival(RSIDOUBLE,value);
 		} else if(key == "OverLimA2") {
 			OverLimA2 = stoival(RSIDOUBLE,value);
 		} else if(key == "OverLimA3") {
 			OverLimA3 = stoival(RSIDOUBLE,value);
 		} else if(key == "OverLimA4") {
 			OverLimA4 = stoival(RSIDOUBLE,value);
 		} else if(key == "OverLimA5") {
 			OverLimA5 = stoival(RSIDOUBLE,value);
 		} else if(key == "OverLimA6") {
 			OverLimA6 = stoival(RSIDOUBLE,value);
 		} else {
 			return -1;
 		}
		return 0;
	}

	virtual int printInfo() override {
		std::cout << std::endl << "Type: " << funcName << " --> " << " CorrType=" << CorrType << std::endl;;
		std::cout << " LowerLimA1=" << LowerLimA1 << " LowerLimA2=" << LowerLimA2 << " LowerLimA3=" << LowerLimA3
				  << " LowerLimA4=" << LowerLimA4 << " LowerLimA5=" << LowerLimA5 << " LowerLimA6=" << LowerLimA6
				  << std::endl 
				  << " UpperLimA1=" << UpperLimA1 << " UpperLimA2=" << UpperLimA2 << " UpperLimA3=" << UpperLimA3
				  << " UpperLimA4=" << UpperLimA4 << " UpperLimA5=" << UpperLimA5 << " UpperLimA6=" << UpperLimA6
				  << std::endl
				  << " OverLimA1=" << OverLimA1 << " OverLimA2=" << OverLimA2 << " OverLimA3=" << OverLimA3
				  << " OverLimA4=" << OverLimA4 << " OverLimA5=" << OverLimA5 << " OverLimA6=" << OverLimA6
				  << std::endl;
				  
	}

public:
	int CorrType; 	// 0: relative  1: absolute

	IValue LowerLimA1;
	IValue LowerLimA2;
	IValue LowerLimA3;
	IValue LowerLimA4;
	IValue LowerLimA5;
	IValue LowerLimA6;

	IValue UpperLimA1;
	IValue UpperLimA2;
	IValue UpperLimA3;
	IValue UpperLimA4;
	IValue UpperLimA5;
	IValue UpperLimA6;

	IValue OverLimA1;
	IValue OverLimA2;
	IValue OverLimA3;
	IValue OverLimA4;
	IValue OverLimA5;
	IValue OverLimA6;

public:
	IValue overDeltaA1;
	IValue overDeltaA2;
	IValue overDeltaA3;
	IValue overDeltaA4;
	IValue overDeltaA5;
	IValue overDeltaA6;
};

class EntityPID : public EntityBase{
public:
	EntityPID() : EntityBase("PID"){}

	virtual int setConfig(std::string key, std::string value) override {
		if(key == "Kp")  {
			kp = stoival(RSIDOUBLE,value);
		} else if(key == "Ki") {
			ki = stoival(RSIDOUBLE,value);
		} else if(key == "Kd") {
			kd = stoival(RSIDOUBLE,value);
		} else {
			return -1;
		}
		return 0;
	}

	virtual int printInfo() override {
		std::cout << std::endl << "Type: " << funcName << " --> ";
		std::cout << "Kp=" << kp << " Ki=" << ki << " Kd=" << kd << std::endl;
	}

public:
	IValue kp;	
	IValue ki;	// Kp*T/Ti
	IValue kd;	// Kp*Td/T

	IValue prev;
	IValue prevErr;
	IValue pprevErr;
};

// ADD BY YCHJ
class EntitySETOFFSET: public EntityBase{
public:
	EntitySETOFFSET():EntityBase("SETOFFSET"),listCnt(0),filterCnt(0),filterCfg(10){}
	virtual int setConfig(std::string key, std::string value) override{
		if(key == "OFFSETCNT"){
			listCnt = std::stoi(value);
		}else if(key == "FILTERCFG"){
			filterCfg = std::stoi(value);
		}else{
			return -1;
		}
		return 0;
	}
	virtual int printInfo() override{
		std::cout << "variable need to set offset " << listCnt << std::endl;
	}
public:
	size_t listCnt,filterCnt,filterCfg;
	std::vector<IValue> offlist;
	std::vector<IValue> maxlist;
	std::vector<IValue> minlist;
};


class EntityPIDn:public EntityBase{
public:
	EntityPIDn() : EntityBase("PIDN"){}

	virtual int setConfig(std::string key, std::string value) override {
		if(key == "Kp")  {
			kp = stoival(RSIDOUBLE,value);
		} else if(key == "Ki") {
			ki = stoival(RSIDOUBLE,value);
		} else if(key == "Kd") {
			kd = stoival(RSIDOUBLE,value);
		} else if(key == "N"){
			SeqCnt = std::stoi(value);
			prevSeq = std::vector<IValue>(SeqCnt);
			prevErr = std::vector<IValue>(SeqCnt);
			pprevErr = std::vector<IValue>(SeqCnt);
		}else {
			return -1;
		}
		return 0;
	}

	virtual int printInfo() override {
		std::cout << std::endl << "Type: " << funcName << " --> ";
		std::cout << "Kp=" << kp << " Ki=" << ki << " Kd=" << kd << "N=" << SeqCnt << std::endl;
	}

public:
	IValue kp;
	IValue ki;
	IValue kd;

	size_t SeqCnt;
	std::vector<IValue> prevSeq;
	std::vector<IValue> prevErr;
	std::vector<IValue> pprevErr;
};

class EntityFactory {
public:
	static EntityBase* getEntity(std::string name) {
		if(name == "PID") {
			return new EntityPID();
		} else if(name == "DELAY") {
			return new EntityDELAY();
		} else if(name == "COMMUNICATION"){
			return new EntityComm();
		} else if(name == "POSCORR") {
			return new EntityPOSCORR();
		} else if(name == "AXISCORR") {
			return new EntityAXISCORR();
		} else if(name == "PIDN"){
			return new EntityPIDn();
		}else if(name == "SETOFFSET"){
			return new EntitySETOFFSET();
		}else{
			return NULL;
		}
	}
};





