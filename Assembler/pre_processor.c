#include "pre_proccessor.h"
#include <stdio.h>
#include <string.h>
#include "dictionary.h"
#include "dynamic_string.h"

const char* search_word = "macro ";
const char* exit_word = "endmacro";

char* expand_macro(char* assembly_input)
{
	dictionary* macro_dict = create_dictionary();

	char* current_line = NULL;

	char* key = NULL;
	dynamic_string* macro_body = create_dynamic_string();
	dynamic_string* output = create_dynamic_string();
	int is_in_macro = 0;

	//Next line
	current_line = strtok(assembly_input, "\r\n");
	
	//Write new string compared to original
	while (current_line != NULL)
	{
		//Add entry 
		if (strstr(current_line, "endmacro") != NULL)
		{
			is_in_macro = 0;
			add_entry(macro_dict, key, get_internal_string(macro_body));
			delete_dynamic_string(macro_body);
		}
		else if (is_in_macro == 1)
		{
			add_string(macro_body, current_line);
			add_string(macro_body, "\n");
		}

		//Add value of key to the output
		else if (key_exists(macro_dict, current_line))
		{
			add_string(output, get_value(macro_dict, current_line));
			add_string(output, "\n");
		}

		//Identify macro name and add to dictionary
		else if (strstr(current_line, "macro") != NULL)
		{
			is_in_macro = 1;
			key = strstr(current_line, " ") + 1;
		}

		else
		{
			add_string(output, current_line);
			add_string(output, "\n");
		}
		
		current_line = strtok(NULL, "\r\n");
	}

	delete_dictionary(macro_dict);

	return get_internal_string(output);
}