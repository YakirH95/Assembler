#include <stdio.h>
#include <string.h>
#include "pre_proccessor.h"
#include <stdlib.h>


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Bad parameter");
		return 1;
	}

	char* buffer = 0;
	int length;
	//Open file given as paramater at argv[1]
	FILE* file = fopen(argv[1], "rb");
	if (file == NULL)
	{
		printf("File not exist");
	}

	//Point to end of file
	fseek(file, 0, SEEK_END);
	//Get file size
	length = ftell(file);
	//Point to beggining of file
	fseek(file, 0, SEEK_SET);
	//Allocate memory for file
	buffer = malloc(length);
	//Read file to buffer
	fread(buffer, 1, length, file);
	fclose(file);

	char* expanded_output = expand_macro(buffer);
	
	return 0;
}