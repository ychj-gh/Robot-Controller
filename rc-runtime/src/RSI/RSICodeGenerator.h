
#pragma once

#include <vector>
#include <stack>
#include <unordered_map>
#include <exception>
#include <stdexcept>

#include <cstdlib>

#include "antlr4-runtime.h"
#include "RSIBaseVisitor.h"

#include "RSIRuntimeModel.h"


using namespace antlr4;






class RSICodeGenerator : public RSIBaseVisitor {
public:
	CodeShadow &cs;
	std::vector<IValue> &addrspace;     // RSI address space --- simple version; addrspace[0] is the returned value of all the library function  in global

	std::unordered_map<std::string, int> &dataIndexMap;	// parser xml file and generator dataMap
	std::unordered_map<std::string, int> &constIndexMap;	// the index of all the constants in addr space 
	std::unordered_map<std::string, EntityBase*> &fbMap;    		// parser xml file and generator functionblock map
	std::unordered_map<std::string, int> &funcMap;  	    // all library function map to check if designated function is existed

	std::stack<std::vector<BaseStatement*>*> compileStack;	

public:
	RSICodeGenerator(CodeShadow &c, SymbolTable &s) : cs(c), addrspace(s.addrspace),
								dataIndexMap(s.dataIndexMap), constIndexMap(s.constIndexMap),
								fbMap(s.fbMap), funcMap(s.funcMap)
								{}

	
public:
	virtual antlrcpp::Any visitProgram(RSIParser::ProgramContext *ctx) override {
#ifdef RSI_DEBUG
		std::cout << "program" << std::endl;
#endif
		compileStack.push(&cs);
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitStatBlock(RSIParser::StatBlockContext *ctx) override {
#ifdef RSI_DEBUG
		std::cout << "statBlock" << std::endl;
#endif
		
		antlrcpp::Any result = defaultResult();
	    size_t n = ctx->children.size();
	    // std::cout << "n : " << n << std::endl;
	    for (size_t i = 0; i < n; i++) {
	        if (!shouldVisitNextChild(ctx, result)) {
	          break;
        	}
	        antlrcpp::Any childResult = ctx->children[i]->accept(this);
	        result = aggregateResult(result, childResult);
	        std::vector<BaseStatement*>* cur = compileStack.top();
	        BaseStatement* tmp = result;
	        cur->push_back(tmp);
      	}

      	return result;
	}

	virtual antlrcpp::Any visitAssignStat(RSIParser::AssignStatContext *ctx) override {
#ifdef RSI_DEBUG
		std::cout << "------assignStat-----" << std::endl;
#endif

		AssignStatement* tmpAssignStat = visitChildren(ctx);
		BaseStatement* tempBaseStat = tmpAssignStat;

		return tempBaseStat;
	}

	virtual antlrcpp::Any visitIfStat(RSIParser::IfStatContext *ctx) override {
#ifdef RSI_DEBUG
		std::cout << "------ifStat------" << std::endl;
#endif

		IfStatement* tmpIfStat = visitChildren(ctx);
		BaseStatement* tempBaseStat = tmpIfStat;

		return tempBaseStat;
	}

	virtual antlrcpp::Any visitWhileStat(RSIParser::WhileStatContext *ctx) override {
#ifdef RSI_DEBUG
		std::cout << "--------whileStat---------" << std::endl;
#endif

		WhileStatement* tmpWhileStat = visitChildren(ctx);
		BaseStatement* tempBaseStat = tmpWhileStat;

		return tempBaseStat;
	}

	virtual antlrcpp::Any visitLoopStat(RSIParser::LoopStatContext *ctx) override {
#ifdef RSI_DEBUG
		std::cout << "--------loopStat---------" << std::endl;
#endif

		LoopStatement* tmpLoopStat = visitChildren(ctx);
		BaseStatement* tempBaseStat = tmpLoopStat;

		return tempBaseStat;
	}

	virtual antlrcpp::Any visitCallStat(RSIParser::CallStatContext *ctx) override {
#ifdef RSI_DEBUG
		std::cout << "--------callStat------" << std::endl;
#endif

		CallStatement* tmpCallStat = visitChildren(ctx);
		BaseStatement* tempBaseStat = tmpCallStat;

		return tempBaseStat;
	}

	virtual antlrcpp::Any visitAssignExpr(RSIParser::AssignExprContext *ctx) override {
#ifdef RSI_DEBUG
		std::cout << "assignExpr" << std::endl;
#endif

		AssignStatement *tempStat = new AssignStatement(&addrspace);

		std::string id = ctx->ID()->getText();
		tempStat->left = dataIndexMap[id];

		antlrcpp::Any ret = visit(ctx->expr());
		if(ret.is<CallStatement*>()) {
			CallStatement* tempCallStat = ret;
			tempStat->caller = tempCallStat;
		} else {
			tempStat->right = ret;
		}

		return tempStat;
	}

	virtual antlrcpp::Any visitIfExpr(RSIParser::IfExprContext *ctx) override {
#ifdef RSI_DEBUG
		std::cout << "ifExpr" << std::endl;
#endif
		IfStatement *tempStat = new IfStatement(&addrspace);

		antlrcpp::Any ret = visit(ctx->expr());
		if(ret.is<CallStatement*>()) {
			CallStatement* tempCallStat = ret;
			tempStat->exprCaller = tempCallStat;
		} else {
			tempStat->exprVar = ret;
		}

		/* if section */
		std::vector<BaseStatement*> *thenStatBlock = new std::vector<BaseStatement*>();
		compileStack.push(thenStatBlock);
		visit(ctx->block());
		tempStat->ifThenStat = thenStatBlock;
		compileStack.pop();

		/* elseif section */
		std::vector<BaseStatement*> *elseifStatBlock = new std::vector<BaseStatement*>();
		int n = (ctx->elseif_stat()).size();
		// std::cout << "else if : " << n << std::endl;
		for(int i = 0; i < n; i ++) {
			ElseifStatement *tmp = visit(ctx->elseif_stat(i));
			BaseStatement* base = tmp;
			elseifStatBlock->push_back(base);
		}
		tempStat->elseifThenStat = elseifStatBlock;

		/* else section */
		std::vector<BaseStatement*> *elseStatBlock = new std::vector<BaseStatement*>();
		compileStack.push(elseStatBlock);
		if(ctx->else_stat() != NULL) visit(ctx->else_stat());
		tempStat->elseThenStat = elseStatBlock;
		compileStack.pop();

		return tempStat;
	}

	virtual antlrcpp::Any visitElseifExpr(RSIParser::ElseifExprContext *ctx) override {
#ifdef RSI_DEBUG
		std::cout << "elseifExpr" << std::endl;
#endif
		ElseifStatement *tempStat = new ElseifStatement(&addrspace);

		antlrcpp::Any ret = visit(ctx->expr());
		if(ret.is<CallStatement*>()) {
			CallStatement* tempCallStat = ret;
			tempStat->exprCaller = tempCallStat;
		} else {
			tempStat->exprVar = ret;
		}

		std::vector<BaseStatement*> *thenStatBlock = new std::vector<BaseStatement*>();
		compileStack.push(thenStatBlock);
		visit(ctx->block());
		tempStat->Stat = thenStatBlock;
		compileStack.pop();

		return tempStat;
	}

	virtual antlrcpp::Any visitElseExpr(RSIParser::ElseExprContext *ctx) override {
#ifdef RSI_DEBUG
		std::cout << "else" << std::endl;
#endif
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitWhileExpr(RSIParser::WhileExprContext *ctx) override {
#ifdef RSI_DEBUG
		std::cout << "whileExpr" << std::endl;
#endif
		WhileStatement *tempStat = new WhileStatement(&addrspace);

		antlrcpp::Any ret = visit(ctx->expr());
		if(ret.is<CallStatement*>()) {
			CallStatement* tempCallStat = ret;
			tempStat->exprCaller = tempCallStat;
		} else {
			tempStat->exprVar = ret;
		}

		std::vector<BaseStatement*> *StatBlock = new std::vector<BaseStatement*>();
		compileStack.push(StatBlock);
		visit(ctx->block());
		tempStat->Stat = StatBlock;
		compileStack.pop();

		return tempStat;
	}

	virtual antlrcpp::Any visitLoopExpr(RSIParser::LoopExprContext *ctx) override {
#ifdef RSI_DEBUG
		std::cout << "loopExpr" << std::endl;
#endif
		LoopStatement *tempStat = new LoopStatement(&addrspace);

		tempStat->varIndex = visit(ctx->var());

		std::vector<BaseStatement*> *StatBlock = new std::vector<BaseStatement*>();
		compileStack.push(StatBlock);
		visit(ctx->block());
		tempStat->Stat = StatBlock;
		compileStack.pop();


		return tempStat;
	}

	virtual antlrcpp::Any visitCallExpr(RSIParser::CallExprContext *ctx) override {
#ifdef RSI_DEBUG
		std::cout << "callExpr" << std::endl;
#endif
		CallStatement *tempStat = new CallStatement(&addrspace);

		std::string call_id = ctx->ID()->getText();
		if(fbMap.find(call_id) != fbMap.end()){
			tempStat->config = fbMap[call_id];
			call_id = fbMap[call_id]->funcName;
		}

		if(funcMap.find(call_id) != funcMap.end()) {
			tempStat->index = funcMap[call_id];
		} else {
			std::cout << "cannot find the called function" << std::endl;
			exit(0);
		}
		std::vector<int> *p = visit(ctx->params());
		tempStat->params = *p;

		return tempStat;
	}

	virtual antlrcpp::Any visitVariable(RSIParser::VariableContext *ctx) override {
#ifdef RSI_DEBUG
		std::cout << "variable" << std::endl;
#endif

		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitCall(RSIParser::CallContext *ctx) override {
#ifdef RSI_DEBUG
		std::cout << "call" << std::endl;
#endif

		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitParamlist(RSIParser::ParamlistContext *ctx) override {
#ifdef RSI_DEBUG
		std::cout << "paramlist" << std::endl;
#endif

		std::vector<int> *tempParams = new std::vector<int>();

		antlrcpp::Any result = defaultResult();
	    size_t n = ctx->children.size();
	    for (size_t i = 0; i < n; i++) {
	        if (!shouldVisitNextChild(ctx, result)) {
	          break;
        	}
        	if(i%2 == 1) continue;  // skip ","
	        antlrcpp::Any childResult = ctx->children[i]->accept(this);
	        result = aggregateResult(result, childResult);
	        int index = result;
	        tempParams->push_back(index);
      	}

		return tempParams;
	}

	virtual antlrcpp::Any visitNum(RSIParser::NumContext *ctx) override {
#ifdef RSI_DEBUG
		std::cout << "num" << std::endl;
#endif
		std::string strNum = ctx->NUM()->getText();
		return constIndexMap[strNum];
	}

	virtual antlrcpp::Any visitId(RSIParser::IdContext *ctx) override {
#ifdef RSI_DEBUG
		std::cout << "id" << std::endl;
#endif
		std::string id = ctx->ID()->getText();

		return dataIndexMap[id];
	}
};


