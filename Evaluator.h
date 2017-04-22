#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "ASTNode.h"

// Class whose member functions read a given AST
class Evaluator{
  double EvaluateSubTree(ASTNode* ast, const char var, const double val); // Evaluates AST starting at given node
public:
  double Evaluate(ASTNode* ast, const char var, const double val); // Calls EvaluateSubTree after verifying that ast appears to be a somewhat valid ASTNode
};

// Handles improperly formated AST's fed to Evaluate class
class EvaluatorException : public std::exception {
  std::string m_Message;
public:
  EvaluatorException(const std::string& message):m_Message(message) {}
  ~EvaluatorException() throw() {}
  const char * what () const throw () {
    return m_Message.c_str();
  }
};

#endif
