#pragma once

#include "rc_innerdata.h"
#include "rc_exception.h"
#include "../../../include/logger.h"

#include "opmanager.hh"
#include "RCSyslib.h"

#include "linuxserial.h"


class RCBaseStatement {
public:

	RCBaseStatement(RC_SymbolTable &sym) :
				addrspace(sym.addrspace),
				stringpool(sym.stringpool),
				apaddr(sym.apaddr),
				cpaddr(sym.cpaddr),
				tooladdr(sym.tooladdr),
				cooraddr(sym.cooraddr), 
				symTable(sym),
				lineno(0)
	{}

	virtual int execute(void *cookie) = 0;

	virtual bool selfCheck() {
		std::cout << "RCBaseStatement selfCheck()" << std::endl;
		return true;
	}

	virtual void printInfo(std::string  empty="") {
		std::cout << empty << "[Line " << lineno << "] ";
		std::cout << empty << "RCBaseStatement" << std::endl;
	}

public:
	RCAddressSpace &addrspace;     // addrspace[0] is the returned value of all the library function  in global
	
	StringPoolSpace &stringpool;
	APDataSpace &apaddr;
	CPDataSpace &cpaddr;
	ToolDataSpace &tooladdr;
	CoorDataSpace &cooraddr;

	RC_SymbolTable &symTable;

	int lineno;
};


class RCCallStatement : public RCBaseStatement {
public:
	RCCallStatement(RC_SymbolTable &sym) :  RCBaseStatement(sym)
											 {}
public:
	virtual int execute(void *cookie) override {

	}

public:
	std::string programName;

public:
	virtual void printInfo(std::string  empty) override {
		std::cout << empty << "[Line " << lineno << "] ";
		std::cout << "Call " << programName << std::endl;
	}
	
};


class RCSingleInstStatemement : public RCBaseStatement {
public:
	enum INST_TYPE{
		NONE = 0, RET = 1, NOP = 2, PAUSE = 3, HALT = 4, BREAK = 5, LABEL = 6
	};
public:
	RCSingleInstStatemement(RC_SymbolTable &sym) :  RCBaseStatement(sym), 
											type(NONE)
											 {}
public:
	virtual int execute(void *cookie) override {
		// rc_core.cur_linenum = lineno;
		std::cout << "PC --------->  line : " << lineno  << std::endl;
		send_filename_and_ptr(lineno, rc_core.cur_program);
		switch(type) {
			case RET: {
				LOGGER_TRACE(lineno, "RET");
				break;
			}
			case NOP: {
				LOGGER_TRACE(lineno, "NOP");
				break;
			}
			case PAUSE: {
				LOGGER_TRACE(lineno, "PAUSE");
				break;
			}
			case HALT: {
				while(1) {
					STEPCHECK();
					LOGGER_TRACE(lineno, "HALT");
				}
				break;
			}
			case BREAK: {
				LOGGER_TRACE(lineno, "BREAK");
				break;
			}
			case LABEL: {
				LOGGER_TRACE(lineno, "LABEL");
				break;
			}
			default:
			break;
		}

	}

public:
	INST_TYPE type;

public:
	virtual void printInfo(std::string  empty) {
		std::cout << empty << "[Line " << lineno << "] ";
		if(type == RET) std::cout << "RET" << std::endl;
		else if(type == NOP) std::cout << "NOP" << std::endl;
		else if(type == PAUSE) std::cout << "PAUSE" << std::endl;
		else if(type == HALT) std::cout << "HALT" << std::endl;
		else if(type == BREAK) std::cout << "BREAK" << std::endl;
		else if(type == LABEL) std::cout << "LABEL" << std::endl;
	}
};


class RCRobotStatement : public RCBaseStatement {
public:
	enum INST_TYPE {
		NONE = 0, MOVJ = 1, MOVL = 2, MOVC = 3, MOVS = 4, SHIFTON = 5, SHIFTOFF = 6
	};
	enum RESO_LEVEL {
		Z0 = 0, Z1 = 1, Z2 = 2, Z3 = 3, Z4 = 4, Z5 = 5, Z6 = 6, Z7 = 7, Z8 = 8
	};
public:
	RCRobotStatement(RC_SymbolTable &sym) :  RCBaseStatement(sym), 
											type(NONE),
											endpointIndex(0),
											midpointIndex(0),
											speed(0),
											Z(Z0)
											 {}
public:
	virtual int execute(void *cookie) override {
		ROBOT_INST temp_inst;			// define a temp robot inst
		std::cout << "PC --------->  line : " << lineno  << std::endl;
		send_filename_and_ptr(lineno, rc_core.cur_program);
		// rc_core.cur_linenum = lineno;
		// STEPCHECK(rc_core.cur_linenum);
		size_t n = pRobot->getRobotAxisNum();
		std::cout << "Axis cnt = " << n << std::endl;
		switch(type) {
			case MOVJ: {
				LOGGER_TRACE(lineno, "MOVJ");
				/* step 1: setting the robot inst type */
				temp_inst.ri_type = PTP;
				/* step 2: specify the first point(the current position) of MOVJ inst  */	
				Position_ACS_deg p1(n);
				pRobot->getActualAxisPos(rc_shm,&rc_mutex_desc,p1);
				temp_inst.args[0].apv = p1;
				/* step 3: specify the second point(the target position) of MOVJ inst  */	
				if(addrspace[endpointIndex].type == TJTPOSE) 
				{
					Position_ACS_deg p2(n);
					int posIndex = addrspace[endpointIndex].v.value_ap;
					for(int i = 0; i < n; i ++)
						p2[i] = apaddr[posIndex][i];
					temp_inst.args[1].apv = p2;
				} else if(addrspace[endpointIndex].type == TTRPOSE) 
				{
					Position_ACS_rad p2(n);
					Position_MCS_rad tarPos(6);
					int posIndex = addrspace[endpointIndex].v.value_cp;
					for(int i = 0; i < 6; i ++)
						tarPos[i] = cpaddr[posIndex][i];
					pRobot->calcInverseKin_RPY(tarPos,p1,p2);
					temp_inst.args[1].apv = rad2deg(p2);
				}
				/* step 4: insert inst into inst-buffer */
				inst_buffer_write(temp_inst);	
				break;
			}
			case MOVL: {
				LOGGER_TRACE(lineno, "MOVL");
				/* step 1: setting the robot inst type */
				temp_inst.ri_type = LIN;
				/* step 2: specify the first point(the current position) of MOVL inst  */	
				Position_ACS_deg p1(n);
				pRobot->getActualAxisPos(rc_shm,&rc_mutex_desc,p1);
				temp_inst.args[0].apv = p1;
				std::cout << "p1: " << temp_inst.args[0].apv.transpose() << std::endl;
				/* step 3: specify the second point(the target position) of MOVL inst  */
				Position_MCS_rad tarPos(6);
				if(addrspace[endpointIndex].type == TTRPOSE) {
					int posIndex = addrspace[endpointIndex].v.value_cp;
					for(int i = 0; i < 3; i ++)
						tarPos[i] = cpaddr[posIndex][i];
					for(int i = 3; i < 6;  ++i)
						tarPos[i] = deg2rad(cpaddr[posIndex][i]);
				} else if(addrspace[endpointIndex].type == TJTPOSE) {
					int posIndex = addrspace[endpointIndex].v.value_ap;
					Position_ACS_deg p2(n);
					for(int i = 0; i < n; i ++)
						p2[i] = apaddr[posIndex][i];
					pRobot->calcForwardKin_RPY(deg2rad(p2),tarPos);
				}
				temp_inst.args[1].cpv = tarPos;
				/* step 4: insert inst into inst-buffer */
				inst_buffer_write(temp_inst);
				break;
			}
			case MOVC: {
				LOGGER_TRACE(lineno, "MOVC");
				break;
			}
			case MOVS: {
				LOGGER_TRACE(lineno, "MOVS");
				break;
			}
			case SHIFTON: {
				LOGGER_TRACE(lineno, "SHIFTON");
				break;
			}
			case SHIFTOFF: {
				LOGGER_TRACE(lineno, "SHIFTOFF");
				break;
			}
			
			default:
			break;
		}
	}
public:
	INST_TYPE type;
	uint32_t endpointIndex;
	uint32_t midpointIndex;
	uint32_t speed;
	RESO_LEVEL Z;
	std::string frame;

public:
	virtual void printInfo(std::string  empty) override{
		std::cout << empty << "[Line " << lineno << "]";
		if(type == MOVJ) 
			std::cout << " MOVJ " << endpointIndex << " V" << speed << " Z" << Z << std::endl;
		if(type == MOVL) 
			std::cout << " MOVL " << endpointIndex << " V" << speed << " Z" << Z << std::endl;
		if(type == MOVC)
			std::cout << " MOVC " << endpointIndex << " " << midpointIndex << " V" << speed << " Z" << Z << std::endl;
		if(type == MOVS)
			std::cout << " MOVS " << endpointIndex << " " << midpointIndex << " V" << speed << " Z" << Z << std::endl;
		if(type == SHIFTON)
			std::cout << " SHIFTON " << endpointIndex << " " << frame << std::endl;
		if(type == SHIFTOFF)
			std::cout << " SHIFTOFF" << std::endl;
	}

};




class RCDataStatement : public RCBaseStatement {
public:
	enum INST_TYPE {
		NONE = 0, SET = 1, SETE = 2, GETE = 3
	};
public:
	RCDataStatement(RC_SymbolTable &sym) :  RCBaseStatement(sym), 
											type(NONE),
											index1(0),
											index2(0)
											{}
public:
	virtual int execute(void *cookie) override {
		std::cout << "PC --------->  line : " << lineno  << std::endl;
		send_filename_and_ptr(lineno, rc_core.cur_program);
		// rc_core.cur_linenum = lineno;
		// STEPCHECK(rc_core.cur_linenum);
		switch(type) {
			case SET: {
				LOGGER_TRACE(lineno, "SET");
				uint8_t type = addrspace[index1].type;
				if(type == TBOOL || type == TCHAR) {
					addrspace[index1].v.value_b = addrspace[index2].v.value_b;
				} else if(type == TINT) {
					addrspace[index1].v.value_i = addrspace[index2].v.value_i;
				} else if(type == TDOUBLE) {
					addrspace[index1].v.value_d = addrspace[index2].v.value_d;
				}
				break;
			}
			case SETE: {
				LOGGER_TRACE(lineno, "SETE");
				uint8_t type = addrspace[elem.first].type;
				if(type == TJTPOSE) {
					uint32_t pointIndex = addrspace[elem.first].v.value_ap;
					apaddr[pointIndex][elem.second-1] = addrspace[index2].v.value_d;
				} else if(type == TTRPOSE) {
					uint32_t pointIndex = addrspace[elem.first].v.value_cp;
					cpaddr[pointIndex][elem.second-1] = addrspace[index2].v.value_d;
				}
				break;
			}
			case GETE: {
				LOGGER_TRACE(lineno, "GETE");
				uint8_t type = addrspace[elem.first].type;
				if(type == TJTPOSE) {
					uint32_t pointIndex = addrspace[elem.first].v.value_ap;
					addrspace[index1].v.value_d = apaddr[pointIndex][elem.second-1];
				} else if(type == TTRPOSE) {
					uint32_t pointIndex = addrspace[elem.first].v.value_cp;
					addrspace[index1].v.value_d = cpaddr[pointIndex][elem.second-1];
				}
				break;
			}
			
			default:
				break;
		}
		send_cmd_to_exec(CMD_NEXT);
	}

public:
	INST_TYPE type;
	uint32_t index1;
	uint32_t index2;
	std::pair<uint32_t, uint32_t> elem;

public:
	virtual void printInfo(std::string  empty) override{
		std::cout << empty << "[Line " << lineno << "]";
		if(type == SET) {
			std::cout << " SET " << index1 << " " << index2 << std::endl;
		} else if(type == SETE) {
			std::cout << " SETE " << elem.first << "(" << elem.second << ") " << index2 << std::endl;
		} else if(type == GETE) {
			std::cout << " GETE " << index1 << " " << elem.first << "(" << elem.second << ")" << std::endl;
		}
	}

};

class RCSignalStatement : public RCBaseStatement {
public:
	enum INST_TYPE {
		NONE = 0, WAIT = 1, DELAY = 2, SETOUT = 3, DIN = 4
	};
	enum OP_TYPE {
		EQ = 0, GE = 1, GT = 2, LE = 3, LT = 4, NE = 5
	};
public:
	RCSignalStatement(RC_SymbolTable &sym) : RCBaseStatement(sym), 
											 type(NONE),
											 op(EQ),
											 time(0),
											 index1(0),
											 index2(0)
											 {}
public:
	virtual int execute(void *cookie) override {
		std::cout << "PC --------->  line : " << lineno  << std::endl;
		send_filename_and_ptr(lineno, rc_core.cur_program);
		// rc_core.cur_linenum = lineno;
		// STEPCHECK(rc_core.cur_linenum);
		switch(type) {
			case WAIT: {
				LOGGER_TRACE(lineno, "WAIT");
				break;
			}
			
			case DELAY: {
				LOGGER_TRACE(lineno, "DELAY");
				break;
			}
			
			case SETOUT: {
				LOGGER_TRACE(lineno, "SETOUT");
				if(addrspace[index2].v.value_i == 1) {
					openItem();
				} else {
					closeItem();
				}
				break;
			}
			
			case DIN: {
				LOGGER_TRACE(lineno, "DIN");
				break;
			}
			
			default:
			break;
		}
		send_cmd_to_exec(CMD_NEXT);
	}

public:
	INST_TYPE type;
	OP_TYPE op;
	double time;
	uint32_t index1;
	uint32_t index2;

public:
	virtual void printInfo(std::string  empty) override {
		std::cout << empty << "[Line " << lineno << "]";
		if(type == WAIT) {
			std::cout << " WAIT " << index1 << " op<" << op << "> " << index2 << " T" << time << std::endl;
		} else if(type == DELAY) {
			std::cout << " DELAY " << "T" << time << std::endl;
		} else if(type == SETOUT) {
			std::cout << " SETOUT " << index1 << " " << index2 << std::endl;
		} else if(type == DIN) {
			std::cout << " DIN " << index1 << " " << index2 << std::endl;
		}
	}
};


class RCMathStatement : public RCBaseStatement {
public:
	enum INST_TYPE {
		NONE = 0, INCR = 1, DECR = 2, 
		ADD = 3, SUB = 4, MUL = 5, DIV = 6, 
		SIN = 7, COS = 8, ATAN = 9, SQRT = 10, 
		AND = 11, OR = 12, NOT = 13, XOR = 14
	};
public:
	RCMathStatement(RC_SymbolTable &sym) : RCBaseStatement(sym), 
											 type(NONE),
											 index1(0),
											 index2(0)
											 {}
public:
	virtual int execute(void *cookie) override {
		std::cout << "PC --------->  line : " << lineno  << std::endl;
		send_filename_and_ptr(lineno, rc_core.cur_program);
		// rc_core.cur_linenum = lineno;
		// STEPCHECK(rc_core.cur_linenum);
		switch(type) {
			case INCR: {
				LOGGER_TRACE(lineno, "INCR");
				uint8_t type = addrspace[index1].type;
				if(type == TCHAR) {
					addrspace[index1].v.value_c ++;
				} else if(type == TINT) {
					addrspace[index1].v.value_i ++;
				} else if(type == TDOUBLE) {
					addrspace[index1].v.value_d = addrspace[index1].v.value_d + 1;
				}
				break;
			}
			case DECR: {
				LOGGER_TRACE(lineno, "DECR");
				uint8_t type = addrspace[index1].type;
				if(type == TCHAR) {
					addrspace[index1].v.value_c --;
				} else if(type == TINT) {
					addrspace[index1].v.value_i --;
				} else if(type == TDOUBLE) {
					addrspace[index1].v.value_d = addrspace[index1].v.value_d - 1;
				}
				break;
			}
			case ADD: {
				LOGGER_TRACE(lineno, "ADD");
				if(index1 == 0) {
					uint8_t type = addrspace[elem1.first].type;
					if(type == TJTPOSE) {
						uint32_t pointIndex = addrspace[elem1.first].v.value_ap;
						apaddr[pointIndex][elem1.second-1] += addrspace[index2].v.value_d;
					} else if(type == TTRPOSE) {
						uint32_t pointIndex = addrspace[elem1.first].v.value_cp;
						cpaddr[pointIndex][elem1.second-1] += addrspace[index2].v.value_d;
					}
				} else {
					uint8_t type = addrspace[index1].type;
					if(type == TCHAR) {
						addrspace[index1].v.value_c += addrspace[index2].v.value_c;
					} else if(type == TINT) {
						addrspace[index1].v.value_i += addrspace[index2].v.value_i;
					} else if(type == TDOUBLE) {
						addrspace[index1].v.value_d += addrspace[index2].v.value_d ;
					} 
				}
				break;
			}
			case SUB: {
				LOGGER_TRACE(lineno, "SUB");
				if(index1 == 0) {
					uint8_t type = addrspace[elem1.first].type;
					if(type == TJTPOSE) {
						uint32_t pointIndex = addrspace[elem1.first].v.value_ap;
						apaddr[pointIndex][elem1.second-1] -= addrspace[index2].v.value_d;
					} else if(type == TTRPOSE) {
						uint32_t pointIndex = addrspace[elem1.first].v.value_cp;
						cpaddr[pointIndex][elem1.second-1] -= addrspace[index2].v.value_d;
					}
				} else {
					uint8_t type = addrspace[index1].type;
					if(type == TCHAR) {
						addrspace[index1].v.value_c -= addrspace[index2].v.value_c;
					} else if(type == TINT) {
						addrspace[index1].v.value_i -= addrspace[index2].v.value_i;
					} else if(type == TDOUBLE) {
						addrspace[index1].v.value_d -= addrspace[index2].v.value_d ;
					} 
				}
				
				break;
			}
			case MUL: {
				LOGGER_TRACE(lineno, "MUL");
				break;
			}
			case DIV: {
				LOGGER_TRACE(lineno, "DIV");
				break;
			}
			case SIN: {
				LOGGER_TRACE(lineno, "SIN");
				break;
			}
			case COS: {
				LOGGER_TRACE(lineno, "COS");
				break;
			}
			case ATAN: {
				LOGGER_TRACE(lineno, "ATAN");
				break;
			}
			case SQRT: {
				LOGGER_TRACE(lineno, "SQRT");
				break;
			}
			case AND: {
				LOGGER_TRACE(lineno, "AND");
				break;
			}
			case OR: {
				LOGGER_TRACE(lineno, "OR");
				break;
			}
			case NOT: {
				LOGGER_TRACE(lineno, "NOT");
				break;
			}
			case XOR: {
				LOGGER_TRACE(lineno, "XOR");
				break;
			}
			default:
			break;
		}
		send_cmd_to_exec(CMD_NEXT);
		
	}

public:
	uint32_t type;
	uint32_t index1;
	uint32_t index2;
	std::pair<int32_t, int32_t> elem1;
	std::pair<int32_t, int32_t> elem2;


public:
	virtual void printInfo(std::string  empty) override {
		std::cout << empty << "[Line " << lineno << "]";
		if(type == INCR) {
			std::cout << " INCR " << index1 << std::endl;
		} else if(type == DECR) {
			std::cout << " DECR " << index1 << std::endl;
		} else  {
			if(type == ADD) std::cout << " ADD " ;
			else if(type == SUB) std::cout << " SUB " ;
			else if(type == MUL) std::cout << " MUL ";
			else if(type == DIV) std::cout << " DIV ";
			else if(type == SIN) std::cout << " SIN ";
			else if(type == COS) std::cout << " COS ";
			else if(type == ATAN) std::cout << " ATAN ";
			else if(type == SQRT) std::cout << " SQRT ";
			else if(type == AND) std::cout << " AND ";
			else if(type == OR) std::cout << " OR ";
			else if(type == NOT) std::cout << " NOT ";
			else if(type == XOR) std::cout << " XOR ";
			if(index1 == 0) std::cout << elem1.first << "(" << elem1.second << ") ";
			else std::cout << index1 << " ";
			if(index2 == 0) std::cout << elem2.first << "(" << elem2.second << ") ";
			else std::cout << index2 << " " << std::endl;
		}

	}
};


class RCLibCallStatement : public RCBaseStatement {
public:
	RCLibCallStatement(RC_SymbolTable &sym) : RCBaseStatement(sym), 
											 index(0),
											 config(NULL)
											 {}
public:
	virtual int execute(void *cookie) override {
		std::cout << "PC --------->  line : " << lineno  << std::endl;
		send_filename_and_ptr(lineno, rc_core.cur_program);
		// rc_core.cur_linenum = lineno;
		// STEPCHECK(rc_core.cur_linenum);
		LOGGER_TRACE(lineno, "LIBCALL");
		rcLibEntry[index].pfun(params, config, symTable);
		send_cmd_to_exec(CMD_NEXT);
	}	
public:
	uint32_t index;						// the index of library function
	std::vector<int> params;			// the index of function parameters
	RCEntityBase *config;

public:
	virtual void printInfo(std::string  empty) override {
		std::cout << empty << "[Line " << lineno << "]";
		std::cout << " f{" << index << "} (";
		for(int i = 0; i < params.size(); i ++) {
			std::cout << " {" << params[i] << "}";
		} 
		std::cout << " )" << std::endl;
	}
};


class RCAssignStatement : public RCBaseStatement {
public:
	enum INST_TYPE {
		NONE = 0, GENERIC = 1, CALL = 2, ARITHMETIC = 3
	};
public:
	RCAssignStatement(RC_SymbolTable &sym) : RCBaseStatement(sym), 
											type(NONE),
											left(0),
											right(0)
											{}
public:
	virtual int execute(void *cookie) override {
		std::cout << "PC --------->  line : " << lineno  << std::endl;
		send_filename_and_ptr(lineno, rc_core.cur_program);
		// rc_core.cur_linenum = lineno;
		// STEPCHECK(rc_core.cur_linenum);

		LOGGER_TRACE(lineno, "ASSIGNMENT");
		switch(type) {
			case GENERIC: {
				addrspace[left] = addrspace[right];
				break;
			}
			
			case CALL: {
				caller->execute(cookie);
				addrspace[left] = addrspace[0];
				break;
			}
			case ARITHMETIC: {
				break;
			}
			
			default:
			break;
		}
		send_cmd_to_exec(CMD_NEXT);
	}	

	virtual bool selfCheck() {
		
		return true;
	}

public:
	INST_TYPE type;
	uint32_t left;
	uint32_t right;
	std::vector<uint32_t> oprand;
	std::vector<std::string> op; 
	RCBaseStatement* caller;

public:
	virtual void printInfo(std::string  empty) override {
		std::cout << empty << "[Line " << lineno << "] ";
		if(type == GENERIC) {
			std::cout << "{" << left << "} = {" << right << "}" << std::endl;
		} else if(type == ARITHMETIC) {
			std::cout << "{" << left << "} = ";
			for(auto &e : oprand) {
				std::cout << " {" << e <<"} ";
			}
			for(auto &e : op) {
				std::cout << " <" << e << "> ";
			}
			std::cout << std::endl;
		} else if(type == CALL) {
			std::cout << "{" << left << "} = ";
			caller->printInfo();
		}
	}
};

class RCGotoStatement : public RCBaseStatement {
public:
	RCGotoStatement(RC_SymbolTable &sym) : RCBaseStatement(sym)
							
											{}
public:
	virtual int execute(void *cookie) override {
		LOGGER_TRACE(lineno, "GOTO");
	}

public:
	std::string label;

public:
	virtual void printInfo(std::string  empty) override {
		std::cout << empty << "[Line " << lineno << "] ";
		std::cout << "GOTO " << label << std::endl;
	}

};

class RCIfStatement : public RCBaseStatement {
public:
	enum INST_TYPE {
		NONE = 0, GENERIC = 1, VAR = 2
	};
	enum OP_TYPE {
		EQ = 0, GE = 1, GT = 2, LE = 3, LT = 4, NE = 5
	};


public:
	RCIfStatement(RC_SymbolTable &sym) : RCBaseStatement(sym),
											type(NONE)
											{}
public:
	virtual int execute(void *cookie) override {
		LOGGER_TRACE(lineno, "IFStatement");
		switch(type) {
			case GENERIC:
			break;
			case VAR:
			break;
			default:
			break;
		}
	}

public:
	INST_TYPE type;
	uint32_t exprVarIndex;
	OP_TYPE op;
	uint32_t oprand1;
	uint32_t oprand2;

	std::vector<RCBaseStatement*> *ifThenStat;
	std::vector<RCBaseStatement*> *elseifThenStat;
	std::vector<RCBaseStatement*> *elseThenStat;

public:
	virtual void printInfo(std::string  empty) override {
		std::cout << empty << "[Line " << lineno << "] " << std::endl;
		if(type == GENERIC) {
			std::cout << empty << "IF " << "{" << oprand1 << "} <" << op << "> {" << oprand2 << "}" << std::endl;
		} else if(type == VAR) {
			std::cout << empty << "IF " << "{" << exprVarIndex << "}" << std::endl;
		}
		for(auto &e : *ifThenStat) {
			e->printInfo(empty + "\t");
		}
		for(auto &e : *elseifThenStat) {
			e->printInfo();
		}
		std::cout << empty << "ELSE" << std::endl;
		for(auto &e : *elseThenStat) {
			e->printInfo(empty + "\t");
		}
		std::cout << empty << "ENDIF" << std::endl;
	}

};

class RCElseifStatement : public RCBaseStatement {
public:
	enum INST_TYPE {
		NONE = 0, GENERIC = 1, VAR = 2
	};
	enum OP_TYPE {
		EQ = 0, GE = 1, GT = 2, LE = 3, LT = 4, NE = 5
	};
public:
	RCElseifStatement(RC_SymbolTable &sym) : RCBaseStatement(sym)
											
											{}
public:
	virtual int execute(void *cookie) override {
		LOGGER_TRACE(lineno, "ELSEStatement");
	}

public:
	INST_TYPE type;
	uint32_t exprVarIndex;
	OP_TYPE op;
	uint32_t oprand1;
	uint32_t oprand2;

	std::vector<RCBaseStatement*> *Stat;
public:
	virtual void printInfo(std::string  empty) override {
		std::cout << empty << "[Line " << lineno << "] " << std::endl;
		if(type == GENERIC) {
			std::cout << empty << "ELSEIF " << "{" << oprand1 << "} <" << op << "> {" << oprand2 << "}" << std::endl;
		} else if(type == VAR) {
			std::cout << empty << "ELSEIF " << "{" << exprVarIndex << "}" << std::endl;
		}
		for(auto &e : *Stat) {
			e->printInfo(empty + "\t");
		}
		
	}
};


class RCForStatement : public RCBaseStatement {
public:
	RCForStatement(RC_SymbolTable &sym) : RCBaseStatement(sym),
											varIndex(0),
											initValue(0),
											stopValue(0),
											step(0)
											{}
public:
	virtual int execute(void *cookie) override {
		LOGGER_TRACE(lineno, "FORStatement");
	}

public:
	uint32_t varIndex;				// the index of var in for statement
	int32_t initValue;				// the init value of var
	int32_t stopValue; 				// the end value of var
	int32_t step; 					// the step value of var in every cycle

	std::vector<RCBaseStatement*> *block;
public:
	virtual void printInfo(std::string  empty) override {
		std::cout << empty << "[Line " << lineno << "] " << std::endl; 
		std::cout << empty << "FOR {" << varIndex << "} = " << initValue << " TO " << stopValue << " BY " << step << std::endl;
		for(auto &e : *block) {
			e->printInfo(empty + "\t");
		}
		std::cout << empty << "ENDFOR" << std::endl;
	}
};


class RCWhileStatement : public RCBaseStatement {
public:
	enum INST_TYPE{
		NONE = 0, GENERIC = 1, VAR = 2
	};
	enum OP_TYPE {
		EQ = 0, GE = 1, GT = 2, LE = 3, LT = 4, NE = 5
	};
public:
	RCWhileStatement(RC_SymbolTable &sym) : RCBaseStatement(sym)
											{}
public:
	virtual int execute(void *cookie) override {
		LOGGER_TRACE(lineno, "WHILEStatement");
		switch(type) {
			case GENERIC:
			break;
			case VAR:
			break;
			default:
			break;
		}
	}

public:
	INST_TYPE type;

	uint32_t exprVarIndex;
	OP_TYPE op;
	uint32_t oprand1;
	uint32_t oprand2;

	std::vector<RCBaseStatement*> *block;

public:
	virtual void printInfo(std::string  empty) override {
		std::cout << empty << "[Line " << lineno << "] " << std::endl;
		if(type == GENERIC) {
			std::cout << empty << "WHILE " << "{" << oprand1 << "} <" << op << "> {" << oprand2 << "} " << "DO"  << std::endl;
		} else if(type == VAR) {
			std::cout << empty << "WHILE " << "{" << exprVarIndex << "} " << "DO" << std::endl;
		}
		for(auto &e : *block) {
			e->printInfo(empty + "\t");
		}
		std::cout << empty << "ENDWL" << std::endl;

	}


};


typedef std::vector<RCBaseStatement*> CodeModel;   // rc code in memory 
