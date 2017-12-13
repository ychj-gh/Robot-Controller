
// Generated from RCdata.g by ANTLR 4.6


#include "RCdataVisitor.h"

#include "RCdataParser.h"


using namespace antlrcpp;
using namespace antlr4;

RCdataParser::RCdataParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

RCdataParser::~RCdataParser() {
  delete _interpreter;
}

std::string RCdataParser::getGrammarFileName() const {
  return "RCdata.g";
}

const std::vector<std::string>& RCdataParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& RCdataParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgContext ------------------------------------------------------------------

RCdataParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RCdataParser::ProgContext::getRuleIndex() const {
  return RCdataParser::RuleProg;
}

void RCdataParser::ProgContext::copyFrom(ProgContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ProgramContext ------------------------------------------------------------------

RCdataParser::BlockContext* RCdataParser::ProgramContext::block() {
  return getRuleContext<RCdataParser::BlockContext>(0);
}

tree::TerminalNode* RCdataParser::ProgramContext::EOF() {
  return getToken(RCdataParser::EOF, 0);
}

RCdataParser::ProgramContext::ProgramContext(ProgContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}
RCdataParser::ProgContext* RCdataParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, RCdataParser::RuleProg);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<ProgContext *>(_tracker.createInstance<RCdataParser::ProgramContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(26);
    block();
    setState(27);
    match(RCdataParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

RCdataParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RCdataParser::BlockContext::getRuleIndex() const {
  return RCdataParser::RuleBlock;
}

void RCdataParser::BlockContext::copyFrom(BlockContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- StatBlockContext ------------------------------------------------------------------

std::vector<RCdataParser::StatContext *> RCdataParser::StatBlockContext::stat() {
  return getRuleContexts<RCdataParser::StatContext>();
}

RCdataParser::StatContext* RCdataParser::StatBlockContext::stat(size_t i) {
  return getRuleContext<RCdataParser::StatContext>(i);
}

RCdataParser::StatBlockContext::StatBlockContext(BlockContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::StatBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitStatBlock(this);
  else
    return visitor->visitChildren(this);
}
RCdataParser::BlockContext* RCdataParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 2, RCdataParser::RuleBlock);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<BlockContext *>(_tracker.createInstance<RCdataParser::StatBlockContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(32);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << RCdataParser::BOOL)
      | (1ULL << RCdataParser::CHAR)
      | (1ULL << RCdataParser::INT)
      | (1ULL << RCdataParser::REAL)
      | (1ULL << RCdataParser::STRING)
      | (1ULL << RCdataParser::JTPOSE)
      | (1ULL << RCdataParser::TRPOSE)
      | (1ULL << RCdataParser::TOOLDATA)
      | (1ULL << RCdataParser::COORDATA)
      | (1ULL << RCdataParser::PID)
      | (1ULL << RCdataParser::BPID)
      | (1ULL << RCdataParser::EXID))) != 0)) {
      setState(29);
      stat();
      setState(34);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatContext ------------------------------------------------------------------

RCdataParser::StatContext::StatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RCdataParser::StatContext::getRuleIndex() const {
  return RCdataParser::RuleStat;
}

void RCdataParser::StatContext::copyFrom(StatContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CharStatContext ------------------------------------------------------------------

RCdataParser::Char_statContext* RCdataParser::CharStatContext::char_stat() {
  return getRuleContext<RCdataParser::Char_statContext>(0);
}

RCdataParser::CharStatContext::CharStatContext(StatContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::CharStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitCharStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TrposeStatContext ------------------------------------------------------------------

RCdataParser::Trpose_statContext* RCdataParser::TrposeStatContext::trpose_stat() {
  return getRuleContext<RCdataParser::Trpose_statContext>(0);
}

RCdataParser::TrposeStatContext::TrposeStatContext(StatContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::TrposeStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitTrposeStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BoolStatContext ------------------------------------------------------------------

RCdataParser::Bool_statContext* RCdataParser::BoolStatContext::bool_stat() {
  return getRuleContext<RCdataParser::Bool_statContext>(0);
}

RCdataParser::BoolStatContext::BoolStatContext(StatContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::BoolStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitBoolStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ToolStatContext ------------------------------------------------------------------

RCdataParser::Tool_statContext* RCdataParser::ToolStatContext::tool_stat() {
  return getRuleContext<RCdataParser::Tool_statContext>(0);
}

RCdataParser::ToolStatContext::ToolStatContext(StatContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::ToolStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitToolStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CoordStatContext ------------------------------------------------------------------

RCdataParser::Coord_statContext* RCdataParser::CoordStatContext::coord_stat() {
  return getRuleContext<RCdataParser::Coord_statContext>(0);
}

RCdataParser::CoordStatContext::CoordStatContext(StatContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::CoordStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitCoordStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RealStatContext ------------------------------------------------------------------

RCdataParser::Real_statContext* RCdataParser::RealStatContext::real_stat() {
  return getRuleContext<RCdataParser::Real_statContext>(0);
}

RCdataParser::RealStatContext::RealStatContext(StatContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::RealStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitRealStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntStatContext ------------------------------------------------------------------

RCdataParser::Int_statContext* RCdataParser::IntStatContext::int_stat() {
  return getRuleContext<RCdataParser::Int_statContext>(0);
}

RCdataParser::IntStatContext::IntStatContext(StatContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::IntStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitIntStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StringStatContext ------------------------------------------------------------------

RCdataParser::String_statContext* RCdataParser::StringStatContext::string_stat() {
  return getRuleContext<RCdataParser::String_statContext>(0);
}

RCdataParser::StringStatContext::StringStatContext(StatContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::StringStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitStringStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- JtposeStatContext ------------------------------------------------------------------

RCdataParser::Jtpose_statContext* RCdataParser::JtposeStatContext::jtpose_stat() {
  return getRuleContext<RCdataParser::Jtpose_statContext>(0);
}

RCdataParser::JtposeStatContext::JtposeStatContext(StatContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::JtposeStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitJtposeStat(this);
  else
    return visitor->visitChildren(this);
}
RCdataParser::StatContext* RCdataParser::stat() {
  StatContext *_localctx = _tracker.createInstance<StatContext>(_ctx, getState());
  enterRule(_localctx, 4, RCdataParser::RuleStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(44);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case RCdataParser::BOOL: {
        _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<RCdataParser::BoolStatContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(35);
        bool_stat();
        break;
      }

      case RCdataParser::CHAR: {
        _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<RCdataParser::CharStatContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(36);
        char_stat();
        break;
      }

      case RCdataParser::INT: {
        _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<RCdataParser::IntStatContext>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(37);
        int_stat();
        break;
      }

      case RCdataParser::REAL: {
        _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<RCdataParser::RealStatContext>(_localctx));
        enterOuterAlt(_localctx, 4);
        setState(38);
        real_stat();
        break;
      }

      case RCdataParser::STRING: {
        _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<RCdataParser::StringStatContext>(_localctx));
        enterOuterAlt(_localctx, 5);
        setState(39);
        string_stat();
        break;
      }

      case RCdataParser::JTPOSE:
      case RCdataParser::PID: {
        _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<RCdataParser::JtposeStatContext>(_localctx));
        enterOuterAlt(_localctx, 6);
        setState(40);
        jtpose_stat();
        break;
      }

      case RCdataParser::TRPOSE:
      case RCdataParser::BPID:
      case RCdataParser::EXID: {
        _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<RCdataParser::TrposeStatContext>(_localctx));
        enterOuterAlt(_localctx, 7);
        setState(41);
        trpose_stat();
        break;
      }

      case RCdataParser::TOOLDATA: {
        _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<RCdataParser::ToolStatContext>(_localctx));
        enterOuterAlt(_localctx, 8);
        setState(42);
        tool_stat();
        break;
      }

      case RCdataParser::COORDATA: {
        _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<RCdataParser::CoordStatContext>(_localctx));
        enterOuterAlt(_localctx, 9);
        setState(43);
        coord_stat();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Bool_statContext ------------------------------------------------------------------

RCdataParser::Bool_statContext::Bool_statContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RCdataParser::Bool_statContext::getRuleIndex() const {
  return RCdataParser::RuleBool_stat;
}

void RCdataParser::Bool_statContext::copyFrom(Bool_statContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BoolExprContext ------------------------------------------------------------------

tree::TerminalNode* RCdataParser::BoolExprContext::BOOL() {
  return getToken(RCdataParser::BOOL, 0);
}

tree::TerminalNode* RCdataParser::BoolExprContext::ID() {
  return getToken(RCdataParser::ID, 0);
}

tree::TerminalNode* RCdataParser::BoolExprContext::ASSIGN() {
  return getToken(RCdataParser::ASSIGN, 0);
}

RCdataParser::BoolvalContext* RCdataParser::BoolExprContext::boolval() {
  return getRuleContext<RCdataParser::BoolvalContext>(0);
}

RCdataParser::BoolExprContext::BoolExprContext(Bool_statContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::BoolExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitBoolExpr(this);
  else
    return visitor->visitChildren(this);
}
RCdataParser::Bool_statContext* RCdataParser::bool_stat() {
  Bool_statContext *_localctx = _tracker.createInstance<Bool_statContext>(_ctx, getState());
  enterRule(_localctx, 6, RCdataParser::RuleBool_stat);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<Bool_statContext *>(_tracker.createInstance<RCdataParser::BoolExprContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(46);
    match(RCdataParser::BOOL);
    setState(47);
    match(RCdataParser::ID);
    setState(50);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RCdataParser::ASSIGN) {
      setState(48);
      match(RCdataParser::ASSIGN);
      setState(49);
      boolval();
    }
    setState(52);
    match(RCdataParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BoolvalContext ------------------------------------------------------------------

RCdataParser::BoolvalContext::BoolvalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RCdataParser::BoolvalContext::getRuleIndex() const {
  return RCdataParser::RuleBoolval;
}

void RCdataParser::BoolvalContext::copyFrom(BoolvalContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FalseExprContext ------------------------------------------------------------------

tree::TerminalNode* RCdataParser::FalseExprContext::FALSE() {
  return getToken(RCdataParser::FALSE, 0);
}

RCdataParser::FalseExprContext::FalseExprContext(BoolvalContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::FalseExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitFalseExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TrueExprContext ------------------------------------------------------------------

tree::TerminalNode* RCdataParser::TrueExprContext::TRUE() {
  return getToken(RCdataParser::TRUE, 0);
}

RCdataParser::TrueExprContext::TrueExprContext(BoolvalContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::TrueExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitTrueExpr(this);
  else
    return visitor->visitChildren(this);
}
RCdataParser::BoolvalContext* RCdataParser::boolval() {
  BoolvalContext *_localctx = _tracker.createInstance<BoolvalContext>(_ctx, getState());
  enterRule(_localctx, 8, RCdataParser::RuleBoolval);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(56);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case RCdataParser::TRUE: {
        _localctx = dynamic_cast<BoolvalContext *>(_tracker.createInstance<RCdataParser::TrueExprContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(54);
        match(RCdataParser::TRUE);
        break;
      }

      case RCdataParser::FALSE: {
        _localctx = dynamic_cast<BoolvalContext *>(_tracker.createInstance<RCdataParser::FalseExprContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(55);
        match(RCdataParser::FALSE);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Char_statContext ------------------------------------------------------------------

RCdataParser::Char_statContext::Char_statContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RCdataParser::Char_statContext::getRuleIndex() const {
  return RCdataParser::RuleChar_stat;
}

void RCdataParser::Char_statContext::copyFrom(Char_statContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CharExprContext ------------------------------------------------------------------

tree::TerminalNode* RCdataParser::CharExprContext::CHAR() {
  return getToken(RCdataParser::CHAR, 0);
}

tree::TerminalNode* RCdataParser::CharExprContext::ID() {
  return getToken(RCdataParser::ID, 0);
}

tree::TerminalNode* RCdataParser::CharExprContext::ASSIGN() {
  return getToken(RCdataParser::ASSIGN, 0);
}

tree::TerminalNode* RCdataParser::CharExprContext::CH() {
  return getToken(RCdataParser::CH, 0);
}

RCdataParser::CharExprContext::CharExprContext(Char_statContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::CharExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitCharExpr(this);
  else
    return visitor->visitChildren(this);
}
RCdataParser::Char_statContext* RCdataParser::char_stat() {
  Char_statContext *_localctx = _tracker.createInstance<Char_statContext>(_ctx, getState());
  enterRule(_localctx, 10, RCdataParser::RuleChar_stat);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<Char_statContext *>(_tracker.createInstance<RCdataParser::CharExprContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(58);
    match(RCdataParser::CHAR);
    setState(59);
    match(RCdataParser::ID);
    setState(62);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RCdataParser::ASSIGN) {
      setState(60);
      match(RCdataParser::ASSIGN);
      setState(61);
      match(RCdataParser::CH);
    }
    setState(64);
    match(RCdataParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Int_statContext ------------------------------------------------------------------

RCdataParser::Int_statContext::Int_statContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RCdataParser::Int_statContext::getRuleIndex() const {
  return RCdataParser::RuleInt_stat;
}

void RCdataParser::Int_statContext::copyFrom(Int_statContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IntExprContext ------------------------------------------------------------------

tree::TerminalNode* RCdataParser::IntExprContext::INT() {
  return getToken(RCdataParser::INT, 0);
}

tree::TerminalNode* RCdataParser::IntExprContext::ID() {
  return getToken(RCdataParser::ID, 0);
}

tree::TerminalNode* RCdataParser::IntExprContext::ASSIGN() {
  return getToken(RCdataParser::ASSIGN, 0);
}

tree::TerminalNode* RCdataParser::IntExprContext::NUM() {
  return getToken(RCdataParser::NUM, 0);
}

RCdataParser::IntExprContext::IntExprContext(Int_statContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::IntExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitIntExpr(this);
  else
    return visitor->visitChildren(this);
}
RCdataParser::Int_statContext* RCdataParser::int_stat() {
  Int_statContext *_localctx = _tracker.createInstance<Int_statContext>(_ctx, getState());
  enterRule(_localctx, 12, RCdataParser::RuleInt_stat);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<Int_statContext *>(_tracker.createInstance<RCdataParser::IntExprContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(66);
    match(RCdataParser::INT);
    setState(67);
    match(RCdataParser::ID);
    setState(70);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RCdataParser::ASSIGN) {
      setState(68);
      match(RCdataParser::ASSIGN);
      setState(69);
      match(RCdataParser::NUM);
    }
    setState(72);
    match(RCdataParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Real_statContext ------------------------------------------------------------------

RCdataParser::Real_statContext::Real_statContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RCdataParser::Real_statContext::getRuleIndex() const {
  return RCdataParser::RuleReal_stat;
}

void RCdataParser::Real_statContext::copyFrom(Real_statContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- RealExprContext ------------------------------------------------------------------

tree::TerminalNode* RCdataParser::RealExprContext::REAL() {
  return getToken(RCdataParser::REAL, 0);
}

tree::TerminalNode* RCdataParser::RealExprContext::ID() {
  return getToken(RCdataParser::ID, 0);
}

tree::TerminalNode* RCdataParser::RealExprContext::ASSIGN() {
  return getToken(RCdataParser::ASSIGN, 0);
}

tree::TerminalNode* RCdataParser::RealExprContext::NUM() {
  return getToken(RCdataParser::NUM, 0);
}

RCdataParser::RealExprContext::RealExprContext(Real_statContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::RealExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitRealExpr(this);
  else
    return visitor->visitChildren(this);
}
RCdataParser::Real_statContext* RCdataParser::real_stat() {
  Real_statContext *_localctx = _tracker.createInstance<Real_statContext>(_ctx, getState());
  enterRule(_localctx, 14, RCdataParser::RuleReal_stat);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<Real_statContext *>(_tracker.createInstance<RCdataParser::RealExprContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(74);
    match(RCdataParser::REAL);
    setState(75);
    match(RCdataParser::ID);
    setState(78);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RCdataParser::ASSIGN) {
      setState(76);
      match(RCdataParser::ASSIGN);
      setState(77);
      match(RCdataParser::NUM);
    }
    setState(80);
    match(RCdataParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- String_statContext ------------------------------------------------------------------

RCdataParser::String_statContext::String_statContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RCdataParser::String_statContext::getRuleIndex() const {
  return RCdataParser::RuleString_stat;
}

void RCdataParser::String_statContext::copyFrom(String_statContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- StringExprContext ------------------------------------------------------------------

tree::TerminalNode* RCdataParser::StringExprContext::STRING() {
  return getToken(RCdataParser::STRING, 0);
}

tree::TerminalNode* RCdataParser::StringExprContext::ID() {
  return getToken(RCdataParser::ID, 0);
}

tree::TerminalNode* RCdataParser::StringExprContext::ASSIGN() {
  return getToken(RCdataParser::ASSIGN, 0);
}

tree::TerminalNode* RCdataParser::StringExprContext::CSTRING() {
  return getToken(RCdataParser::CSTRING, 0);
}

RCdataParser::StringExprContext::StringExprContext(String_statContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::StringExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitStringExpr(this);
  else
    return visitor->visitChildren(this);
}
RCdataParser::String_statContext* RCdataParser::string_stat() {
  String_statContext *_localctx = _tracker.createInstance<String_statContext>(_ctx, getState());
  enterRule(_localctx, 16, RCdataParser::RuleString_stat);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<String_statContext *>(_tracker.createInstance<RCdataParser::StringExprContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(82);
    match(RCdataParser::STRING);
    setState(83);
    match(RCdataParser::ID);
    setState(86);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RCdataParser::ASSIGN) {
      setState(84);
      match(RCdataParser::ASSIGN);
      setState(85);
      match(RCdataParser::CSTRING);
    }
    setState(88);
    match(RCdataParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Jtpose_statContext ------------------------------------------------------------------

RCdataParser::Jtpose_statContext::Jtpose_statContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RCdataParser::Jtpose_statContext::getRuleIndex() const {
  return RCdataParser::RuleJtpose_stat;
}

void RCdataParser::Jtpose_statContext::copyFrom(Jtpose_statContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- JtposeExpr1Context ------------------------------------------------------------------

tree::TerminalNode* RCdataParser::JtposeExpr1Context::JTPOSE() {
  return getToken(RCdataParser::JTPOSE, 0);
}

tree::TerminalNode* RCdataParser::JtposeExpr1Context::ID() {
  return getToken(RCdataParser::ID, 0);
}

tree::TerminalNode* RCdataParser::JtposeExpr1Context::ASSIGN() {
  return getToken(RCdataParser::ASSIGN, 0);
}

std::vector<tree::TerminalNode *> RCdataParser::JtposeExpr1Context::NUM() {
  return getTokens(RCdataParser::NUM);
}

tree::TerminalNode* RCdataParser::JtposeExpr1Context::NUM(size_t i) {
  return getToken(RCdataParser::NUM, i);
}

RCdataParser::JtposeExpr1Context::JtposeExpr1Context(Jtpose_statContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::JtposeExpr1Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitJtposeExpr1(this);
  else
    return visitor->visitChildren(this);
}
//----------------- JtposeExpr2Context ------------------------------------------------------------------

tree::TerminalNode* RCdataParser::JtposeExpr2Context::PID() {
  return getToken(RCdataParser::PID, 0);
}

tree::TerminalNode* RCdataParser::JtposeExpr2Context::ASSIGN() {
  return getToken(RCdataParser::ASSIGN, 0);
}

std::vector<tree::TerminalNode *> RCdataParser::JtposeExpr2Context::NUM() {
  return getTokens(RCdataParser::NUM);
}

tree::TerminalNode* RCdataParser::JtposeExpr2Context::NUM(size_t i) {
  return getToken(RCdataParser::NUM, i);
}

RCdataParser::JtposeExpr2Context::JtposeExpr2Context(Jtpose_statContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::JtposeExpr2Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitJtposeExpr2(this);
  else
    return visitor->visitChildren(this);
}
RCdataParser::Jtpose_statContext* RCdataParser::jtpose_stat() {
  Jtpose_statContext *_localctx = _tracker.createInstance<Jtpose_statContext>(_ctx, getState());
  enterRule(_localctx, 18, RCdataParser::RuleJtpose_stat);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(111);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case RCdataParser::JTPOSE: {
        _localctx = dynamic_cast<Jtpose_statContext *>(_tracker.createInstance<RCdataParser::JtposeExpr1Context>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(90);
        match(RCdataParser::JTPOSE);
        setState(91);
        match(RCdataParser::ID);
        setState(92);
        match(RCdataParser::ASSIGN);
        setState(93);
        match(RCdataParser::NUM);
        setState(96); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(94);
          match(RCdataParser::T__1);
          setState(95);
          match(RCdataParser::NUM);
          setState(98); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == RCdataParser::T__1);
        setState(100);
        match(RCdataParser::T__0);
        break;
      }

      case RCdataParser::PID: {
        _localctx = dynamic_cast<Jtpose_statContext *>(_tracker.createInstance<RCdataParser::JtposeExpr2Context>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(101);
        match(RCdataParser::PID);
        setState(102);
        match(RCdataParser::ASSIGN);
        setState(103);
        match(RCdataParser::NUM);
        setState(106); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(104);
          match(RCdataParser::T__1);
          setState(105);
          match(RCdataParser::NUM);
          setState(108); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == RCdataParser::T__1);
        setState(110);
        match(RCdataParser::T__0);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Trpose_statContext ------------------------------------------------------------------

RCdataParser::Trpose_statContext::Trpose_statContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RCdataParser::Trpose_statContext::getRuleIndex() const {
  return RCdataParser::RuleTrpose_stat;
}

void RCdataParser::Trpose_statContext::copyFrom(Trpose_statContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- TrposeExpr1Context ------------------------------------------------------------------

tree::TerminalNode* RCdataParser::TrposeExpr1Context::TRPOSE() {
  return getToken(RCdataParser::TRPOSE, 0);
}

tree::TerminalNode* RCdataParser::TrposeExpr1Context::ID() {
  return getToken(RCdataParser::ID, 0);
}

tree::TerminalNode* RCdataParser::TrposeExpr1Context::ASSIGN() {
  return getToken(RCdataParser::ASSIGN, 0);
}

std::vector<tree::TerminalNode *> RCdataParser::TrposeExpr1Context::NUM() {
  return getTokens(RCdataParser::NUM);
}

tree::TerminalNode* RCdataParser::TrposeExpr1Context::NUM(size_t i) {
  return getToken(RCdataParser::NUM, i);
}

RCdataParser::TrposeExpr1Context::TrposeExpr1Context(Trpose_statContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::TrposeExpr1Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitTrposeExpr1(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TrposeExpr3Context ------------------------------------------------------------------

tree::TerminalNode* RCdataParser::TrposeExpr3Context::EXID() {
  return getToken(RCdataParser::EXID, 0);
}

tree::TerminalNode* RCdataParser::TrposeExpr3Context::ASSIGN() {
  return getToken(RCdataParser::ASSIGN, 0);
}

std::vector<tree::TerminalNode *> RCdataParser::TrposeExpr3Context::NUM() {
  return getTokens(RCdataParser::NUM);
}

tree::TerminalNode* RCdataParser::TrposeExpr3Context::NUM(size_t i) {
  return getToken(RCdataParser::NUM, i);
}

RCdataParser::TrposeExpr3Context::TrposeExpr3Context(Trpose_statContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::TrposeExpr3Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitTrposeExpr3(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TrposeExpr2Context ------------------------------------------------------------------

tree::TerminalNode* RCdataParser::TrposeExpr2Context::BPID() {
  return getToken(RCdataParser::BPID, 0);
}

tree::TerminalNode* RCdataParser::TrposeExpr2Context::ASSIGN() {
  return getToken(RCdataParser::ASSIGN, 0);
}

std::vector<tree::TerminalNode *> RCdataParser::TrposeExpr2Context::NUM() {
  return getTokens(RCdataParser::NUM);
}

tree::TerminalNode* RCdataParser::TrposeExpr2Context::NUM(size_t i) {
  return getToken(RCdataParser::NUM, i);
}

RCdataParser::TrposeExpr2Context::TrposeExpr2Context(Trpose_statContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::TrposeExpr2Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitTrposeExpr2(this);
  else
    return visitor->visitChildren(this);
}
RCdataParser::Trpose_statContext* RCdataParser::trpose_stat() {
  Trpose_statContext *_localctx = _tracker.createInstance<Trpose_statContext>(_ctx, getState());
  enterRule(_localctx, 20, RCdataParser::RuleTrpose_stat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(156);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case RCdataParser::TRPOSE: {
        _localctx = dynamic_cast<Trpose_statContext *>(_tracker.createInstance<RCdataParser::TrposeExpr1Context>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(113);
        match(RCdataParser::TRPOSE);
        setState(114);
        match(RCdataParser::ID);
        setState(115);
        match(RCdataParser::ASSIGN);
        setState(116);
        match(RCdataParser::NUM);
        setState(117);
        match(RCdataParser::T__1);
        setState(118);
        match(RCdataParser::NUM);
        setState(119);
        match(RCdataParser::T__1);
        setState(120);
        match(RCdataParser::NUM);
        setState(121);
        match(RCdataParser::T__1);
        setState(122);
        match(RCdataParser::NUM);
        setState(123);
        match(RCdataParser::T__1);
        setState(124);
        match(RCdataParser::NUM);
        setState(125);
        match(RCdataParser::T__1);
        setState(126);
        match(RCdataParser::NUM);
        setState(127);
        match(RCdataParser::T__0);
        break;
      }

      case RCdataParser::BPID: {
        _localctx = dynamic_cast<Trpose_statContext *>(_tracker.createInstance<RCdataParser::TrposeExpr2Context>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(128);
        match(RCdataParser::BPID);
        setState(129);
        match(RCdataParser::ASSIGN);
        setState(130);
        match(RCdataParser::NUM);
        setState(131);
        match(RCdataParser::T__1);
        setState(132);
        match(RCdataParser::NUM);
        setState(133);
        match(RCdataParser::T__1);
        setState(134);
        match(RCdataParser::NUM);
        setState(135);
        match(RCdataParser::T__1);
        setState(136);
        match(RCdataParser::NUM);
        setState(137);
        match(RCdataParser::T__1);
        setState(138);
        match(RCdataParser::NUM);
        setState(139);
        match(RCdataParser::T__1);
        setState(140);
        match(RCdataParser::NUM);
        setState(141);
        match(RCdataParser::T__0);
        break;
      }

      case RCdataParser::EXID: {
        _localctx = dynamic_cast<Trpose_statContext *>(_tracker.createInstance<RCdataParser::TrposeExpr3Context>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(142);
        match(RCdataParser::EXID);
        setState(143);
        match(RCdataParser::ASSIGN);
        setState(144);
        match(RCdataParser::NUM);
        setState(145);
        match(RCdataParser::T__1);
        setState(146);
        match(RCdataParser::NUM);
        setState(147);
        match(RCdataParser::T__1);
        setState(148);
        match(RCdataParser::NUM);
        setState(149);
        match(RCdataParser::T__1);
        setState(150);
        match(RCdataParser::NUM);
        setState(151);
        match(RCdataParser::T__1);
        setState(152);
        match(RCdataParser::NUM);
        setState(153);
        match(RCdataParser::T__1);
        setState(154);
        match(RCdataParser::NUM);
        setState(155);
        match(RCdataParser::T__0);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Tool_statContext ------------------------------------------------------------------

RCdataParser::Tool_statContext::Tool_statContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RCdataParser::Tool_statContext::getRuleIndex() const {
  return RCdataParser::RuleTool_stat;
}

void RCdataParser::Tool_statContext::copyFrom(Tool_statContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ToolExprContext ------------------------------------------------------------------

tree::TerminalNode* RCdataParser::ToolExprContext::TOOLDATA() {
  return getToken(RCdataParser::TOOLDATA, 0);
}

tree::TerminalNode* RCdataParser::ToolExprContext::ID() {
  return getToken(RCdataParser::ID, 0);
}

tree::TerminalNode* RCdataParser::ToolExprContext::ASSIGN() {
  return getToken(RCdataParser::ASSIGN, 0);
}

std::vector<tree::TerminalNode *> RCdataParser::ToolExprContext::NUM() {
  return getTokens(RCdataParser::NUM);
}

tree::TerminalNode* RCdataParser::ToolExprContext::NUM(size_t i) {
  return getToken(RCdataParser::NUM, i);
}

RCdataParser::ToolExprContext::ToolExprContext(Tool_statContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::ToolExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitToolExpr(this);
  else
    return visitor->visitChildren(this);
}
RCdataParser::Tool_statContext* RCdataParser::tool_stat() {
  Tool_statContext *_localctx = _tracker.createInstance<Tool_statContext>(_ctx, getState());
  enterRule(_localctx, 22, RCdataParser::RuleTool_stat);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<Tool_statContext *>(_tracker.createInstance<RCdataParser::ToolExprContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(158);
    match(RCdataParser::TOOLDATA);
    setState(159);
    match(RCdataParser::ID);
    setState(160);
    match(RCdataParser::ASSIGN);
    setState(161);
    match(RCdataParser::NUM);
    setState(162);
    match(RCdataParser::T__1);
    setState(163);
    match(RCdataParser::NUM);
    setState(164);
    match(RCdataParser::T__1);
    setState(165);
    match(RCdataParser::NUM);
    setState(166);
    match(RCdataParser::T__1);
    setState(167);
    match(RCdataParser::NUM);
    setState(168);
    match(RCdataParser::T__1);
    setState(169);
    match(RCdataParser::NUM);
    setState(170);
    match(RCdataParser::T__1);
    setState(171);
    match(RCdataParser::NUM);
    setState(186);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RCdataParser::T__1) {
      setState(172);
      match(RCdataParser::T__1);
      setState(173);
      match(RCdataParser::NUM);
      setState(174);
      match(RCdataParser::T__1);
      setState(175);
      match(RCdataParser::NUM);
      setState(176);
      match(RCdataParser::T__1);
      setState(177);
      match(RCdataParser::NUM);
      setState(178);
      match(RCdataParser::T__1);
      setState(179);
      match(RCdataParser::NUM);
      setState(180);
      match(RCdataParser::T__1);
      setState(181);
      match(RCdataParser::NUM);
      setState(182);
      match(RCdataParser::T__1);
      setState(183);
      match(RCdataParser::NUM);
      setState(184);
      match(RCdataParser::T__1);
      setState(185);
      match(RCdataParser::NUM);
    }
    setState(188);
    match(RCdataParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Coord_statContext ------------------------------------------------------------------

RCdataParser::Coord_statContext::Coord_statContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RCdataParser::Coord_statContext::getRuleIndex() const {
  return RCdataParser::RuleCoord_stat;
}

void RCdataParser::Coord_statContext::copyFrom(Coord_statContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CoordExprContext ------------------------------------------------------------------

tree::TerminalNode* RCdataParser::CoordExprContext::COORDATA() {
  return getToken(RCdataParser::COORDATA, 0);
}

std::vector<tree::TerminalNode *> RCdataParser::CoordExprContext::ID() {
  return getTokens(RCdataParser::ID);
}

tree::TerminalNode* RCdataParser::CoordExprContext::ID(size_t i) {
  return getToken(RCdataParser::ID, i);
}

tree::TerminalNode* RCdataParser::CoordExprContext::COORDO() {
  return getToken(RCdataParser::COORDO, 0);
}

tree::TerminalNode* RCdataParser::CoordExprContext::COORDT() {
  return getToken(RCdataParser::COORDT, 0);
}

std::vector<tree::TerminalNode *> RCdataParser::CoordExprContext::BPID() {
  return getTokens(RCdataParser::BPID);
}

tree::TerminalNode* RCdataParser::CoordExprContext::BPID(size_t i) {
  return getToken(RCdataParser::BPID, i);
}

RCdataParser::CoordExprContext::CoordExprContext(Coord_statContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RCdataParser::CoordExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RCdataVisitor*>(visitor))
    return parserVisitor->visitCoordExpr(this);
  else
    return visitor->visitChildren(this);
}
RCdataParser::Coord_statContext* RCdataParser::coord_stat() {
  Coord_statContext *_localctx = _tracker.createInstance<Coord_statContext>(_ctx, getState());
  enterRule(_localctx, 24, RCdataParser::RuleCoord_stat);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<Coord_statContext *>(_tracker.createInstance<RCdataParser::CoordExprContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(190);
    match(RCdataParser::COORDATA);
    setState(191);
    match(RCdataParser::ID);
    setState(192);
    match(RCdataParser::T__1);
    setState(193);
    dynamic_cast<CoordExprContext *>(_localctx)->op = _input->LT(1);
    _la = _input->LA(1);
    if (!(_la == RCdataParser::COORDO

    || _la == RCdataParser::COORDT)) {
      dynamic_cast<CoordExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(194);
    match(RCdataParser::T__1);
    setState(195);
    dynamic_cast<CoordExprContext *>(_localctx)->op1 = _input->LT(1);
    _la = _input->LA(1);
    if (!(_la == RCdataParser::BPID

    || _la == RCdataParser::ID)) {
      dynamic_cast<CoordExprContext *>(_localctx)->op1 = _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(196);
    match(RCdataParser::T__1);
    setState(197);
    dynamic_cast<CoordExprContext *>(_localctx)->op2 = _input->LT(1);
    _la = _input->LA(1);
    if (!(_la == RCdataParser::BPID

    || _la == RCdataParser::ID)) {
      dynamic_cast<CoordExprContext *>(_localctx)->op2 = _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(198);
    match(RCdataParser::T__1);
    setState(199);
    dynamic_cast<CoordExprContext *>(_localctx)->op3 = _input->LT(1);
    _la = _input->LA(1);
    if (!(_la == RCdataParser::BPID

    || _la == RCdataParser::ID)) {
      dynamic_cast<CoordExprContext *>(_localctx)->op3 = _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(200);
    match(RCdataParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> RCdataParser::_decisionToDFA;
atn::PredictionContextCache RCdataParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN RCdataParser::_atn;
std::vector<uint16_t> RCdataParser::_serializedATN;

std::vector<std::string> RCdataParser::_ruleNames = {
  "prog", "block", "stat", "bool_stat", "boolval", "char_stat", "int_stat", 
  "real_stat", "string_stat", "jtpose_stat", "trpose_stat", "tool_stat", 
  "coord_stat"
};

std::vector<std::string> RCdataParser::_literalNames = {
  "", "';'", "','", "'='", "'BOOL'", "'CHAR'", "'INT'", "'REAL'", "'STRING'", 
  "'JTPOSE'", "'TRPOSE'", "'TOOLDATA'", "'COORDATA'", "'O'", "'T'", "'TRUE'", 
  "'FALSE'"
};

std::vector<std::string> RCdataParser::_symbolicNames = {
  "", "", "", "ASSIGN", "BOOL", "CHAR", "INT", "REAL", "STRING", "JTPOSE", 
  "TRPOSE", "TOOLDATA", "COORDATA", "COORDO", "COORDT", "TRUE", "FALSE", 
  "PID", "BPID", "EXID", "CSTRING", "CH", "ID", "NUM", "COMMENT", "SPACE", 
  "OTHER"
};

dfa::Vocabulary RCdataParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> RCdataParser::_tokenNames;

RCdataParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x430, 0xd6d1, 0x8206, 0xad2d, 0x4417, 0xaef1, 0x8d80, 0xaadd, 
    0x3, 0x1c, 0xcd, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x7, 0x3, 0x21, 0xa, 0x3, 0xc, 0x3, 
    0xe, 0x3, 0x24, 0xb, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x2f, 0xa, 0x4, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x35, 0xa, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x3b, 0xa, 0x6, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0x41, 0xa, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x49, 0xa, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 
    0x51, 0xa, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x5, 0xa, 0x59, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x6, 0xb, 0x63, 0xa, 0xb, 0xd, 
    0xb, 0xe, 0xb, 0x64, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x6, 0xb, 0x6d, 0xa, 0xb, 0xd, 0xb, 0xe, 0xb, 0x6e, 0x3, 0xb, 
    0x5, 0xb, 0x72, 0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0x9f, 0xa, 0xc, 0x3, 0xd, 
    0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 
    0xbd, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x2, 0x2, 0xf, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 
    0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x2, 0x4, 0x3, 0x2, 0xf, 0x10, 
    0x4, 0x2, 0x14, 0x14, 0x18, 0x18, 0xd4, 0x2, 0x1c, 0x3, 0x2, 0x2, 0x2, 
    0x4, 0x22, 0x3, 0x2, 0x2, 0x2, 0x6, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x8, 0x30, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0x3a, 0x3, 0x2, 0x2, 0x2, 0xc, 0x3c, 0x3, 0x2, 
    0x2, 0x2, 0xe, 0x44, 0x3, 0x2, 0x2, 0x2, 0x10, 0x4c, 0x3, 0x2, 0x2, 
    0x2, 0x12, 0x54, 0x3, 0x2, 0x2, 0x2, 0x14, 0x71, 0x3, 0x2, 0x2, 0x2, 
    0x16, 0x9e, 0x3, 0x2, 0x2, 0x2, 0x18, 0xa0, 0x3, 0x2, 0x2, 0x2, 0x1a, 
    0xc0, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1d, 0x5, 0x4, 0x3, 0x2, 0x1d, 0x1e, 
    0x7, 0x2, 0x2, 0x3, 0x1e, 0x3, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x21, 0x5, 
    0x6, 0x4, 0x2, 0x20, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x21, 0x24, 0x3, 0x2, 
    0x2, 0x2, 0x22, 0x20, 0x3, 0x2, 0x2, 0x2, 0x22, 0x23, 0x3, 0x2, 0x2, 
    0x2, 0x23, 0x5, 0x3, 0x2, 0x2, 0x2, 0x24, 0x22, 0x3, 0x2, 0x2, 0x2, 
    0x25, 0x2f, 0x5, 0x8, 0x5, 0x2, 0x26, 0x2f, 0x5, 0xc, 0x7, 0x2, 0x27, 
    0x2f, 0x5, 0xe, 0x8, 0x2, 0x28, 0x2f, 0x5, 0x10, 0x9, 0x2, 0x29, 0x2f, 
    0x5, 0x12, 0xa, 0x2, 0x2a, 0x2f, 0x5, 0x14, 0xb, 0x2, 0x2b, 0x2f, 0x5, 
    0x16, 0xc, 0x2, 0x2c, 0x2f, 0x5, 0x18, 0xd, 0x2, 0x2d, 0x2f, 0x5, 0x1a, 
    0xe, 0x2, 0x2e, 0x25, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x26, 0x3, 0x2, 0x2, 
    0x2, 0x2e, 0x27, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x28, 0x3, 0x2, 0x2, 0x2, 
    0x2e, 0x29, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x2e, 
    0x2b, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x2d, 
    0x3, 0x2, 0x2, 0x2, 0x2f, 0x7, 0x3, 0x2, 0x2, 0x2, 0x30, 0x31, 0x7, 
    0x6, 0x2, 0x2, 0x31, 0x34, 0x7, 0x18, 0x2, 0x2, 0x32, 0x33, 0x7, 0x5, 
    0x2, 0x2, 0x33, 0x35, 0x5, 0xa, 0x6, 0x2, 0x34, 0x32, 0x3, 0x2, 0x2, 
    0x2, 0x34, 0x35, 0x3, 0x2, 0x2, 0x2, 0x35, 0x36, 0x3, 0x2, 0x2, 0x2, 
    0x36, 0x37, 0x7, 0x3, 0x2, 0x2, 0x37, 0x9, 0x3, 0x2, 0x2, 0x2, 0x38, 
    0x3b, 0x7, 0x11, 0x2, 0x2, 0x39, 0x3b, 0x7, 0x12, 0x2, 0x2, 0x3a, 0x38, 
    0x3, 0x2, 0x2, 0x2, 0x3a, 0x39, 0x3, 0x2, 0x2, 0x2, 0x3b, 0xb, 0x3, 
    0x2, 0x2, 0x2, 0x3c, 0x3d, 0x7, 0x7, 0x2, 0x2, 0x3d, 0x40, 0x7, 0x18, 
    0x2, 0x2, 0x3e, 0x3f, 0x7, 0x5, 0x2, 0x2, 0x3f, 0x41, 0x7, 0x17, 0x2, 
    0x2, 0x40, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x40, 0x41, 0x3, 0x2, 0x2, 0x2, 
    0x41, 0x42, 0x3, 0x2, 0x2, 0x2, 0x42, 0x43, 0x7, 0x3, 0x2, 0x2, 0x43, 
    0xd, 0x3, 0x2, 0x2, 0x2, 0x44, 0x45, 0x7, 0x8, 0x2, 0x2, 0x45, 0x48, 
    0x7, 0x18, 0x2, 0x2, 0x46, 0x47, 0x7, 0x5, 0x2, 0x2, 0x47, 0x49, 0x7, 
    0x19, 0x2, 0x2, 0x48, 0x46, 0x3, 0x2, 0x2, 0x2, 0x48, 0x49, 0x3, 0x2, 
    0x2, 0x2, 0x49, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x4b, 0x7, 0x3, 0x2, 
    0x2, 0x4b, 0xf, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x4d, 0x7, 0x9, 0x2, 0x2, 
    0x4d, 0x50, 0x7, 0x18, 0x2, 0x2, 0x4e, 0x4f, 0x7, 0x5, 0x2, 0x2, 0x4f, 
    0x51, 0x7, 0x19, 0x2, 0x2, 0x50, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x50, 0x51, 
    0x3, 0x2, 0x2, 0x2, 0x51, 0x52, 0x3, 0x2, 0x2, 0x2, 0x52, 0x53, 0x7, 
    0x3, 0x2, 0x2, 0x53, 0x11, 0x3, 0x2, 0x2, 0x2, 0x54, 0x55, 0x7, 0xa, 
    0x2, 0x2, 0x55, 0x58, 0x7, 0x18, 0x2, 0x2, 0x56, 0x57, 0x7, 0x5, 0x2, 
    0x2, 0x57, 0x59, 0x7, 0x16, 0x2, 0x2, 0x58, 0x56, 0x3, 0x2, 0x2, 0x2, 
    0x58, 0x59, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x5a, 
    0x5b, 0x7, 0x3, 0x2, 0x2, 0x5b, 0x13, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5d, 
    0x7, 0xb, 0x2, 0x2, 0x5d, 0x5e, 0x7, 0x18, 0x2, 0x2, 0x5e, 0x5f, 0x7, 
    0x5, 0x2, 0x2, 0x5f, 0x62, 0x7, 0x19, 0x2, 0x2, 0x60, 0x61, 0x7, 0x4, 
    0x2, 0x2, 0x61, 0x63, 0x7, 0x19, 0x2, 0x2, 0x62, 0x60, 0x3, 0x2, 0x2, 
    0x2, 0x63, 0x64, 0x3, 0x2, 0x2, 0x2, 0x64, 0x62, 0x3, 0x2, 0x2, 0x2, 
    0x64, 0x65, 0x3, 0x2, 0x2, 0x2, 0x65, 0x66, 0x3, 0x2, 0x2, 0x2, 0x66, 
    0x72, 0x7, 0x3, 0x2, 0x2, 0x67, 0x68, 0x7, 0x13, 0x2, 0x2, 0x68, 0x69, 
    0x7, 0x5, 0x2, 0x2, 0x69, 0x6c, 0x7, 0x19, 0x2, 0x2, 0x6a, 0x6b, 0x7, 
    0x4, 0x2, 0x2, 0x6b, 0x6d, 0x7, 0x19, 0x2, 0x2, 0x6c, 0x6a, 0x3, 0x2, 
    0x2, 0x2, 0x6d, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x6c, 0x3, 0x2, 0x2, 
    0x2, 0x6e, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x70, 0x3, 0x2, 0x2, 0x2, 
    0x70, 0x72, 0x7, 0x3, 0x2, 0x2, 0x71, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x71, 
    0x67, 0x3, 0x2, 0x2, 0x2, 0x72, 0x15, 0x3, 0x2, 0x2, 0x2, 0x73, 0x74, 
    0x7, 0xc, 0x2, 0x2, 0x74, 0x75, 0x7, 0x18, 0x2, 0x2, 0x75, 0x76, 0x7, 
    0x5, 0x2, 0x2, 0x76, 0x77, 0x7, 0x19, 0x2, 0x2, 0x77, 0x78, 0x7, 0x4, 
    0x2, 0x2, 0x78, 0x79, 0x7, 0x19, 0x2, 0x2, 0x79, 0x7a, 0x7, 0x4, 0x2, 
    0x2, 0x7a, 0x7b, 0x7, 0x19, 0x2, 0x2, 0x7b, 0x7c, 0x7, 0x4, 0x2, 0x2, 
    0x7c, 0x7d, 0x7, 0x19, 0x2, 0x2, 0x7d, 0x7e, 0x7, 0x4, 0x2, 0x2, 0x7e, 
    0x7f, 0x7, 0x19, 0x2, 0x2, 0x7f, 0x80, 0x7, 0x4, 0x2, 0x2, 0x80, 0x81, 
    0x7, 0x19, 0x2, 0x2, 0x81, 0x9f, 0x7, 0x3, 0x2, 0x2, 0x82, 0x83, 0x7, 
    0x14, 0x2, 0x2, 0x83, 0x84, 0x7, 0x5, 0x2, 0x2, 0x84, 0x85, 0x7, 0x19, 
    0x2, 0x2, 0x85, 0x86, 0x7, 0x4, 0x2, 0x2, 0x86, 0x87, 0x7, 0x19, 0x2, 
    0x2, 0x87, 0x88, 0x7, 0x4, 0x2, 0x2, 0x88, 0x89, 0x7, 0x19, 0x2, 0x2, 
    0x89, 0x8a, 0x7, 0x4, 0x2, 0x2, 0x8a, 0x8b, 0x7, 0x19, 0x2, 0x2, 0x8b, 
    0x8c, 0x7, 0x4, 0x2, 0x2, 0x8c, 0x8d, 0x7, 0x19, 0x2, 0x2, 0x8d, 0x8e, 
    0x7, 0x4, 0x2, 0x2, 0x8e, 0x8f, 0x7, 0x19, 0x2, 0x2, 0x8f, 0x9f, 0x7, 
    0x3, 0x2, 0x2, 0x90, 0x91, 0x7, 0x15, 0x2, 0x2, 0x91, 0x92, 0x7, 0x5, 
    0x2, 0x2, 0x92, 0x93, 0x7, 0x19, 0x2, 0x2, 0x93, 0x94, 0x7, 0x4, 0x2, 
    0x2, 0x94, 0x95, 0x7, 0x19, 0x2, 0x2, 0x95, 0x96, 0x7, 0x4, 0x2, 0x2, 
    0x96, 0x97, 0x7, 0x19, 0x2, 0x2, 0x97, 0x98, 0x7, 0x4, 0x2, 0x2, 0x98, 
    0x99, 0x7, 0x19, 0x2, 0x2, 0x99, 0x9a, 0x7, 0x4, 0x2, 0x2, 0x9a, 0x9b, 
    0x7, 0x19, 0x2, 0x2, 0x9b, 0x9c, 0x7, 0x4, 0x2, 0x2, 0x9c, 0x9d, 0x7, 
    0x19, 0x2, 0x2, 0x9d, 0x9f, 0x7, 0x3, 0x2, 0x2, 0x9e, 0x73, 0x3, 0x2, 
    0x2, 0x2, 0x9e, 0x82, 0x3, 0x2, 0x2, 0x2, 0x9e, 0x90, 0x3, 0x2, 0x2, 
    0x2, 0x9f, 0x17, 0x3, 0x2, 0x2, 0x2, 0xa0, 0xa1, 0x7, 0xd, 0x2, 0x2, 
    0xa1, 0xa2, 0x7, 0x18, 0x2, 0x2, 0xa2, 0xa3, 0x7, 0x5, 0x2, 0x2, 0xa3, 
    0xa4, 0x7, 0x19, 0x2, 0x2, 0xa4, 0xa5, 0x7, 0x4, 0x2, 0x2, 0xa5, 0xa6, 
    0x7, 0x19, 0x2, 0x2, 0xa6, 0xa7, 0x7, 0x4, 0x2, 0x2, 0xa7, 0xa8, 0x7, 
    0x19, 0x2, 0x2, 0xa8, 0xa9, 0x7, 0x4, 0x2, 0x2, 0xa9, 0xaa, 0x7, 0x19, 
    0x2, 0x2, 0xaa, 0xab, 0x7, 0x4, 0x2, 0x2, 0xab, 0xac, 0x7, 0x19, 0x2, 
    0x2, 0xac, 0xad, 0x7, 0x4, 0x2, 0x2, 0xad, 0xbc, 0x7, 0x19, 0x2, 0x2, 
    0xae, 0xaf, 0x7, 0x4, 0x2, 0x2, 0xaf, 0xb0, 0x7, 0x19, 0x2, 0x2, 0xb0, 
    0xb1, 0x7, 0x4, 0x2, 0x2, 0xb1, 0xb2, 0x7, 0x19, 0x2, 0x2, 0xb2, 0xb3, 
    0x7, 0x4, 0x2, 0x2, 0xb3, 0xb4, 0x7, 0x19, 0x2, 0x2, 0xb4, 0xb5, 0x7, 
    0x4, 0x2, 0x2, 0xb5, 0xb6, 0x7, 0x19, 0x2, 0x2, 0xb6, 0xb7, 0x7, 0x4, 
    0x2, 0x2, 0xb7, 0xb8, 0x7, 0x19, 0x2, 0x2, 0xb8, 0xb9, 0x7, 0x4, 0x2, 
    0x2, 0xb9, 0xba, 0x7, 0x19, 0x2, 0x2, 0xba, 0xbb, 0x7, 0x4, 0x2, 0x2, 
    0xbb, 0xbd, 0x7, 0x19, 0x2, 0x2, 0xbc, 0xae, 0x3, 0x2, 0x2, 0x2, 0xbc, 
    0xbd, 0x3, 0x2, 0x2, 0x2, 0xbd, 0xbe, 0x3, 0x2, 0x2, 0x2, 0xbe, 0xbf, 
    0x7, 0x3, 0x2, 0x2, 0xbf, 0x19, 0x3, 0x2, 0x2, 0x2, 0xc0, 0xc1, 0x7, 
    0xe, 0x2, 0x2, 0xc1, 0xc2, 0x7, 0x18, 0x2, 0x2, 0xc2, 0xc3, 0x7, 0x4, 
    0x2, 0x2, 0xc3, 0xc4, 0x9, 0x2, 0x2, 0x2, 0xc4, 0xc5, 0x7, 0x4, 0x2, 
    0x2, 0xc5, 0xc6, 0x9, 0x3, 0x2, 0x2, 0xc6, 0xc7, 0x7, 0x4, 0x2, 0x2, 
    0xc7, 0xc8, 0x9, 0x3, 0x2, 0x2, 0xc8, 0xc9, 0x7, 0x4, 0x2, 0x2, 0xc9, 
    0xca, 0x9, 0x3, 0x2, 0x2, 0xca, 0xcb, 0x7, 0x3, 0x2, 0x2, 0xcb, 0x1b, 
    0x3, 0x2, 0x2, 0x2, 0xf, 0x22, 0x2e, 0x34, 0x3a, 0x40, 0x48, 0x50, 0x58, 
    0x64, 0x6e, 0x71, 0x9e, 0xbc, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

RCdataParser::Initializer RCdataParser::_init;
