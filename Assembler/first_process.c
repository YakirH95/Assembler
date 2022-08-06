#include "dictionary.h"
#include "first_process.h"
#include "pre_proccessor.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operations_table.h"
#include "symbol_table.h"
#include "first_process.h"
#include "data_image.h"


symbol_table* identify_symbols(char* assembly_input, dictionary* operation_dict, data_entry* data_image, code_entry* code_image)
{
	int is_symbol_define = 0;
	int L = 0;
	int IC = 0;
	int DC = 0;
	symbol_table* symbols_table = create_table();
	
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

		//Ex LENGTH: .data 6
		if (strstr(current_line, ".data") || strstr(current_line, ".string") || strstr(current_line, ".struct"))
		{
			if (is_symbol_define)
			{
				define_symbol(symbols_table,symbol_name, current_line, DC);
				DC++;
			}

			if (strstr(current_line, ".data"))
			{
				extract_parameters(current_line, ".data", DC, data_image);
			}

			else if (strstr(current_line, ".string"))
			{
				extract_parameters(current_line, ".string", DC, data_image);
			}
			
			else if (strstr(current_line, ".struct"))
			{
				extract_parameters(current_line, ".struct", DC, data_image);
			}
		}

		//EX .extern HELLO
		else if (strstr(current_line, ".extern") || strstr(current_line, ".entry"))
		{
			if (strstr(current_line, ".extern"))
			{
				define_extern_symbol(symbols_table, current_line, is_symbol_define);
			}

			else if (strstr(current_line, ".entry"))
			{
				//in second pass
			}
		}

		// If it's symbol + operation ex  MAIN: mov
		else 
		{
			if (is_symbol_define)
			{
				define_symbol(symbols_table, symbol_name, current_line, IC);
			}

			int operation_index = is_operation(operation_dict, current_line);
			if (operation_index == 0)
			{
				printf("Operation name is invalid");
			}
			else
			{
				// TODO: bad function argument
				//char* operation_name = get_key(operation_dict, operation_index);
				//insert_code_image(code_image, operation_name, IC);
			}
		}


		current_line = strtok(NULL, "\r\n");
	}

	//if there are errors, stop
	return symbols_table;
}

void extract_parameters(char* current_line, char* data_type, int DC, data_entry* data_entry)
{
	char* token = NULL;
	
	//Point to after ".data"
	token = strstr(current_line, data_type) + strlen(data_type + 1);
	
	if (strcmp(data_type, ".data"))
	{
		char* parameter = strtok(token, ",");
		while (parameter != NULL)
		{
			int num_paramater = atoi(parameter);
			// count tokens
			// delimiters present in current line.	

			insert_data_image(data_entry, num_paramater ,DC);
			DC++;
			parameter = strtok(NULL, ",");
		}
	}

	else if (strcmp(data_type, ".string"))
	{
		for (int i = 0; i < strlen(token); i++)
		{
			char c = token[i];
			int ascii_val = (int)c;
			insert_data_image(data_entry, ascii_val, DC);
			DC++;
		}
		insert_data_image(data_entry, '\0', DC);
		DC++;
	}

	else if (strcmp(data_type, ".struct"))
	{
		char* parameter = strtok(token, ",");
		int num_paramater = atoi(parameter);
		insert_data_image(data_entry, num_paramater, DC);
		DC++;
		parameter = strtok(NULL, ",");
		
		for (int i = 0; i < strlen(token); i++)
		{
			char c = token[i];
			int ascii_val = (int)c;
			insert_data_image(data_entry, ascii_val, DC);
			DC++;
		}
		insert_data_image(data_entry, '\0', DC);
		DC++;
	}
}



