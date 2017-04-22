/* Function to char key

sin -> s
cos -> c
tan -> t
sqrt -> r
exp -> e
abs -> a
ln -> l

*/

#ifndef FUNCTIONKEY_H
#define FUNCTIONKEY_H

#include <cmath>
#include <cstring>
#include <cctype>
#include <cstddef>
#include <sstream>
#include <exception>
#include <cstdlib>


typedef double (*f)(double);

char ParseKey(char *longkey);
f GetFunction(char shortkey);

class FunctionKeyException : public std::exception {
  std::string m_Message;
public:
  FunctionKeyException(const std::string& message):m_Message(message) {}
  ~FunctionKeyException() throw() {}
  const char * what () const throw () {
    return m_Message.c_str();
  }
};

#endif
