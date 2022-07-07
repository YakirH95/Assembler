#include <stdio.h>
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>

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

//Dictionary constructor 
dictionary* create_dictionary()
{
	dictionary* d = malloc(sizeof(dictionary));
	d->items = malloc(sizeof(entry) * 5);
	d->used_size = 0;
	d->allocated_size = 5;
	return d;
}

//Dictionary destructor
void delete_dictionary(dictionary* d)
{
	free(d->items);
	free(d);
}

void add_entry(dictionary* d, char* k, char* v)
{
	if (d->used_size == d->allocated_size)
	{
		d->allocated_size += 5;
		d->items = realloc(d->items, d->allocated_size);
	}

	d->items[d->used_size].key = k;
	d->items[d->used_size].value = v;
	d->used_size++;
}

char* get_value(dictionary* d, char* key)
{
	for (int i = 0; i < d->used_size; i++)
	{
		if (strcmp(d->items[i].key, key == 0))
		{
			return d->items[i].value;
		}
	}
}




