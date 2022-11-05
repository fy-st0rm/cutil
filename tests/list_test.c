#include "../list.h"

void list_add_test() {
	printf("------------LIST ADD TEST---------------\n");
	cutil_list_def(int) list = NULL;
	cutil_list_add(list, 10);
	cutil_list_add(list, 20);
	cutil_list_add(list, 30);

	printf("Size: %d\nLen: %d\n", list->size, list->len);
	printf("Values:\n");
	for (int i = 0; i < list->len; i++) {
		int val = cutil_list_get(list, i);
		printf("  %d\n", val);
	}

	cutil_list_delete(list);
}

void list_remove_test() {
	printf("------------LIST REMOVE TEST--------------\n");
	cutil_list_def(char*) list = NULL;

	cutil_list_add(list, "Helo 1");
	cutil_list_add(list, "Helo 2");
	cutil_list_add(list, "Helo 3");

	cutil_list_remove_by_idx(list, 1);
	cutil_list_remove_by_val(list, "Helo 3");

	printf("Size: %d\nLen: %d\n", list->size, list->len);
	printf("Values:\n");
	for (int i = 0; i < list->len; i++) {
		char* val = cutil_list_get(list, i);
		printf("  %s\n", val);
	}

	cutil_list_delete(list);
}

void list_pop_test() {
	printf("------------LIST POP TEST-----------------\n");
	cutil_list_def(int) list = NULL;
	cutil_list_add(list, 10);
	cutil_list_add(list, 20);
	cutil_list_add(list, 30);

	printf("Size: %d\nLen: %d\n", list->size, list->len);
	printf("Values:\n");
	int val = cutil_list_pop(list, 0);
	printf("  %d\n", val);
	val = cutil_list_pop(list, 0);
	printf("  %d\n", val);
	val = cutil_list_pop(list, 0);
	printf("  %d\n", val);
	printf("Size: %d\nLen: %d\n", list->size, list->len);

	cutil_list_delete(list);
}

int main() {
	list_add_test();
	list_remove_test();
	list_pop_test();
	cutil_alert();
	return 0;
}
