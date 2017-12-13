
// Generated from RSI.g by ANTLR 4.6

#pragma once


#include "antlr4-runtime.h"
#include "RSIParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by RSIParser.
 */
class  RSIVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by RSIParser.
   */
    virtual antlrcpp::Any visitProgram(RSIParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitStatBlock(RSIParser::StatBlockContext *context) = 0;

    virtual antlrcpp::Any visitAssignStat(RSIParser::AssignStatContext *context) = 0;

    virtual antlrcpp::Any visitIfStat(RSIParser::IfStatContext *context) = 0;

    virtual antlrcpp::Any visitWhileStat(RSIParser::WhileStatContext *context) = 0;

    virtual antlrcpp::Any visitLoopStat(RSIParser::LoopStatContext *context) = 0;

    virtual antlrcpp::Any visitCallStat(RSIParser::CallStatContext *context) = 0;

    virtual antlrcpp::Any visitAssignExpr(RSIParser::AssignExprContext *context) = 0;

    virtual antlrcpp::Any visitIfExpr(RSIParser::IfExprContext *context) = 0;

    virtual antlrcpp::Any visitElseifExpr(RSIParser::ElseifExprContext *context) = 0;

    virtual antlrcpp::Any visitElseExpr(RSIParser::ElseExprContext *context) = 0;

    virtual antlrcpp::Any visitWhileExpr(RSIParser::WhileExprContext *context) = 0;

    virtual antlrcpp::Any visitLoopExpr(RSIParser::LoopExprContext *context) = 0;

    virtual antlrcpp::Any visitCallExpr(RSIParser::CallExprContext *context) = 0;

    virtual antlrcpp::Any visitVariable(RSIParser::VariableContext *context) = 0;

    virtual antlrcpp::Any visitCall(RSIParser::CallContext *context) = 0;

    virtual antlrcpp::Any visitParamlist(RSIParser::ParamlistContext *context) = 0;

    virtual antlrcpp::Any visitNum(RSIParser::NumContext *context) = 0;

    virtual antlrcpp::Any visitId(RSIParser::IdContext *context) = 0;


};

