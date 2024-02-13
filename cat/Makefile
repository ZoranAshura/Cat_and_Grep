CC= gcc -std=c11 -D_GNU_SOURCE
CFLAGS= -Wall -Wextra -Werror
CAT= s21_cat.c

all: s21_cat

s21_cat:
	$(CC) $(CFLAGS) $(CAT) -o s21_cat

test:
	sh test_func_cat.sh

clean:
	rm -rf s21_cat
