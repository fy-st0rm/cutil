#include "../str.h"

void test_hello_world() {
	str text = cutil_str_new("Hello world");
	printf("%s\n", text.c_str);
	cutil_str_delete(&text);
}

void test_str_add() {
	str a = cutil_str_new("foo ");
	str b = cutil_str_new("bar");
	cutil_str_add(&a, &b);
	cutil_str_add_c_str(&a, " Hello world");
	printf("Final result: %s\n", a.c_str);
	cutil_str_delete(&a);
	cutil_str_delete(&b);
}

void test_str_split() {
	str a = cutil_str_new("Hello world");
	printf("Org str: %s\n", a.c_str);
	str b = cutil_str_split(&a, ' ');
	printf("New str: %s\n", a.c_str);
	printf("Splitted half: %s\n", b.c_str);

	cutil_str_delete(&a);
	cutil_str_delete(&b);
}

int main() {
	test_hello_world();
	test_str_add();
	test_str_split();
	cutil_alert();
	return 0;
}
