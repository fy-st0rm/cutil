#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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

// Macros
#define cutil_alloc(x) __alloc(x, __FILE__, __LINE__)
void cutil_free(void* ptr);
void* __alloc(int size, const char* file, int line);
void __pop_mem(void* ptr);
void cutil_alert();

void cutil_print_alloc_buffer();

#endif
