SANITIZER:=#-fsanitize=address
CFLAGS:=-Wall -Werror -Wextra -std=c11 -pedantic -g $(SANITIZER)
CC:=gcc

s21_cat: s21_cat.o
	$(CC) $(SANITIZER) $< -o $@

clean:
	$(RM) s21_cat.o s21_cat