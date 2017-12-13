#pragma once


#include <vector>
#include "rc_exception.h"

class RCEntityBase;


/* Internal Value Type Tag */
#define TBOOL   	0
#define TCHAR   	1
#define TINT    	2
#define TDOUBLE 	3
#define TSTRING 	4	
#define TJTPOSE    	5
#define TTRPOSE		6
#define TTOOLDATA   7
#define TCOORDATA	8


/* Internal Basic Type */
typedef uint8_t  IBool;
typedef uint8_t  IChar;
typedef int32_t  IInt;
typedef double   IDouble;
typedef uint32_t IString;
typedef uint32_t IJtpose;
typedef uint32_t ITrpose;
typedef uint32_t ITooldata;
typedef uint32_t ICoordata;


/*-----------------------------------------------------------------------------
 * Value Helper Function Macro
 *---------------------------------------------------------------------------*/
/* type checker */
#define ivtype(v) 			((v).type) /* type getter */
#define checktype(v, t) 	(ivtype(v) == t)
#define isbool(v)    		checktype(v, TBOOL)
#define ischar(v)   		checktype(v, TCHAR)
#define isint(v) 			checktype(v, TINT)
#define isdouble(v) 		checktype(v, TDOUBLE)
#define isstring(v)			checktype(v, TSTRING)
#define isjtpose(v)			checktype(v, TJTPOSE)
#define istrpose(v)			checktype(v, TTRPOSE)
#define istooldata(v) 		checktype(v, TTOOLDATA)
#define iscoordata(v)		checktype(v, TCOORDATA)

/* type setter */
#define settype(v, t) 		{(v).type = t;}
#define settbool(v)			settype(v, TBOOL)
#define settchar(v)			settype(v, TCHAR)
#define settint(v)    		settype(v, TINT)
#define settdouble(v) 		settype(v, TDOUBLE)
#define settstring(v) 		settype(v, TSTRING)
#define settjtpose(v)		settype(v, TJTPOSE)
#define setttrpose(v)		settype(v, TTRPOSE)
#define setttooldata(v)		settype(v, TTOOLDATA)
#define settcoordata(v)		settype(v, TCOORDATA)

/* value getter */
#define vbool(value)   		((value).v.value_b)
#define vchar(value)		((value).v.value_c)
#define vint(value)    		((value).v.value_i)
#define vdouble(value) 		((value).v.value_d)
#define vstring(value) 		((value).v.value_s)
#define vjtpos(value)   	((value).v.value_ap)
#define vtrpose(value) 		((value).v.value_cp)
#define vtooldata(value) 	((value).v.value_tool)
#define vcoordata(value)	((value).v.value_coord)

// #define vnumber(t, v)  ((t)((t==TCHAR)*vchar(v) + (t==TBOOL)*vbool(v) + (t==TINT)*vint(v) + (t==TDOUBLE)*vdouble(v))) /* CAN'T be left value */
#define vnumber(t, v)  ((t)((t==TINT)*vint(v)))
/* value setter */
#define setvbool(value, data_b)	  		{(value).v.value_b = (data_b);}
#define setvchar(value, data_c)			{(value).v.value_c = (data_c);}
#define setvint(value, data_i)    		{(value).v.value_i = (data_i);}
#define setvdouble(value, data_d) 		{(value).v.value_d = (data_d);}
#define setvstring(value, data_s) 		{(value).v.value_s = (data_s);}
#define setvjtpose(value, data_ap)		{(value).v.value_ap = (data_ap);}
#define setvtrpose(value, data_cp)		{(value).v.value_cp = (data_cp);}
#define setvtooldata(value, data_tool)	{(value).v.value_tool = (data_tool);}
#define setvcoordata(value, data_coord)	{(value).v.value_coord = (data_coord);}



struct RC_IValue {
	uint8_t type;
    union {
    	IBool value_b;
 		IChar value_c;
        IInt value_i;
        IDouble value_d;
        IString value_s;
        IJtpose value_ap; 
        ITrpose value_cp;
        ITooldata value_tool;
        ICoordata value_coord;
    } v;
public:
	RC_IValue(){}
	RC_IValue(uint8_t t, uint8_t val) : type(t) { v.value_b = val; } 
	RC_IValue(uint8_t t, int32_t val) : type(t) { v.value_i = val; } 
	RC_IValue(uint8_t t, uint32_t val) : type(t) { v.value_s = val; } 
	RC_IValue(uint8_t t, double val) : type(t) { v.value_d = val; } 

public:
	RC_IValue &operator=(const RC_IValue& rhs) {
		switch(type) {
			case TBOOL: {
				this->v.value_b = (rhs.type==TBOOL) * rhs.v.value_b + (rhs.type == TCHAR) * rhs.v.value_c
								+ (rhs.type==TINT) * rhs.v.value_i + (rhs.type==TDOUBLE) * rhs.v.value_d;
				break;
			}
			case TCHAR: {
				this->v.value_c = (rhs.type==TBOOL) * rhs.v.value_b + (rhs.type == TCHAR) * rhs.v.value_c
								+ (rhs.type==TINT) * rhs.v.value_i + (rhs.type==TDOUBLE) * rhs.v.value_d;
				break;
			}
			case TINT: {
				this->v.value_i = (rhs.type==TBOOL) * rhs.v.value_b + (rhs.type == TCHAR) * rhs.v.value_c
								+ (rhs.type==TINT) * rhs.v.value_i + (rhs.type==TDOUBLE) * rhs.v.value_d;
				break;
			}
			case TDOUBLE: {
				this->v.value_d = (rhs.type==TBOOL) * rhs.v.value_b + (rhs.type == TCHAR) * rhs.v.value_c
								+ (rhs.type==TINT) * rhs.v.value_i + (rhs.type==TDOUBLE) * rhs.v.value_d;
				break;
			}
			case TSTRING: {
				this->v.value_s = rhs.v.value_s;
				break;
			}
			default : {
				throw rc_exception();
				break;
			}
		}
	}


public:
	friend std::ostream& operator<<(std::ostream& os, const RC_IValue &iv) {
		switch(iv.type) {
			case TBOOL:
				os << "TBOOL" << " : " << (int)iv.v.value_b ;
				break;
			case TCHAR:
				os << "TCHAR" << " : " << iv.v.value_c ;
				break;
			case TINT:
				os << "TINT" << " : " << iv.v.value_i ;
				break;
			case TDOUBLE:
				os << "TDOUBLE" << " : " << iv.v.value_d ;
				break;
			case TSTRING:
				os << "TSTRING" << " : " << iv.v.value_s ;
				break;
			case TJTPOSE:
				os << "TJTPOSE" << " : " << iv.v.value_ap ;
				break;
			case TTRPOSE:
				os << "TTRPOSE" << " : " << iv.v.value_cp ;
				break;
			case TTOOLDATA:
				os << "TTOOLDATA" << " : " << iv.v.value_tool ;
				break;
			case TCOORDATA:
				os << "TCOORDATA" << " : " << iv.v.value_coord ;
				break;
			default:
				os << "null type" ;
			  	break;
		}
	}
};






/* coordinate type def */
typedef struct {
	uint8_t type ;   // 'T' or 'O'
	uint32_t p1;
	uint32_t p2;
	uint32_t p3;
} Coordinate;


/* global data space type */
typedef std::vector<RC_IValue> RCAddressSpace;				// main address space

typedef std::vector<std::string> StringPoolSpace;			// string data space
typedef std::vector<std::vector<double>> APDataSpace; 		// axis data space
typedef std::vector<std::vector<double>> CPDataSpace; 		// cart data space
typedef std::vector<std::vector<double>> ToolDataSpace; 	// tool data space
typedef std::vector<Coordinate> CoorDataSpace; 	// coor data space




class RC_SymbolTable {
public:
	
	RC_SymbolTable( RCAddressSpace &a,     // addrspace[0] is the returned value of all the library function  in global
					StringPoolSpace &s,
					APDataSpace &ap,
					CPDataSpace &cp,
					ToolDataSpace &to,
					CoorDataSpace &co,

			  		std::unordered_map<std::string, int> &d,		
					std::unordered_map<std::string, int> &c,	
					std::unordered_map<std::string, int> &func,
					std::unordered_map<std::string, RCEntityBase*> &fb,
					std::unordered_map<int, std::string> &rdata) : 
						addrspace(a), 

						stringpool(s),
						apaddr(ap),
						cpaddr(cp),
						tooladdr(to),
						cooraddr(co),

						dataIndexMap(d), 
						constIndexMap(c), 
						funcMap(func),
						fbMap(fb),
						rDataIndexMap(rdata) 
	{
		addrspace.push_back(RC_IValue(TINT, 0));

		int index = addrspace.size();
		dataIndexMap.insert({"FALSE", index});
		addrspace.push_back(RC_IValue(TBOOL, 0));

		index = addrspace.size();
		dataIndexMap.insert({"TRUE", index});
		addrspace.push_back(RC_IValue(TBOOL, 1));

		// funcMap.insert({"COMM", 0});
	}

public:
	RCAddressSpace &addrspace;     // addrspace[0] is the returned value of all the library function  in global
	
	StringPoolSpace &stringpool;
	APDataSpace &apaddr;
	CPDataSpace &cpaddr;
	ToolDataSpace &tooladdr;
	CoorDataSpace &cooraddr;

	std::unordered_map<std::string, int> &dataIndexMap;		// parser xml file and generator dataMap
	std::unordered_map<std::string, int> &constIndexMap;	// the index of all the constants in addr space 
	std::unordered_map<std::string, int> &funcMap;  	    // all library function map to check if designated function is existed
	std::unordered_map<std::string, RCEntityBase*> &fbMap;     // all library function map to check if designated function is existed

	std::unordered_map<int, std::string> &rDataIndexMap;  // index ---> data
	// std::unordered_map<std::string, CodeModel> &progList; 	// <programName, code>
};
