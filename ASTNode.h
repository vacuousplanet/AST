#ifndef ASTNODE_H
#define ASTNODE_H

#include "FunctionKey.h"

enum ASTNodeType{
  Undefined,
  OperatorPlus,
  OperatorMinus,
  OperatorMul,
  OperatorDiv,
  OperatorPow,
  UnaryMinus,
  NumberValue,
  VariableValue,
  Function
};

class ASTNode{
public:
  ASTNodeType Type;
  double Value;
  char Symbol;
  ASTNode* Right;
  ASTNode* Left;

  ASTNode();

  ~ASTNode();
};

#endif
