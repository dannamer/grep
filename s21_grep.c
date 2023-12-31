#include "s21_grep.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>



int main(int argc, char **argv) { FLAGS flags = {0}; }

void parser(int argc, char **argv, FLAGS *flags) {
  const char SHORTOPTS[] = "e:f:isvnholc";
  int opt;
  while ((opt = getopt(argc, argv, SHORTOPTS)) != -1) {
    switch (opt) {
      case 'e':
				
        printf("Option -e is set with value: %s\n", optarg);
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
	E->patern = realloc(E->patern, ++E->count * sizeof(char *));
	size_t len = strlen(optarg);
	E->patern[E->count] = realloc(E->patern[E->count], len * sizeof(char));
	
}