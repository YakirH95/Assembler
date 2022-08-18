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

int get_symbol_address(symbol_table* s_t, char* symbol_name)
{
	for (int i = 0; i < s_t->used_size; i++)
	{
		
		if (strstr(symbol_name, s_t->items[i].symbol_name))
		{
			return s_t->items[i].symbol_address;
		}
	}

	return NULL;
}

//symbol type: 0 for data, 1 for extern, 2 for code, 3 for entry
void add_symbol_entry(symbol_table* s_t, char* symbol_name, int symbol_address, int symbol_type)
{
	if (s_t->used_size == s_t->allocated_size)
	{
		s_t->allocated_size += 5;
		s_t->items = realloc(s_t->items, s_t->allocated_size * sizeof(symbol_entry));
	}

	s_t->items[s_t->used_size].symbol_name = strdup(symbol_name);
	s_t->items[s_t->used_size].symbol_address = symbol_address + 100;
	s_t->items[s_t->used_size].symbol_type = symbol_type;
	s_t->used_size++;
}

int symbol_exists(symbol_table* s_t, char* search_symbol)
{
	for (int i = 0; i < s_t->used_size; i++)
	{
		//If string are equal
		if (strcmp(s_t->items[i].symbol_name, search_symbol) == 0)
		{
			return i;
		}
	}
	//if not exists
	return -1;
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

void define_symbol(symbol_table* symbol_table, char* current_line, int IC_DC, int isCode)
{
	char* colon_start = strchr(current_line, ':');
	int symbol_name_length = colon_start - current_line;
	char* symbol_name = malloc(symbol_name_length + 1);
	symbol_name[symbol_name_length] = 0;
	strncpy(symbol_name, current_line, symbol_name_length);


	if (symbol_exists(symbol_table, symbol_name)!= -1)
	{
		printf("label %s already exist", symbol_name);
		return;
	}

	if (isCode == 1)
	{
		add_symbol_entry(symbol_table, symbol_name, IC_DC, 2);

	}

	else
	{
		add_symbol_entry(symbol_table, symbol_name, IC_DC, 0);
	}
}

void modify_symbol_type(symbol_table* symbol_table, int symbol_index, int symbol_type)
{
	symbol_table->items[symbol_index].symbol_type = symbol_type;
}

void add_offset_data_symbols(symbol_table* s_t, int offset)
{
	for (int i = 0; i < s_t->used_size; i++)
	{
		if (s_t->items[i].symbol_type == 0)
		{
			s_t->items[i].symbol_address += offset;
		}
	}
}

void define_entry_symbol(symbol_table* symbol_table, char* current_line, int IC)
{
	char* symbol_name = strstr(current_line, ".entry") + 6;
	while (*symbol_name == ' ')
	{
		symbol_name++;
	}

	add_symbol_entry(symbol_table, symbol_name, IC, 3);
}

