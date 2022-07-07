#include "pre_proccessor.h"
#include <stdio.h>
#include <string.h>

char* expand_macro(char* assembly_input)
{
	char* current_line = NULL;
	current_line = strtok(assembly_input, "\r\n");
	while (current_line != NULL)
	{
		current_line = strtok(NULL, "\r\n");
	}
}