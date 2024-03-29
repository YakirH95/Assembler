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

/*Building symbol table, starting first process*/
symbol_table* identify_symbols(char* assembly_input, dictionary* operation_dict,
	address_entries* data_table, address_entries* code_table, dictionary* register_dict, dictionary* entry_external_dict, symbol_table* external_symbols_address)
{
	/*Flag for symbol found*/
	int is_symbol_define = 0;
	int L = 0;
	int IC = 0;
	int DC = 0;
	symbol_table* symbols_table = create_table();
	char* colon_start = NULL;
	int symbol_name_length = 0;
	char* symbol_name = NULL;
	int symbol_index = 0;
	int operation_index = 0;
	char* operation_name = NULL;
	char binary_code[10] = { 0 };


	char* current_line = NULL;

	/*Next line*/
	current_line = strtok(assembly_input, "\r\n");

	while (current_line != NULL)
	{
		is_symbol_define = 0;
		/*If found symbol definition*/
		if (strstr(current_line, ":") != NULL)
		{
			is_symbol_define = 1;
		}

		/*It's symbol*/
		if (is_symbol_define)
		{
			/*Extract symbol name*/
			colon_start = strchr(current_line, ':');
			symbol_name_length = colon_start - current_line;
			symbol_name = calloc(symbol_name_length + 1, 1);
			strncpy(symbol_name, current_line, symbol_name_length);


			/*If its entry or external*/
			if (key_exists(entry_external_dict, symbol_name) != -1)
			{
				symbol_index = key_exists(entry_external_dict, symbol_name);
				/*If it's entry*/
				if (strcmp(entry_external_dict->items[symbol_index].value, "3") == 0)
				{
					/*Insert to main symbol table*/
					define_symbol(symbols_table, current_line, IC + DC, 1);
				}
			}

			free(symbol_name);
		}

		/* Check if.data.string or .struct line, extract paramaters*/
		if (strstr(current_line, ".data") || strstr(current_line, ".string") || strstr(current_line, ".struct"))
		{
			/*If line also contain symbol*/
			if (is_symbol_define)
			{
				define_symbol(symbols_table, current_line, DC, 0);
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
				extract_parameters(current_line, ".struct", &DC, data_table);
			}
		}

		/*If it's entry or extern, save on dictionary for entries and externals*/
		else if (strstr(current_line, ".extern") || strstr(current_line, ".entry"))
		{
			if (strstr(current_line, ".extern"))
			{
				symbol_name = strstr(current_line, ".extern") + 7;
				while (*symbol_name == ' ')
				{
					symbol_name++;
				}
				add_entry(entry_external_dict, symbol_name, "1"); /*1 for external, 3 for entry*/
			}

			else if (strstr(current_line, ".entry"))
			{
				symbol_name = strstr(current_line, ".entry") + 6;
				while (*symbol_name == ' ')
				{
					symbol_name++;
				}
				add_entry(entry_external_dict, symbol_name, "3"); /*1 for external, 3 for entry*/
			}
		}

		/* If it's operation */
		else
		{
			/*Found symbol*/
			if (is_symbol_define)
			{
				define_symbol(symbols_table, current_line, IC, 1);
			}

			/*Check that operation is valid*/
			operation_index = is_operation(operation_dict, current_line);
			if (operation_index == -1)
			{
				printf("Operation name is invalid\n");
			}

			else
			{
				operation_name = get_key(operation_dict, operation_index);
				/*Identify special operations*/
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
				/*Analize operands*/
				else
				{
					analize_operands(operation_dict, code_table, operation_name,
						current_line, symbols_table, register_dict, &L, IC, binary_code, entry_external_dict, external_symbols_address);
					insert_address_entry(code_table, IC, binary_code);
					IC += (L + 1);
					L = 0;
				}
			}
		}
		current_line = strtok(NULL, "\r\n");
	}

	/*Synch addresses to show chorologiacaly*/
	add_offset_to_table(data_table, IC);
	add_offset_data_symbols(symbols_table, IC);

	return symbols_table;
}

/*Get integers or strings, encode them */
void extract_parameters(char* current_line, char* data_type, int* DC, address_entries* data_table)
{
	char* token = NULL;
	int last_int = 0;
	char* comma_ptr = NULL;
	char* parameter = NULL;
	int length = 0;
	int num_paramater = 0;
	int binary_converted[10] = { 0 };
	char* chars = NULL;
	char char_binary[10] = {0};
	char char_to_add[10] = {0};
	char c = 0;
	int ascii_val = 0;
	int i = 0;
	char binary_char[10] = { '0','0','0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' };
	char struct_char_binary[10] = {0};
	char struct_binary_char[10] = { '0','0','0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' };


	/*Point to after ".struct" */
	token = strstr(current_line, data_type) + strlen(data_type);
	/*Ignore empty spaces*/
	while (token != NULL && *token == ' ')
	{
		token++;
	}

	/*Encode numbers*/
	if (strcmp(data_type, ".data") == 0)
	{
		/*Identify when last num*/
		while (token != NULL)
		{
			comma_ptr = strchr(token, ',');
			parameter = calloc(10, 1);

			/*Identify when reached last int*/
			if (comma_ptr != NULL)
			{
				length = comma_ptr - token;
				strncpy(parameter, token, length);

			}
			else
			{
				strcpy(parameter, token);
				last_int = 1;
			}

			num_paramater = atoi(parameter);

			/*Identify negative numbers*/
			if (parameter[0] == '-')
			{
				ndec_to_binary(num_paramater, binary_converted);
			}

			else
			{
				dec_to_binary(num_paramater, binary_converted);
			}

			/*Convert int array to char array*/
			for (i = 0; i < 10; i++)
			{
				binary_char[i] = '0' + binary_converted[i];
			}

			insert_address_entry(data_table, *DC, binary_char);
			(*DC)++;
			/*Next num*/
			token = comma_ptr + 1;

			free(parameter);
			if (last_int == 1)
			{
				break;
			}
		}
	}

	/*Encode string*/
	else if (strcmp(data_type, ".string") == 0)
	{
		chars = strchr(token, '"') + 1;
		
		char_to_add[0] = '0';
		char_to_add[1] = '0';
		char_to_add[2] = '0';

		for (i = 0; i < strlen(chars); i++)
		{
			c = chars[i];

			/*Identify end of string*/
			if (c == '\"')
			{
				break;
			}

			ascii_val = (int)c;
			itoas(ascii_val, char_binary, 2);

			/*Complete encoding*/
			for (i = 0; i < 7; i++)
			{
				char_to_add[i + 3] = char_binary[i];
			}
			insert_address_entry(data_table, *DC, char_to_add);
			(*DC)++;

		}

		/*End of string is 0*/
		insert_address_entry(data_table, *DC, binary_char);
		(*DC)++;
	}

	/* Encode struct*/
	else if (strcmp(data_type, ".struct") == 0)
	{
		/*int part*/
		comma_ptr = strchr(token, ',');
		parameter = calloc(10, 1);

		if (comma_ptr != NULL)
		{
			length = comma_ptr - token;
			strncpy(parameter, token, length);

		}
		else
		{
			strcpy(parameter, token);
		}

		num_paramater = atoi(parameter);

		if (parameter[0] == '-')
		{
			ndec_to_binary(num_paramater, binary_converted);
		}

		else
		{
			dec_to_binary(num_paramater, binary_converted);
		}

		
		for (i = 0; i < 10; i++)
		{
			binary_char[i] = '0' + binary_converted[i];
		}

		insert_address_entry(data_table, *DC, binary_char);
		(*DC)++;

		free(parameter);

		/*string part*/
		chars = strchr(token, '"') + 1;
		char_to_add[0] = '0';
		char_to_add[1] = '0';
		char_to_add[2] = '0';

		for (i = 0; i < strlen(chars); i++)
		{
			c = chars[i];

			/*Identify end of string*/
			if (c == '\"')
			{
				break;
			}

			ascii_val = (int)c;
			itoas(ascii_val, struct_char_binary, 2);
			/*Complete encoding*/
			for (i = 0; i < 7; i++)
			{
				char_to_add[i + 3] = struct_char_binary[i];
			}
			insert_address_entry(data_table, *DC, char_to_add);
			(*DC)++;
		}

		/*End of string is 0*/
		insert_address_entry(data_table, *DC, struct_binary_char);
		(*DC)++;
	}
}

/* convert n to characters in s, with minimum field width */
void itoas(int n, char s[], int width)
{
	int i, sign;
	if ((sign = n) < 0)
		/* record sign */
		n = -1 * n;  /* make n positive */
	i = 0;
	do
	{     /* generate digits in reverse order */
		s[i++] = n % 10 + '0';  /* get next digit */
		printf("%d %% %d + '0' = %d\n", n, 10, s[i - 1]);
	} while ((n /= 10) > 0); /* delete it */

	if (sign < 0)
	{
		s[i++] = '-';
	}

	while (i < width)
	{
		/*  addition to original function  */
		s[i++] = ' ';
	}

	s[i] = '\0';

	reverse(s);
}

char* strdups(char* str)
{
	char* result = calloc(strlen(str) + 1, 1);
	strcpy(result, str);
	return result;
}

/* reverse characters in s */
void reverse(char s[])
{
	int c, i, j;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}