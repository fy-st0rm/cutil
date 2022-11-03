CC=gcc -w

usage:
	@echo Make [test name]
	@echo Test names:
	@echo ---- alloc
	@echo ---- hmap
	@echo ---- str
	@echo ---- list

alloc:
	$(CC) -c alloc.c tests/alloc_test.c
	$(CC) -o alloc_test *.o
	rm alloc_test.o
	./alloc_test

hmap:
	$(CC) -c alloc.c tests/hmap_test.c
	$(CC) -o hmap_test *.o
	rm hmap_test.o
	./hmap_test

str:
	$(CC) -c alloc.c tests/str_test.c
	$(CC) -o str_test *.o
	rm str_test.o
	./str_test

list:
	$(CC) -c alloc.c tests/list_test.c
	$(CC) -o list_test *.o
	rm list_test.o
	./list_test
