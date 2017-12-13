
// Generated from RCcode.g by ANTLR 4.6

#pragma once


#include "antlr4-runtime.h"
#include "RCcodeParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by RCcodeParser.
 */
class  RCcodeVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by RCcodeParser.
   */
    virtual antlrcpp::Any visitProgram(RCcodeParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitStatBlock(RCcodeParser::StatBlockContext *context) = 0;

    virtual antlrcpp::Any visitStat(RCcodeParser::StatContext *context) = 0;

    virtual antlrcpp::Any visitMovjExpr(RCcodeParser::MovjExprContext *context) = 0;

    virtual antlrcpp::Any visitMovlExpr(RCcodeParser::MovlExprContext *context) = 0;

    virtual antlrcpp::Any visitMovcExpr(RCcodeParser::MovcExprContext *context) = 0;

    virtual antlrcpp::Any visitMovsExpr(RCcodeParser::MovsExprContext *context) = 0;

    virtual antlrcpp::Any visitShiftonExpr(RCcodeParser::ShiftonExprContext *context) = 0;

    virtual antlrcpp::Any visitShiftoffExpr(RCcodeParser::ShiftoffExprContext *context) = 0;

    virtual antlrcpp::Any visitSetExpr(RCcodeParser::SetExprContext *context) = 0;

    virtual antlrcpp::Any visitSeteExpr(RCcodeParser::SeteExprContext *context) = 0;

    virtual antlrcpp::Any visitGeteExpr(RCcodeParser::GeteExprContext *context) = 0;

    virtual antlrcpp::Any visitWaitExpr(RCcodeParser::WaitExprContext *context) = 0;

    virtual antlrcpp::Any visitDelayExpr(RCcodeParser::DelayExprContext *context) = 0;

    virtual antlrcpp::Any visitSetoutExpr(RCcodeParser::SetoutExprContext *context) = 0;

    virtual antlrcpp::Any visitDinExpr(RCcodeParser::DinExprContext *context) = 0;

    virtual antlrcpp::Any visitIncExpr(RCcodeParser::IncExprContext *context) = 0;

    virtual antlrcpp::Any visitDecExpr(RCcodeParser::DecExprContext *context) = 0;

    virtual antlrcpp::Any visitFuncExpr(RCcodeParser::FuncExprContext *context) = 0;

    virtual antlrcpp::Any visitCallExpr(RCcodeParser::CallExprContext *context) = 0;

    virtual antlrcpp::Any visitAssignExpr1(RCcodeParser::AssignExpr1Context *context) = 0;

    virtual antlrcpp::Any visitAssignExpr2(RCcodeParser::AssignExpr2Context *context) = 0;

    virtual antlrcpp::Any visitAssignExpr3(RCcodeParser::AssignExpr3Context *context) = 0;

    virtual antlrcpp::Any visitAssignExpr4(RCcodeParser::AssignExpr4Context *context) = 0;

    virtual antlrcpp::Any visitGotoExpr(RCcodeParser::GotoExprContext *context) = 0;

    virtual antlrcpp::Any visitIfExpr1(RCcodeParser::IfExpr1Context *context) = 0;

    virtual antlrcpp::Any visitIfExpr2(RCcodeParser::IfExpr2Context *context) = 0;

    virtual antlrcpp::Any visitElseifExpr1(RCcodeParser::ElseifExpr1Context *context) = 0;

    virtual antlrcpp::Any visitElseifExpr2(RCcodeParser::ElseifExpr2Context *context) = 0;

    virtual antlrcpp::Any visitElseExpr(RCcodeParser::ElseExprContext *context) = 0;

    virtual antlrcpp::Any visitForExpr(RCcodeParser::ForExprContext *context) = 0;

    virtual antlrcpp::Any visitWhileExpr1(RCcodeParser::WhileExpr1Context *context) = 0;

    virtual antlrcpp::Any visitWhileExpr2(RCcodeParser::WhileExpr2Context *context) = 0;

    virtual antlrcpp::Any visitLibcallExpr(RCcodeParser::LibcallExprContext *context) = 0;

    virtual antlrcpp::Any visitFuncallExpr(RCcodeParser::FuncallExprContext *context) = 0;

    virtual antlrcpp::Any visitParamlist(RCcodeParser::ParamlistContext *context) = 0;

    virtual antlrcpp::Any visitNumExpr(RCcodeParser::NumExprContext *context) = 0;

    virtual antlrcpp::Any visitIdExpr(RCcodeParser::IdExprContext *context) = 0;

    virtual antlrcpp::Any visitCstrExpr(RCcodeParser::CstrExprContext *context) = 0;

    virtual antlrcpp::Any visitLabelExpr(RCcodeParser::LabelExprContext *context) = 0;

    virtual antlrcpp::Any visitRetExpr(RCcodeParser::RetExprContext *context) = 0;

    virtual antlrcpp::Any visitNopExpr(RCcodeParser::NopExprContext *context) = 0;

    virtual antlrcpp::Any visitPauseExpr(RCcodeParser::PauseExprContext *context) = 0;

    virtual antlrcpp::Any visitHaltExpr(RCcodeParser::HaltExprContext *context) = 0;

    virtual antlrcpp::Any visitBreakExpr(RCcodeParser::BreakExprContext *context) = 0;


};

