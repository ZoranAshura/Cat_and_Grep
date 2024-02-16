CC= gcc -std=c11 -D_GNU_SOURCE
CFLAGS= -Wall -Wextra -Werror
GREP= s21_grep.c

all: s21_grep

s21_grep:
	$(CC) $(CFLAGS) $(GREP) -o s21_grep

test:
	sh tests.sh
clean:
	rm -rf s21_grep