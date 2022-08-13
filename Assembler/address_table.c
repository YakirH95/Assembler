#include "address_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

address_entries* initialize_address_table()
{
	address_entries* i_e = malloc(sizeof(address_entries));
	i_e->entries = (address_entry*)malloc(sizeof(address_entry) * 5);
	i_e->allocated_size = 5;
	i_e->used_size = 0;
	return i_e;
}

void delete_data_image(address_entries* i_e)
{
	free(i_e->entries);
	free(i_e);
}

void insert_address_entry(address_entries* i_e, int decimal_address, char* binary_num)
{
	if (i_e->used_size == i_e->allocated_size)
	{
		i_e->allocated_size += 5;
		i_e->entries = realloc(i_e->entries, i_e->allocated_size * sizeof(address_entry));
	}

	i_e->entries[i_e->used_size].decimal_address = 100 + decimal_address;
	strncpy(i_e->entries[i_e->used_size].binary_code, binary_num, 10);
	i_e->used_size++;
}

void set_address_binary_num(address_entries* a_e, int decimal_address, char* binary_code)
{
	for (int i = 0; i < a_e->used_size; i++)
	{
		if (strcmp(a_e->entries[i].decimal_address, decimal_address) == 0)
		{
			strncpy(a_e->entries[i].binary_code, binary_code, 10);
		}
	}
}

