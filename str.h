#ifndef _STR_H_
#define _STR_H_

#include "alloc.h"
#include "string.h"

#define BIAS 10

typedef struct {
	char* c_str;
	int size;
	int len;
} str;

// Extends the string according to the given size
#define cutil_str_extend(s, i)\
	s->len += i;\
	if (s->len >= s->size)\
		__str_extend(s)

static void __str_extend(str* s) {
	char tmp[s->len];
	strcpy(tmp, s->c_str);

	cutil_free(s->c_str);
	s->c_str = cutil_alloc(s->len + BIAS);
	strcpy(s->c_str, tmp);
}

// String constructor
static str cutil_str_new(const char* text) {
	str s =  {
		.c_str = cutil_alloc(strlen(text)),
		.size  = strlen(text) + BIAS,
		.len   = strlen(text)
	};
	strcpy(s.c_str, text);
	return s;
}

// String destructor
static void cutil_str_delete(str* s) {
	cutil_free(s->c_str);
}

// Operators
static void cutil_str_add(str* dest, str* src) {
	cutil_str_extend(dest, src->len);
	strcat(dest->c_str, src->c_str);
}

static void cutil_str_add_c_str(str* dest, char* src) {
	cutil_str_extend(dest, strlen(src));
	strcat(dest->c_str, src);
}

static void cutil_str_add_char(str* dest, char src) {
	cutil_str_extend(dest, 1);
	dest->c_str[dest->len-1] = src;
}

static str cutil_str_split(str* src, char ch) {
	str new_s = cutil_str_new("");

	char i = *(src->c_str)++;
	cutil_str_add_char(&new_s, (char*) i);
	
	while (i != ch) {
		i = *(src->c_str)++;
		cutil_str_add_char(&new_s, (char*) i);

		if (!i) break;
	}
	return new_s;
}

#endif
