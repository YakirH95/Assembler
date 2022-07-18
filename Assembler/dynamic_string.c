#include "dynamic_string.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 


dynamic_string* create_dynamic_string()
{
	dynamic_string* d_s = malloc(sizeof(dynamic_string));
	d_s->allocated_size = 10;
	d_s->string = malloc(sizeof(char) * 10);
	d_s->string[0] = NULL;

	return d_s;
}

void delete_dynamic_string(dynamic_string* d_s)
{
	free(d_s->string);
	free(d_s);
}

void add_string(dynamic_string* d_s, char* string_to_add)
{
	int length_of_strcat = strlen(string_to_add) + strlen(d_s->string);
	if (d_s->allocated_size <= length_of_strcat)
	{
		d_s->allocated_size += (length_of_strcat * 2);
		d_s->string = realloc(d_s->string, d_s->allocated_size);
	}

	strcat(d_s->string, string_to_add);
}

char* get_internal_string(dynamic_string* d_s)
{
	return d_s->string;
}