#include "s21_cat.h"

int main(int argc, char *argv[]) {
  int err = 1;
  flg_t flg = {0};
  err = flg_parser(argc, argv, &flg);
  if (!err) {
    if (flg.b == 1) {
      flg.n = 0;
    }
    while (optind < argc) {
      if (!read_file(argv, &flg)) {
        printf("No such file or directory\n");
      }
      optind++;
    }
  } else {
    printf("usage: s21_cat [-benstuv] [file ...]");
  }
  return 0;
}

int flg_parser(int argc, char *argv[], flg_t *flg) {
  int c;
  int ret = 0;
  static struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {0, 0, 0, 0}};

  while ((c = getopt_long(argc, argv, "bEnsTvet", long_options, NULL)) != -1) {
    switch (c) {
      case 'b':
        flg->b = 1;
        break;
      case 'E':
        flg->e = 1;
        break;
      case 'n':
        flg->n = 1;
        break;
      case 's':
        flg->s = 1;
        break;
      case 'T':
        flg->t = 1;
        break;
      case 'v':
        flg->v = 1;
        break;
      case 'e':
        flg->e = 1;
        flg->v = 1;
        break;
      case 't':
        flg->t = 1;
        flg->v = 1;
        break;
      case '?':
        ret = 1;
        break;
    }
  }
  return ret;
}

int read_file(char *argv[], flg_t *flg) {
  FILE *file = fopen(argv[optind], "r");
  int ret = 1;
  if (file != NULL) {
    int str_count = 1;
    int empty_str_count = 0;
    int last_sym = '\n';
    while (1) {
      int cur_c = fgetc(file);
      if (cur_c == EOF) {
        break;
      }
      if (flg->s && cur_c == '\n' && last_sym == '\n') {
        empty_str_count++;
        if (empty_str_count > 1) {
          continue;
        }
      } else {
        empty_str_count = 0;
      }
      if (last_sym == '\n' && ((flg->b && cur_c != '\n') || flg->n)) {
        printf("%6d\t", str_count++);
      }
      if (flg->t && cur_c == '\t') {
        printf("^");
        cur_c = 'I';
      }
      if (flg->e && cur_c == '\n') {
        printf("$");
      }
      if (flg->v && !(cur_c >= 32 && cur_c < 127) && cur_c != '\n' &&
          cur_c != '\t') {
        if (cur_c == 127) {
          printf("^");
          cur_c -= 64;
        } else if (cur_c < 32 && cur_c >= 0) {
          printf("^");
          cur_c += 64;
        }
      }
      printf("%c", cur_c);
      last_sym = cur_c;
    }
    fclose(file);
  } else {
    ret = 0;
  }
  return ret;
}
