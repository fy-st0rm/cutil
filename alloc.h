#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "misc.h"

#define ALLOC_BUFF_SZ 1024

// Memory structure
typedef struct {
	void* ptr;
	const char* file;
	int line;
} Memory;

static void cutil_print_mem(Memory* mem) {
	printf("%s:%d -> %p\n", mem->file, mem->line, mem->ptr);
}

// Buffer of the memories allocated
static Memory alloc_buffer[ALLOC_BUFF_SZ];
static int alloc_buff_sz = 0;

// Macros
#define cutil_alloc(x) __alloc(x, __FILE__, __LINE__)
#define cutil_free(x)\
	__pop_mem(x);\
	--alloc_buff_sz

// Function to allocate memory
static void* __alloc(int size, const char* file, int line) {
	Memory mem = {
		malloc(size),
		file,
		line 
	};
	memset(mem.ptr, 0, size);

	cutil_assert(alloc_buff_sz < ALLOC_BUFF_SZ, "Alloc buffer ran out of memory at %s:%d\n", file, line);

	alloc_buffer[alloc_buff_sz] = mem;
	++alloc_buff_sz;
	return mem.ptr;
}

// Pops the memory from the buffer
static void __pop_mem(void* ptr) {
	for (int i = 0; i < alloc_buff_sz; i++) {
		if (alloc_buffer[i].ptr == ptr) {
			memmove(&alloc_buffer[i], &alloc_buffer[i+1], (alloc_buff_sz - i - 1) * sizeof(Memory));
			free(ptr);
			break;
		}
	}
}

// Alert function
static void cutil_alert() {
	if (!alloc_buff_sz) return;

	printf("---------ALLOC ALERT START---------\n");
	for (int i = 0; i < alloc_buff_sz; i++) {
		printf("Non freed memories: %p in %s:%d\n", alloc_buffer[i].ptr, alloc_buffer[i].file, alloc_buffer[i].line);
	}
	printf("---------ALLOC ALERT END---------\n");
}

static void cutil_print_alloc_buffer() {
	printf("-------ALLOC BUFFER START--------\n");
	for (int i = 0; i < alloc_buff_sz; i++) {
		cutil_print_mem(&alloc_buffer[i]);
	}
	printf("-------ALLOC BUFFER END--------\n");
}

#endif
