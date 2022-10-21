#ifndef _HMAP_H_
#define _HMAP_H_

#include "alloc.h"

// Hash map Node
typedef struct Hmap_node Hmap_node;
struct Hmap_node {
	unsigned long hash;
	void* key;
	void* value;
	Hmap_node* next;
};

static void print_node(Hmap_node* node) {
	printf("%lu: (%p, %p)\n", node->hash, node->key, node->value);
}

// Hmap structure
typedef struct {
	Hmap_node* buffer;
	int buff_sz;
	int max_sz;
} Hmap;

static Hmap cutil_hmap_new(int max_sz) {
	Hmap hmap = {
		.buffer = cutil_alloc(sizeof(Hmap_node) * max_sz),
		.buff_sz = 0,
		.max_sz = max_sz
	};
	return hmap;
}

static void cutil_hmap_delete(Hmap* hmap) {
	cutil_free(hmap->buffer);
}

// Functions to calculate hash codes
unsigned long hash_code(const char* key)
{
	unsigned long hash = 5381;
	int c;
	while (c = *key++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	return hash;
}

// Functions to add items
static void cutil_hmap_adds(Hmap* hmap, const char* key, void* value) {
	unsigned long hash = hash_code(key);
	Hmap_node node = {
		hash,
		key,
		value
	};
	//TODO: Implement node collision
	hmap->buffer[hash & (hmap->max_sz - 1)] = node;
	hmap->buff_sz++;
}

static void cutil_hmap_addc(char key, void* value) {
	assert(false && "cutil_hmap_addc hasnt been implemented yet!");
}
static void cutil_hmap_addi(int key, void* value) {
	assert(false && "cutil_hmap_addi hasnt been implemented yet!");
}
static void cutil_hmap_addf(float key, void* value) {
	assert(false && "cutil_hmap_addf hasnt been implemented yet!");
}

// Function to remove item
static void cutil_hmap_removes(Hmap* hmap, const char* key) {
	unsigned long hash = hash_code(key);
	Hmap_node dummy = {0};
	hmap->buffer[hash & (hmap->max_sz - 1)] = dummy;
}

static void cutil_hmap_removec(Hmap* hmap, char key) {
	assert(false && "cutil_hmap_removec hasnt been implemented yet!");
}
static void cutil_hmap_removei(Hmap* hmap, int key) {
	assert(false && "cutil_hmap_removei hasnt been implemented yet!");
}
static void cutil_hmap_removef(Hmap* hmap, float key) {
	assert(false && "cutil_hmap_removef hasnt been implemented yet!");
}

// Function to get item
static void* cutil_hmap_gets(Hmap* hmap, const char* key) {
	//TODO: Check the key for match
	unsigned long hash = hash_code(key);
	return hmap->buffer[hash & (hmap->max_sz - 1)].value;
}

static void* cutil_hmap_getc(Hmap* hmap, char key) {
	assert(false && "cutil_hmap_getc hasnt been implemented yet!");
}
static void* cutil_hmap_geti(Hmap* hmap, int key) {
	assert(false && "cutil_hmap_geti hasnt been implemented yet!");
}
static void* cutil_hmap_getf(Hmap* hmap, float key) {
	assert(false && "cutil_hmap_getf hasnt been implemented yet!");
}

// Print function
static void cutil_print_hmap_buffer(Hmap* hmap) {
	printf("---------HMAP BUFFER START----------\n");
	for (int i = 0; i < hmap->max_sz; i++) {
		print_node(&hmap->buffer[i]);
	}
	printf("---------HMAP BUFFER END----------\n");
}

#endif
