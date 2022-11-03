#ifndef _LIST_H_
#define _LIST_H_

#include "alloc.h"

#define LIST_SIZE_BIAS 10

#define cutil_list_def(v_type)\
	struct {\
		v_type* value;\
		uint64_t len;\
		size_t size;\
	}*

#define cutil_list_init(list)\
	list = cutil_alloc(sizeof(list));\
	list->value = cutil_alloc(list->size);\
	list->len   = 0;\
	list->size  = LIST_SIZE_BIAS;\

#define cutil_list_delete(list)\
	if (list == NULL) {\
		cutil_assert(false, "List is none. Can`t be deleted.\n");\
	}\
	cutil_free(list->value);\
	cutil_free(list);\

#define cutil_list_extend(list, amt)\
	void* tmp = cutil_alloc(list->size);\
	memcpy(tmp, list->value, list->size);\
	cutil_free(list->value);\
	list->size += amt;\
	list->value = cutil_alloc(list->size);\

#define cutil_list_add(list, x)\
	if (list == NULL) {\
		cutil_list_init(list);\
	}\
	if (list->len + 1 >= list->size) {\
		cutil_list_extend(list, LIST_SIZE_BIAS);\
	}\
	list->value[list->len++] = x;

#define cutil_list_get(list, idx)\
	(idx < list->len) ? list->value[idx] : 0;\
	cutil_assert(list->len > idx, "Index out of bounds. Index: %d, Length of list: %d\n", idx, list->len);

#endif
