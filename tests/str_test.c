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
	str a = cutil_str_new("Hello  world");
	str b = cutil_str_split(&a, '\n');
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

int main() {
	test_hello_world();
	test_str_add();
	test_str_split();
	test_str_slice();
	cutil_alert();
	return 0;
}
