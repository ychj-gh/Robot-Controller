

#pragma once

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

#include "antlr4-runtime.h"
#include "RSILexer.h"
#include "RSIParser.h"
#include "RSIVisitor.h"
#include "RSIBaseVisitor.h"
#include "RSIConstVisitor.h"
#include "RSICodeGenerator.h"
#include "RSIExecutor.h"

#include "RSIXml.h"
#include "RSIRuntimeModel.h"
#include <native/timer.h>

using namespace antlr4;
using namespace antlr4::tree;

extern bool RSIStopFlag; /* THIS IS VERY IMPORTANT, WHICH CONTROL THE WHOLE LIFECYCLE OF RSI */

// #define RSI_DEBUG

class RSIExecutor {
public:
	RSIExecutor(std::string f) : file(f) {
		addrspace.push_back(0);  // addrspace[0] is the returned value of all the library function  in global
	}

	int compile() {
		RSIXmlLoader loader(file + ".xml");
		loader.parseXml(addrspace, dataIndexMap, fbMap);

		SymbolTable symTable(addrspace, dataIndexMap, constIndexMap, fbMap, funcMap);
		symTable.create();

		/* read rsi code */
		std::ifstream infile(file + ".rsi");     
		ANTLRInputStream input(infile);     
		/* rsi code lexer analysis */  
		RSILexer lexer(&input);
		CommonTokenStream tokens(&lexer);
		/* rsi code parser analysis */  
		RSIParser parser(&tokens);
		ParseTree *tree = parser.prog();

		RSIConstVisitor vi(symTable);                // first time, build constant table
		vi.visit(tree);

		RSICodeGenerator CG(code, symTable);        // second time, generate execute model
		CG.visit(tree);
#ifdef RSI_DEBUG
		for(int i = 0; i < addrspace.size(); i ++) {
			std::cout << i << ": " << addrspace[i] << std::endl;
		}
#endif

		return 0;

	}

	int execute() {
		std::cout << std::endl << "| ==== RSI executor start ===>" << std::endl;
		RTIME start = rt_timer_read();
		for(int i = 0; i < code.size(); i ++) {
			code[i]->execute(NULL);

		}
					RTIME tmp = rt_timer_read();
			std::cout << "cost time = " << tmp << " ----- " << start <<"-----"<< tmp - start << std::endl;
		std::cout << std::endl << " <=== RSI executor stop ==== |" << std::endl;
		return 0;
	}

public:
	std::string file;		// the name of config file and code file with different suffix

private:
	std::unordered_map<std::string, int> dataIndexMap;    // parser xml file and generator dataMap; var --> index
	std::unordered_map<std::string, int> constIndexMap;   // the index of all the constants in addr space 
	std::unordered_map<std::string, EntityBase*> fbMap;   // parser xml file and generator functionblock map
	std::unordered_map<std::string, int> funcMap;         // all library function map to check if designated function is existed

	std::vector<IValue> addrspace;     	// RSI address space ; 
	CodeShadow code;					// code model in memory
};


