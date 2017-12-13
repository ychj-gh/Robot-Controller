
// Generated from RCdata.g by ANTLR 4.6

#pragma once


#include "antlr4-runtime.h"
#include "RCdataVisitor.h"


/**
 * This class provides an empty implementation of RCdataVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  RCdataBaseVisitor : public RCdataVisitor {
public:

  virtual antlrcpp::Any visitProgram(RCdataParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatBlock(RCdataParser::StatBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBoolStat(RCdataParser::BoolStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCharStat(RCdataParser::CharStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIntStat(RCdataParser::IntStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRealStat(RCdataParser::RealStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStringStat(RCdataParser::StringStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitJtposeStat(RCdataParser::JtposeStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTrposeStat(RCdataParser::TrposeStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitToolStat(RCdataParser::ToolStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCoordStat(RCdataParser::CoordStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBoolExpr(RCdataParser::BoolExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTrueExpr(RCdataParser::TrueExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFalseExpr(RCdataParser::FalseExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCharExpr(RCdataParser::CharExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIntExpr(RCdataParser::IntExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRealExpr(RCdataParser::RealExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStringExpr(RCdataParser::StringExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitJtposeExpr1(RCdataParser::JtposeExpr1Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitJtposeExpr2(RCdataParser::JtposeExpr2Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTrposeExpr1(RCdataParser::TrposeExpr1Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTrposeExpr2(RCdataParser::TrposeExpr2Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTrposeExpr3(RCdataParser::TrposeExpr3Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitToolExpr(RCdataParser::ToolExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCoordExpr(RCdataParser::CoordExprContext *ctx) override {
    return visitChildren(ctx);
  }


};

