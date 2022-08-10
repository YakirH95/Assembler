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
#include "address_analizer.h"
#include "registers.h"



void fill_address_table(image_entries* data_image, char* assembly_input)
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
		}
		
		else if (strstr(current_line, ".entry"))
		{

		}


		current_line = strtok(NULL, "\r\n");
	}
}