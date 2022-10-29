#include "../str.h"

void test_hello_world() {
	printf("-----HELLO WORLD TEST--------\n");
	str text = cutil_str_new("Hello world");
	printf("%s\n", text.c_str);
	cutil_str_delete(&text);
}

void test_str_add() {
	printf("-----STRING ADD TEST--------\n");
	str a = cutil_str_new("foo ");
	str b = cutil_str_new("bar");
	cutil_str_add(&a, &b);
	cutil_str_add_c_str(&a, " Hello world");
	printf("Final result: %s\n", a.c_str);
	cutil_str_delete(&a);
	cutil_str_delete(&b);
}

void test_str_split() {
	printf("-----STRING SPLIT TEST--------\n");
	str a = cutil_str_new("hello");
	str b = cutil_str_split(&a, '\n');
	printf("%d %d\n", b.len, strlen(b.c_str));
	printf("%s\n", a.c_str);
	printf("%s\n", b.c_str);
	printf("%d\n", a.len);

	cutil_str_delete(&a);
	cutil_str_delete(&b);
}

void test_str_slice() {
	printf("-----STRING SLICE TEST--------\n");
	str a = cutil_str_new("Hello world");
	str b = cutil_str_slice(&a, 0, 5);
	printf("A: %s\nB: %s\n", a.c_str, b.c_str);
	cutil_str_delete(&a);
	cutil_str_delete(&b);
}

void test_str_insert() {
	printf("-----STRING INSERT TEST--------\n");
	str a = cutil_str_new("Hello world");
	cutil_str_insert(&a, 5, ',');
	printf("Middle inserted: %s\n", a.c_str);
	cutil_str_insert(&a, a.len, '.');
	printf("Last inserted: %s\n", a.c_str);
	cutil_str_delete(&a);
}

void test_str_pop() {
	printf("-------STRING POP TEST-----------\n");
	str a = cutil_str_new("Hello world");
	cutil_str_pop(&a, 5);
	printf("Middle poped: %s\n", a.c_str);
	cutil_str_pop(&a, 0);
	printf("Front poped: %s\n", a.c_str);
	cutil_str_pop(&a, a.len-1);
	printf("Last poped: %s\n", a.c_str);
	cutil_str_delete(&a);
}

int main() {
	test_hello_world();
	test_str_add();
	test_str_split();
	test_str_slice();
	test_str_insert();
	test_str_pop();
	cutil_alert();
	return 0;
}
