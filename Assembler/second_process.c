#include "dictionary.h"
#include "first_process.h"
#include "pre_proccessor.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operations_table.h"
#include "symbol_table.h"
#include "first_process.h"
#include "address_table.h"
#include "address_analizer.h"
#include "registers.h"
#include "second_process.h"

/*Second process, replace fields of "?" on code table*/
void fill_address_table(symbol_table* symbol_table, address_entries* code_table, address_entries* data_table, char* assembly_input, dictionary* operation_table, dictionary* registers_dict, dictionary* entry_external_dict)
{
	int L = 0;
	int IC = 0;
	int DC = 0;

	char* current_line = NULL;

	/*Next line*/
	current_line = strtok(assembly_input, "\r\n");

	while (current_line != NULL)
	{
		/*If theres entry symbol, modify its type on symbol table */
		if (strstr(current_line, ":") != NULL)
		{
			char* colon_start = strchr(current_line, ':');
			int symbol_name_length = colon_start - current_line;
			char* symbol_name = calloc(symbol_name_length + 1, 1);
			strncpy(symbol_name, current_line, symbol_name_length);
			if (key_exists(entry_external_dict, symbol_name) != -1)
			{
				int symbol_index = key_exists(entry_external_dict, symbol_name);
				int main_symbol_index = symbol_exists(symbol_table, symbol_name);
				/*If it's entry*/
				if (strcmp(entry_external_dict->items[symbol_index].value, "3") == 0)
				{
					modify_symbol_type(symbol_table, main_symbol_index, 3);
				}
			}
		} 

		/*Irrelevant for second process, move to next line*/
		if (strstr(current_line, ".data") || strstr(current_line, ".string") ||
			strstr(current_line, ".struct") || strstr(current_line, "extern") || strstr(current_line, ".entry"))
		{
			current_line = strtok(NULL, "\r\n");
			continue;
		}
		
		

		analize_remaining_address(code_table, current_line, symbol_table, &L, IC, operation_table, registers_dict);
		
		IC += (L+1);
		L = 0;
		/*Next line*/
		current_line = strtok(NULL, "\r\n");
	}
}