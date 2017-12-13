
// Generated from RCcode.g by ANTLR 4.6

#pragma once


#include "antlr4-runtime.h"
#include "RCcodeVisitor.h"


/**
 * This class provides an empty implementation of RCcodeVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  RCcodeBaseVisitor : public RCcodeVisitor {
public:

  virtual antlrcpp::Any visitProgram(RCcodeParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatBlock(RCcodeParser::StatBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStat(RCcodeParser::StatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMovjExpr(RCcodeParser::MovjExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMovlExpr(RCcodeParser::MovlExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMovcExpr(RCcodeParser::MovcExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMovsExpr(RCcodeParser::MovsExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitShiftonExpr(RCcodeParser::ShiftonExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitShiftoffExpr(RCcodeParser::ShiftoffExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSetExpr(RCcodeParser::SetExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSeteExpr(RCcodeParser::SeteExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGeteExpr(RCcodeParser::GeteExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWaitExpr(RCcodeParser::WaitExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDelayExpr(RCcodeParser::DelayExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSetoutExpr(RCcodeParser::SetoutExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDinExpr(RCcodeParser::DinExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIncExpr(RCcodeParser::IncExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDecExpr(RCcodeParser::DecExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncExpr(RCcodeParser::FuncExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCallExpr(RCcodeParser::CallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAssignExpr1(RCcodeParser::AssignExpr1Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAssignExpr2(RCcodeParser::AssignExpr2Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAssignExpr3(RCcodeParser::AssignExpr3Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAssignExpr4(RCcodeParser::AssignExpr4Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGotoExpr(RCcodeParser::GotoExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIfExpr1(RCcodeParser::IfExpr1Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIfExpr2(RCcodeParser::IfExpr2Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitElseifExpr1(RCcodeParser::ElseifExpr1Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitElseifExpr2(RCcodeParser::ElseifExpr2Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitElseExpr(RCcodeParser::ElseExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitForExpr(RCcodeParser::ForExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWhileExpr1(RCcodeParser::WhileExpr1Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWhileExpr2(RCcodeParser::WhileExpr2Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLibcallExpr(RCcodeParser::LibcallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncallExpr(RCcodeParser::FuncallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParamlist(RCcodeParser::ParamlistContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNumExpr(RCcodeParser::NumExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdExpr(RCcodeParser::IdExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCstrExpr(RCcodeParser::CstrExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLabelExpr(RCcodeParser::LabelExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRetExpr(RCcodeParser::RetExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNopExpr(RCcodeParser::NopExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPauseExpr(RCcodeParser::PauseExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitHaltExpr(RCcodeParser::HaltExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBreakExpr(RCcodeParser::BreakExprContext *ctx) override {
    return visitChildren(ctx);
  }


};

