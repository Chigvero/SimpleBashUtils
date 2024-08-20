#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
struct flags {
  int b, e, E, n, s, t, T, v;
} flags;
int print_previous(int c1, int count, int *c1_continue);
int parser(int argc, char **argv);
int print_file(int argc, char **argv);

int main(int argc, char **argv) {
  parser(argc, argv);
  print_file(argc, argv);
  return 0;
}

int parser(int argc, char **argv) {
  int t;
  const struct option opt[] = {{"number-nonblank", 0, NULL, 'b'},
                               {"number", 0, NULL, 'n'},
                               {"squeeze-blank", 0, NULL, 's'},
                               {0, 0, NULL, 0}};
  while ((t = getopt_long(argc, argv, "beEnstTv", opt, NULL)) != -1) {
    switch (t) {
      case ('b'):
        flags.b = 1;
        break;
      case ('e'):
        flags.e = 1;
        flags.v = 1;
        break;
      case ('n'):
        flags.n = 1;
        break;
      case ('s'):
        flags.s = 1;
        break;
      case ('t'):
        flags.t = 1;
        flags.v = 1;
        break;
      case ('E'):
        flags.e = 1;
        break;
      case ('T'):
        flags.t = 1;
        break;
      case ('v'):
        flags.v = 1;
    }
  }
  return 0;
}

int print_file(int argc, char **argv) {
  for (int i = optind; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");
    if (fp == NULL) return 1;
    int c;
    int c1 = getc(fp);
    fseek(fp, 0, SEEK_SET);
    int count = 1, s_check = 0;
    if (c1 == '\n') s_check = 1;
    while ((c = getc(fp)) != EOF) {
      if (flags.b == 1 &&
          ((count == 1 && c1 != '\n') || (c != '\n' && c1 == '\n'))) {
        printf("%6d\t", count);
        count++;
      }
      if (flags.b == 0 && flags.n == 1 && (c1 == '\n' || count == 1)) {
        printf("%6d\t", count);
        count++;
      }
      if (flags.e == 1 && flags.v == 1 && c == '\n') printf("$");
      if (flags.t == 1 && flags.v == 1 && c == '\t') {
        printf("^I");
        continue;
      }
      if (flags.v == 1) {
        if (c < 32 && c != 9 && c != 10) {
          printf("^%c", c + 64);
          continue;
        } else if (c > 127 && c < 160) {
          printf("M-^%c", c - 64);
          continue;
        } else if (c == 127) {
          printf("^%c", c - 64);
          continue;
        }
      }
      if (flags.s == 1 && c == '\n') {
        s_check++;
        if (s_check > 2) continue;
      } else
        s_check = 0;
      printf("%c", c);
      c1 = c;
    }
    fclose(fp);
  }
  return 0;
}