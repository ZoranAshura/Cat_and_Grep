#ifndef S21_CAT_H_
#define S21_CAT_H_

#include <getopt.h>
#include <stdio.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} flg_t;

int flg_parser(int argc, char *argv[], flg_t *flg);
int read_file(char *argv[], flg_t *flg);

#endif  // S21_CAT_H
