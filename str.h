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
static void cutil_str_extend(str* s, int i) {
	s->len += i;
	if (s->len >= s->size) {
		char tmp[s->len];
		strcpy(tmp, s->c_str);

		cutil_free(s->c_str);
		s->c_str = cutil_alloc(s->len + BIAS);
		strcpy(s->c_str, tmp);
	}
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

// Helpful functions
static str cutil_str_split(str* src, char ch) {
	str new_s = cutil_str_new("");
	
	char i;
	do { 
		i = *(src->c_str)++;
		src->len--;

		if (!i) break;
		if (i != ch) cutil_str_add_char(&new_s, i);

	} while (i != ch);
	return new_s;
}

#define cutil_str_slice(src, start, end)\
	__str_slice(src, start, end, __FILE__, __LINE__);\

static str __str_slice(str* src, int start, int end, const char* file, int line) {
	str new_s = cutil_str_new("");
	cutil_assert(start < end, "%s:%d: Start position should be less then end position\n", file, line);
	cutil_assert(start <= src->len, "%s:%d: Start position should be less then string length\n", file, line);
	cutil_assert(end <= src->len, "%s:%d: End position should be less then string length\n", file, line);

	for (int i = start; i <= end; i++) {
		cutil_str_add_char(&new_s, src->c_str[i]);
	}

	return new_s;
}

#endif
