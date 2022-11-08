#ifndef _HMAP_H_
#define _HMAP_H_

#include "alloc.h"

#define HMAP_SIZE_BIAS 10

// Functions to calculate hash codes
static unsigned long __hash_data(char* data) {
	unsigned long hash = 5381;
	int c;
	while (c = *data++) {
		hash = ((hash << 5) + hash) + c; // hash * 33 + c
	}
	return hash;
}

typedef enum {
	HMAP_ACTIVE,
	HMAP_INACTIVE
} Cutil_Hmap_State;

#define __cutil_hmap_entry_def(k_type, v_type)\
	struct {\
		k_type key;\
		v_type val;\
		Cutil_Hmap_State state;\
	}

#define cutil_hmap_def(k_type, v_type)\
	struct {\
		__cutil_hmap_entry_def(k_type, v_type)* data;\
		k_type tmp_key;\
		v_type tmp_val;\
		uint64_t len;\
		uint64_t size;\
	}*

#define cutil_hmap_delete(hmap)\
	cutil_free(hmap->data);\
	cutil_free(hmap)

#define __hmap_init_data(hmap, start, end)\
	do {\
		for (int i = start; i < end; i++) {\
			hmap->data[i].state = HMAP_INACTIVE;\
		}\
	} while(0)

#define cutil_hmap_init(hmap)\
	do {\
		hmap = cutil_alloc(sizeof(*hmap));\
		hmap->len = 0;\
		hmap->size = HMAP_SIZE_BIAS;\
		hmap->data = cutil_alloc(hmap->size);\
		__hmap_init_data(hmap, 0, hmap->size);\
	} while(0)

#define cutil_hmap_extend(hmap, amt)\
	do {\
		void* tmp = cutil_alloc(hmap->size);\
		memcpy(tmp, hmap->data, hmap->size);\
		cutil_free(hmap->data);\
		hmap->size += amt;\
		hmap->data = cutil_alloc(hmap->size);\
		memcpy(hmap->data, tmp, sizeof(tmp));\
		cutil_free(tmp);\
		__hmap_init_data(hmap, hmap->len, hmap->size);\
	} while(0)

// TODO: Implement data collision
#define cutil_hmap_add(hmap, _k, _v)\
	do {\
		if (hmap == NULL) {\
			cutil_hmap_init(hmap);\
		}\
		if (hmap->len + 1 >= hmap->size) {\
			cutil_hmap_extend(hmap, HMAP_SIZE_BIAS);\
		}\
		\
		hmap->tmp_key = _k;\
		unsigned long hash = __hash_data((char*)&hmap->tmp_key);\
		int idx = hash & (hmap->size - 1);\
		\
		cutil_assert(hmap->data[idx].state == HMAP_INACTIVE, "Data collision\n");\
		hmap->data[idx].key = _k;\
		hmap->data[idx].val = _v;\
		hmap->data[idx].state = HMAP_ACTIVE;\
		hmap->len++;\
	} while(0)

bool __hmap_exists(void** data, void* key, uint64_t cap, size_t stride) {
	// Calculating the index from the hash
	unsigned long h2 = __hash_data((char*) &key);
	int idx = h2 & (cap - 1);

	// Getting key and state from the data structure
	int k = ((char*)(*data + (idx * stride)))[0];
	Cutil_Hmap_State s = ((char*)(*data + (idx * stride)))[stride - sizeof(Cutil_Hmap_State)];

	unsigned long h1 = __hash_data((char*) &k);
	if (h1 == h2 && s == HMAP_ACTIVE)
		return true;
	return false;
}

#define cutil_hmap_exists(hmap, _k)\
	__hmap_exists(&hmap->data, (void*) _k, hmap->size, sizeof(*(hmap->data)))

#define cutil_hmap_get(hmap, _k)\
	(\
		hmap->tmp_key = _k,\
		hmap->data[__hash_data((char*)&hmap->tmp_key) & (hmap->size - 1)].val\
	);\
	cutil_assert(cutil_hmap_exists(hmap, _k), "Required key doesnt exists.\n")

/*
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
static unsigned long hash_code(const char* key) {
	unsigned long hash = 5381;
	int c;
	while (c = *key++)
		hash = ((hash << 5) + hash) + c; // hash * 33 + c
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
	cutil_assert(false , "cutil_hmap_addc hasnt been implemented yet!");
}
static void cutil_hmap_addi(int key, void* value) {
	cutil_assert(false , "cutil_hmap_addi hasnt been implemented yet!");
}
static void cutil_hmap_addf(float key, void* value) {
	cutil_assert(false , "cutil_hmap_addf hasnt been implemented yet!");
}

// Function to remove item
static void cutil_hmap_removes(Hmap* hmap, const char* key) {
	unsigned long hash = hash_code(key);
	Hmap_node dummy = {0};
	hmap->buffer[hash & (hmap->max_sz - 1)] = dummy;
}

static void cutil_hmap_removec(Hmap* hmap, char key) {
	cutil_assert(false , "cutil_hmap_removec hasnt been implemented yet!");
}
static void cutil_hmap_removei(Hmap* hmap, int key) {
	cutil_assert(false , "cutil_hmap_removei hasnt been implemented yet!");
}
static void cutil_hmap_removef(Hmap* hmap, float key) {
	cutil_assert(false , "cutil_hmap_removef hasnt been implemented yet!");
}

// Function to get item
static void* cutil_hmap_gets(Hmap* hmap, const char* key) {
	//TODO: Check the key for match
	unsigned long hash = hash_code(key);
	return hmap->buffer[hash & (hmap->max_sz - 1)].value;
}

static void* cutil_hmap_getc(Hmap* hmap, char key) {
	cutil_assert(false , "cutil_hmap_getc hasnt been implemented yet!");
}
static void* cutil_hmap_geti(Hmap* hmap, int key) {
	cutil_assert(false , "cutil_hmap_geti hasnt been implemented yet!");
}
static void* cutil_hmap_getf(Hmap* hmap, float key) {
	cutil_assert(false , "cutil_hmap_getf hasnt been implemented yet!");
}

// Print function
static void cutil_print_hmap_buffer(Hmap* hmap) {
	printf("---------HMAP BUFFER START----------\n");
	for (int i = 0; i < hmap->max_sz; i++) {
		print_node(&hmap->buffer[i]);
	}
	printf("---------HMAP BUFFER END----------\n");
}
*/

#endif
