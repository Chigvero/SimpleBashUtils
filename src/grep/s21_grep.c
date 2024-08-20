#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e, o, f, s, h, n, l, c, v, i;
  char buffer[4096];
} flags;

int parser(int argc, char **argv, flags *flag);
int realization_comp(char **argv, regex_t *regex, char *pattern, char *line_f,
                     FILE *file_open, flags *flag);
void print_if_no_reti(int count_n, int i, char **argv, char *line, flags *flag);
void print_if_reti(int count_n, int i, char **argv, char *line, flags *flag);
void print_file(int argc, char **argv, flags *flag);
int flag_s_debug(FILE *fp, int *contin, flags *flag);

int main(int argc, char **argv) {
  flags flag = {0};
  flag.e = 1;
  parser(argc, argv, &flag);
  print_file(argc, argv, &flag);
  return 0;
}

int parser(int argc, char **argv, flags *flag) {
  int c = 0;
  while ((c = getopt(argc, argv, "e:ivclnhsfo")) != -1) {
    switch (c) {
      case 'e':
        flag->e = 2;
        strcat(flag->buffer, optarg);
        strcat(flag->buffer, "|");
        break;
      case 'i':
        flag->i = 1;
        flag->e = 0;
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
      case 'o':
        flag->o = 1;
        break;
      case 'f':
        flag->f = 1;
        break;
      default:
        break;
    }
  }
  if (flag->e == 2) {
    flag->buffer[strlen(flag->buffer) - 1] = '\0';
  }
  return 0;
}
void print_file(int argc, char **argv, flags *flag) {
  regex_t regex;
  int reti = 0, count_pattern = 0, out = 0, count_h = argc - optind,
      i = optind + 1;
  char line[4096] = "";
  char line_f[4096] = "";
  char *pattern = "";
  char c_end = 0;
  FILE *fp_1 = NULL;
  if (flag->f == 1) {
    fp_1 = fopen(argv[optind], "r");
    flag_s_debug(fp_1, &out, flag);
    if (out == 1) return;
    while (fgets(line_f, 4096, fp_1)) count_pattern++;
    fseek(fp_1, 0, SEEK_SET);
  }
  if (flag->f == 0) count_pattern = 1;
  if (flag->e == 2) i = optind;
  if (flag->e == 2) count_h = argc - optind + 1;
  if (count_h <= 2) flag->h = 1;
  for (; i < argc; i++) {
    int count_c = 0, count_n = 0, contin = 0;
    FILE *fp = fopen(argv[i], "r");
    flag_s_debug(fp, &contin, flag);
    if (contin == 1) continue;
    while (fgets(line, 4096, fp)) {
      count_n++;
      if (line[strlen(line) - 1] != '\n') strcat(line, "\n");
      for (int j = 0; j < count_pattern; j++) {
        realization_comp(argv, &regex, pattern, line_f, fp_1, flag);
        reti = regexec(&regex, line, 0, NULL, 0);
        regfree(&regex);
        if (flag->v != 1 && !reti && flag->l != 1) {
          count_c++;
          c_end = line[strlen(line) - 1];
          print_if_no_reti(count_n, i, argv, line, flag);
          break;
        }
        if (flag->v == 1 && reti && flag->l != 1) {
          count_c++;
          c_end = line[strlen(line) - 1];
          print_if_reti(count_n, i, argv, line, flag);
          break;
        }
      }
      if (flag->l == 1 && !reti) {
        printf("%s\n", argv[i]);
        break;
      }
      if (flag->f == 1) fseek(fp_1, 0, SEEK_SET);
    }
    if (flag->c == 1 && flag->h != 1) printf("%s:%d\n", argv[i], count_c);
    if (flag->c == 1 && flag->h == 1) printf("%d\n", count_c);
    if (count_c != 0 && c_end != '\n' && i < argc - 1) printf("\n");
    fclose(fp);
  }
  if (flag->f == 1) fclose(fp_1);
}

int realization_comp(char **argv, regex_t *regex, char *pattern, char *line_f,
                     FILE *file_open, flags *flag) {
  if (flag->f == 1) {
    fgets(line_f, 4096, file_open);
    if (line_f[0] != '\n') line_f[strcspn(line_f, "\n")] = 0;
    pattern = (char *)malloc(strlen(line_f) + 1);
    if (!pattern) {
      perror("Error allocating memory");
      exit(EXIT_FAILURE);
    }
    strcpy(pattern, line_f);
    if (flag->i == 1 && flag->e == 0) {
      regcomp(regex, pattern, REG_ICASE);
      free(pattern);
    } else if (flag->e == 1 && flag->i == 0) {
      regcomp(regex, pattern, REG_EXTENDED);
      free(pattern);
    } else if (line_f[0] == '\n')
      regcomp(regex, ".", 0);
  } else {
    if (flag->i == 1 && flag->e == 0) {
      regcomp(regex, argv[optind], REG_ICASE);
    } else if (flag->e == 1 && flag->i == 0) {
      regcomp(regex, argv[optind], REG_EXTENDED);
    }
    if (flag->e == 2 && flag->i == 0) {
      regcomp(regex, flag->buffer, REG_EXTENDED);
    }
  }
  return 0;
}

void print_if_no_reti(int count_n, int i, char **argv, char *line,
                      flags *flag) {
  if (flag->c != 1 && flag->n != 1 && flag->h != 1) {
    if (flag->o == 1)
      printf("%s:%s\n", argv[i], argv[optind]);
    else
      printf("%s:%s", argv[i], line);
  }
  if (flag->c != 1 && flag->n == 1 && flag->h != 1) {
    if (flag->o == 1)
      printf("%s:%d:%s", argv[i], count_n, argv[optind]);
    else
      printf("%s:%d:%s", argv[i], count_n, line);
  }
  if (flag->c != 1 && flag->n != 1 && flag->h == 1) {
    if (flag->o == 1)
      printf("%s", argv[optind]);
    else
      printf("%s", line);
  }
  if (flag->c != 1 && flag->n == 1 && flag->h == 1) {
    if (flag->o == 1)
      printf("%d:%s", count_n, argv[optind]);
    else
      printf("%d:%s", count_n, line);
  }
}
void print_if_reti(int count_n, int i, char **argv, char *line, flags *flag) {
  if (flag->c != 1 && flag->n != 1 && flag->h != 1) {
    if (flag->o == 1)
      printf("%s:%s", argv[i], argv[optind]);
    else
      printf("%s:%s", argv[i], line);
  }
  if (flag->c != 1 && flag->n == 1 && flag->h != 1) {
    if (flag->o == 1)
      printf("%s:%d:%s", argv[i], count_n, argv[optind]);
    else
      printf("%s:%d:%s", argv[i], count_n, line);
  }
  if (flag->c != 1 && flag->n != 1 && flag->h == 1) {
    if (flag->o == 1)
      printf("%s", argv[optind]);
    else
      printf("%s", line);
  }
  if (flag->c != 1 && flag->n == 1 && flag->h == 1) {
    if (flag->o == 1)
      printf("%d:%s", count_n, argv[optind]);
    else
      printf("%d:%s", count_n, line);
  }
}
int flag_s_debug(FILE *fp, int *contin, flags *flag) {
  if (!fp) {
    if (flag->s == 1)
      *contin = 1;
    else {
      perror("Error opening file");
      *contin = 1;
    }
  }
  return 1;
}