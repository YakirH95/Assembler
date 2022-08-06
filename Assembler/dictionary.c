#include <stdio.h>
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>

//Dictionary constructor 
dictionary* create_dictionary()
{
	dictionary* d = (dictionary*)malloc(sizeof(dictionary));
	d->items = (entry*)malloc(sizeof(entry) * 5);
	//Used space in dictionary
	d->used_size = 0;
	//Allocated memory for dictionary
	d->allocated_size = 5;
	return d;
}

//Dictionary destructor
void delete_dictionary(dictionary* d)
{
	for (int i = 0; i < d->used_size; i++)
	{
		free(d->items[i].key);
		free(d->items[i].value);
	}

	free(d->items);
	free(d);
}

void add_entry(dictionary* d, char* k, char* v)
{
	if (d->used_size == d->allocated_size)
	{
		d->allocated_size += 5;
		d->items = realloc(d->items, d->allocated_size * sizeof(entry));
	}

	d->items[d->used_size].key = strdup(k);
	d->items[d->used_size].value = strdup(v);
	d->used_size++;
}

char* get_value(dictionary* d, char* key)
{
	for (int i = 0; i < d->used_size; i++)
	{
		if (strcmp(d->items[i].key, key) == 0)
		{
			return d->items[i].value;
		}
	}

	return NULL;
}


int key_exists(dictionary* d, char* search_key)
{
	for (int i = 0; i < d->used_size; i++)
	{
		//If string are equal
		if (strcmp(d->items[i].key, search_key) == 0)
		{
			return 1;
		}
	}

	return 0;
}

char* get_key(dictionary* d, int index)
{
	return d->items[index].key;
}



