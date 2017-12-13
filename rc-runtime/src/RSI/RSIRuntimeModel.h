
#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "IValue.h"
#include "RSISyslib.h"

// #define RSI_DEBUG 


#ifdef RSI_PRINT
extern std::unordered_map<int, std::string> rdataIndexMap;   // index --> var
#endif

class BaseStatement {
public:
	BaseStatement() {}
	BaseStatement(std::vector<IValue> *as) : addr(as) {}

	virtual int execute(void *cookie) = 0;
public:
	std::vector<IValue> *addr;
};

class AssignStatement : public BaseStatement {
public:
	AssignStatement(){}
	AssignStatement(std::vector<IValue> *as) : BaseStatement(as), caller(NULL) {}

	virtual int execute(void *cookie) override{
#ifdef RSI_DEBUG
		std::cout << "=====assign state execute=====" << std::endl;
#endif  
		RSI_STOP_CHECK();
		if(caller == NULL) {
			(*addr)[left] = (*addr)[right];
		} else {
			caller->execute(cookie);
			(*addr)[left] = (*addr)[0];
		}
	}

public:
	int left;
	int right;
	BaseStatement* caller;
};

class IfStatement : public BaseStatement {
public:
	IfStatement() {}
	IfStatement(std::vector<IValue> *as) : 
			BaseStatement(as), exprCaller(NULL),
			ifThenStat(NULL), elseifThenStat(NULL), elseThenStat(NULL)
			{}

	virtual int execute(void *cookie) override {
#ifdef RSI_DEBUG
		std::cout << "=====if state execute=====" << std::endl;
#endif  
		RSI_STOP_CHECK();
		int cond = 0;
		if(exprCaller == NULL) {
			cond = (*addr)[exprVar].RSIint();
		} else {
			exprCaller->execute(cookie);
			cond = (*addr)[0].RSIint();
		}
		if(cond) {
			for(auto &elem : *ifThenStat) {
				RSI_STOP_CHECK();
				elem->execute(cookie);
			}
		} else {
			if(elseifThenStat != NULL) {
				for(int i = 0; i < elseifThenStat->size(); i ++) {
					RSI_STOP_CHECK();
					int flag = ((*elseifThenStat)[i])->execute(cookie);
					if(flag) return 0;
				}
			}
			if(elseThenStat != NULL) {
				for(int i = 0; i < elseThenStat->size(); i ++) {
					RSI_STOP_CHECK();
					((*elseThenStat)[i])->execute(cookie);
				}
			}
		}
		return 0;
	}

public:
	int exprVar;
	BaseStatement* exprCaller;

	std::vector<BaseStatement*> *ifThenStat;
	std::vector<BaseStatement*> *elseifThenStat;
	std::vector<BaseStatement*> *elseThenStat;
};

class ElseifStatement : public BaseStatement {
public:
	ElseifStatement() {}
	ElseifStatement(std::vector<IValue> *as) : 
						BaseStatement(as), flag(0),
						exprCaller(NULL), Stat(NULL)
			 			{}

	virtual int execute(void *cookie) override {
		RSI_STOP_CHECK();
		int cond = 0;
		if(exprCaller == NULL) {
			cond = (*addr)[exprVar].RSIint();
		} else {
			exprCaller->execute(cookie);
			cond = (*addr)[0].RSIint();
		}
		if(cond) {
			flag = 1;
			for(auto &elem : *Stat) {
				RSI_STOP_CHECK();
				elem->execute(cookie);
			}
		}
		return flag;
	}

public:
	int flag;
	int exprVar;
	BaseStatement* exprCaller;

	std::vector<BaseStatement*> *Stat;
};

class LoopStatement : public BaseStatement {
public:
	LoopStatement() {}
	LoopStatement(std::vector<IValue> *as) : BaseStatement(as) {}

	virtual int execute(void *cookie) override {
#ifdef RSI_DEBUG
		std::cout << "=====loop state execute=====" << std::endl;
#endif
		RSI_STOP_CHECK();
		int times = (*addr)[varIndex].RSIint();
		times = times > 0 ? times : 0;
		for(int i = 0; i < times; i ++) {
			for(auto &elem : *Stat) {
				RSI_STOP_CHECK();
				elem->execute(cookie);
			}
		}

	}

public:
	int varIndex;
	std::vector<BaseStatement*> *Stat;
};

class WhileStatement : public BaseStatement {
public:
	WhileStatement() {}
	WhileStatement(std::vector<IValue> *as) : 
									BaseStatement(as),exprCaller(NULL) {}

	virtual int execute(void *cookie) override {
#ifdef RSI_DEBUG
		std::cout << "=====while state execute=====" << std::endl;
#endif		
		RSI_STOP_CHECK();
		int cond = 0;
		if(exprCaller == NULL) {
			while(cond = ((*addr)[exprVar] > 0 ? (*addr)[exprVar].RSIint() : 0)) {
				for(auto &elem : *Stat) {
					RSI_STOP_CHECK();
					elem->execute(cookie);
				}
			}
		} else {
			while(1) {
				exprCaller->execute(cookie);
				cond = (*addr)[0].RSIint();
				if(cond == 0) break;
				for(auto &elem : *Stat) {
					RSI_STOP_CHECK();
					elem->execute(cookie);
				}
			}
		}
	}

public:
	int exprVar;
	BaseStatement* exprCaller;
	std::vector<BaseStatement*> *Stat;
};

class CallStatement : public BaseStatement {
public:
	CallStatement() {}
	CallStatement(std::vector<IValue> *as) : BaseStatement(as), config(NULL) {}

	virtual int execute(void *cookie) override {
#ifdef RSI_DEBUG
		std::cout << "=====call state execute=====" << std::endl;
#endif		
		RSI_STOP_CHECK();
		libEntry[index].pfun(params, config, *addr);
	}

public:
	int index;						// the index of library function
	std::vector<int> params;		// the index of function parameters
	EntityBase *config;					// the config of fb
};


typedef std::vector<BaseStatement*> CodeShadow;		// code model in memory

struct PouParam {									// pou parameter
	std::string pname;
	int type;
	double defvalue;
};

class SysPou {										// system library pou
public:
	std::string name;
	std::vector<PouParam> paramlist;
};


class SymbolTable{
public:
	std::vector<IValue> &addrspace;     // RSI address space --- simple version; addrspace[0] is the returned value of all the library function  in global

	std::unordered_map<std::string, int> &dataIndexMap;		// parser xml file and generator dataMap
	std::unordered_map<std::string, int> &constIndexMap;	// the index of all the constants in addr space 
	std::unordered_map<std::string, EntityBase*> &fbMap;    // parser xml file and generator functionblock map
	std::unordered_map<std::string, int> &funcMap;  	    // all library function map to check if designated function is existed

	SymbolTable(std::vector<IValue> &a,
		  		std::unordered_map<std::string, int> &d,		
				std::unordered_map<std::string, int> &c,	
				std::unordered_map<std::string, EntityBase*> &fb,   
				std::unordered_map<std::string, int> &func) : 
						addrspace(a), dataIndexMap(d), constIndexMap(c), fbMap(fb), funcMap(func) {}

public:
	int create() {
		for(int i = 0; i < RSI_LIB_SIZE; i ++) {
			funcMap.insert(std::pair<std::string, int>(libEntry[i].name, i));
		}
#ifdef RSI_DEBUG_PRINT
		for(auto elem : dataIndexMap) {
			rdataIndexMap.insert(std::pair<int, std::string>(elem.second, elem.first));
		}
#endif
	}

};

