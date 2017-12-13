
#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory.h>
#include <unistd.h>


#include "tinyxml.h"
#include "rc_innerdata.h"
#include "rc_exception.h"
#include "opmanager.hh"


extern RT_TASK rc_rsi_desc;                                /* RSI任务描述符 */
extern RT_TASK_INFO  rc_rsi_info;                          /* RSI任务状态 */
void rsi_routine(void *cookie) ;							/* RSI task instance */
extern RT_TASK rc_executor_desc;                           /* RC执行器任务描述符 */
extern RT_TASK_INFO  rc_executor_info;                     /* RC执行器任务状态 */


class RCEntityBase;


typedef struct {
    std::string name;
    int param_count;
    int (*pfun)(std::vector<int>&, RCEntityBase*, RC_SymbolTable&);
} RCLibEntry; /* System-level POU(Library) descriptor of RC*/



/* ** ALL THE IMPLEMENTATION OF LIBRARY FUNCTION IN C/C++ ************** */
inline int rc_sum(std::vector<int>& params, RCEntityBase* config, RC_SymbolTable& symTable) {
	std::cout << "LIBCALL : RC_SUM" << std::endl;
	return 0;
}

inline int rc_sub(std::vector<int>& params, RCEntityBase* config, RC_SymbolTable& symTable) {
	std::cout << "LIBCALL : RC_SUB" << std::endl;
	return 0;
}

inline int rc_multi(std::vector<int>& params, RCEntityBase* config, RC_SymbolTable& symTable) {
	std::cout << "LIBCALL : RC_MULTI" << std::endl;
	return 0;
}

inline int rc_div(std::vector<int>& params, RCEntityBase* config, RC_SymbolTable& symTable) {
	std::cout << "LIBCALL : RC_DIV" << std::endl;
	return 0;
}

#include <fstream>
extern std::ofstream Posdatafile;
extern std::ofstream Veldatafile;
extern std::ofstream PosUsedfile;

inline int rc_start_rsi(std::vector<int>& params, RCEntityBase* config, RC_SymbolTable& symTable) {
	std::cerr << "LIBCALL : RC_START_RSI" << std::endl;
	if( params.size() == 1 ) {
		Posdatafile.open("/home/seu/workspace/datafile/Posdata.txt");
		Veldatafile.open("/home/seu/workspace/datafile/Veldata.txt");
		PosUsedfile.open("/home/seu/workspace/datafile/RSIPos.txt");
		if(!Posdatafile || !Veldatafile) std::cerr << "!!! open file error" << std::endl;
		Posdatafile << "Pos" << std::endl;
		Veldatafile << "Vel" << std::endl;
		PosUsedfile << "Pos" << std::endl;
		int32_t index = symTable.addrspace[params[0]].v.value_s;
		std::string rsiName = "./rc-runtime/" + symTable.stringpool[index];
		rt_task_create(&rc_rsi_desc, RC_RSI_NAME, 0, RC_RSI_PRIORITY, T_JOINABLE|T_FPU|T_CPU(2));
		rt_task_start(&rc_rsi_desc, rsi_routine, &rsiName);
		SHM_RC_MODE_SET(rc_shm);
		rt_task_join(&rc_rsi_desc);
		SHM_RC_MODE_CLR(rc_shm);
		Posdatafile.close();
		Veldatafile.close();
		PosUsedfile.close();
	} else {
		throw rc_wrongfuncparams_exception("RC_START_RSI");
	}
	return 0;
}

int rc_communication(std::vector<int>& params, RCEntityBase* config, RC_SymbolTable& symTable);

inline int rc_posact(std::vector<int>& params, RCEntityBase* config, RC_SymbolTable& symTable) {
	std::cerr << "LIBCALL : RC_POSACT" << std::endl;
	for(int i = 0; i < params.size(); i ++) {
		uint8_t type = symTable.addrspace[params[i]].type;
		if(type != TDOUBLE && type != TTRPOSE) {
			throw rc_wrongfuncparams_exception("RC_POSACT");
		}
	}
	Position_MCS_rad pos(6);
	pRobot->getActualTCPPos(rc_shm,&rc_mutex_desc,pos);
	// std::vector<double> pos(6, 0);
	// cur_cartpos_get(pos);

	if(params.size() == 1 && symTable.addrspace[params[0]].type == TTRPOSE) {
		uint32_t pointIndex = symTable.addrspace[params[0]].v.value_cp;
		for(int i = 0; i < 6; i ++) {
			symTable.cpaddr[pointIndex][i] = pos[i];
		}
	} else {
		for(int i = 0; i < params.size() && i < 6; i ++) {
			symTable.addrspace[params[i]].v.value_d = pos[i];
		}
	}
	
	return 0;
}

inline int rc_axisact(std::vector<int>& params, RCEntityBase* config, RC_SymbolTable& symTable) {
	std::cerr << "LIBCALL : RC_AXISACT" << std::endl;
	for(int i = 0; i < params.size(); i ++) {
		uint8_t type = symTable.addrspace[params[i]].type;
		if(type != TDOUBLE && type != TJTPOSE ) {
			throw rc_wrongfuncparams_exception("RC_AXISACT");
		}
	}
	size_t n = pRobot->getRobotAxisNum();
	Position_ACS_deg pos(n);
	pRobot->getActualAxisPos(rc_shm,&rc_mutex_desc,pos);
	// std::vector<double> pos(6, 0);
	// cur_axispos_get(pos);
	if(params.size() == 1 && symTable.addrspace[params[0]].type == TJTPOSE) {
		uint32_t pointIndex = symTable.addrspace[params[0]].v.value_ap;
		for(int i = 0; i < n; i ++) {
			symTable.apaddr[pointIndex][i] = pos[i];
		}
	} else {
		for(int i = 0; i < params.size() && i < n; i ++) {
			symTable.addrspace[params[i]].v.value_d = pos[i];
		}
	}
	
	return 0;
}

inline int rc_tool(std::vector<int>& params, RCEntityBase* config, RC_SymbolTable& symTable) {
	std::cerr << "LIBCALL : RC_TOOL" << std::endl;
	
	// tmatrix toolmat;
    Position_MCS_deg toolPos(6);
    for(int i = 0; i < 6; i ++)
       toolPos[i] = symTable.tooladdr[symTable.addrspace[params[0]].v.value_i][i];
    Position_MCS_rad toolPosture = posMCS_deg2rad(toolPos);
    pRobot->setToolMatrix(toolPosture);
    // toolmat = TermPos2TransMatrix(toolpos);
    // for(int i = 0; i < 4; ++i) {
    // 	for(int j = 0; j < 4; ++j)  {
    //             rc_runtime_param.toolMatrix[i][j] = toolmat(i,j);
    //     }
    // }
    std::cout << toolPos.transpose() << std::endl;
	return 0;
}

inline int rc_ref_sys(std::vector<int>& params, RCEntityBase* config, RC_SymbolTable& symTable) {
	std::cerr << "LIBCALL : RC_REF_SYS" << std::endl;
	if(params.size() == 1 && symTable.addrspace[params[0]].type == TINT) {
		if(symTable.addrspace[params[0]].v.value_i == 0) {
			rc_core.coordinate = 0;
		} else if(symTable.addrspace[params[0]].v.value_i == 1) {
			rc_core.coordinate = 1;
		} else if(symTable.addrspace[params[0]].v.value_i == 2) {
			rc_core.coordinate = 2;
		} else {
			throw rc_wrongfuncparams_exception("RC_REF_SYS");
		}
	} else {
		throw rc_wrongfuncparams_exception("RC_REF_SYS");
	}
	return 0;
}

inline int rc_frame_trans(std::vector<int>& params, RCEntityBase* config, RC_SymbolTable& symTable) {
	std::cerr << "LIBCALL : RC_FRAME_TRANS" << std::endl;
	
	return 0;
}



inline int rc_print(std::vector<int>& params, RCEntityBase* config, RC_SymbolTable& symTable) {
	std::cerr << "LIBCALL : RC_PRINT" << std::endl;
	int size = params.size();
	for(int i = 0; i < size; i ++) {
		std::cout << symTable.rDataIndexMap[params[i]] << " --> "
					<< symTable.addrspace[params[i]];
		if(symTable.addrspace[params[i]].type == TJTPOSE) {
			std::cout << " < " ;
			uint32_t pointIndex = symTable.addrspace[params[i]].v.value_ap;
			for(int i = 0; i < symTable.apaddr[pointIndex].size(); i ++) {
				std::cout << symTable.apaddr[pointIndex][i] << " ";
			}
			std::cout << " > ";
		} else if(symTable.addrspace[params[i]].type == TTRPOSE) {
			std::cout << " < " ;
			uint32_t pointIndex = symTable.addrspace[params[i]].v.value_cp;
			for(int i = 0; i < symTable.cpaddr[pointIndex].size(); i ++) {
				std::cout << symTable.cpaddr[pointIndex][i] << " ";
			}
			std::cout << " > ";
		}
		std::cout << std::endl;
	}
	return 0;
}

/* ** THE WHOLE RC FUNCTION LIBRARY HERE ******************************* */
#define VARIABLE_LEN 0
#define RC_LIB_SIZE  12

/* ORDER SENSITIVE */
static const RCLibEntry rcLibEntry[RC_LIB_SIZE] = {
	{"RC_SUM", VARIABLE_LEN, rc_sum},
	{"RC_SUB", 2, rc_sub},
	{"RC_MULTI", 2, rc_multi},
	{"RC_DIV", 2, rc_div},

	{"RC_START_RSI", 1, rc_start_rsi},

	{"RC_COMMUNICATION", VARIABLE_LEN, rc_communication},
	{"RC_POSACT", VARIABLE_LEN, rc_posact},
	{"RC_AXISACT", VARIABLE_LEN, rc_axisact},

	{"RC_FRAME_TRANS", 1, rc_frame_trans},
	{"RC_TOOL", 1, rc_tool},
	{"RC_REF_SYS", 1, rc_ref_sys},

	{"RC_PRINT", VARIABLE_LEN, rc_print}
};



/* ** the RC Entity type of function block **************************** */
class RCEntityBase {
public:
	RCEntityBase(std::string f) : funcName(f) {}

	virtual int setConfig(std::string key, std::string value) = 0;

	virtual int printInfo() { std::cout << "[> RCEntityBase <]" << std::endl; }

public:
	std::string funcName;
};


class RCCommEntity : public RCEntityBase {
public:
	struct SendDataElem{
		std::string tag;
		std::vector<std::pair<std::string, int>> dataMap;
		std::pair<std::string, int> tagText;
	};
public:
	RCCommEntity() : RCEntityBase("RC_COMMUNICATION"), initflag(false) {
		memset(sendBuffer, 0, 4096);
		memset(recvBuffer, 0, 4096);
	}

public:
	virtual int setConfig(std::string key, std::string value) {
		if(key == "COM_TYPE") {
			comm_type = value;
		} else if(key == "IP") {
			ip = value;
		} else if(key == "PORT") {
			port = value;
		} else if(key == "ROOTNAME") {
			rootNode = value;
		} else {
			return -1;
		} 
		return 0;
	}

	int setSendDataMap(std::string &tagName, int varIndex) {
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
		for(; index < sendDataMap.size(); index ++) {
			if(sendDataMap[index].tag == tag) {
				break;
			}
		}
		if(index == sendDataMap.size()) {
			SendDataElem tmp;
			tmp.tag = tag;
			if(tag != key) {
				tmp.dataMap.push_back(std::pair<std::string, int>(key, varIndex));
			} else {
				tmp.tagText = std::pair<std::string, int>(key, varIndex);
			}
			sendDataMap.push_back(tmp);
		} else {
			if(tag != key) {
				sendDataMap[index].dataMap.push_back(std::pair<std::string, int>(key, varIndex));
			} else{
				sendDataMap[index].tagText = std::pair<std::string, int>(key, varIndex);
			}
		}

		return 0;
	}

	int setRecvDataMap(std::string &tagName, int varIndex) {
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

	}

	virtual int printInfo() { 
		std::cout << std::endl << "Type: " << funcName << " --> ";
		std::cout << "comm_type=" << comm_type << " ip=" << ip << " port=" << port << " rootNode=" << rootNode << std::endl;
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

public:
	int xmlGenerate(RC_SymbolTable &symTable) {
		TiXmlDocument doc;
		TiXmlElement *rootEle = new TiXmlElement(rootNode);
		for(auto &e : sendDataMap) {
			TiXmlElement *tagEle = new TiXmlElement(e.tag);
			for(auto &elem : e.dataMap) {
				tagEle->SetAttribute(elem.first, std::to_string(symTable.addrspace[elem.second].v.value_d));
			}
			if(e.tagText.first != "") {
				tagEle->LinkEndChild(new TiXmlText(std::to_string(symTable.addrspace[e.tagText.second].v.value_d)));
			}
			rootEle->LinkEndChild(tagEle);
		}
		doc.LinkEndChild(rootEle);

		TiXmlPrinter printer;
		// printer.SetIndent( "\t" );

		doc.Accept( &printer );
		sprintf( sendBuffer, "%s", printer.CStr() );

		return 0;
	}


	int xmlParse(RC_SymbolTable &symTable) {
		TiXmlDocument doc;
		doc.Parse(recvBuffer);
		
		TiXmlElement* rootEle = doc.RootElement();  

		if(rootEle != NULL && rootEle->Value() == rootNode) {
			TiXmlElement* dataEle = rootEle->FirstChildElement();

			for(; dataEle != NULL; dataEle = dataEle->NextSiblingElement()) {
				std::string tag = dataEle->Value();
				std::unordered_map<std::string, int> &mp = recvDataMap[tag];

				TiXmlAttribute* attr = dataEle->FirstAttribute();
				for(; attr != NULL; attr = attr->Next()) {
					symTable.addrspace[mp[attr->Name()]].v.value_d = std::stod(attr->Value());
				}
				if(mp.find(tag) != mp.end()) {
					symTable.addrspace[mp[tag]].v.value_d = std::stod(dataEle->GetText());
				} 
			}
			return 0;
		} else {
			return -1;
		}
	}


public:
	std::string comm_type;
	std::string ip;
	std::string port;
	std::string rootNode;

	std::unordered_map<std::string, std::unordered_map<std::string, int>> recvDataMap; // <tag, <property, index>>
	std::vector<SendDataElem> sendDataMap; 		// send data rule

public:
	bool initflag;

	int sockfd;
	struct sockaddr_in addr;

	char sendBuffer[4096];
	char recvBuffer[4096];
};

class RCEntityFactory {
public:
	static RCEntityBase* getEntity(std::string name) {
		if(name == "RC_COMMUNICATION") {
			return new RCCommEntity();
		}
		return NULL;
	}
};

