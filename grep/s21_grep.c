#include "s21_grep.h"

int main(int argc, char *argv[]) {
  char **patterns = (char **)malloc(1000 * sizeof(char *));
  for (int i = 0; i < 1000; i++) {
    patterns[i] = (char *)malloc(1000 * sizeof(char));
  }
  int opt_ind = 0;
  flags flag = {0};
  grep_values value = {0};

  int file_location = 0;
  opt_ind = parser(argc, argv, &flag, &value, patterns);
  if (argc >= 3 && flag.error != 1) {
    file_location = find_pattern(opt_ind, argv, patterns, value);
    while (file_location < argc) {
      if (argv[file_location + 1] != NULL) {
        value.count_files = value.count_files + 1;
      }
      value.path = argv[file_location];

      grep(value, flag, patterns);

      file_location++;
    }
  }
  for (int i = 0; i < 1000; i++) {
    free(patterns[i]);
  }
  free(patterns);
  return 0;
}

int find_pattern(int opt_ind, char *argv[], char **patterns,
                 grep_values value) {
  int file_location = 0;
  if (value.count_pattern == 0) {
    file_location = opt_ind + 1;
    strcpy(patterns[0], argv[optind]);
  } else {
    file_location = opt_ind;
  }
  return file_location;
}

int parser(int argc, char *argv[], flags *flag, grep_values *value,
           char **patterns) {
  int c = 0;
  while ((c = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) != -1) {
    switch (c) {
      case 'e':
        strcpy(patterns[value->count_pattern], optarg);
        value->count_pattern += 1;
        flag->e = 1;
        break;
      case 'i':
        flag->i = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'c':
        flag->c = 1;
        break;
      case 'l':
        flag->l = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 'h':
        flag->h = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'f':
        f_flag(optarg, patterns, value);
        flag->f = 1;
        break;
      case 'o':
        flag->o = 1;
        break;
      case '?':
        flag->error = 1;
        break;
    }
  }
  return optind;
}

void f_flag(char *path, char **pattern, grep_values *value) {
  FILE *filename;
  filename = fopen(path, "r");
  int lenght = 0;
  if (filename != NULL) {
    while (!feof(filename)) {
      fgets(pattern[value->count_pattern], 1000, filename);
      lenght = strlen(pattern[value->count_pattern]);

      if (pattern[value->count_pattern][0] != '\n' &&
          pattern[value->count_pattern][lenght - 1] == '\n') {
        pattern[value->count_pattern][lenght - 1] = '\0';
      }
      value->count_pattern += 1;
    }
    fclose(filename);
  } else {
    printf("No such file or directory");
  }
}

void grep(grep_values value, flags flag, char **pattern) {
  FILE *filename;
  int count_lines = 0, count_matched_lines = 0, comp_flag1 = REG_EXTENDED,
      stop = 0, result_regex = 0;
  regex_t preg;
  if (flag.v == 1 || flag.c == 1 || flag.l == 1) flag.o = 0;
  filename = fopen(value.path, "r");
  if (filename != NULL) {
    if (value.count_pattern == 0 && flag.e == 0 && flag.f == 0)
      value.count_pattern = 1;
    if (flag.i == 1) comp_flag1 = REG_ICASE;
    char *string = (char *)malloc(1000 * sizeof(char));
    while ((fgets(string, 1000, filename)) && (stop == 0)) {
      int findline = 0;
      count_lines++;
      int pattern_no_match = 0;
      if (strchr(string, '\n') == NULL) strcat(string, "\n");
      for (int i = 0; i < value.count_pattern; i++) {
        int match = 0;
        regcomp(&preg, pattern[i], comp_flag1 | REG_NEWLINE);
        result_regex = regexec(&preg, string, 0, NULL, 0);
        if (result_regex == 0 && flag.v == 0) match = 1;
        if (result_regex == REG_NOMATCH && flag.v == 1) {
          pattern_no_match++;
          if (pattern_no_match == value.count_pattern) match = 1;
        }
        if (flag.l == 1 && match == 1 && flag.c == 0) {
          printf("%s\n", value.path);
          match = 0;
          stop = 1;
        }
        if (flag.c == 1 && match == 1) {
          count_matched_lines++;
          match = 0;
        }
        if (findline == 0 && match == 1) {
          print(flag, value, count_lines, string);
          findline++;
        }
        if (flag.o == 1) flag_o(string, preg);
        regfree(&preg);
      }
    }
    if (flag.c == 1) {
      flag_c_l(value, flag, count_matched_lines);
    }
    free(string);
    fclose(filename);
  } else if (flag.s == 0) {
    fprintf(stderr, "No such file or directory: %s\n", value.path);
  }
}

void print(flags flag, grep_values value, int count_lines, char *string) {
  if (value.count_files >= 1 && flag.h == 0) printf("%s:", value.path);
  if (flag.n == 1) printf("%d:", count_lines);
  if (flag.o == 0) printf("%s", string);
}

void flag_c_l(grep_values value, flags flag, int count_matched_lines) {
  if (value.count_files >= 1 && flag.h == 0) {
    printf("%s:", value.path);
  }
  if (flag.l == 0) {
    printf("%d\n", count_matched_lines);
  } else if (flag.l == 1) {
    if (count_matched_lines > 0) {
      printf("1\n");
      printf("%s\n", value.path);
    } else {
      printf("0\n");
    }
  }
}

void flag_o(char *string, regex_t preg) {
  regmatch_t pmatch[1];
  while (regexec(&preg, string, 1, pmatch, 0) == 0) {
    for (int i = 0; i < pmatch->rm_eo; i++) {
      if (i >= pmatch->rm_so) {
        printf("%c", string[i]);
      }
      string[i] = 127;
    }
    printf("\n");
  }
}
