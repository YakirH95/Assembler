#include <stdio.h>
#include <string.h>
#include "pre_proccessor.h"
#include <stdlib.h>
#include "operations_table.h"
#include "first_process.h"
#include "data_image.h"
#include "registers.h"


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Bad parameter");
		return 1;
	}

	dictionary* operation_dict = create_operations_dict();
	image_entries* address_table = initialize_data_image();
	dictionary* registers_dict = create_registers_dict();
	
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

	char* expanded_output_file_name = expand_macro(buffer);

	FILE* expanded_output = fopen(expanded_output_file_name, "rt");
	
	//Point to end of file
	fseek(expanded_output, 0, SEEK_END);
	//Get file size
	length = ftell(file);
	//Point to beggining of file
	fseek(expanded_output, 0, SEEK_SET);
	//Allocate memory for file
	buffer = malloc(length + 1);
	//Read file to buffer
	fread(buffer, 1, length, expanded_output);
	buffer[length] = 0;
	fclose(expanded_output);
	symbol_table* sym_table = identify_symbols(buffer, operation_dict, address_table, registers_dict);

	//Return pointer to beggining of file

	
	delete_registers_dict(registers_dict);
	delete_operations_dict(operation_dict);
	return 0;
}