
// Generated from RCdata.g by ANTLR 4.6

#pragma once


#include "antlr4-runtime.h"




class  RCdataParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, ASSIGN = 3, BOOL = 4, CHAR = 5, INT = 6, REAL = 7, 
    STRING = 8, JTPOSE = 9, TRPOSE = 10, TOOLDATA = 11, COORDATA = 12, COORDO = 13, 
    COORDT = 14, TRUE = 15, FALSE = 16, PID = 17, BPID = 18, EXID = 19, 
    CSTRING = 20, CH = 21, ID = 22, NUM = 23, COMMENT = 24, SPACE = 25, 
    OTHER = 26
  };

  enum {
    RuleProg = 0, RuleBlock = 1, RuleStat = 2, RuleBool_stat = 3, RuleBoolval = 4, 
    RuleChar_stat = 5, RuleInt_stat = 6, RuleReal_stat = 7, RuleString_stat = 8, 
    RuleJtpose_stat = 9, RuleTrpose_stat = 10, RuleTool_stat = 11, RuleCoord_stat = 12
  };

  RCdataParser(antlr4::TokenStream *input);
  ~RCdataParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class ProgContext;
  class BlockContext;
  class StatContext;
  class Bool_statContext;
  class BoolvalContext;
  class Char_statContext;
  class Int_statContext;
  class Real_statContext;
  class String_statContext;
  class Jtpose_statContext;
  class Trpose_statContext;
  class Tool_statContext;
  class Coord_statContext; 

  class  ProgContext : public antlr4::ParserRuleContext {
  public:
    ProgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ProgContext() : antlr4::ParserRuleContext() { }
    void copyFrom(ProgContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ProgramContext : public ProgContext {
  public:
    ProgramContext(ProgContext *ctx);

    BlockContext *block();
    antlr4::tree::TerminalNode *EOF();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ProgContext* prog();

  class  BlockContext : public antlr4::ParserRuleContext {
  public:
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    BlockContext() : antlr4::ParserRuleContext() { }
    void copyFrom(BlockContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  StatBlockContext : public BlockContext {
  public:
    StatBlockContext(BlockContext *ctx);

    std::vector<StatContext *> stat();
    StatContext* stat(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  BlockContext* block();

  class  StatContext : public antlr4::ParserRuleContext {
  public:
    StatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    StatContext() : antlr4::ParserRuleContext() { }
    void copyFrom(StatContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  CharStatContext : public StatContext {
  public:
    CharStatContext(StatContext *ctx);

    Char_statContext *char_stat();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TrposeStatContext : public StatContext {
  public:
    TrposeStatContext(StatContext *ctx);

    Trpose_statContext *trpose_stat();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BoolStatContext : public StatContext {
  public:
    BoolStatContext(StatContext *ctx);

    Bool_statContext *bool_stat();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ToolStatContext : public StatContext {
  public:
    ToolStatContext(StatContext *ctx);

    Tool_statContext *tool_stat();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CoordStatContext : public StatContext {
  public:
    CoordStatContext(StatContext *ctx);

    Coord_statContext *coord_stat();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  RealStatContext : public StatContext {
  public:
    RealStatContext(StatContext *ctx);

    Real_statContext *real_stat();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IntStatContext : public StatContext {
  public:
    IntStatContext(StatContext *ctx);

    Int_statContext *int_stat();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StringStatContext : public StatContext {
  public:
    StringStatContext(StatContext *ctx);

    String_statContext *string_stat();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  JtposeStatContext : public StatContext {
  public:
    JtposeStatContext(StatContext *ctx);

    Jtpose_statContext *jtpose_stat();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  StatContext* stat();

  class  Bool_statContext : public antlr4::ParserRuleContext {
  public:
    Bool_statContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Bool_statContext() : antlr4::ParserRuleContext() { }
    void copyFrom(Bool_statContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  BoolExprContext : public Bool_statContext {
  public:
    BoolExprContext(Bool_statContext *ctx);

    antlr4::tree::TerminalNode *BOOL();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *ASSIGN();
    BoolvalContext *boolval();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Bool_statContext* bool_stat();

  class  BoolvalContext : public antlr4::ParserRuleContext {
  public:
    BoolvalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    BoolvalContext() : antlr4::ParserRuleContext() { }
    void copyFrom(BoolvalContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  FalseExprContext : public BoolvalContext {
  public:
    FalseExprContext(BoolvalContext *ctx);

    antlr4::tree::TerminalNode *FALSE();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TrueExprContext : public BoolvalContext {
  public:
    TrueExprContext(BoolvalContext *ctx);

    antlr4::tree::TerminalNode *TRUE();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  BoolvalContext* boolval();

  class  Char_statContext : public antlr4::ParserRuleContext {
  public:
    Char_statContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Char_statContext() : antlr4::ParserRuleContext() { }
    void copyFrom(Char_statContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  CharExprContext : public Char_statContext {
  public:
    CharExprContext(Char_statContext *ctx);

    antlr4::tree::TerminalNode *CHAR();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *ASSIGN();
    antlr4::tree::TerminalNode *CH();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Char_statContext* char_stat();

  class  Int_statContext : public antlr4::ParserRuleContext {
  public:
    Int_statContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Int_statContext() : antlr4::ParserRuleContext() { }
    void copyFrom(Int_statContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  IntExprContext : public Int_statContext {
  public:
    IntExprContext(Int_statContext *ctx);

    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *ASSIGN();
    antlr4::tree::TerminalNode *NUM();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Int_statContext* int_stat();

  class  Real_statContext : public antlr4::ParserRuleContext {
  public:
    Real_statContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Real_statContext() : antlr4::ParserRuleContext() { }
    void copyFrom(Real_statContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  RealExprContext : public Real_statContext {
  public:
    RealExprContext(Real_statContext *ctx);

    antlr4::tree::TerminalNode *REAL();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *ASSIGN();
    antlr4::tree::TerminalNode *NUM();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Real_statContext* real_stat();

  class  String_statContext : public antlr4::ParserRuleContext {
  public:
    String_statContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    String_statContext() : antlr4::ParserRuleContext() { }
    void copyFrom(String_statContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  StringExprContext : public String_statContext {
  public:
    StringExprContext(String_statContext *ctx);

    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *ASSIGN();
    antlr4::tree::TerminalNode *CSTRING();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  String_statContext* string_stat();

  class  Jtpose_statContext : public antlr4::ParserRuleContext {
  public:
    Jtpose_statContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Jtpose_statContext() : antlr4::ParserRuleContext() { }
    void copyFrom(Jtpose_statContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  JtposeExpr1Context : public Jtpose_statContext {
  public:
    JtposeExpr1Context(Jtpose_statContext *ctx);

    antlr4::tree::TerminalNode *JTPOSE();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *ASSIGN();
    std::vector<antlr4::tree::TerminalNode *> NUM();
    antlr4::tree::TerminalNode* NUM(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  JtposeExpr2Context : public Jtpose_statContext {
  public:
    JtposeExpr2Context(Jtpose_statContext *ctx);

    antlr4::tree::TerminalNode *PID();
    antlr4::tree::TerminalNode *ASSIGN();
    std::vector<antlr4::tree::TerminalNode *> NUM();
    antlr4::tree::TerminalNode* NUM(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Jtpose_statContext* jtpose_stat();

  class  Trpose_statContext : public antlr4::ParserRuleContext {
  public:
    Trpose_statContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Trpose_statContext() : antlr4::ParserRuleContext() { }
    void copyFrom(Trpose_statContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  TrposeExpr1Context : public Trpose_statContext {
  public:
    TrposeExpr1Context(Trpose_statContext *ctx);

    antlr4::tree::TerminalNode *TRPOSE();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *ASSIGN();
    std::vector<antlr4::tree::TerminalNode *> NUM();
    antlr4::tree::TerminalNode* NUM(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TrposeExpr3Context : public Trpose_statContext {
  public:
    TrposeExpr3Context(Trpose_statContext *ctx);

    antlr4::tree::TerminalNode *EXID();
    antlr4::tree::TerminalNode *ASSIGN();
    std::vector<antlr4::tree::TerminalNode *> NUM();
    antlr4::tree::TerminalNode* NUM(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TrposeExpr2Context : public Trpose_statContext {
  public:
    TrposeExpr2Context(Trpose_statContext *ctx);

    antlr4::tree::TerminalNode *BPID();
    antlr4::tree::TerminalNode *ASSIGN();
    std::vector<antlr4::tree::TerminalNode *> NUM();
    antlr4::tree::TerminalNode* NUM(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Trpose_statContext* trpose_stat();

  class  Tool_statContext : public antlr4::ParserRuleContext {
  public:
    Tool_statContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Tool_statContext() : antlr4::ParserRuleContext() { }
    void copyFrom(Tool_statContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ToolExprContext : public Tool_statContext {
  public:
    ToolExprContext(Tool_statContext *ctx);

    antlr4::tree::TerminalNode *TOOLDATA();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *ASSIGN();
    std::vector<antlr4::tree::TerminalNode *> NUM();
    antlr4::tree::TerminalNode* NUM(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Tool_statContext* tool_stat();

  class  Coord_statContext : public antlr4::ParserRuleContext {
  public:
    Coord_statContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Coord_statContext() : antlr4::ParserRuleContext() { }
    void copyFrom(Coord_statContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  CoordExprContext : public Coord_statContext {
  public:
    CoordExprContext(Coord_statContext *ctx);

    antlr4::Token *op = nullptr;
    antlr4::Token *op1 = nullptr;
    antlr4::Token *op2 = nullptr;
    antlr4::Token *op3 = nullptr;
    antlr4::tree::TerminalNode *COORDATA();
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    antlr4::tree::TerminalNode *COORDO();
    antlr4::tree::TerminalNode *COORDT();
    std::vector<antlr4::tree::TerminalNode *> BPID();
    antlr4::tree::TerminalNode* BPID(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Coord_statContext* coord_stat();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

