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



void fill_address_table(symbol_table* symbol_table, address_entries* code_table, address_entries* data_table, char* assembly_input, dictionary* operation_table, dictionary* registers_dict)
{
	int L = 0;
	int IC = 0;
	int DC = 0;
	

	char* current_line = NULL;

	//Next line
	current_line = strtok(assembly_input, "\r\n");

	while (current_line != NULL)
	{
		if (strstr(current_line, ".data") || strstr(current_line, ".string") || strstr(current_line, ".struct") || strstr(current_line, "extern"))
		{
			current_line = strtok(NULL, "\r\n");
			continue;
		}
		
		else if (strstr(current_line, ".entry"))
		{
			char* symbol_after_entry = strstr(current_line, ".entry") + strlen(".entry");
			int symbol_index = symbol_exists(symbol_table, symbol_after_entry);
			modify_symbol_type(symbol_table, symbol_index, 3);
		}

		
		analize_remaining_address(code_table, current_line, symbol_table, &L, IC, operation_table, registers_dict);
		
		
		IC += (L+1);
		L = 0;

		current_line = strtok(NULL, "\r\n");
	}
}