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
  bool files;
  int flag;
} FLAGS;

void printFinish(FLAGS flags, FILE *file);
void addFilePattern(char **patern);
void paternCheckFile(FLAGS *flags, FILE *file, char *files);
char *readline(FILE *file);
void openFile(int argc, char **argv, FLAGS *flags);
void parser(int argc, char **argv, FLAGS *flags);
void addPattern(char **pattern);

#endif