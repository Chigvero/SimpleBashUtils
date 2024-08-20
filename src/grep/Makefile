SANITIZER:=#-fsanitize=address
CFLAGS:=-Wall -Werror -Wextra -std=c11 -pedantic -g $(SANITIZER)
CC:=gcc

s21_grep: s21_grep.o
	$(CC) $(SANITIZER) $< -o $@

clean:
	$(RM) s21_grep.o s21_grep