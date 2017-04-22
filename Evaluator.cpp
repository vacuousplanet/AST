#include "Evaluator.h"
#include <cmath>

double Evaluator::EvaluateSubTree(ASTNode* ast, const char var, const double val){
  if(ast == NULL){
    throw EvaluatorException("Incorrect syntax tree!");
  }
  if(ast->Type == NumberValue){
    return ast->Value;
  }
  else if(ast->Type == VariableValue){
    if(ast->Symbol == var){
      return val;
    }
    else{
      throw EvaluatorException("Incorrect variable name");
    }
  }
  else if(ast->Type == UnaryMinus){
    return -EvaluateSubTree(ast->Left, var, val);
  }
  else if(ast->Type == Function){
    f retFunc = GetFunction(ast->Symbol);
    return retFunc(EvaluateSubTree(ast->Left, var, val));
  }
  else{
    double v1 = EvaluateSubTree(ast->Left, var, val);
    double v2 = EvaluateSubTree(ast->Right, var, val);
    switch(ast->Type)
    {
    case OperatorPlus:  return v1 + v2;
    case OperatorMinus: return v1 - v2;
    case OperatorMul:   return v1 * v2;
    case OperatorDiv:   return v1 / v2;
    case OperatorPow:   return pow(v1, v2);
    }
  }
  throw EvaluatorException("Incorrect syntax tree!");
}

double Evaluator::Evaluate(ASTNode* ast, const char var, const double val){
  if(ast == NULL){
    throw EvaluatorException("Incorrect abstract syntax tree");
  }
  return EvaluateSubTree(ast, var, val);
}
