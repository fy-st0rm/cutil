#include "cutil.h"

void test_list()
{
	int a = 10;
	List* list = list_new();

	// Testing append
	for (int i = 0; i < a; i++)
	{
		list_append(list, (void*) &i, sizeof(i));
	}

	// Testing printing pointers
	list_print(list);

	// Testing get function
	for (int i = 0; i < a; i++)
	{
		int* b = list_get(list, i);
		printf("%d\n", *b);
	}

	// Testing pop function
	printf("\n\n");
	list_pop(list, 8);
	for (int i = 0; i < 9; i++)
	{
		int *b = list_get(list, i);
		printf("%d\n", *b);
	}

	// Testing with different data types
	char* text = "Hello world\n";
	list_append(list, (void*) text, strlen(text) * sizeof(char));
	printf("%s\n", list_get(list, list->len-1));

	// Testing clean function
	list_clean(list);
}

void test_dict()
{
	Dict* dict = dict_new();

	// Testing appending
	char* key = "hello";
	char* val = "World";
	dict_insert(dict, (void*) key, (void*) val, sizeof(char) * strlen(key), sizeof(char) * strlen(val)); 

	int   key2 = 69;
	char* val2 = "HAHA";
	dict_insert(dict, (void*) &key2, (void*) val2, sizeof(key2), sizeof(char) * strlen(val2)); 

	int   key3 = 20;
	int   val3 = 30;
	dict_insert(dict, (void*) &key3, (void*) &val3, sizeof(key3), sizeof(val3));

	// Testing dict print
	dict_print(dict);

	// Testing dict get
	char* g_val = dict_get(dict, (void*) key, sizeof(char) * strlen(key));
	printf("%p = %s\n", g_val, g_val);

	char* g_val2 = dict_get(dict, (void*) &key2, sizeof(key2));
	printf("%p = %s\n", g_val2, g_val2);

	int*  g_val3 = dict_get(dict, (void*) &key3, sizeof(key3));
	printf("%p = %d\n", g_val3, *g_val3);

	// Testing dict pop
	dict_pop(dict, (void*) &key3, sizeof(key3));
	dict_print(dict);

	// Clean up
	dict_clean(dict);
}

int main()
{
	//test_list();
	test_dict();
}
