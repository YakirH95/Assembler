#include "dictionary.h"
#include "first_process.h"
#include "pre_proccessor.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operations_table.h"


symbol_table* create_table()
{
	symbol_table* s_t = malloc(sizeof(symbol_table));
	s_t->items = malloc(sizeof(symbol_entry) * 5);
	//Used space in dictionary
	s_t->used_size = 0;
	//Allocated memory for dictionary
	s_t->allocated_size = 5;
	return s_t;
}

//Dictionary destructor
void delete_table(symbol_table* s_t)
{
	for (int i = 0; i < s_t->used_size; i++)
	{
		free(s_t->items[i].symbol_name);
		
	}

	free(s_t->items);
	free(s_t);
}

void add_symbol_entry(symbol_table* s_t, char* symbol_name, int symbol_address, int is_external)
{
	if (s_t->used_size == s_t->allocated_size)
	{
		s_t->allocated_size += 5;
		s_t->items = realloc(s_t->items, s_t->allocated_size);
	}

	s_t->items[s_t->used_size].symbol_name = _strdup(symbol_name);
	s_t->items[s_t->used_size].symbol_address = symbol_address;
	s_t->items[s_t->used_size].symbol_type = is_external;
	s_t->used_size++;
}

int symbol_exists(symbol_table* s_t, char* search_symbol)
{
	for (int i = 0; i < s_t->used_size; i++)
	{
		//If string are equal
		if (strcmp(s_t->items[i].symbol_name, search_symbol) == 0)
		{
			return 1;
		}
	}

	return 0;
}

void define_extern_symbol(symbol_table* symbol_table, char* current_line, int is_symbol_define)
{
	if (is_symbol_define)
	{
		printf("Warning- symbol defined before extern won't be added to the symbol table");
	}

	char* extern_symbol_name = NULL;
	char* toBeSearched = ".extern";
	extern_symbol_name = strstr(current_line, toBeSearched) + strlen(toBeSearched + 1);

	add_symbol_entry(symbol_table, extern_symbol_name, 0, 1);
}

void define_symbol(symbol_table* symbol_table, char* symbol_name, char* current_line, int IC_DC)
{
	symbol_name = strtok(current_line, ":");
	if (symbol_exists(symbol_table, symbol_name))
	{
		printf("label already exist");
		return;
	}

	add_symbol_entry(symbol_table, symbol_name, IC_DC, 0);
}