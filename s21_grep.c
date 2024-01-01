#include "s21_grep.h"

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char **argv) {
  FLAGS flags = {0};
  FILE *file;
  parser(argc, argv, &flags);
  openFile(argc, argv, &file);

}

void printFinish(FLAGS flags, FILE *file) {
  
}

void openFile(int argc, char **argv, FILE **file) {
  for (int i = optarg; i < argc, i++) {
    if(*file = fopen(argv[i], "r") == NULL) {
      // ошибка;
    }
  }
}

void parser(int argc, char **argv, FLAGS *flags) {
  const char SHORTOPTS[] = "e:f:isvnholc";
  int opt;
  while ((opt = getopt(argc, argv, SHORTOPTS)) != -1) {
    switch (opt) {
      case 'e':
        addPaternE(&FLAGS->e);
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

void addPaternE(FLAG_E *E) {
  E->patern = realloc(E->patern, (E->count + 1) * sizeof(char *));
  size_t len = strlen(optarg);
  E->patern[E->count] = realloc(E->patern[E->count], len * sizeof(char) + 1);
  strcpy(E->patern[E->count++], optarg);
}