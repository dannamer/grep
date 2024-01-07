#include "s21_grep.h"

#include <getopt.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  FLAGS flags = {0};
  parser(argc, argv, &flags);
  openFile(argc, argv, &flags);
}

void paternCheckFile(FLAGS *flags, FILE *file, char *files) {
  regex_t regex;
  if (regcomp(&regex, flags->patern, 0)) {
    fprintf(stderr, "Could not compile regex\n");
    exit(1);
  }
  char *line;
  while ((line = readline(file)) != NULL) {
    if (flags->v == regexec(&regex, line, 0, NULL, 0)) {
      if (flags->l) {
        printf("%s\n", files);
        break;
      } else {
        if (flags->files) {
          printf("%s:%s\n", files, line);
        } else {
          printf("%s\n", line);
        }
      }
    }
    free(line);
  }
  regfree(&regex);
}

void openFile(int argc, char **argv, FLAGS *flags) {
  FILE *file;
  for (int i = optind; i < argc; i++) {
    if (!flags->h && i != argc - 1) flags->files = true;
    if ((file = fopen(argv[i], "r")) == NULL) {
      if (!flags->s)
        fprintf(stderr, "grep: %s No such file or directory\n", argv[i]);
    } else {
      paternCheckFile(flags, file, argv[i]);
      fclose(file);
    }
  }
}

char *readline(FILE *file) {
  char *line = NULL, *tmp = NULL;
  size_t size = 0, index = 0, chunkSize = 100;
  int ch;
  while ((ch = fgetc(file)) != EOF) {
    if (index == size) {
      tmp = realloc(line, size += chunkSize);
      if (!tmp) {
        free(line);
        line = NULL;
        break;
      }
      line = tmp;
    }
    if (ch == '\n') break;
    line[index++] = ch;
  }
  if (line) {
    line[index] = '\0';
  }

  return line;
}

void parser(int argc, char **argv, FLAGS *flags) {
  int opt;
  while ((opt = getopt(argc, argv, "e:f:isvnholc")) != -1) {
    switch (opt) {
      case 'e':
        if (!flags->f) {
          addPattern(&flags->patern);
          flags->e = true;
        }
        break;
      case 'f':
        flags->f = true;
        addFilePattern(&flags->patern);
        break;
      case 'i':
        flags->i = true;
        flags->flag = 1;
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
    }
  }
  if (flags->l) {
    flags->v = flags->n = false;
  }
  // if (!flags->e || flags->f) {
  //   flags->patern = malloc(strlen(argv[optind] + 1));
  //   strcpy(flags->patern, argv[optind++]);
  // }
}

void addFilePattern(char **patern) {
  FILE *file = fopen(optarg, "r");
  if (file == NULL) {
    fprintf(stderr, "grep: %s No such file or directory\n", optarg);
  } else {
    char *line;
    while ((line = readline(file)) != NULL) {
      optarg = line;
      addPattern(patern);
      free(line);
    }
  }
}

void addPattern(char **pattern) {
  int len = 0;
  if (*pattern) len = strlen(*pattern);
  *pattern = realloc(*pattern, strlen(optarg) + len + 4);
  len ? strcat(strcat(*pattern, "\\|"), optarg) : strcpy(*pattern, optarg);
}