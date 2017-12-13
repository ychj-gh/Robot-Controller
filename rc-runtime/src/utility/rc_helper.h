#pragma once

#include "rc_innerdata.h"
#include "unordered_map"
#include "rc_exception.h"
#include "RCRuntimeModel.h"


class Utility {
public:
	static void printfAddrspace(RCAddressSpace &addrspace) {
		std::cout << "[>>>>>>>>>>>  Addrspace  <<<<<<<<<<<<]" << std::endl;
		for(int i = 0; i < addrspace.size(); i ++) {
			std::cout << "[" << i << "] " << addrspace[i] << std::endl;
		}
		std::cout << std::endl;
	}

	static void printfDataIndexMap(std::unordered_map<std::string, int> &dataIndexMap) {
		std::cout << "[>----------  DataIndexMap  --------<]" << std::endl;
		for(auto &e : dataIndexMap) {
			std::cout << e.first << " --> [" << e.second << "]" << std::endl; 
		}
		std::cout << std::endl;
	}


	static void printfStringPool(StringPoolSpace &stringpool) {
		std::cout << "[>+++++++++++++  StringPool  +++++++++++<]" << std::endl;
		for(int i = 0; i < stringpool.size(); i ++) {
			std::cout << "[" << i << "] " << stringpool[i] << std::endl;
		}
		std::cout << std::endl;
	}

	static void printfAPDataSpace(APDataSpace &apaddr) {
		std::cout << "[>************  APDataSpace  ***********<]" << std::endl;
		for(int i = 0; i < apaddr.size(); i ++) {
			std::cout << "[" << i << "] " ;
			int len = apaddr[i].size();
			for(int j = 0; j < len; j ++) {
				std::cout << apaddr[i][j];
				if(j < len-1) std::cout << ", ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	static void printfCPDataSpace(CPDataSpace &cpaddr) {
		std::cout << "[>************  CPDataSpace  ***********<]" << std::endl;
		for(int i = 0; i < cpaddr.size(); i ++) {
			std::cout << "[" << i << "] " ;
			int len = cpaddr[i].size();
			for(int j = 0; j < len; j ++) {
				std::cout << cpaddr[i][j];
				if(j < len-1) std::cout << ", ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	static void printfToolDataSpace(ToolDataSpace &tooladdr) {
		std::cout << "[>==========  ToolDataSpace  ===========<]" << std::endl;
		for(int i = 0; i < tooladdr.size(); i ++) {
			std::cout << "[" << i << "] " ;
			int len = tooladdr[i].size();
			for(int j = 0; j < len; j ++) {
				std::cout << tooladdr[i][j];
				if(j < len-1) std::cout << ", ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	static void printfCoorDataSpace(CoorDataSpace &cooraddr) {
		std::cout << "[>==========  CoorDataSpace  ===========<]" << std::endl;
		for(int i = 0; i < cooraddr.size(); i ++) {
			std::cout << "[" << i << "] " ;
			std::cout << cooraddr[i].type << " " 
						<< cooraddr[i].p1 << " "
						<< cooraddr[i].p2 << " "
						<< cooraddr[i].p3 ;
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}


	static void printfCodeShadow(CodeModel &code) {
		std::cout << std::endl;
		std::cout << "|< ----------- RC code shadow ------------ >|" << std::endl;
		for(int i = 0; i < code.size(); i ++) {
			code[i]->printInfo();
		}
		std::cout << "|< -------- END OF RC CODE SHADOW -------- >|" << std::endl << std::endl;
	}

public:
	static int parseInt(std::string &str) {
		if(checkInt(str)) {
			if(str.find("^B") == 0) {
				std::string num = str.substr(2);
				return std::stoi(num, 0, 2);
			} else if(str.find("^H") == 0) {
				std::string num = str.substr(2);
				return std::stoi(num, 0, 16);
			} else {
				return std::stoi(str);
			}
		} else {
			throw std::exception();
		}
	}	

	static double parseDouble(std::string &str) {
	
		if(str.find("^B") == std::string::npos && str.find("^H") == std::string::npos) {
			return std::stod(str);
		} else {
			throw std::exception();
		}
	}	

	static int parseSpeed(std::string &str) {
		int size = str.size();
		if(size < 2) return -1;
		for(int i = 0; i < size; i ++) {
			if(i == 0 && str[i] != 'V')  return -1;
			if(i != 0 && (str[i] < '0' || str[i] > '9')) return -1;
		}
		return std::stoi(str.substr(1));
	}


	static int parseElem(std::string &str, std::pair<std::string, std::string> &elem) {
		int size = str.size();
		if(size < 4) return -1;
		int pos = str.find("(");
		if(pos == std::string::npos) return -1;
		elem.first = str.substr(0, pos);
		elem.second = str.substr(pos+1, 1);
		return 0;
	}

public:
	static bool checkTypeMatch(uint8_t type1, uint8_t type2) {
		if(type1 == TBOOL || type1 == TCHAR || type1 == TINT || type1 == TDOUBLE) {
			if(type2 != TBOOL && type2 != TCHAR && type2 != TINT && type2 != TDOUBLE) {
				return false;
			} else {
				return true;
			}
		} 

		if(type1 == TJTPOSE) {
			if(type2 == TJTPOSE) return true;
			else return false;
		}
		if(type1 == TTRPOSE) {
			if(type2 == TTRPOSE) return true;
			else return false;
		}

		if(type1 == TSTRING) {
			if(type2 == TSTRING) return true;
			else return false;
		} 
		return false;
	}
	

public:
	static bool checkInt(std::string &str) {
		return str.find(".") == std::string::npos;
	}

	static bool checkNum(uint8_t type) {
		if(type == TBOOL || type == TCHAR || type == TINT || type == TDOUBLE) {
			return true;
		} else {
			return false;
		}
	}

	static bool startWith(std::string &str, std::string &pattern) {
		return str.find(pattern) == 0;
	}



};

