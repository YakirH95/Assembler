#include <stdio.h>
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>

char* strdups(char* str);

/*Dictionary constructor*/
dictionary* create_dictionary()
{
	dictionary* d = (dictionary*)malloc(sizeof(dictionary));
	d->items = (entry*)malloc(sizeof(entry) * 5);
	/* Used space in dictionary */
	d->used_size = 0;
	/* Allocated memory for dictionary */
	d->allocated_size = 5;
	return d;
}

/*Dictionary destructor*/
void delete_dictionary(dictionary* d)
{
	int i;
	for (i = 0; i < d->used_size; i++)
	{
		free(d->items[i].key);
		free(d->items[i].value);
	}

	free(d->items);
	free(d);
}

/*Add entry dynaimcally*/
void add_entry(dictionary* d, char* k, char* v)
{
	if (d->used_size == d->allocated_size)
	{
		d->allocated_size += 5;
		d->items = realloc(d->items, d->allocated_size * sizeof(entry));
	}

	d->items[d->used_size].key = strdups(k);
	d->items[d->used_size].value = strdups(v);
	d->used_size++;
}

/*Get specific value*/
char* get_value(dictionary* d, char* key)
{
	int i;
	for (i = 0; i < d->used_size; i++)
	{
		if (strcmp(d->items[i].key, key) == 0)
		{
			return d->items[i].value;
		}
	}

	return NULL;
}

/*Check if key is already in dict*/
int key_exists(dictionary* d, char* search_key)
{
	int i;
	for (i = 0; i < d->used_size; i++)
	{
		/* If string are equal */
		if (strcmp(d->items[i].key, search_key) == 0)
		{
			return i;
		}
	}

	return -1;
}

/*Get specific key*/
char* get_key(dictionary* d, int index)
{
	return d->items[index].key;
}