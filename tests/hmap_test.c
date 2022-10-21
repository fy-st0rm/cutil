#include "../hmap.h"

int main() {
	Hmap* hmap = cutil_hmap_new(10);

	cutil_hmap_adds(hmap, "Hello", 10);
	cutil_print_hmap_buffer(hmap);
	printf("%p\n", cutil_hmap_gets(hmap, "Hello"));
	cutil_hmap_removes(hmap, "Hello");
	cutil_print_hmap_buffer(hmap);

	cutil_hmap_delete(hmap);
	cutil_alert();
	return 0;
}
