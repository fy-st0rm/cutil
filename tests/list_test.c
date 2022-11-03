#include "../list.h"

void list_insert_test() {
	printf("------------LIST INSERT TEST---------------\n");
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

int main() {
	list_insert_test();
	cutil_alert();
	return 0;
}
