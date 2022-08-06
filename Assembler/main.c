#include <stdio.h>
#include <string.h>
#include "pre_proccessor.h"
#include <stdlib.h>
#include "operations_table.h"
#include "first_process.h"
#include "data_image.h"


int main(int argc, char* argv[])
{
	dictionary* operation_dict = create_operations_dict();
	data_entry* data_image = initialize_data_image();
	code_entry* code_image = initialize_code_image();
	
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

	//pre processor
	//Point to end of file
	fseek(file, 0, SEEK_END);
	//Get file size
	length = ftell(file);
	//Point to beggining of file
	fseek(file, 0, SEEK_SET);
	//Allocate memory for file
	buffer = malloc(length + 1);
	//Read file to buffer
	fread(buffer, 1, length, file);
	buffer[length] = 0;
	fclose(file);

	FILE* expanded_output = expand_macro(buffer);
	
	//first process
	FILE* file2 = fopen(expanded_output, "rb");
	//Point to end of file
	fseek(file2, 0, SEEK_END);
	//Get file size
	length = ftell(file);
	//Point to beggining of file
	fseek(file2, 0, SEEK_SET);
	//Allocate memory for file
	buffer = malloc(length + 1);
	//Read file to buffer
	fread(buffer, 1, length, file2);
	buffer[length] = 0;
	fclose(file2);
	symbol_table* sym_table = identify_symbols(buffer, operation_dict, data_image, code_image);
	
	
	delete_operations_dict(operation_dict);
	return 0;
}