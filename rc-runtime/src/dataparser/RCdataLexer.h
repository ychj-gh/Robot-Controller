
// Generated from RCdata.g by ANTLR 4.6

#pragma once


#include "antlr4-runtime.h"




class  RCdataLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, ASSIGN = 3, BOOL = 4, CHAR = 5, INT = 6, REAL = 7, 
    STRING = 8, JTPOSE = 9, TRPOSE = 10, TOOLDATA = 11, COORDATA = 12, COORDO = 13, 
    COORDT = 14, TRUE = 15, FALSE = 16, PID = 17, BPID = 18, EXID = 19, 
    CSTRING = 20, CH = 21, ID = 22, NUM = 23, COMMENT = 24, SPACE = 25, 
    OTHER = 26
  };

  RCdataLexer(antlr4::CharStream *input);
  ~RCdataLexer();

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

