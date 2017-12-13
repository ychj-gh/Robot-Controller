
// Generated from RCcode.g by ANTLR 4.6

#pragma once


#include "antlr4-runtime.h"




class  RCcodeLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, GOTO = 5, IF = 6, THEN = 7, 
    ELSEIF = 8, ELSE = 9, ENDIF = 10, ASSIGN = 11, WHILE = 12, DO = 13, 
    ENDWL = 14, FOR = 15, TO = 16, BY = 17, ENDFOR = 18, MOVJ = 19, MOVL = 20, 
    MOVC = 21, MOVS = 22, SHIFTON = 23, SHIFTOFF = 24, SET = 25, SETE = 26, 
    GETE = 27, WAIT = 28, DELAY = 29, SETOUT = 30, DIN = 31, LABEL = 32, 
    RET = 33, NOP = 34, PAUSE = 35, HALT = 36, BREAK = 37, INCR = 38, DECR = 39, 
    CALL = 40, EQ = 41, GT = 42, GE = 43, LT = 44, LE = 45, NE = 46, ADD = 47, 
    SUB = 48, MUL = 49, DIV = 50, FUNC = 51, TIME = 52, ELEM = 53, CSTRING = 54, 
    CH = 55, ID = 56, NUM = 57, COMMENT = 58, SPACE = 59, OTHER = 60
  };

  RCcodeLexer(antlr4::CharStream *input);
  ~RCcodeLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

