#pragma once
#include "dictionary.h"
#include "first_process.h"
#include "pre_proccessor.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operations_table.h"

typedef struct
{
	char* symbol_name;
	int symbol_address;
	int symbol_type; //0 for relocatable, 1 for external
}   symbol_entry;

typedef struct
{
	symbol_entry* items;
	int used_size;
	int allocated_size;
}   symbol_table;

symbol_table* create_table();
void delete_table(symbol_table* s_t);
void add_symbol_entry(symbol_table* s_t, char* symbol_name, int symbol_address, int symbol_type);
int symbol_exists(symbol_table* s_t, char* search_symbol);