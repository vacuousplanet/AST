#include "FunctionKey.h"

char ParseKey(char *longkey){
  int size = 0;
  while(longkey[size] != '\0'){
    size++;
  }
  char* lowerLongkey = new char[size];
  int i = 0;
  while(i <= size){
    lowerLongkey[i] = tolower(longkey[i]);
    i++;
  }
  if(strcmp(lowerLongkey, "sin") == 0){
    return 's';
  }
  else if(strcmp(lowerLongkey, "cos") == 0){
    return 'c';
  }
  else if(strcmp(lowerLongkey, "tan") == 0){
    return 't';
  }
  else if(strcmp(lowerLongkey, "sqrt") == 0){
    return 'r';
  }
  else if(strcmp(lowerLongkey, "exp") == 0){
    return 'e';
  }
  else if(strcmp(lowerLongkey, "abs") == 0){
    return 'a';
  }
  else if(strcmp(lowerLongkey, "ln") == 0 || strcmp(lowerLongkey, "log") == 0){
    return 'l';
  }
  else{
    throw FunctionKeyException("Function not found!");
  }
}

f GetFunction(char shortkey){
  switch(shortkey){
  case 's': return sin;
  case 'c': return cos;
  case 't': return tan;
  case 'r': return sqrt;
  case 'e': return exp;
  case 'a': return fabs;
  case 'l': return log;
  default: throw FunctionKeyException("Invalid function key!");
  }
}
