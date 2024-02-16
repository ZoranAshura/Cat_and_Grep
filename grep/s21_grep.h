#ifndef S21_GREP_H_
#define S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int error;
} flags;

typedef struct {
  char *path;
  int count_files;
  int count_pattern;
} grep_values;

int parser(int argc, char *argv[], flags *flag, grep_values *value,
           char **patterns);
int find_pattern(int opt_ind, char *argv[], char **patterns, grep_values value);
void f_flag(char *path, char **pattern, grep_values *value);
void grep(grep_values value, flags flag, char **pattern);
void print(flags flag, grep_values value, int count_lines, char *string);
void flag_c_l(grep_values value, flags flag, int count_matched_lines);
void flag_o(char *string, regex_t preg);
#endif  // S21_GREP_H
