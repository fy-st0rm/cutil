CC=gcc -w

usage:
	@echo Make [test name]
	@echo Test names:
	@echo ---- alloc
	@echo ---- hmap

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

