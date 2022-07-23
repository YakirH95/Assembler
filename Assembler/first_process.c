#include "dictionary.h"
#include "first_process.h"
#include "pre_proccessor.h"
#include <stdio.h>
#include <string.h>



dictionary* identify_labels(char* assembly_input)
{
	int IC = 0;
	int DC = 0;
	int is_label_define = 0;
	dictionary* labels_dict = create_dictionary();

	char* current_line = NULL;

	//Next line
	current_line = strtok(assembly_input, "\r\n");

	while (current_line != NULL)
	{
		if (strstr(current_line, ":") != NULL)
		{
			is_label_define = 1;
			
		}

		if (strstr(current_line, ".data") != NULL)
		{

		}

		else if (strstr(current_line, ".string") != NULL)
		{

		}

		else if (strstr(current_line, ".struct") != NULL)
		{

		}

		else if (strstr(current_line, ".extern") != NULL)
		{

		}

		else if (strstr(current_line, ".entry") != NULL)
		{

		}

		//None of the above
		else
		{
			define_label(labels_dict, current_line, IC);
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
