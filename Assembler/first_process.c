#include "first_process.h"
#include "dictionary.h"
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


symbol_table* identify_symbols(char* assembly_input, dictionary* operation_dict,
	                   address_entries* data_table, address_entries* code_table, dictionary* register_dict)
{
	int is_symbol_define = 0;
	int L = 0;
	int IC = 0;
	int DC = 0;
	symbol_table* symbols_table = create_table();
	
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

		// Check if .data .string or .struct line for Ex LENGTH: .data 6
		if (strstr(current_line, ".data") || strstr(current_line, ".string") || strstr(current_line, ".struct"))
		{
			if (is_symbol_define)
			{
				define_symbol(symbols_table, current_line, &DC, 0);
			}

			if (strstr(current_line, ".data"))
			{
				extract_parameters(current_line, ".data", &DC, data_table);
			}

			else if (strstr(current_line, ".string"))
			{
				extract_parameters(current_line, ".string", &DC, data_table);
			}
			
			else if (strstr(current_line, ".struct"))
			{
				extract_parameters(current_line, ".struct", DC, data_table);
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
				define_symbol(symbols_table, current_line, IC, 1);
			}

			int operation_index = is_operation(operation_dict, current_line);
			if (operation_index == -1)
			{
				printf("Operation name is invalid");
			}
			
			else
			{
				char* operation_name = get_key(operation_dict, operation_index);
				char binary_code[10] = { 0 };
				if (operation_index == 14)
				{
					insert_address_entry(code_table, IC, "1110000000");
					IC += (L + 1);
				}
				else if (operation_index == 15)
				{
					insert_address_entry(code_table, IC, "1111000000");
					IC += (L + 1);
				}
				else
				{
					analize_operands(operation_dict, code_table, operation_name,
						current_line, symbols_table, register_dict, &L, IC, binary_code);
					insert_address_entry(code_table, IC, binary_code);
					IC += (L + 1);
					L = 0;
				}
			}
		}


		current_line = strtok(NULL, "\r\n");
	}

	//if there are errors, stop
	return symbols_table;
}

void extract_parameters(char* current_line, char* data_type, int* DC, address_entries* data_table)
{
	char* token = NULL;
	
	//Point to after ".data"
	token = strstr(current_line, data_type) + strlen(data_type);
	while (token != NULL && *token == ' ')
	{
		token++;
	}
	
	if (strcmp(data_type, ".data") == 0)
	{
		while (token != NULL)
		{
			char* comma_ptr = strchr(token, ',');
			int length = comma_ptr - token;
			char* parameter = calloc(length + 1, 1);
			strncpy(parameter, token, length);

			int num_paramater = atoi(parameter);

			int binary_converted[10] = {0};
			if (parameter[0] == '-')
			{
				num_paramater *= -1;
				ndec_to_binary(num_paramater, binary_converted);
			}

			else
			{
				dec_to_binary(num_paramater, binary_converted);
			}

			char binary_char[10] = { 0 };
			sprintf(binary_char, "%d", binary_converted);
				
			insert_address_entry(data_table,  * DC, binary_char);
			(* DC)++;
			token = comma_ptr + 1;
		}
	}

	else if (strcmp(data_type, ".string")== 0)
	{
		char* chars = strchr(token, '"') + 1;
		int binary_converted[10] = {0};
		char char_binary[10];
		char char_to_add[10];
		char_to_add[0] = '0';
		char_to_add[1] = '0';
		char_to_add[2] = '0';
		
		for (int i = 0; i < strlen(chars); i++)
		{
			char c = chars[i];

			if (c  == '\"')
			{
				break;
			}
			
			int ascii_val = (int)c;
			_itoa(ascii_val, char_binary, 2);
			for (int i = 0; i < 7; i++)
			{
				char_to_add[i + 3] = char_binary[i];
			}
			insert_address_entry(data_table, *DC, char_to_add);
			(* DC)++;

		}

		char binary_char[10] = { '0','0','0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' };
		//sprintf(binary_char, "%d", binary_converted);
		insert_address_entry(data_table, *DC, binary_char);
		(* DC)++;
	}

	// EDIT
	else if (strcmp(data_type, ".struct"))
	{
		while (token != NULL)
		{
			char* comma_ptr = strchr(token, ',');
			int length = comma_ptr - token;
			char* parameter = calloc(length + 1, 1);
			strncpy(parameter, token, length);

			int num_paramater = atoi(parameter);

			int binary_converted[10] = { 0 };
			if (parameter[0] == '-')
			{
				num_paramater *= -1;
				ndec_to_binary(num_paramater, binary_converted);
			}

			else
			{
				dec_to_binary(num_paramater, binary_converted);
			}

			char binary_char[10] = { 0 };
			sprintf(binary_char, "%d", binary_converted);

			insert_address_entry(data_table, *DC, binary_char);
			(* DC)++;
			token = comma_ptr + 1;
		}

		char* chars = strchr(token, '"') + 1;
		int binary_converted = NULL;
		for (int i = 0; i < strlen(chars); i++)
		{
			char c = chars[i];
			int ascii_val = (int)c;
			dec_to_binary(ascii_val, binary_converted);
			insert_address_entry(data_table, *DC, binary_converted);
			(* DC)++;
		}

		char binary_char[10] = { 0 };
		sprintf(binary_char, "%d", binary_converted);
		insert_address_entry(data_table, *DC, binary_char);
		(* DC)++;
	}
}



