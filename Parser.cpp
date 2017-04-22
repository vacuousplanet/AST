#include "Parser.h"

ASTNode* Parser::Expression(){
  ASTNode* tnode = Term();
  ASTNode* e1node = Expression1();

  return CreateNode(OperatorPlus, tnode, e1node);
}

ASTNode* Parser::Expression1(){
  ASTNode* tnode;
  ASTNode* e1node;

  switch(m_crtToken.Type)
  {
  case Plus:
    GetNextToken();
    tnode = Term();
    e1node = Expression1();

    return CreateNode(OperatorPlus, e1node, tnode);
  case Minus:
    GetNextToken();
    tnode = Term();
    e1node = Expression1();

    return CreateNode(OperatorMinus, e1node, tnode);
  }

  return CreateNodeNumber(0);
}

ASTNode* Parser::Term(){
  ASTNode* pnode = Powa();
  ASTNode* t1node = Term1();

  return CreateNode(OperatorMul, pnode, t1node);
}

ASTNode* Parser::Term1(){
  ASTNode* pnode;
  ASTNode* t1node;

  switch(m_crtToken.Type)
  {
  case Mul:
    GetNextToken();
    pnode = Powa();
    t1node = Term1();

    return CreateNode(OperatorMul, t1node, pnode);
  case Div:
    GetNextToken();
    pnode = Powa();
    t1node = Term1();

    return CreateNode(OperatorDiv, t1node, pnode);
  }

  return CreateNodeNumber(1);
}

ASTNode* Parser::Powa(){
  ASTNode* fnode = Factor();
  ASTNode* p1node = Powa1();

  return CreateNode(OperatorPow, fnode, p1node);
}

ASTNode* Parser::Powa1(){
  ASTNode* fnode;
  ASTNode* p1node;

  if(m_crtToken.Type == Power){
    GetNextToken();
    fnode = Factor();
    p1node = Powa1();

    return CreateNode(OperatorPow, fnode, p1node);
  }
  else{
    return CreateNodeNumber(1);
  }
}

ASTNode* Parser::Factor(){
  ASTNode* node;
  double value;
  char symbol;
  switch(m_crtToken.Type)
  {
  case OpenParenthesis:
    GetNextToken();
    node = Expression();
    Match(')');
    return node;
  case Minus:
    GetNextToken();
    node = Factor();
    return CreateUnaryNode(node);
  case Number:
    value = m_crtToken.Value;
    GetNextToken();
    return CreateNodeNumber(value);
  case Variable:
    symbol = m_crtToken.Symbol;
    GetNextToken();
    return CreateNodeVariable(symbol);
  case Func:
    symbol = m_crtToken.Symbol;
    GetNextToken();
    node = Factor();
    return CreateFunctionNode(node, symbol);
  default:
    std::stringstream sstr;
    sstr << "Unexpected token '" << m_crtToken.Symbol << "' at position " << m_Index;
    throw ParserException(sstr.str(), m_Index);
  }
}

ASTNode* Parser::CreateNode(ASTNodeType type, ASTNode* left, ASTNode* right){
  ASTNode* node = new ASTNode;
  node->Type = type;
  node->Left = left;
  node->Right = right;

  return node;
}

ASTNode* Parser::CreateUnaryNode(ASTNode* left){
  ASTNode* node = new ASTNode;
  node->Type = UnaryMinus;
  node->Left = left;
  node->Right = NULL;

  return node;
}

ASTNode* Parser::CreateNodeNumber(double value){
  ASTNode* node = new ASTNode;
  node->Type = NumberValue;
  node->Value = value;

  return node;
}

ASTNode* Parser::CreateNodeVariable(char symbol){
  ASTNode* node = new ASTNode;
  node->Type = VariableValue;
  node->Symbol = symbol;

  return node;
}

ASTNode* Parser::CreateFunctionNode(ASTNode* left, char shortkey){
  ASTNode* node = new ASTNode;
  node->Type = Function;
  node->Symbol = shortkey;
  node->Left = left;
  node->Right = NULL;

  return node;
}

void Parser::Match(char expected){
  if(m_Text[m_Index-1] == expected){
    GetNextToken();
  }
  else{
    std::stringstream sstr;
    sstr << "Expected token '" << expected << "' at position " << m_Index;
    throw ParserException(sstr.str(), m_Index);
  }
}

void Parser::SkipWhitespaces(){
  while(isspace(m_Text[m_Index])) m_Index++;
}

void Parser::GetNextToken(){
  SkipWhitespaces();

  m_crtToken.Value = 0;
  m_crtToken.Symbol = 0;

  if(m_Text[m_Index] == 0){
    m_crtToken.Type = EndOfText;
    return;
  }

  if(isdigit(m_Text[m_Index])){
    m_crtToken.Type = Number;
    m_crtToken.Value = GetNumber();
    return;
  }

  m_crtToken.Type = Error;

  switch(m_Text[m_Index])
  {
  case '+': m_crtToken.Type = Plus; break;
  case '-': m_crtToken.Type = Minus; break;
  case '*': m_crtToken.Type = Mul; break;
  case '/': m_crtToken.Type = Div; break;
  case '^': m_crtToken.Type = Power; break;
  case '(': m_crtToken.Type = OpenParenthesis; break;
  case ')': m_crtToken.Type = ClosedParenthesis; break;
  }
  if(isalpha(m_Text[m_Index])){
    if(m_Text[m_Index] == m_Var && !isalpha(m_Text[m_Index+1]) ){ // FIXME? This line makes the program vulnerable to functions written like 'S I N' if S is your variable, but this shouldn't be an issue
      m_crtToken.Type = Variable;
      m_crtToken.Symbol = m_Var;
    }
    else{
      m_crtToken.Type = Func;
      m_crtToken.Symbol = ReadFunction();
      return;
    }
  }
  if(m_crtToken.Type != Error){
    m_crtToken.Symbol = m_Text[m_Index];
    m_Index++;
  }
  else{
    std::stringstream sstr;
    sstr << "Unexpected token '" << m_Text[m_Index] << "' at position " << m_Index;
    throw ParserException(sstr.str(), m_Index);
  }
}

double Parser::GetNumber(){
  SkipWhitespaces();

  int index = m_Index;
  while(isdigit(m_Text[m_Index])) m_Index++;
  if(m_Text[m_Index] == '.') m_Index++;
  while(isdigit(m_Text[m_Index])) m_Index++;

  if(m_Index - index == 0){
    throw ParserException("Number expected but not found!", m_Index);
  }
  char buffer[32] = {0};
  memcpy(buffer, &m_Text[index], m_Index - index);

  return atof(buffer);
}

char Parser::ReadFunction(){
  SkipWhitespaces();

  int index = m_Index;
  while(isalpha(m_Text[m_Index])) m_Index++;

  if(m_Index - index == 0){
    throw ParserException("Function expected but not found!", m_Index);
  }
  char buffer[4] = {0};
  memcpy(buffer, &m_Text[index], m_Index - index);

  return ParseKey(buffer);
}

ASTNode* Parser::Parse(const char* text, const char var){
  m_Text = text;
  m_Index = 0;
  m_Var = var;
  GetNextToken();

  return Expression();
}
