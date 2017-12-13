
// Generated from RSI.g by ANTLR 4.6


#include "RSIVisitor.h"

#include "RSIParser.h"


using namespace antlrcpp;
using namespace antlr4;

RSIParser::RSIParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

RSIParser::~RSIParser() {
  delete _interpreter;
}

std::string RSIParser::getGrammarFileName() const {
  return "RSI.g";
}

const std::vector<std::string>& RSIParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& RSIParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgContext ------------------------------------------------------------------

RSIParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RSIParser::ProgContext::getRuleIndex() const {
  return RSIParser::RuleProg;
}

void RSIParser::ProgContext::copyFrom(ProgContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ProgramContext ------------------------------------------------------------------

RSIParser::BlockContext* RSIParser::ProgramContext::block() {
  return getRuleContext<RSIParser::BlockContext>(0);
}

tree::TerminalNode* RSIParser::ProgramContext::EOF() {
  return getToken(RSIParser::EOF, 0);
}

RSIParser::ProgramContext::ProgramContext(ProgContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RSIParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RSIVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}
RSIParser::ProgContext* RSIParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, RSIParser::RuleProg);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<ProgContext *>(_tracker.createInstance<RSIParser::ProgramContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(26);
    block();
    setState(27);
    match(RSIParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

RSIParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RSIParser::BlockContext::getRuleIndex() const {
  return RSIParser::RuleBlock;
}

void RSIParser::BlockContext::copyFrom(BlockContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- StatBlockContext ------------------------------------------------------------------

std::vector<RSIParser::StatContext *> RSIParser::StatBlockContext::stat() {
  return getRuleContexts<RSIParser::StatContext>();
}

RSIParser::StatContext* RSIParser::StatBlockContext::stat(size_t i) {
  return getRuleContext<RSIParser::StatContext>(i);
}

RSIParser::StatBlockContext::StatBlockContext(BlockContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RSIParser::StatBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RSIVisitor*>(visitor))
    return parserVisitor->visitStatBlock(this);
  else
    return visitor->visitChildren(this);
}
RSIParser::BlockContext* RSIParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 2, RSIParser::RuleBlock);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<BlockContext *>(_tracker.createInstance<RSIParser::StatBlockContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(32);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << RSIParser::IF)
      | (1ULL << RSIParser::WHILE)
      | (1ULL << RSIParser::LOOP)
      | (1ULL << RSIParser::ID))) != 0)) {
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

RSIParser::StatContext::StatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RSIParser::StatContext::getRuleIndex() const {
  return RSIParser::RuleStat;
}

void RSIParser::StatContext::copyFrom(StatContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- WhileStatContext ------------------------------------------------------------------

RSIParser::While_statContext* RSIParser::WhileStatContext::while_stat() {
  return getRuleContext<RSIParser::While_statContext>(0);
}

RSIParser::WhileStatContext::WhileStatContext(StatContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RSIParser::WhileStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RSIVisitor*>(visitor))
    return parserVisitor->visitWhileStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LoopStatContext ------------------------------------------------------------------

RSIParser::Loop_statContext* RSIParser::LoopStatContext::loop_stat() {
  return getRuleContext<RSIParser::Loop_statContext>(0);
}

RSIParser::LoopStatContext::LoopStatContext(StatContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RSIParser::LoopStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RSIVisitor*>(visitor))
    return parserVisitor->visitLoopStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignStatContext ------------------------------------------------------------------

RSIParser::AssignmentContext* RSIParser::AssignStatContext::assignment() {
  return getRuleContext<RSIParser::AssignmentContext>(0);
}

RSIParser::AssignStatContext::AssignStatContext(StatContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RSIParser::AssignStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RSIVisitor*>(visitor))
    return parserVisitor->visitAssignStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfStatContext ------------------------------------------------------------------

RSIParser::If_statContext* RSIParser::IfStatContext::if_stat() {
  return getRuleContext<RSIParser::If_statContext>(0);
}

RSIParser::IfStatContext::IfStatContext(StatContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RSIParser::IfStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RSIVisitor*>(visitor))
    return parserVisitor->visitIfStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CallStatContext ------------------------------------------------------------------

RSIParser::Call_statContext* RSIParser::CallStatContext::call_stat() {
  return getRuleContext<RSIParser::Call_statContext>(0);
}

RSIParser::CallStatContext::CallStatContext(StatContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RSIParser::CallStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RSIVisitor*>(visitor))
    return parserVisitor->visitCallStat(this);
  else
    return visitor->visitChildren(this);
}
RSIParser::StatContext* RSIParser::stat() {
  StatContext *_localctx = _tracker.createInstance<StatContext>(_ctx, getState());
  enterRule(_localctx, 4, RSIParser::RuleStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(40);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<RSIParser::AssignStatContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(35);
      assignment();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<RSIParser::IfStatContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(36);
      if_stat();
      break;
    }

    case 3: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<RSIParser::WhileStatContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(37);
      while_stat();
      break;
    }

    case 4: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<RSIParser::LoopStatContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(38);
      loop_stat();
      break;
    }

    case 5: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<RSIParser::CallStatContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(39);
      call_stat();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

RSIParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RSIParser::AssignmentContext::getRuleIndex() const {
  return RSIParser::RuleAssignment;
}

void RSIParser::AssignmentContext::copyFrom(AssignmentContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- AssignExprContext ------------------------------------------------------------------

tree::TerminalNode* RSIParser::AssignExprContext::ID() {
  return getToken(RSIParser::ID, 0);
}

tree::TerminalNode* RSIParser::AssignExprContext::ASSIGN() {
  return getToken(RSIParser::ASSIGN, 0);
}

RSIParser::ExprContext* RSIParser::AssignExprContext::expr() {
  return getRuleContext<RSIParser::ExprContext>(0);
}

RSIParser::AssignExprContext::AssignExprContext(AssignmentContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RSIParser::AssignExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RSIVisitor*>(visitor))
    return parserVisitor->visitAssignExpr(this);
  else
    return visitor->visitChildren(this);
}
RSIParser::AssignmentContext* RSIParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 6, RSIParser::RuleAssignment);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<AssignmentContext *>(_tracker.createInstance<RSIParser::AssignExprContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(42);
    match(RSIParser::ID);
    setState(43);
    match(RSIParser::ASSIGN);
    setState(44);
    expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- If_statContext ------------------------------------------------------------------

RSIParser::If_statContext::If_statContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RSIParser::If_statContext::getRuleIndex() const {
  return RSIParser::RuleIf_stat;
}

void RSIParser::If_statContext::copyFrom(If_statContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IfExprContext ------------------------------------------------------------------

tree::TerminalNode* RSIParser::IfExprContext::IF() {
  return getToken(RSIParser::IF, 0);
}

RSIParser::ExprContext* RSIParser::IfExprContext::expr() {
  return getRuleContext<RSIParser::ExprContext>(0);
}

tree::TerminalNode* RSIParser::IfExprContext::THEN() {
  return getToken(RSIParser::THEN, 0);
}

RSIParser::BlockContext* RSIParser::IfExprContext::block() {
  return getRuleContext<RSIParser::BlockContext>(0);
}

tree::TerminalNode* RSIParser::IfExprContext::END_IF() {
  return getToken(RSIParser::END_IF, 0);
}

std::vector<RSIParser::Elseif_statContext *> RSIParser::IfExprContext::elseif_stat() {
  return getRuleContexts<RSIParser::Elseif_statContext>();
}

RSIParser::Elseif_statContext* RSIParser::IfExprContext::elseif_stat(size_t i) {
  return getRuleContext<RSIParser::Elseif_statContext>(i);
}

RSIParser::Else_statContext* RSIParser::IfExprContext::else_stat() {
  return getRuleContext<RSIParser::Else_statContext>(0);
}

RSIParser::IfExprContext::IfExprContext(If_statContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RSIParser::IfExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RSIVisitor*>(visitor))
    return parserVisitor->visitIfExpr(this);
  else
    return visitor->visitChildren(this);
}
RSIParser::If_statContext* RSIParser::if_stat() {
  If_statContext *_localctx = _tracker.createInstance<If_statContext>(_ctx, getState());
  enterRule(_localctx, 8, RSIParser::RuleIf_stat);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    _localctx = dynamic_cast<If_statContext *>(_tracker.createInstance<RSIParser::IfExprContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(46);
    match(RSIParser::IF);
    setState(47);
    expr();
    setState(48);
    match(RSIParser::THEN);
    setState(49);
    block();
    setState(53);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(50);
        elseif_stat(); 
      }
      setState(55);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
    setState(57);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RSIParser::ELSE) {
      setState(56);
      else_stat();
    }
    setState(59);
    match(RSIParser::END_IF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Elseif_statContext ------------------------------------------------------------------

RSIParser::Elseif_statContext::Elseif_statContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RSIParser::Elseif_statContext::getRuleIndex() const {
  return RSIParser::RuleElseif_stat;
}

void RSIParser::Elseif_statContext::copyFrom(Elseif_statContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ElseifExprContext ------------------------------------------------------------------

tree::TerminalNode* RSIParser::ElseifExprContext::ELSE() {
  return getToken(RSIParser::ELSE, 0);
}

tree::TerminalNode* RSIParser::ElseifExprContext::IF() {
  return getToken(RSIParser::IF, 0);
}

RSIParser::ExprContext* RSIParser::ElseifExprContext::expr() {
  return getRuleContext<RSIParser::ExprContext>(0);
}

tree::TerminalNode* RSIParser::ElseifExprContext::THEN() {
  return getToken(RSIParser::THEN, 0);
}

RSIParser::BlockContext* RSIParser::ElseifExprContext::block() {
  return getRuleContext<RSIParser::BlockContext>(0);
}

RSIParser::ElseifExprContext::ElseifExprContext(Elseif_statContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RSIParser::ElseifExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RSIVisitor*>(visitor))
    return parserVisitor->visitElseifExpr(this);
  else
    return visitor->visitChildren(this);
}
RSIParser::Elseif_statContext* RSIParser::elseif_stat() {
  Elseif_statContext *_localctx = _tracker.createInstance<Elseif_statContext>(_ctx, getState());
  enterRule(_localctx, 10, RSIParser::RuleElseif_stat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<Elseif_statContext *>(_tracker.createInstance<RSIParser::ElseifExprContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(61);
    match(RSIParser::ELSE);
    setState(62);
    match(RSIParser::IF);
    setState(63);
    expr();
    setState(64);
    match(RSIParser::THEN);
    setState(65);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Else_statContext ------------------------------------------------------------------

RSIParser::Else_statContext::Else_statContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RSIParser::Else_statContext::getRuleIndex() const {
  return RSIParser::RuleElse_stat;
}

void RSIParser::Else_statContext::copyFrom(Else_statContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ElseExprContext ------------------------------------------------------------------

tree::TerminalNode* RSIParser::ElseExprContext::ELSE() {
  return getToken(RSIParser::ELSE, 0);
}

RSIParser::BlockContext* RSIParser::ElseExprContext::block() {
  return getRuleContext<RSIParser::BlockContext>(0);
}

RSIParser::ElseExprContext::ElseExprContext(Else_statContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RSIParser::ElseExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RSIVisitor*>(visitor))
    return parserVisitor->visitElseExpr(this);
  else
    return visitor->visitChildren(this);
}
RSIParser::Else_statContext* RSIParser::else_stat() {
  Else_statContext *_localctx = _tracker.createInstance<Else_statContext>(_ctx, getState());
  enterRule(_localctx, 12, RSIParser::RuleElse_stat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<Else_statContext *>(_tracker.createInstance<RSIParser::ElseExprContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(67);
    match(RSIParser::ELSE);
    setState(68);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- While_statContext ------------------------------------------------------------------

RSIParser::While_statContext::While_statContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RSIParser::While_statContext::getRuleIndex() const {
  return RSIParser::RuleWhile_stat;
}

void RSIParser::While_statContext::copyFrom(While_statContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- WhileExprContext ------------------------------------------------------------------

tree::TerminalNode* RSIParser::WhileExprContext::WHILE() {
  return getToken(RSIParser::WHILE, 0);
}

RSIParser::ExprContext* RSIParser::WhileExprContext::expr() {
  return getRuleContext<RSIParser::ExprContext>(0);
}

tree::TerminalNode* RSIParser::WhileExprContext::DO() {
  return getToken(RSIParser::DO, 0);
}

RSIParser::BlockContext* RSIParser::WhileExprContext::block() {
  return getRuleContext<RSIParser::BlockContext>(0);
}

tree::TerminalNode* RSIParser::WhileExprContext::END_WHILE() {
  return getToken(RSIParser::END_WHILE, 0);
}

RSIParser::WhileExprContext::WhileExprContext(While_statContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RSIParser::WhileExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RSIVisitor*>(visitor))
    return parserVisitor->visitWhileExpr(this);
  else
    return visitor->visitChildren(this);
}
RSIParser::While_statContext* RSIParser::while_stat() {
  While_statContext *_localctx = _tracker.createInstance<While_statContext>(_ctx, getState());
  enterRule(_localctx, 14, RSIParser::RuleWhile_stat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<While_statContext *>(_tracker.createInstance<RSIParser::WhileExprContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(70);
    match(RSIParser::WHILE);
    setState(71);
    expr();
    setState(72);
    match(RSIParser::DO);
    setState(73);
    block();
    setState(74);
    match(RSIParser::END_WHILE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Loop_statContext ------------------------------------------------------------------

RSIParser::Loop_statContext::Loop_statContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RSIParser::Loop_statContext::getRuleIndex() const {
  return RSIParser::RuleLoop_stat;
}

void RSIParser::Loop_statContext::copyFrom(Loop_statContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- LoopExprContext ------------------------------------------------------------------

tree::TerminalNode* RSIParser::LoopExprContext::LOOP() {
  return getToken(RSIParser::LOOP, 0);
}

RSIParser::VarContext* RSIParser::LoopExprContext::var() {
  return getRuleContext<RSIParser::VarContext>(0);
}

tree::TerminalNode* RSIParser::LoopExprContext::DO() {
  return getToken(RSIParser::DO, 0);
}

RSIParser::BlockContext* RSIParser::LoopExprContext::block() {
  return getRuleContext<RSIParser::BlockContext>(0);
}

tree::TerminalNode* RSIParser::LoopExprContext::END_LOOP() {
  return getToken(RSIParser::END_LOOP, 0);
}

RSIParser::LoopExprContext::LoopExprContext(Loop_statContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RSIParser::LoopExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RSIVisitor*>(visitor))
    return parserVisitor->visitLoopExpr(this);
  else
    return visitor->visitChildren(this);
}
RSIParser::Loop_statContext* RSIParser::loop_stat() {
  Loop_statContext *_localctx = _tracker.createInstance<Loop_statContext>(_ctx, getState());
  enterRule(_localctx, 16, RSIParser::RuleLoop_stat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<Loop_statContext *>(_tracker.createInstance<RSIParser::LoopExprContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(76);
    match(RSIParser::LOOP);
    setState(77);
    var();
    setState(78);
    match(RSIParser::DO);
    setState(79);
    block();
    setState(80);
    match(RSIParser::END_LOOP);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Call_statContext ------------------------------------------------------------------

RSIParser::Call_statContext::Call_statContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RSIParser::Call_statContext::getRuleIndex() const {
  return RSIParser::RuleCall_stat;
}

void RSIParser::Call_statContext::copyFrom(Call_statContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CallExprContext ------------------------------------------------------------------

tree::TerminalNode* RSIParser::CallExprContext::ID() {
  return getToken(RSIParser::ID, 0);
}

RSIParser::ParamsContext* RSIParser::CallExprContext::params() {
  return getRuleContext<RSIParser::ParamsContext>(0);
}

RSIParser::CallExprContext::CallExprContext(Call_statContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RSIParser::CallExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RSIVisitor*>(visitor))
    return parserVisitor->visitCallExpr(this);
  else
    return visitor->visitChildren(this);
}
RSIParser::Call_statContext* RSIParser::call_stat() {
  Call_statContext *_localctx = _tracker.createInstance<Call_statContext>(_ctx, getState());
  enterRule(_localctx, 18, RSIParser::RuleCall_stat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<Call_statContext *>(_tracker.createInstance<RSIParser::CallExprContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(82);
    match(RSIParser::ID);
    setState(83);
    match(RSIParser::T__0);
    setState(84);
    params();
    setState(85);
    match(RSIParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

RSIParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RSIParser::ExprContext::getRuleIndex() const {
  return RSIParser::RuleExpr;
}

void RSIParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CallContext ------------------------------------------------------------------

RSIParser::Call_statContext* RSIParser::CallContext::call_stat() {
  return getRuleContext<RSIParser::Call_statContext>(0);
}

RSIParser::CallContext::CallContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RSIParser::CallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RSIVisitor*>(visitor))
    return parserVisitor->visitCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VariableContext ------------------------------------------------------------------

RSIParser::VarContext* RSIParser::VariableContext::var() {
  return getRuleContext<RSIParser::VarContext>(0);
}

RSIParser::VariableContext::VariableContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RSIParser::VariableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RSIVisitor*>(visitor))
    return parserVisitor->visitVariable(this);
  else
    return visitor->visitChildren(this);
}
RSIParser::ExprContext* RSIParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 20, RSIParser::RuleExpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(89);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<ExprContext *>(_tracker.createInstance<RSIParser::VariableContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(87);
      var();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<ExprContext *>(_tracker.createInstance<RSIParser::CallContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(88);
      call_stat();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamsContext ------------------------------------------------------------------

RSIParser::ParamsContext::ParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RSIParser::ParamsContext::getRuleIndex() const {
  return RSIParser::RuleParams;
}

void RSIParser::ParamsContext::copyFrom(ParamsContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ParamlistContext ------------------------------------------------------------------

std::vector<RSIParser::VarContext *> RSIParser::ParamlistContext::var() {
  return getRuleContexts<RSIParser::VarContext>();
}

RSIParser::VarContext* RSIParser::ParamlistContext::var(size_t i) {
  return getRuleContext<RSIParser::VarContext>(i);
}

RSIParser::ParamlistContext::ParamlistContext(ParamsContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RSIParser::ParamlistContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RSIVisitor*>(visitor))
    return parserVisitor->visitParamlist(this);
  else
    return visitor->visitChildren(this);
}
RSIParser::ParamsContext* RSIParser::params() {
  ParamsContext *_localctx = _tracker.createInstance<ParamsContext>(_ctx, getState());
  enterRule(_localctx, 22, RSIParser::RuleParams);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<ParamsContext *>(_tracker.createInstance<RSIParser::ParamlistContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(92);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RSIParser::ID

    || _la == RSIParser::NUM) {
      setState(91);
      var();
    }
    setState(98);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RSIParser::T__2) {
      setState(94);
      match(RSIParser::T__2);
      setState(95);
      var();
      setState(100);
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

//----------------- VarContext ------------------------------------------------------------------

RSIParser::VarContext::VarContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t RSIParser::VarContext::getRuleIndex() const {
  return RSIParser::RuleVar;
}

void RSIParser::VarContext::copyFrom(VarContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IdContext ------------------------------------------------------------------

tree::TerminalNode* RSIParser::IdContext::ID() {
  return getToken(RSIParser::ID, 0);
}

RSIParser::IdContext::IdContext(VarContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RSIParser::IdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RSIVisitor*>(visitor))
    return parserVisitor->visitId(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NumContext ------------------------------------------------------------------

tree::TerminalNode* RSIParser::NumContext::NUM() {
  return getToken(RSIParser::NUM, 0);
}

RSIParser::NumContext::NumContext(VarContext *ctx) { copyFrom(ctx); }

antlrcpp::Any RSIParser::NumContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RSIVisitor*>(visitor))
    return parserVisitor->visitNum(this);
  else
    return visitor->visitChildren(this);
}
RSIParser::VarContext* RSIParser::var() {
  VarContext *_localctx = _tracker.createInstance<VarContext>(_ctx, getState());
  enterRule(_localctx, 24, RSIParser::RuleVar);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(103);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case RSIParser::NUM: {
        _localctx = dynamic_cast<VarContext *>(_tracker.createInstance<RSIParser::NumContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(101);
        match(RSIParser::NUM);
        break;
      }

      case RSIParser::ID: {
        _localctx = dynamic_cast<VarContext *>(_tracker.createInstance<RSIParser::IdContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(102);
        match(RSIParser::ID);
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

// Static vars and initialization.
std::vector<dfa::DFA> RSIParser::_decisionToDFA;
atn::PredictionContextCache RSIParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN RSIParser::_atn;
std::vector<uint16_t> RSIParser::_serializedATN;

std::vector<std::string> RSIParser::_ruleNames = {
  "prog", "block", "stat", "assignment", "if_stat", "elseif_stat", "else_stat", 
  "while_stat", "loop_stat", "call_stat", "expr", "params", "var"
};

std::vector<std::string> RSIParser::_literalNames = {
  "", "'('", "')'", "','", "'='", "'IF'", "'THEN'", "'ELSE'", "'END_IF'", 
  "'WHILE'", "'DO'", "'END_WHILE'", "'LOOP'", "'END_LOOP'"
};

std::vector<std::string> RSIParser::_symbolicNames = {
  "", "", "", "", "ASSIGN", "IF", "THEN", "ELSE", "END_IF", "WHILE", "DO", 
  "END_WHILE", "LOOP", "END_LOOP", "ID", "NUM", "COMMENT", "SPACE", "OTHER"
};

dfa::Vocabulary RSIParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> RSIParser::_tokenNames;

RSIParser::Initializer::Initializer() {
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
    0x3, 0x14, 0x6c, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x7, 0x3, 0x21, 0xa, 0x3, 0xc, 0x3, 
    0xe, 0x3, 0x24, 0xb, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x5, 0x4, 0x2b, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 0x36, 0xa, 
    0x6, 0xc, 0x6, 0xe, 0x6, 0x39, 0xb, 0x6, 0x3, 0x6, 0x5, 0x6, 0x3c, 0xa, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0x5c, 0xa, 0xc, 0x3, 0xd, 0x5, 0xd, 
    0x5f, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x7, 0xd, 0x63, 0xa, 0xd, 0xc, 0xd, 
    0xe, 0xd, 0x66, 0xb, 0xd, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0x6a, 0xa, 0xe, 
    0x3, 0xe, 0x2, 0x2, 0xf, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 
    0x14, 0x16, 0x18, 0x1a, 0x2, 0x2, 0x69, 0x2, 0x1c, 0x3, 0x2, 0x2, 0x2, 
    0x4, 0x22, 0x3, 0x2, 0x2, 0x2, 0x6, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x8, 0x2c, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0x30, 0x3, 0x2, 0x2, 0x2, 0xc, 0x3f, 0x3, 0x2, 
    0x2, 0x2, 0xe, 0x45, 0x3, 0x2, 0x2, 0x2, 0x10, 0x48, 0x3, 0x2, 0x2, 
    0x2, 0x12, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x14, 0x54, 0x3, 0x2, 0x2, 0x2, 
    0x16, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x18, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x1a, 
    0x69, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1d, 0x5, 0x4, 0x3, 0x2, 0x1d, 0x1e, 
    0x7, 0x2, 0x2, 0x3, 0x1e, 0x3, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x21, 0x5, 
    0x6, 0x4, 0x2, 0x20, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x21, 0x24, 0x3, 0x2, 
    0x2, 0x2, 0x22, 0x20, 0x3, 0x2, 0x2, 0x2, 0x22, 0x23, 0x3, 0x2, 0x2, 
    0x2, 0x23, 0x5, 0x3, 0x2, 0x2, 0x2, 0x24, 0x22, 0x3, 0x2, 0x2, 0x2, 
    0x25, 0x2b, 0x5, 0x8, 0x5, 0x2, 0x26, 0x2b, 0x5, 0xa, 0x6, 0x2, 0x27, 
    0x2b, 0x5, 0x10, 0x9, 0x2, 0x28, 0x2b, 0x5, 0x12, 0xa, 0x2, 0x29, 0x2b, 
    0x5, 0x14, 0xb, 0x2, 0x2a, 0x25, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x26, 0x3, 
    0x2, 0x2, 0x2, 0x2a, 0x27, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x28, 0x3, 0x2, 
    0x2, 0x2, 0x2a, 0x29, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x7, 0x3, 0x2, 0x2, 
    0x2, 0x2c, 0x2d, 0x7, 0x10, 0x2, 0x2, 0x2d, 0x2e, 0x7, 0x6, 0x2, 0x2, 
    0x2e, 0x2f, 0x5, 0x16, 0xc, 0x2, 0x2f, 0x9, 0x3, 0x2, 0x2, 0x2, 0x30, 
    0x31, 0x7, 0x7, 0x2, 0x2, 0x31, 0x32, 0x5, 0x16, 0xc, 0x2, 0x32, 0x33, 
    0x7, 0x8, 0x2, 0x2, 0x33, 0x37, 0x5, 0x4, 0x3, 0x2, 0x34, 0x36, 0x5, 
    0xc, 0x7, 0x2, 0x35, 0x34, 0x3, 0x2, 0x2, 0x2, 0x36, 0x39, 0x3, 0x2, 
    0x2, 0x2, 0x37, 0x35, 0x3, 0x2, 0x2, 0x2, 0x37, 0x38, 0x3, 0x2, 0x2, 
    0x2, 0x38, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x39, 0x37, 0x3, 0x2, 0x2, 0x2, 
    0x3a, 0x3c, 0x5, 0xe, 0x8, 0x2, 0x3b, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x3b, 
    0x3c, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x3e, 
    0x7, 0xa, 0x2, 0x2, 0x3e, 0xb, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x40, 0x7, 
    0x9, 0x2, 0x2, 0x40, 0x41, 0x7, 0x7, 0x2, 0x2, 0x41, 0x42, 0x5, 0x16, 
    0xc, 0x2, 0x42, 0x43, 0x7, 0x8, 0x2, 0x2, 0x43, 0x44, 0x5, 0x4, 0x3, 
    0x2, 0x44, 0xd, 0x3, 0x2, 0x2, 0x2, 0x45, 0x46, 0x7, 0x9, 0x2, 0x2, 
    0x46, 0x47, 0x5, 0x4, 0x3, 0x2, 0x47, 0xf, 0x3, 0x2, 0x2, 0x2, 0x48, 
    0x49, 0x7, 0xb, 0x2, 0x2, 0x49, 0x4a, 0x5, 0x16, 0xc, 0x2, 0x4a, 0x4b, 
    0x7, 0xc, 0x2, 0x2, 0x4b, 0x4c, 0x5, 0x4, 0x3, 0x2, 0x4c, 0x4d, 0x7, 
    0xd, 0x2, 0x2, 0x4d, 0x11, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x4f, 0x7, 0xe, 
    0x2, 0x2, 0x4f, 0x50, 0x5, 0x1a, 0xe, 0x2, 0x50, 0x51, 0x7, 0xc, 0x2, 
    0x2, 0x51, 0x52, 0x5, 0x4, 0x3, 0x2, 0x52, 0x53, 0x7, 0xf, 0x2, 0x2, 
    0x53, 0x13, 0x3, 0x2, 0x2, 0x2, 0x54, 0x55, 0x7, 0x10, 0x2, 0x2, 0x55, 
    0x56, 0x7, 0x3, 0x2, 0x2, 0x56, 0x57, 0x5, 0x18, 0xd, 0x2, 0x57, 0x58, 
    0x7, 0x4, 0x2, 0x2, 0x58, 0x15, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5c, 0x5, 
    0x1a, 0xe, 0x2, 0x5a, 0x5c, 0x5, 0x14, 0xb, 0x2, 0x5b, 0x59, 0x3, 0x2, 
    0x2, 0x2, 0x5b, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x17, 0x3, 0x2, 0x2, 
    0x2, 0x5d, 0x5f, 0x5, 0x1a, 0xe, 0x2, 0x5e, 0x5d, 0x3, 0x2, 0x2, 0x2, 
    0x5e, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x5f, 0x64, 0x3, 0x2, 0x2, 0x2, 0x60, 
    0x61, 0x7, 0x5, 0x2, 0x2, 0x61, 0x63, 0x5, 0x1a, 0xe, 0x2, 0x62, 0x60, 
    0x3, 0x2, 0x2, 0x2, 0x63, 0x66, 0x3, 0x2, 0x2, 0x2, 0x64, 0x62, 0x3, 
    0x2, 0x2, 0x2, 0x64, 0x65, 0x3, 0x2, 0x2, 0x2, 0x65, 0x19, 0x3, 0x2, 
    0x2, 0x2, 0x66, 0x64, 0x3, 0x2, 0x2, 0x2, 0x67, 0x6a, 0x7, 0x11, 0x2, 
    0x2, 0x68, 0x6a, 0x7, 0x10, 0x2, 0x2, 0x69, 0x67, 0x3, 0x2, 0x2, 0x2, 
    0x69, 0x68, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xa, 
    0x22, 0x2a, 0x37, 0x3b, 0x5b, 0x5e, 0x64, 0x69, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

RSIParser::Initializer RSIParser::_init;
