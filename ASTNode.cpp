#include "ASTNode.h"

ASTNode::ASTNode(){
  Type = Undefined;
  Value = 0;
  Symbol = 0;
  Right = NULL;
  Left = NULL;
}

ASTNode::~ASTNode(){
  delete Right;
  delete Left;
}
