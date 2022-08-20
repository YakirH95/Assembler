#include "address_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Code and data table constructor*/
address_entries* initialize_address_table()
{
	address_entries* i_e = malloc(sizeof(address_entries));
	i_e->entries = (address_entry*)malloc(sizeof(address_entry) * 5);
	i_e->allocated_size = 5;
	i_e->used_size = 0;
	return i_e;
}

/*Destructor*/
void delete_address_table(address_entries* a_e)
{
	free(a_e->entries);
	free(a_e);
}

/*Add line to code/data table dynamically*/
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

/*Set address for missing values at second process*/
void set_address_binary_num(address_entries* a_e, int offset, char* binary_code)
{
	int i;
	for (i = 0; i < a_e->used_size; i++)
	{
		if (a_e->entries[i].decimal_address == (offset + 100))
		{
			strncpy(a_e->entries[i].binary_code, binary_code, 10);
		}
	}
}

/*Synchronize data and code tables indexes*/
void add_offset_to_table(address_entries* a_e, int offset)
{ 
	int i;
	for (i = 0; i < a_e->used_size; i++)
	{
		a_e->entries[i].decimal_address += offset;
	}
}

/*Arrange indexes in the correct order*/
void sort_by_address(address_entries* a_e)
{
	address_entry temp = { 0 };

	int i;
	for (i = 0; i < a_e->used_size; i++)
	{
		int j;
		for (j = i + 1; j < a_e->used_size - 1; j++)
		{
			if (a_e->entries[i].decimal_address > a_e->entries[j].decimal_address)
			{
				memcpy(&temp, &a_e->entries[i], sizeof(address_entry));
				memcpy(&a_e->entries[i], &a_e->entries[j], sizeof(address_entry));
				memcpy(&a_e->entries[j], &temp, sizeof(address_entry));
			}
		}
	}
}