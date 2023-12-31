#include "s21_grep.h"
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char **argv) { FLAGS flags = {0}; }

void parser(int argc, char **argv, FLAGS *flags) {
  int opt;
  while ((opt = getopt(argc, argv, "e:")) != -1) {
    switch (opt) {
      case 'e':
				
        printf("Option -e is set with value: %s\n", optarg);
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