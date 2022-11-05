#include "../hmap.h"

int main() {
	cutil_hmap_def(int, int) map = NULL;
	cutil_hmap_add(map, 10, 110);
	int a = cutil_hmap_get(map, 10);
	printf("%d\n", a);
	cutil_alert();
	return 0;
}
