#ifndef PARSER_H
#define PARSER_H

#include "ASTNode.h"

// Type of symbol read by parser
enum TokenType
{
  Error, // Handles unexpected symbols
  Plus, // Handles addition
  Minus, // Handles subtraction and unary minus
  Mul, // Handles multiplication
  Div, // Handles division
  Power, // Handles powers
  EndOfText, // Handles end of expression
  OpenParenthesis, // Handles open parenthesis
  ClosedParenthesis, // Handles closed parenthesis
  Number, // Handles numeric values
  Variable, // Handles variable
  Func // Handles functions
};

// Holds information on read token
struct Token{
  TokenType Type;
  double Value; // Parsed to zero if non-number
  char Symbol;

  Token():Type(Error), Value(0), Symbol(0) // Default Token
  {}
};

// Handles all parsing
class Parser{
  Token m_crtToken; // current token
  const char* m_Text; // string to be parsed
  size_t m_Index; // current reading position in m_Text

  char m_Var; // given variable symbol

private:

  ASTNode* Expression(); // creates node L: TERM + R: EXP1

  ASTNode* Expression1(); // creates node L: EXP1 + or - R: TERM or if other symbol present, creates 0 number node

  ASTNode* Term(); // creates node L: POWA * R: TERM1

  ASTNode* Term1(); // creates node L: TERM1 * or / R: POWA or if other symbol present, creates 1 number node

  ASTNode* Powa();  // creates node L: FACT ^ R: POWA1

  ASTNode* Powa1(); // creates node L: FACT ^ R: POWA1 or if other symbol present, creates 1 number node

  ASTNode* Factor(); // creates parenthetical node (restart at expression), unary minus node (as left factor node), or creates number node.

  ASTNode* CreateNode(ASTNodeType type, ASTNode* left, ASTNode* right); // creates simple node

  ASTNode* CreateUnaryNode(ASTNode* left); // creates unary minus node

  ASTNode* CreateNodeNumber(double value); // creates number node

  ASTNode* CreateNodeVariable(char symbol); // create variable node

  ASTNode* CreateFunctionNode(ASTNode* left, char shortkey); // creates function node

  void Match(char expected); // checks to make sure loaded text index has predicted symbol before loading next token

  void SkipWhitespaces(); // skips whitespaces in input

  void GetNextToken(); // determines and loads desired token from m_Text[m_Index] to m_crtToken.

  double GetNumber(); // reads m_Text for decimal numbers

  char ReadFunction(); // reads m_Text for functions

public:

  ASTNode* Parse(const char* text, const char var); // loads text to m_Text, sets m_Index to zero and creates AST node by node

};

// Handles events occuring in Parser member functions which occur due to invalid user input
class ParserException : public std::exception {
  int m_Pos;
  std::string m_Message;

public:
  ParserException(const std::string& message, int pos):m_Message(message), m_Pos(pos){}
  ~ParserException() throw () {}
  const char * what () const throw () {
    return m_Message.c_str();
  }

};

#endif
