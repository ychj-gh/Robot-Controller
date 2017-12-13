
#pragma once


#include <iostream>
#include <exception>
#include <unordered_map>

enum RC_EXCEPTION_TYPE{
	EXCEP_RUNTIME = 0,
	EXECP_VAR_DUP,
	EXECP_NUM_FORMAT,
	EXECP_POINT_NOT_DEFINED,
	EXECP_NULL_INSTRUCTION,
	EXECP_WRONG_VAR_TYPE,
	EXECP_WRONG_PARAM,
	EXECP_LACK_PARAM,
	EXECP_VAR_NOT_DEFINED,
	EXECP_LIB_FUNC_NOT_EXIST,
	EXECP_PROJ_NOT_FOUND,
	EXECP_PROGRAM_NOT_FOUND,
	EXECP_WRONG_LIBFUNC_PARAM,
	EXECP_RSICOMM_OUTOFTIME,
	EXECP_XMLPARSE_FORMAT,
	EXECP_FB_LACKOF_CONFIG
};

static std::vector<std::string> rc_excep_info = {
	"RC executor general runtime exception",
	"RC variable duplicated defination",
	"RC bad number format or bad number type",
	"RC the point is not defined",
	"RC the instruction type is null",
	"RC the type of var is not right in such situation",
	"RC the param is not proper in this expression",
	"RC the inst is lack of parameters",
	"RC the var is not defined in this program",
	"RC the lib function is not existing",
	"RC the project is not found",
	"RC the program is not found",
	"RC the type or num of the parameters of lib function is wrong",
	"RC rsi communication out of time",
	"RC wrong xml format or wrong xml file name"
	"RC this function block is lack of config entity"
};


class rc_exception : public std::exception {
public:
	rc_exception():line(0), col(0) {
		this->type = EXCEP_RUNTIME;
	}
	rc_exception(int t): type(t) {}
	rc_exception(int t, int l, int c): type(t), line(l), col(c) {}

public:
	virtual void what() {
		std::cerr << "[EXCEPTION" << " " << type << "]: " << rc_excep_info[type] << std::endl;
	} 

public:
	int type;
	int line;
	int col;
};


class rc_vardup_exception : public rc_exception {
public:
	rc_vardup_exception() : rc_exception(EXECP_VAR_DUP, 0, 0){
	}

	rc_vardup_exception(int l, int c, std::string s) : rc_exception(EXECP_VAR_DUP, l, c), var(s){
	}

public:
	virtual void what() {
		std::cerr << "[EXCEPTION" << " " << type << "] " 
					<< "line " << line << ":" << col << " " 
					<< "[Var:" << var << "] --> "
					<< rc_excep_info[type] 
					<< std::endl;
	}

private:
	std::string var;

};


class rc_numformat_exception : public rc_exception {
public:
	rc_numformat_exception() : rc_exception(EXECP_NUM_FORMAT, 0, 0){
	}

	rc_numformat_exception(int l, int c, std::string s) : rc_exception(EXECP_NUM_FORMAT, l, c), num(s){
	}

public:
	virtual void what() {
		std::cerr << "[EXCEPTION" << " " << type << "] " 
					<< "line " << line << ":" << col << " " 
					<< "[NUM:" << num << "] --> "
					<< rc_excep_info[type] 
					<< std::endl;
	}

private:
	std::string num;

};



class rc_pointnotdefined_exception :  public rc_exception {
public:
	rc_pointnotdefined_exception() : rc_exception(EXECP_POINT_NOT_DEFINED, 0, 0){
	}

	rc_pointnotdefined_exception(int l, int c, std::string s) : rc_exception(EXECP_POINT_NOT_DEFINED, l, c), point(s){
	}
public:
	virtual void what() {
		std::cerr << "[EXCEPTION" << " " << type << "] " 
					<< "line " << line << ":" << col << " " 
					<< "[POINT:" << point << "] --> "
					<< rc_excep_info[type] 
					<< std::endl;
	}

private:
	std::string point;

};


class rc_nullinstruction_exception : public rc_exception {
public:
	rc_nullinstruction_exception() : rc_exception(EXECP_NULL_INSTRUCTION, 0, 0) {
	}

	rc_nullinstruction_exception(int l, int c, std::string s) : rc_exception(EXECP_NULL_INSTRUCTION, l, c), inst(s){
	}

public:
	virtual void what() {
		std::cerr << "[EXCEPTION" << " " << type << "] " 
					<< "line " << line << ":" << col << " " 
					<< "[INST:" << inst << "] --> "
					<< rc_excep_info[type] 
					<< std::endl;
	}

private:
	std::string inst;

};



class rc_wrongvartype_exception : public rc_exception {
public:
	rc_wrongvartype_exception() : rc_exception(EXECP_WRONG_VAR_TYPE, 0, 0){
	}

	rc_wrongvartype_exception(int l, int c, std::string s) : rc_exception(EXECP_WRONG_VAR_TYPE, l, c), var(s){
	}

public:
	virtual void what() {
		std::cerr << "[EXCEPTION" << " " << type << "] " 
					<< "line " << line << ":" << col << " " 
					<< "[VAR:" << var << "] --> "
					<< rc_excep_info[type] 
					<< std::endl;
	}

private:
	std::string var;

};


class rc_wrongparam_exception : public rc_exception {
public:
	rc_wrongparam_exception() : rc_exception(EXECP_WRONG_PARAM, 0, 0){
	}

	rc_wrongparam_exception(int l, int c, std::string s) : rc_exception(EXECP_WRONG_PARAM, l, c), var(s){
	}

public:
	virtual void what() {
		std::cerr << "[EXCEPTION" << " " << type << "] " 
					<< "line " << line << ":" << col << " " 
					<< "[VAR:" << var << "] --> "
					<< rc_excep_info[type] 
					<< std::endl;
	}

private:
	std::string var;

};

class rc_lackparam_exception : public rc_exception {
public:
	rc_lackparam_exception() : rc_exception(EXECP_LACK_PARAM, 0, 0){
	}

	rc_lackparam_exception(int l, int c, std::string s) : rc_exception(EXECP_LACK_PARAM, l, c), var(s){
	}

public:
	virtual void what() {
		std::cerr << "[EXCEPTION" << " " << type << "] " 
					<< "line " << line << ":" << col << " " 
					<< "[INST:" << var << "] --> "
					<< rc_excep_info[type] 
					<< std::endl;
	}

private:
	std::string var;

};


class rc_varnotdefined_exception : public rc_exception {
public:
	rc_varnotdefined_exception() : rc_exception(EXECP_VAR_NOT_DEFINED, 0, 0){
	}

	rc_varnotdefined_exception(int l, int c, std::string s) : rc_exception(EXECP_VAR_NOT_DEFINED, l, c), var(s){
	}

public:
	virtual void what() {
		std::cerr << "[EXCEPTION" << " " << type << "] " 
					<< "line " << line << ":" << col << " " 
					<< "[VAR:" << var << "] --> "
					<< rc_excep_info[type] 
					<< std::endl;
	}

private:
	std::string var;

};



class rc_libfuncnotexist_exception : public rc_exception {
public:
	rc_libfuncnotexist_exception() : rc_exception(EXECP_LIB_FUNC_NOT_EXIST, 0, 0){
	}

	rc_libfuncnotexist_exception(int l, int c, std::string s) : rc_exception(EXECP_LIB_FUNC_NOT_EXIST, l, c), func(s){
	}

public:
	virtual void what() {
		std::cerr << "[EXCEPTION" << " " << type << "] " 
					<< "line " << line << ":" << col << " " 
					<< "[FUNC:" << func << "] --> "
					<< rc_excep_info[type] 
					<< std::endl;
	}

private:
	std::string func;

};


class rc_projectnotfind_exception : public rc_exception {
public:
	rc_projectnotfind_exception(std::string n) : rc_exception(EXECP_PROJ_NOT_FOUND, 0, 0),
												 name(n)

	{
	}

public:
	virtual void what() {
		std::cerr << "[EXCEPTION" << " " << type << "] " 
					<< "line " << line << ":" << col << " " 
					<< "[PROJ:" << name << "] --> "
					<< rc_excep_info[type] 
					<< std::endl;
	}

private:
	std::string name;
};


class rc_programnotfound_exception : public rc_exception {
public:
	rc_programnotfound_exception(std::string n) : rc_exception(EXECP_PROGRAM_NOT_FOUND, 0, 0),
												 name(n)

	{
	}

public:
	virtual void what() {
		std::cerr << "[EXCEPTION" << " " << type << "] " 
					<< "line " << line << ":" << col << " " 
					<< "[PROGRAM:" << name << "] --> "
					<< rc_excep_info[type] 
					<< std::endl;
	}

private:
	std::string name;
};



class rc_wrongfuncparams_exception : public rc_exception {
public:
	rc_wrongfuncparams_exception(std::string n) : rc_exception(EXECP_WRONG_LIBFUNC_PARAM, 0, 0),
												 name(n)

	{
	}

public:
	virtual void what() {
		std::cerr << "[EXCEPTION" << " " << type << "] " 
					<< "line " << line << ":" << col << " " 
					<< "[LIBFUNC:" << name << "] --> "
					<< rc_excep_info[type] 
					<< std::endl;
	}

private:
	std::string name;
};


class rc_rsicomm_outoftime_exception : public rc_exception {
public:
	rc_rsicomm_outoftime_exception(std::string n) : rc_exception(EXECP_RSICOMM_OUTOFTIME, 0, 0),
												 name(n)

	{
	}

public:
	virtual void what() {
		std::cerr << "[EXCEPTION" << " " << type << "] " 
					<< "line " << line << ":" << col << " " 
					<< "[RSI:" << name << "] --> "
					<< rc_excep_info[type] 
					<< std::endl;
	}

private:
	std::string name;
};

class rc_xmlparser_exception : public rc_exception {
public:
	rc_xmlparser_exception(std::string n) : rc_exception(EXECP_XMLPARSE_FORMAT, 0, 0),
												 name(n)

	{
	}

public:
	virtual void what() {
		std::cerr << "[EXCEPTION" << " " << type << "] " 
					<< "line " << line << ":" << col << " " 
					<< "[XML:" << name << "] --> "
					<< rc_excep_info[type] 
					<< std::endl;
	}

private:
	std::string name;
};


class rc_fb_lackofconfig_exception : public rc_exception {
public:
	rc_fb_lackofconfig_exception(std::string n) : rc_exception(EXECP_FB_LACKOF_CONFIG, 0, 0),
												 name(n)

	{
	}

public:
	virtual void what() {
		std::cerr << "[EXCEPTION" << " " << type << "] " 
					<< "line " << line << ":" << col << " " 
					<< "[FB:" << name << "] --> "
					<< rc_excep_info[type] 
					<< std::endl;
	}

private:
	std::string name;
};