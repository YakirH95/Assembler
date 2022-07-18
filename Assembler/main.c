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
	FILE* file = fopen(argv[1], "rb");
	if (file == NULL)
	{
		printf("File not exist");
	}

	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);
	buffer = malloc(length);
	fread(buffer, 1, length, file);
	fclose(file);

	char* expanded_output = expand_macro(buffer);
	

	return 0;
}