
// Generated from RSI.g by ANTLR 4.6

#pragma once


#include "antlr4-runtime.h"
#include "RSIVisitor.h"


/**
 * This class provides an empty implementation of RSIVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  RSIBaseVisitor : public RSIVisitor {
public:

  virtual antlrcpp::Any visitProgram(RSIParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatBlock(RSIParser::StatBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAssignStat(RSIParser::AssignStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIfStat(RSIParser::IfStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWhileStat(RSIParser::WhileStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLoopStat(RSIParser::LoopStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCallStat(RSIParser::CallStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAssignExpr(RSIParser::AssignExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIfExpr(RSIParser::IfExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitElseifExpr(RSIParser::ElseifExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitElseExpr(RSIParser::ElseExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWhileExpr(RSIParser::WhileExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLoopExpr(RSIParser::LoopExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCallExpr(RSIParser::CallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariable(RSIParser::VariableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCall(RSIParser::CallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParamlist(RSIParser::ParamlistContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNum(RSIParser::NumContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitId(RSIParser::IdContext *ctx) override {
    return visitChildren(ctx);
  }


};

