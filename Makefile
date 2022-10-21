CC=gcc -w

usage:
	@echo Make [test name]
	@echo Test names:
	@echo ---- alloc
	@echo ---- hmap
	@echo ---- str

alloc:
	$(CC) -c tests/alloc_test.c
	$(CC) -o alloc_test alloc_test.o
	rm alloc_test.o
	./alloc_test

hmap:
	$(CC) -c tests/hmap_test.c
	$(CC) -o hmap_test hmap_test.o
	rm hmap_test.o
	./hmap_test

str:
	$(CC) -c tests/str_test.c
	$(CC) -o str_test str_test.o
	rm str_test.o
	./str_test
