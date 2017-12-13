#ifndef __IVALUE_H__
#define __IVALUE_H__
// #pragma once
#include <stdint.h>
#include <arpa/inet.h>
#include <iostream>
#include <cassert>
#include <string>
#include <unordered_map>

#define USE_ALL_TYPE
#ifdef USE_ALL_TYPE

#define RSIBOOL 	0
#define RSICHAR	 	1
#define RSISHORT 	2
#define RSIUSHORT	3
#define RSIINT		4
#define RSIUINT		5
#define RSILONG     6
#define RSIDOUBLE   7

class IValue{
friend std::ostream& operator<<(std::ostream&,const IValue&);
friend IValue operator+(const IValue& lhs, const IValue& rhs);
friend IValue operator-(const IValue& lhs, const IValue& rhs);
friend IValue operator*(const IValue& lhs, const IValue& rhs);
friend IValue operator/(const IValue& lhs, const IValue& rhs);
friend bool operator==(const IValue& lhs, const IValue& rhs);
friend bool operator<(const IValue& lhs, const IValue& rhs);
friend bool operator>(const IValue& lhs, const IValue& rhs);
public:
	IValue():type(RSIDOUBLE){ v.value_d = 0.0;}
	// IValue(uint8_t t): type(t){}
	IValue(int val):type(RSIINT){ v.value_i = val; }	// non explicit
	// IValue(double val):type(RSIDOUBLE) {v.value_d = val;}
	IValue(uint8_t t, int64_t val):type(t) {
		switch (t) {
		case RSIBOOL: v.value_b = val ? true:false;	break;
		case RSICHAR: v.value_c = static_cast<uint8_t>(val);break;
		case RSISHORT: v.value_s = static_cast<int16_t>(val);break;
		case RSIUSHORT: v.value_us = static_cast<uint16_t>(val);break;
		case RSIINT: v.value_i = static_cast<int32_t>(val); break;
		case RSIUINT: v.value_ui = static_cast<uint32_t>(val); break;
		case RSILONG: v.value_l = static_cast<int64_t>(val); break;
		default: break;
		}
	}
	IValue(uint8_t t, double val) :type(t) { v.value_d = val; }
	IValue& operator=(const IValue& rhs);
	IValue& operator+=(const IValue& rhs);
	IValue& operator-=(const IValue& rhs);

	IValue operator-(){
		switch(type){
			case RSIBOOL:{
				IValue ret(RSIBOOL,static_cast<int64_t>(v.value_b)); 
				return ret;
			}
			case RSICHAR:{
				IValue ret(RSICHAR,static_cast<int64_t>(-v.value_c)); 
				return ret;
			}
			case RSISHORT:{
				IValue ret(RSISHORT,static_cast<int64_t>(-v.value_s)); 
				return ret;
			}
			case RSIINT:{
				IValue ret(RSIINT,static_cast<int64_t>(-v.value_i)); 
				return ret;
			}
			case RSILONG:{
				IValue ret(RSILONG,static_cast<int64_t>(-v.value_l)); 
				return ret;
			}
			case RSIDOUBLE:{
				IValue ret(RSIDOUBLE,-v.value_d); 
				return ret;
			}
			default:
				break; 
		}
	}

	void* operator&(){
		return &v.value_b;
	}

	int RSIint() const{
		if(type < RSIDOUBLE) return static_cast<int>(getIntVal());
		else 				 return static_cast<int>(getDoubleVal());
	}

	double RSIDouble() const{
		return getDoubleVal();
	}

	std::string RSIstring() const{
		if(type < RSIDOUBLE) return std::to_string(getIntVal());
		else                 return std::to_string(getDoubleVal());
	}

	size_t DataSize(){
		switch(type){
			case RSIBOOL:
			case RSICHAR:
				return sizeof(uint8_t);
			case RSISHORT:
			case RSIUSHORT:
				return sizeof(int16_t);
			case RSIINT:
			case RSIUINT:
				return sizeof(int32_t);
			case RSILONG:
			case RSIDOUBLE:
				return sizeof(int64_t);
			default:
				break;
		}
	}
	IValue htonival();
	IValue ntohival();
private:
	int64_t getIntVal() const {
		assert(type < RSIDOUBLE);
		int64_t ret;
		switch(type){
			case RSIBOOL: ret = static_cast<int64_t>(v.value_b);break;
			case RSICHAR: ret = static_cast<int64_t>(v.value_c);break;
			case RSISHORT: ret = static_cast<int64_t>(v.value_s);break;
			case RSIUSHORT: ret = static_cast<int64_t>(v.value_us);break;
			case RSIINT: ret = static_cast<int64_t>(v.value_i);break;
			case RSIUINT: ret = static_cast<int64_t>(v.value_ui);break;
			case RSILONG: ret = v.value_l;
		}
		return ret;
	}

	double getDoubleVal() const {
		double ret;
		if(type < RSIDOUBLE)
			ret = static_cast<double>(getIntVal());
		else 
			ret = v.value_d;
		return ret;
	}

private:
	uint8_t type;
	union{
		bool value_b;
		uint8_t value_c;
		int16_t value_s;
		uint16_t value_us;
		int32_t value_i;
		uint32_t value_ui;
		int64_t value_l;
		double value_d;
	}v;
};

inline IValue& IValue::operator=(const IValue& rhs){
		switch(type){
			case RSIBOOL:
				v.value_b = (rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal()) ? true:false; 
				break;
			case RSICHAR:
				v.value_c = static_cast<uint8_t>(rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal());
				break;
			case RSISHORT:
				v.value_s = static_cast<int16_t>(rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal());
				break;
			case RSIUSHORT:
				v.value_us = static_cast<uint16_t>(rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal());
				break;
			case RSIINT:
				v.value_i = static_cast<int32_t>(rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal());
				break;
			case RSIUINT:
				v.value_ui = static_cast<uint32_t>(rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal());
				break;
			case RSILONG:
				v.value_l = static_cast<int64_t>(rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal());
				break;
			case RSIDOUBLE:
				v.value_d = static_cast<double>(rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal());
				break;
			default:
				break;
		}
		return *this;
	}

inline IValue& IValue::operator+=(const IValue& rhs){
	switch(type){
		case RSIBOOL: 
			v.value_b = v.value_b + (rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal()) ? true:false; 
			break;
		case RSICHAR: 
			v.value_c = static_cast<uint8_t>(v.value_c + (rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal()));
			break;
		case RSISHORT:
			v.value_s = static_cast<int16_t>(v.value_s + (rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal()));
			break;
		case RSIUSHORT:
			v.value_us = static_cast<uint16_t>(v.value_s + rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal());
			break;
		case RSIINT:  
			v.value_i = static_cast<int32_t>(v.value_i + (rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal()));
			break;
		case RSIUINT:
			v.value_ui = static_cast<uint32_t>(v.value_i + (rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal()));
			break;
		case RSILONG: 
			v.value_l = static_cast<int64_t>(v.value_l + (rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal()));
			break;
		case RSIDOUBLE:
			v.value_d = static_cast<double>(v.value_d + (rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal()));
			break;
	}
	return *this;
}


inline IValue& IValue::operator-=(const IValue& rhs){
	switch(type){
		case RSIBOOL: 
			v.value_b = v.value_b - (rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal()) ? true:false; 
			break;
		case RSICHAR: 
			v.value_c = static_cast<uint8_t>(v.value_c - (rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal()));
			break;
		case RSISHORT:
			v.value_s = static_cast<int16_t>(v.value_s - (rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal()));
			break;
		case RSIUSHORT:
			v.value_us = static_cast<uint16_t>(v.value_s - (rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal()));
			break;
		case RSIINT:  
			v.value_i = static_cast<int32_t>(v.value_i - (rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal()));
			break;
		case RSIUINT:
			v.value_ui = static_cast<uint32_t>(v.value_i - (rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal()));
			break;
		case RSILONG: 
			v.value_l = static_cast<int64_t>(v.value_l - (rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal()));
			break;
		case RSIDOUBLE:
			v.value_d = static_cast<double>(v.value_d - (rhs.type < RSIDOUBLE ? rhs.getIntVal():rhs.getDoubleVal()));
			break;
	}
	return *this;
}

inline IValue IValue::htonival(){
	assert(type == RSISHORT || type == RSIINT || type == RSIUSHORT || type == RSIUINT);
	switch(type){
		case RSISHORT:{
			IValue ret(RSISHORT,static_cast<int64_t>(htons(v.value_s)));
			return ret;
		}
		case RSIUSHORT:{
			IValue ret(RSIUSHORT,static_cast<int64_t>(htons(v.value_us)));
			return ret;
		}
		case RSIINT:{
			IValue ret(RSIINT,static_cast<int64_t>(htonl(v.value_i)));
			return ret;
		}
		case RSIUINT:{
			IValue ret(RSIUINT,static_cast<int64_t>(htonl(v.value_ui)));
			return ret;
		}
	}
}

inline IValue IValue::ntohival(){
	assert(type == RSISHORT || type == RSIINT || type == RSIUSHORT || type == RSIUINT);
	switch(type){
		case RSISHORT:{
			IValue ret(RSISHORT,static_cast<int64_t>(ntohs(v.value_s)));
			return ret;
		}
		case RSIUSHORT:{
			IValue ret(RSIUSHORT,static_cast<int64_t>(ntohs(v.value_us)));
			return ret;
		}
		case RSIINT:{
			IValue ret(RSIINT,static_cast<int64_t>(ntohl(v.value_i)));
			return ret;
		}
		case RSIUINT:{
			IValue ret(RSIUINT,static_cast<int64_t>(ntohl(v.value_ui)));
			return ret;
		}
	}
}

inline std::ostream& operator<<(std::ostream& os,const IValue& var){
	switch(var.type){
		case RSIBOOL:
			os << "bool " << var.v.value_b;
			break;
		case RSICHAR:
			os << "uint8 " << var.v.value_c;
			break;
		case RSISHORT:
			os << "int16 " << var.v.value_s;
			break;
		case RSIUSHORT:
			os << "uint16 " << var.v.value_us;
			break;
		case RSIINT:
			os << "int32 " << var.v.value_i;
			break;
		case RSIUINT:
			os << "uint32 " << var.v.value_ui;
			break;
		case RSILONG:
			os << "int64 " << var.v.value_l;
			break;
		case RSIDOUBLE:
			os << "double " << var.v.value_d;
			break;
	} 
}

inline IValue operator+(const IValue& lhs, const IValue& rhs){
	uint8_t type = std::max(lhs.type,rhs.type);
	if(type < RSIDOUBLE){
		IValue ret(type,lhs.getIntVal()+rhs.getIntVal());
		return ret;
	}else{
		IValue ret(type,lhs.getDoubleVal()+rhs.getDoubleVal());
		return ret;
	}
}

inline IValue operator-(const IValue& lhs, const IValue& rhs){
	uint8_t type = std::max(lhs.type,rhs.type);
	if(type < RSIDOUBLE){
		IValue ret(type,lhs.getIntVal()-rhs.getIntVal());
		return ret;
	}else{
		IValue ret(type,lhs.getDoubleVal()-rhs.getDoubleVal());
		return ret;
	}
}


inline IValue operator*(const IValue& lhs, const IValue& rhs){
	uint8_t type = std::max(lhs.type,rhs.type);
	if(type < RSIDOUBLE){
		IValue ret(type,lhs.getIntVal()*rhs.getIntVal());
		return ret;
	}else{
		IValue ret(type,lhs.getDoubleVal()*rhs.getDoubleVal());
		return ret;
	}
}

inline IValue operator/(const IValue& lhs, const IValue& rhs){
	uint8_t type = std::max(lhs.type,rhs.type);
	if(type < RSIDOUBLE){
		IValue ret(type,lhs.getIntVal()/rhs.getIntVal());
		return ret;
	}else{
		IValue ret(type,lhs.getDoubleVal()/rhs.getDoubleVal());
		return ret;
	}
}

inline bool operator==(const IValue& lhs, const IValue& rhs){
	if(lhs.type < RSIDOUBLE && rhs.type < RSIDOUBLE)
		return lhs.getIntVal() == rhs.getIntVal();
	else 
		return false;
}

inline bool operator!=(const IValue& lhs, const IValue& rhs){
	return !(lhs == rhs);
}

inline bool operator<(const IValue& lhs, const IValue& rhs){
	return lhs.getDoubleVal() < rhs.getDoubleVal();
}

inline bool operator>(const IValue& lhs, const IValue& rhs){
	return lhs.getDoubleVal() > rhs.getDoubleVal();
}

inline bool operator<=(const IValue& lhs, const IValue& rhs){
	return lhs == rhs || lhs < rhs;
}

inline bool operator>=(const IValue& lhs, const IValue& rhs){
	return lhs == rhs || lhs > rhs;
}


static std::unordered_map<std::string, uint8_t> RSI_typetable = {
	{"BOOL",RSIBOOL},
	{"UINT8",RSICHAR},
	{"INT8",RSICHAR},
	{"INT16",RSISHORT},
	{"UINT16",RSIUSHORT},
	{"INT32",RSIINT},
	{"UINT32",RSIUINT},
	{"INT64",RSILONG},
	{"UINT64",RSILONG},
	{"DOUBLE",RSIDOUBLE},
};


inline IValue stoival(uint8_t type, const std::string& numstr){
	if(type < RSIDOUBLE){
		int64_t tmp = static_cast<int64_t>(std::stoi(numstr,nullptr,0));
		IValue ret(type,tmp);
		return ret;
	}else{
		double tmp = std::stod(numstr);
		IValue ret(type,tmp);
		return ret;
	}
}

inline IValue stoival(const std::string& typestr, const std::string& numstr){
	uint8_t type = RSI_typetable[typestr];
	return stoival(type,numstr);
}

#else

#define IValue	double

#endif

#endif