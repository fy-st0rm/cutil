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
	do {\
		list = cutil_alloc(sizeof(list));\
		list->len   = 0;\
		list->size  = LIST_SIZE_BIAS;\
		list->value = cutil_alloc(list->size);\
	} while(0)

#define cutil_list_delete(list)\
	do {\
		if (list == NULL) {\
			cutil_assert(false, "List is none. Can`t be deleted.\n");\
		}\
		cutil_free(list->value);\
		cutil_free(list);\
	} while(0)

#define cutil_list_extend(list, amt)\
	do {\
		void* tmp = cutil_alloc(list->size);\
		memcpy(tmp, list->value, list->size);\
		cutil_free(list->value);\
		list->size += amt;\
		list->value = cutil_alloc(list->size);\
		memcpy(list->value, tmp, sizeof(tmp));\
		cutil_free(tmp);\
	} while(0)

#define cutil_list_add(list, x)\
	do {\
		if (list == NULL) {\
			cutil_list_init(list);\
		}\
		if (list->len + 1 >= list->size) {\
			cutil_list_extend(list, LIST_SIZE_BIAS);\
		}\
		list->value[list->len++] = x;\
	} while(0)

#define cutil_list_remove_by_idx(list, idx)\
	do {\
		if (list == NULL) cutil_assert(false, "List is null.\n");\
		cutil_assert(list->len > idx, "Index out of bounds. Index: %d, Length of list: %d\n", idx, list->len);\
		memmove(&list->value[idx], &list->value[idx+1], sizeof(*list->value) * (--list->len - idx));\
	} while(0)

#define cutil_list_remove_by_val(list, val)\
	do {\
		if (list == NULL) cutil_assert(false, "List is null.\n");\
		int i;\
		for (i = 0; i < list->len; i++) {\
			if (list->value[i] == val) {\
				cutil_list_remove_by_idx(list, i);\
				i = 0;\
				break;\
			}\
		}\
		cutil_assert(i < list->len, "Cannot find the required value in the list.\n");\
	} while(0)

// TODO: Temporary ig
#define cutil_list_clear(list) list->len = 0

#define cutil_list_pop(list, idx)\
	cutil_list_get(list, idx);\
	cutil_list_remove_by_idx(list, idx);\

#define cutil_list_get(list, idx)\
	list->value[idx];\
	cutil_assert(list->len > idx, "Index out of bounds. Index: %d, Length of list: %d\n", idx, list->len);\

#endif
