#include <stdio.h>
#include "../alloc.h"

void test_alloc_str() {
	char* str = (char*) cutil_alloc(100);
	strcpy(str, "Hello world");
	printf("%s\n", str);
	cutil_free(str);
}

void test_alloc_pop() {
	int* a = cutil_alloc(10);
	int* b = cutil_alloc(10);
	int* c = cutil_alloc(10);
	cutil_free(b);
}

int main() {
	test_alloc_str();
	test_alloc_pop();
	cutil_alert();
	return 0;
}
