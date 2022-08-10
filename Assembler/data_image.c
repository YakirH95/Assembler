#include "data_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

image_entries* initialize_data_image()
{
	image_entries* i_e = malloc(sizeof(image_entries));
	i_e->entries = (data_image*)malloc(sizeof(data_image) * 5);
	i_e->allocated_size = 0;
	i_e->used_size = 5;
	return i_e;
}

void delete_data_image(image_entries* i_e)
{
	free(i_e->entries);
	free(i_e);
}

void insert_data_image(image_entries* i_e, int decimal_address, char* binary_num)
{
	if (i_e->used_size == i_e->allocated_size)
	{
		i_e->allocated_size += 5;
		i_e->entries = realloc(i_e->entries, i_e->allocated_size * sizeof(data_image));
	}

	i_e->entries[i_e->used_size].decimal_address = 100 + decimal_address;
	strncpy(i_e->entries[i_e->used_size].binary_code, binary_num, 10);
	i_e->used_size++;
}

