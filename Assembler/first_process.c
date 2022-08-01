#include "dictionary.h"
#include "first_process.h"
#include "pre_proccessor.h"
#include <stdio.h>
#include <string.h>
#include "operations_table.h"


dictionary* identify_labels(char* assembly_input)
{
	int IC = 0;
	int DC = 0;
	int is_symbol_define = 0;
	dictionary* data_symbols_dict = create_dictionary();
	dictionary* instructions_symbols_dict = create_dictionary();
	dictionary* operation_dict = create_operations_dict();

	char* current_line = NULL;

	//Next line
	current_line = strtok(assembly_input, "\r\n");

	while (current_line != NULL)
	{
		if (strstr(current_line, ":") != NULL)
		{
			is_symbol_define = 1;
		}

	

	}
}

void define_label(dictionary* label_dict, char* current_line, int IC)
{
	char* label_name;
	label_name = strtok(current_line, ":");
	if (key_exists(label_dict, label_name))
	{
		printf("label already exist");
		return;
	}

	char* IC_str = NULL;
	sprintf(IC_str, "%d", IC);
	
	add_entry(label_dict, label_name, IC_str);

	
}

int search_operation(dictionary* operation_table, char* current_line)
{
	for (int i = 0; i < operation_table->used_size; i++)
	{
		if (strstr(current_line, get_key(operation_table, i)))
		{
			return 1;
		}
		return 0;
	}
}
