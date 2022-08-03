#include "dictionary.h"
#include "first_process.h"
#include "pre_proccessor.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operations_table.h"
#include "symbol_table.h"


int is_symbol_define = 0;
symbol_table* identify_symbols(char* assembly_input)
{
	int IC = 0;
	int DC = 0;
	symbol_table* symbols_table = create_table();
	dictionary* operation_dict = create_operations_dict();
	int data_counter = 0;
	char* symbol_name = NULL;

	char* current_line = NULL;

	//Next line
	current_line = strtok(assembly_input, "\r\n");

	while (current_line != NULL)
	{
		is_symbol_define = 0;
		if (strstr(current_line, ":") != NULL)
		{
			is_symbol_define = 1;
		}

		if (strstr(current_line, ".data") || strstr(current_line, ".string") || strstr(current_line, ".struct"))
		{
			if (is_symbol_define)
			{
				define_symbol(symbols_table,symbol_name, current_line, DC);
				DC ++;
				char* token = strtok(current_line + strlen(symbol_name), ","); ///check with amit
			}

			char* token = strtok(current_line, ",");
				// count tokens
				// delimiters present in current line.
			while (token != NULL) {
				data_counter++;
				//need to add insert token to data array******
				token = strtok(NULL, ",");
			}

			DC += data_counter;
			data_counter = 0;
		}

		else if (strstr(current_line, ".extern") || strstr(current_line, ".entry"))
		{
			if (strstr(current_line, ".extern"))
			{
				define_extern_symbol(symbols_table, current_line);
			}

			else if (strstr(current_line, ".entry"))
			{
				//in second pass
			}
		}

		else 
		{
			if (is_symbol_define)
			{
				define_symbol(symbols_table, symbol_name, current_line, IC);
			}

			if (is_operation(operation_dict, current_line) == 0)
			{
				printf("Operation name is invalid");
			}
		}


		current_line = strtok(NULL, "\r\n");
	}

	//if there are errors, stop
}

void define_extern_symbol(symbol_table* symbol_table, char* current_line)
{
	if (is_symbol_define)
	{
		printf("Warning- symbol defined before extern won't be added to the symbol table");
	}

	char* extern_symbol_name = NULL;
	char* toBeSearched = ".entry";
	extern_symbol_name = strstr(current_line, toBeSearched) + strlen(toBeSearched +1);
	
	add_symbol_entry(symbol_table, extern_symbol_name, current_line, 0, 1);
}

void define_symbol(symbol_table* symbol_table, char* symbol_name, char* current_line, int IC_DC)
{
	symbol_name = strtok(current_line, ":");
	if (symbol_exists(symbol_table, symbol_name))
	{
		printf("label already exist");
		return;
	}

	add_symbol_entry(symbol_table, symbol_name, current_line, IC_DC, 0);
}

int is_operation(dictionary* operation_table, char* current_line)
{
	for (int i = 0; i < operation_table->used_size; i++)
	{
		if (strstr(current_line, get_key(operation_table, i)) != NULL)
		{
			return 1;
		}
	}

	return 0;
}
