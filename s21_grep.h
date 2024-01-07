#ifndef S21_GREP_H
#define S21_GREP_H
#include <stdbool.h>
#include <stdio.h>

typedef struct {
  char *patern;
  bool e;
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

void printFinish(FLAGS flags, FILE *file);
void paternCheckFile(char *patern, FILE *file);
char *readline(FILE *file);
void openFile(int argc, char **argv, FILE **file);
void parser(int argc, char **argv, FLAGS *flags);
void addPatern(char **patern);

#endif