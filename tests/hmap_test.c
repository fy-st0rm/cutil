#include "../hmap.h"

void hmap_add_get_test() {
	cutil_hmap_def(int, int) map = NULL;
	cutil_hmap_add(map, 5, 110);
	cutil_hmap_add(map, 10, 220);

	int a = cutil_hmap_get(map, 5);
	int b = cutil_hmap_get(map, 10);
	printf("A: %d\nB: %d\n", a, b);

	cutil_hmap_delete(map);
}

int main() {
	hmap_add_get_test();
	cutil_alert();
	return 0;
}
