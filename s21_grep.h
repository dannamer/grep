#ifndef S21_GREP_H
#define S21_GREP_H
#include <stdbool.h>

typedef struct {
  size_t count;
  char **patern;
} Pattern;

typedef struct {
  Pattern e;
  bool i;
  bool v;
  bool c;
  bool l;
  bool n;
  bool h;
  bool s;
  bool f;
  bool o;
} FLAGS;

#endif