
// Generated from RCdata.g by ANTLR 4.6

#pragma once


#include "antlr4-runtime.h"
#include "RCdataParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by RCdataParser.
 */
class  RCdataVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by RCdataParser.
   */
    virtual antlrcpp::Any visitProgram(RCdataParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitStatBlock(RCdataParser::StatBlockContext *context) = 0;

    virtual antlrcpp::Any visitBoolStat(RCdataParser::BoolStatContext *context) = 0;

    virtual antlrcpp::Any visitCharStat(RCdataParser::CharStatContext *context) = 0;

    virtual antlrcpp::Any visitIntStat(RCdataParser::IntStatContext *context) = 0;

    virtual antlrcpp::Any visitRealStat(RCdataParser::RealStatContext *context) = 0;

    virtual antlrcpp::Any visitStringStat(RCdataParser::StringStatContext *context) = 0;

    virtual antlrcpp::Any visitJtposeStat(RCdataParser::JtposeStatContext *context) = 0;

    virtual antlrcpp::Any visitTrposeStat(RCdataParser::TrposeStatContext *context) = 0;

    virtual antlrcpp::Any visitToolStat(RCdataParser::ToolStatContext *context) = 0;

    virtual antlrcpp::Any visitCoordStat(RCdataParser::CoordStatContext *context) = 0;

    virtual antlrcpp::Any visitBoolExpr(RCdataParser::BoolExprContext *context) = 0;

    virtual antlrcpp::Any visitTrueExpr(RCdataParser::TrueExprContext *context) = 0;

    virtual antlrcpp::Any visitFalseExpr(RCdataParser::FalseExprContext *context) = 0;

    virtual antlrcpp::Any visitCharExpr(RCdataParser::CharExprContext *context) = 0;

    virtual antlrcpp::Any visitIntExpr(RCdataParser::IntExprContext *context) = 0;

    virtual antlrcpp::Any visitRealExpr(RCdataParser::RealExprContext *context) = 0;

    virtual antlrcpp::Any visitStringExpr(RCdataParser::StringExprContext *context) = 0;

    virtual antlrcpp::Any visitJtposeExpr1(RCdataParser::JtposeExpr1Context *context) = 0;

    virtual antlrcpp::Any visitJtposeExpr2(RCdataParser::JtposeExpr2Context *context) = 0;

    virtual antlrcpp::Any visitTrposeExpr1(RCdataParser::TrposeExpr1Context *context) = 0;

    virtual antlrcpp::Any visitTrposeExpr2(RCdataParser::TrposeExpr2Context *context) = 0;

    virtual antlrcpp::Any visitTrposeExpr3(RCdataParser::TrposeExpr3Context *context) = 0;

    virtual antlrcpp::Any visitToolExpr(RCdataParser::ToolExprContext *context) = 0;

    virtual antlrcpp::Any visitCoordExpr(RCdataParser::CoordExprContext *context) = 0;


};

