#include "s21_grep.h"

#include <getopt.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  FLAGS flags = {"", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  FILE *file;
  parser(argc, argv, &flags);
  openFile(argc, argv, &file);
}

void printFinish(FLAGS flags, FILE *file) {}

void paternCheckFile(char *patern, FILE *file) {
  regex_t regex;
  if (regcomp(&regex, patern, 0)) {
    fprintf(stderr, "Could not compile regex\n");
    exit(1);
  }
  char *line;
  while ((line = readline(file)) != NULL) {
    if (!regexec(&regex, line, 0, NULL, 0)) {
      printf("%s\n", line);
    }
    free(line);
  }
}

char *readline(FILE *file) {
  char *line = NULL, *tmp = NULL;
  size_t size = 0, index = 0, chunkSize = 100;
  int ch;
  while ((ch = fgetc(file)) != '\n' && ch != EOF) {
    if (index == size) {
      size += chunkSize;
      tmp = realloc(line, size);
      if (!tmp) {
        free(line);
        line = NULL;
        break;
      }
      line = tmp;
    }
    line[index++] = ch;
  }
  if (line) {
    line[index] = '\0';
  }

  return line;
}

void openFile(int argc, char **argv, FILE **file) {
  for (int i = optind; i < argc; i++) {
    if ((*file = fopen(argv[i], "r")) == NULL) {
      fprintf(stderr, "grep: %s No such file or directory\n", argv[i]);
    }
  }
}

void parser(int argc, char **argv, FLAGS *flags) {
  int opt;
  while ((opt = getopt(argc, argv, "e:f:isvnholc")) != -1) {
    switch (opt) {
      case 'e':
        flags->e = true;
        addPatern(&flags->patern);
        break;
      case 'f':
        flags->f = true;
        break;
      case 'i':
        flags->i = true;
        break;
      case 's':
        flags->s = true;
        break;
      case 'v':
        flags->v = true;
        break;
      case 'n':
        flags->n = true;
        break;
      case 'h':
        flags->h = true;
        break;
      case 'o':
        flags->o = true;
        break;
      case 'l':
        flags->l = true;
        break;
      case 'c':
        flags->c = true;
        break;
      default: /* '?' */
        fprintf(stderr, "Usage: %s [-e value]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
  }
}

void addPatern(char **patern) {
  int len = 0;
  if (*patern) len = strlen(*patern);
  int lol = 0;
  lol = strlen(optarg);
  *patern = realloc(*patern, len + lol + 4);
  len ? strcat(strcat(*patern, "\\|"), optarg) : strcpy(patern, optarg);
}