#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Line 
typedef struct
{
	int decimal_address;
	char binary_code[10];
}   address_entry;

//All gruops
typedef struct
{
	address_entry* entries;
	int used_size;
	int allocated_size;
}   address_entries;

address_entries* initialize_address_table();
void insert_address_entry(address_entries* a_e, int decimal_address, char* binary_num);
void set_address_binary_num(address_entries* a_e, int offset, char* binary_code);

void add_offset_to_table(address_entries* a_e, int offset);
