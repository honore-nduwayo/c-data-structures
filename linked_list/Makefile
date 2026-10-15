CC = cc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g

test_list: list.c test_list.c list.h
	$(CC) $(CFLAGS) -o test_list list.c test_list.c

test: test_list
	./test_list

# Memory-error check (out-of-bounds, use-after-free) using AddressSanitizer
asan: list.c test_list.c list.h
	$(CC) $(CFLAGS) -fsanitize=address,undefined -o test_list_asan list.c test_list.c
	./test_list_asan

# Leak check: 'leaks' on macOS, valgrind on Linux
leaks: test_list
ifeq ($(shell uname),Darwin)
	leaks --atExit -- ./test_list
else
	valgrind --leak-check=full --error-exitcode=1 ./test_list
endif

clean:
	rm -f test_list test_list_asan
	rm -rf *.dSYM

.PHONY: test asan leaks clean
