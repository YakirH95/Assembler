#include <stdio.h>
#include <string.h>
#include "pre_proccessor.h"
#include <stdlib.h>
#include "operations_table.h"
#include "first_process.h"
#include "address_table.h"
#include "registers.h"
#include "second_process.h"
#include "base32.h"


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Bad parameter");
		return 1;
	}

	dictionary* operation_dict = create_operations_dict();
	address_entries* data_table = initialize_address_table();
	address_entries* code_table = initialize_address_table();
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
	buffer = calloc(length + 1, 1);
	//Read file to buffer
	fread(buffer, 1, length, expanded_output);
	fclose(expanded_output);

	char* second_buffer = strdup(buffer);
	symbol_table* sym_table = identify_symbols(buffer, operation_dict, data_table, code_table, registers_dict);
	fill_address_table(sym_table, code_table, data_table, second_buffer, operation_dict, registers_dict);

	delete_registers_dict(registers_dict);
	delete_operations_dict(operation_dict);
	free(buffer);
	free(second_buffer);
	delete_address_table(code_table);
	delete_address_table(data_table);
	delete_table(sym_table);
	return 0;
}