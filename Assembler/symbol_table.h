#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
void add_symbol_entry(symbol_table* s_t, char* symbol_name, int symbol_address, int is_external);
int symbol_exists(symbol_table* s_t, char* search_symbol);
void define_extern_symbol(symbol_table* symbol_table, char* current_line, int is_symbol_define);
void define_symbol(symbol_table* symbol_table, char* current_line, int IC_DC, int isCode);
void modify_symbol_type(symbol_table* symbol_table, int symbol_index, int symbol_type);
int get_symbol_address(symbol_table* s_t, char* symbol_name);

