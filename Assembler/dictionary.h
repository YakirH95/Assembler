#pragma once


typedef struct
{
	char* key;
	char* value;
}   entry;

typedef struct
{
	entry* items;
	int used_size;
	int allocated_size;
}   dictionary;

dictionary* create_dictionary();
void delete_dictionary(dictionary* d);
void add_entry(dictionary* d, char* k, char* v);
char* get_value(dictionary* d, char* key);
int key_exists(dictionary* d, char* search_key);
