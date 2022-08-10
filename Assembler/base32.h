#pragma once

typedef struct
{
	int decimal_value;
	char base32_value;
}   entry;

typedef struct
{
	entry* items;
	int used_size;
	int allocated_size;
}   base32_table;