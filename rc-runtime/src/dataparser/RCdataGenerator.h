
#pragma once


#include "antlr4-runtime.h"
#include "RCdataBaseVisitor.h"

#include "rc_innerdata.h"
#include "../../../include/logger.h"
#include "rc_exception.h"
#include "rc_helper.h"


class RCdataGenerator : public RCdataBaseVisitor {
public:
	RCAddressSpace &addrspace;     // addrspace[0] is the returned value of all the library function  in global
	
	StringPoolSpace &stringpool;
	APDataSpace &apaddr;
	CPDataSpace &cpaddr;
	ToolDataSpace &tooladdr;
	CoorDataSpace &cooraddr;

	std::unordered_map<std::string, int> &dataIndexMap;		// parser xml file and generator dataMap
	std::unordered_map<std::string, int> &constIndexMap;	// the index of all the constants in addr space 

public:
	RCdataGenerator(RC_SymbolTable &sym) :
				addrspace(sym.addrspace),
				stringpool(sym.stringpool),
				apaddr(sym.apaddr),
				cpaddr(sym.cpaddr),
				tooladdr(sym.tooladdr),
				cooraddr(sym.cooraddr),
				dataIndexMap(sym.dataIndexMap),
				constIndexMap(sym.constIndexMap)

	{}

public:
	virtual antlrcpp::Any visitProgram(RCdataParser::ProgramContext *ctx) override {
		LOGGER_INF("program");
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitStatBlock(RCdataParser::StatBlockContext *ctx) override {
		LOGGER_INF("statblock");
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitBoolStat(RCdataParser::BoolStatContext *ctx) override {
		LOGGER_INF("boolstat");
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitCharStat(RCdataParser::CharStatContext *ctx) override {
		LOGGER_INF("charstat");
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitIntStat(RCdataParser::IntStatContext *ctx) override {
		LOGGER_INF("intstat");
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitRealStat(RCdataParser::RealStatContext *ctx) override {
		LOGGER_INF("realstat");
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitStringStat(RCdataParser::StringStatContext *ctx) override {
		LOGGER_INF("stringstat");
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitJtposeStat(RCdataParser::JtposeStatContext *ctx) override {
		LOGGER_INF("jtposestat");
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitTrposeStat(RCdataParser::TrposeStatContext *ctx) override {
		LOGGER_INF("trposestat");
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitToolStat(RCdataParser::ToolStatContext *ctx) override {
		LOGGER_INF("toolstat");
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitCoordStat(RCdataParser::CoordStatContext *ctx) override {
		LOGGER_INF("coordstat");
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitBoolExpr(RCdataParser::BoolExprContext *ctx) override {
		LOGGER_INF("[> BoolExpr <]");

		// Get bool variable name
		std::string varName = ctx->ID()->getText();
		// Get bool variable value
		IBool varVal = 0;
		if(ctx->ASSIGN() == NULL) {
			varVal = 0;
		} else {
			varVal = (IBool)visit(ctx->boolval());
		}
		// Check Duplicate Definition
		if(dataIndexMap.find(varName) == dataIndexMap.end()) {
			int index = addrspace.size();
			dataIndexMap.insert({varName, index});
			addrspace.push_back(RC_IValue(TBOOL, varVal));
		} else {
			int line = ctx->ID()->getSymbol()->getLine();
			throw rc_vardup_exception(line, 0, varName);
		}

		return NULL;
	}

	virtual antlrcpp::Any visitTrueExpr(RCdataParser::TrueExprContext *ctx) override {
		LOGGER_INF("TrueExpr");
		return (IBool)1;
	}

	virtual antlrcpp::Any visitFalseExpr(RCdataParser::FalseExprContext *ctx) override {
		LOGGER_INF("FalseExpr");
		return (IBool)0;
	}

	virtual antlrcpp::Any visitCharExpr(RCdataParser::CharExprContext *ctx) override {
		LOGGER_INF("CharExpr");
		// Get char variable name
		std::string varName = ctx->ID()->getText();
		// Get char variable value
		IChar varVal = 0;
		if(ctx->ASSIGN() == NULL) {
			varVal = 0;
		} else {
			std::string ch = ctx->CH()->getText();
			varVal = (IChar)ch[1];
		}
		// Check Duplicate Definition
		if(dataIndexMap.find(varName) == dataIndexMap.end()) {
			int index = addrspace.size();
			dataIndexMap.insert({varName, index});
			addrspace.push_back(RC_IValue(TCHAR, varVal));
		} else {
			int line = ctx->ID()->getSymbol()->getLine();
			throw rc_vardup_exception(line, 0, varName);
		}

		return NULL;
	}

	virtual antlrcpp::Any visitIntExpr(RCdataParser::IntExprContext *ctx) override {
		LOGGER_INF("IntExpr");
		// Get char variable name
		std::string varName = ctx->ID()->getText();
		// Get char variable value
		IInt varVal = 0;
		if(ctx->ASSIGN() == NULL) {
			varVal = 0;
		} else {
			std::string num = ctx->NUM()->getText();
			try{
				varVal = Utility::parseInt(num);
			} catch(std::exception &e) {
				int line = ctx->NUM()->getSymbol()->getLine();
				int col = ctx->NUM()->getSymbol()->getCharPositionInLine();
				throw rc_numformat_exception(line, col, num);
			}
			
		}
		// Check Duplicate Definition
		if(dataIndexMap.find(varName) == dataIndexMap.end()) {
			int index = addrspace.size();
			dataIndexMap.insert({varName, index});
			addrspace.push_back(RC_IValue(TINT, varVal));
		} else {
			int line = ctx->ID()->getSymbol()->getLine();
			throw rc_vardup_exception(line, 0, varName);
		}
		return NULL;
	}

	virtual antlrcpp::Any visitRealExpr(RCdataParser::RealExprContext *ctx) override {
		LOGGER_INF("RealExpr");
		// Get real variable name
		std::string varName = ctx->ID()->getText();
		// Get real variable value
		IDouble varVal = 0;
		if(ctx->ASSIGN() == NULL) {
			varVal = 0;
		} else {
			std::string num = ctx->NUM()->getText();
			try{
				varVal = Utility::parseDouble(num);
			} catch(std::exception &e) {
				int line = ctx->NUM()->getSymbol()->getLine();
				int col = ctx->NUM()->getSymbol()->getCharPositionInLine();
				throw rc_numformat_exception(line, col, num);
			}
		}
		// Check Duplicate Definition
		if(dataIndexMap.find(varName) == dataIndexMap.end()) {
			int index = addrspace.size();
			dataIndexMap.insert({varName, index});
			addrspace.push_back(RC_IValue(TDOUBLE, varVal));
		} else {
			int line = ctx->ID()->getSymbol()->getLine();
			throw rc_vardup_exception(line, 0, varName);
		}
		return NULL;
	}

	virtual antlrcpp::Any visitStringExpr(RCdataParser::StringExprContext *ctx) override {
		LOGGER_INF("StringExpr");
		// Get string variable name
		std::string varName = ctx->ID()->getText();
		// Get string variable value
		IString strIndex = 0;
		std::string strVal;
		if(ctx->ASSIGN() == NULL) {
			strVal = "";
		} else {
			strVal = ctx->CSTRING()->getText();
			if(strVal.size() > 2) {
				strVal = strVal.substr(1, strVal.size()-2);
			} 
		}
		// Check Duplicate Definition
		if(dataIndexMap.find(varName) == dataIndexMap.end()) {
			int index = addrspace.size();
			dataIndexMap.insert({varName, index});

			strIndex = stringpool.size();
			stringpool.push_back(strVal);
			addrspace.push_back(RC_IValue(TSTRING, strIndex));
		} else {
			int line = ctx->ID()->getSymbol()->getLine();
			throw rc_vardup_exception(line, 0, varName);
		}
		return NULL;
	}

	virtual antlrcpp::Any visitJtposeExpr1(RCdataParser::JtposeExpr1Context *ctx) override {
		LOGGER_INF("JtposeExpr1");
		// Get Jtpose variable name
		std::string varName = ctx->ID()->getText();

		std::vector<double> pose;
		for(int i = 0; i < ctx->NUM().size(); i ++) {
			std::string strNum = ctx->NUM(i)->getText();
			double numVal = std::stod(strNum);
			pose.push_back(numVal);
		}

		// Check Duplicate Definition
		if(dataIndexMap.find(varName) == dataIndexMap.end()) {
			int index = addrspace.size();
			dataIndexMap.insert({varName, index});

			IJtpose poseIndex = apaddr.size();
			apaddr.push_back(pose);
			addrspace.push_back(RC_IValue(TJTPOSE, poseIndex));
		} else {
			int line = ctx->ID()->getSymbol()->getLine();
			throw rc_vardup_exception(line, 0, varName);
		}
		return NULL;
	}

	virtual antlrcpp::Any visitJtposeExpr2(RCdataParser::JtposeExpr2Context *ctx) override {
		LOGGER_INF("JtposeExpr2");
		// Get Jtpose variable name
		std::string varName = ctx->PID()->getText();

		std::vector<double> pose;
		for(int i = 0; i < ctx->NUM().size(); i ++) {
			std::string strNum = ctx->NUM(i)->getText();
			double numVal = std::stod(strNum);
			pose.push_back(numVal);
		}

		// Check Duplicate Definition
		if(dataIndexMap.find(varName) == dataIndexMap.end()) {
			int index = addrspace.size();
			dataIndexMap.insert({varName, index});

			IJtpose poseIndex = apaddr.size();
			apaddr.push_back(pose);
			addrspace.push_back(RC_IValue(TJTPOSE, poseIndex));
		} else {
			int line = ctx->PID()->getSymbol()->getLine();
			throw rc_vardup_exception(line, 0, varName);
		}
		return NULL;
	}

	virtual antlrcpp::Any visitTrposeExpr1(RCdataParser::TrposeExpr1Context *ctx) override {
		LOGGER_INF("TrposeExpr1");
		// Get Trpose variable name
		std::string varName = ctx->ID()->getText();

		std::vector<double> pose;
		for(int i = 0; i < ctx->NUM().size(); i ++) {
			std::string strNum = ctx->NUM(i)->getText();
			double numVal = std::stod(strNum);
			pose.push_back(numVal);
		}

		// Check Duplicate Definition
		if(dataIndexMap.find(varName) == dataIndexMap.end()) {
			int index = addrspace.size();
			dataIndexMap.insert({varName, index});

			ITrpose poseIndex = cpaddr.size();
			cpaddr.push_back(pose);
			addrspace.push_back(RC_IValue(TTRPOSE, poseIndex));
		} else {
			int line = ctx->ID()->getSymbol()->getLine();
			throw rc_vardup_exception(line, 0, varName);
		}
		return NULL;
	}

	virtual antlrcpp::Any visitTrposeExpr2(RCdataParser::TrposeExpr2Context *ctx) override {
		LOGGER_INF("TrposeExpr2");
		// Get Trpose variable name
		std::string varName = ctx->BPID()->getText();

		std::vector<double> pose;
		for(int i = 0; i < ctx->NUM().size(); i ++) {
			std::string strNum = ctx->NUM(i)->getText();
			double numVal = std::stod(strNum);
			pose.push_back(numVal);
		}

		// Check Duplicate Definition
		if(dataIndexMap.find(varName) == dataIndexMap.end()) {
			int index = addrspace.size();
			dataIndexMap.insert({varName, index});

			ITrpose poseIndex = cpaddr.size();
			cpaddr.push_back(pose);
			addrspace.push_back(RC_IValue(TTRPOSE, poseIndex));
		} else {
			int line = ctx->BPID()->getSymbol()->getLine();
			throw rc_vardup_exception(line, 0, varName);
		}
		return NULL;
	}

	virtual antlrcpp::Any visitTrposeExpr3(RCdataParser::TrposeExpr3Context *ctx) override {
		LOGGER_INF("TrposeExpr3");
		// Get Trpose variable name
		std::string varName = ctx->EXID()->getText();

		std::vector<double> pose;
		for(int i = 0; i < ctx->NUM().size(); i ++) {
			std::string strNum = ctx->NUM(i)->getText();
			double numVal = std::stod(strNum);
			pose.push_back(numVal);
		}

		// Check Duplicate Definition
		if(dataIndexMap.find(varName) == dataIndexMap.end()) {
			int index = addrspace.size();
			dataIndexMap.insert({varName, index});

			ITrpose poseIndex = cpaddr.size();
			cpaddr.push_back(pose);
			addrspace.push_back(RC_IValue(TTRPOSE, poseIndex));
		} else {
			int line = ctx->EXID()->getSymbol()->getLine();
			throw rc_vardup_exception(line, 0, varName);
		}
		return NULL;
	}

	virtual antlrcpp::Any visitToolExpr(RCdataParser::ToolExprContext *ctx) override {
		LOGGER_INF("ToolExpr");
		// Get Tool variable name
		std::string varName = ctx->ID()->getText();

		std::vector<double> tool;
		for(int i = 0; i < ctx->NUM().size(); i ++) {
			std::string strNum = ctx->NUM(i)->getText();
			double numVal = std::stod(strNum);
			tool.push_back(numVal);
		}

		// Check Duplicate Definition
		if(dataIndexMap.find(varName) == dataIndexMap.end()) {
			int index = addrspace.size();
			dataIndexMap.insert({varName, index});

			ITooldata toolIndex = tooladdr.size();
			tooladdr.push_back(tool);
			addrspace.push_back(RC_IValue(TTOOLDATA, toolIndex));
		} else {
			int line = ctx->ID()->getSymbol()->getLine();
			throw rc_vardup_exception(line, 0, varName);
		}
		return NULL;
	}

	virtual antlrcpp::Any visitCoordExpr(RCdataParser::CoordExprContext *ctx) override {
		LOGGER_INF("CoordExpr");
		// Get Tool variable name
		std::string varName = ctx->ID(0)->getText();
		int line = ctx->ID(0)->getSymbol()->getLine();

		Coordinate coord;

		if(ctx->op->getType() == RCdataParser::COORDO){
			coord.type = 'O';
		} else {
			coord.type = 'T';
		}

		int index1 = 1; 		// index of IDs
		int index2 = 0; 		// index of BPIDs
		std::string strp; 		// temp var

		if(ctx->op1->getType() == RCdataParser::BPID) {
			strp = ctx->BPID(index2)->getText();
			index2 ++;
		} else {
			strp = ctx->ID(index1)->getText();
			index1 ++;
		}
		if(dataIndexMap.find(strp) != dataIndexMap.end()) {
			coord.p1 = dataIndexMap[strp];
		} else {
			throw rc_pointnotdefined_exception(line, 0, strp);
		}

		if(ctx->op2->getType() == RCdataParser::BPID) {
			strp = ctx->BPID(index2)->getText();
			index2 ++;
		} else {
			strp = ctx->ID(index1)->getText();
			index1 ++;
		}
		if(dataIndexMap.find(strp) != dataIndexMap.end()) {
			coord.p2 = dataIndexMap[strp];
		} else {
			throw rc_pointnotdefined_exception(line, 0, strp);
		}

		if(ctx->op3->getType() == RCdataParser::BPID) {
			strp = ctx->BPID(index2)->getText();
			index2 ++;
		} else {
			strp = ctx->ID(index1)->getText();
			index1 ++;
		}
		if(dataIndexMap.find(strp) != dataIndexMap.end()) {
			coord.p3 = dataIndexMap[strp];
		} else {
			throw rc_pointnotdefined_exception(line, 0, strp);
		}

		// Check Duplicate Definition
		if(dataIndexMap.find(varName) == dataIndexMap.end()) {
			int index = addrspace.size();
			dataIndexMap.insert({varName, index});

			ICoordata coordIndex = cooraddr.size();
			cooraddr.push_back(coord);
			addrspace.push_back(RC_IValue(TCOORDATA, coordIndex));
		} else {
			throw rc_vardup_exception(line, 0, varName);
		}
		return NULL;
	}


};