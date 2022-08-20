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

/*Address and binary table*/
void create_object_file(address_entries* code_table, address_entries* data_table)
{
	FILE* file = fopen("Assembler.ob", "wt");

	for (int i = 0; i < code_table->used_size; i++)
	{
		char address_base32[3] = { 0 };
		char binary_base32[3] = { 0 };

		address_to_base32(code_table->entries[i].decimal_address, address_base32);
		binary_to_base32(code_table->entries[i].binary_code, binary_base32);

		fwrite(address_base32, 1, 2, file);
		fwrite("\t", 1, 1, file);
		fwrite(binary_base32, 1, 2, file);
		fwrite("\n", 1, 1, file);
	}

	for (int i = 0; i < data_table->used_size; i++)
	{
		char address_base32[3] = { 0 };
		char binary_base32[3] = { 0 };

		address_to_base32(data_table->entries[i].decimal_address, address_base32);
		binary_to_base32(data_table->entries[i].binary_code, binary_base32);

		fwrite(address_base32, 1, 2, file);
		fwrite("\t", 1, 1, file);
		fwrite(binary_base32, 1, 2, file);
		fwrite("\n", 1, 1, file);
	}

	fclose(file);
}

/*All entries*/
void create_entry_file(symbol_table* sym_table)
{
	FILE* file = fopen("Assembler.ent", "wt");

	for (int i = 0; i < sym_table->used_size; i++)
	{
		char address_base32[3] = { 0 };

		if (sym_table->items[i].symbol_type == 3)
		{
			address_to_base32(sym_table->items[i].symbol_address, address_base32);
			fwrite(sym_table->items[i].symbol_name, 1, strlen(sym_table->items[i].symbol_name), file);
			fwrite("\t", 1, 1, file);
			fwrite(address_base32, 1, 2, file);
			fwrite("\n", 1, 1, file);
		}
	}

	fclose(file);
}

/*All externals*/
void create_extern_file(symbol_table* extern_address)
{
	FILE* file = fopen("Assembler.ext", "wt");

	for (int i = 0; i < extern_address->used_size; i++)
	{
		char address_base32[3] = { 0 };
	
		
		address_to_base32(extern_address->items[i].symbol_address, address_base32);
		fwrite(extern_address->items[i].symbol_name, 1, strlen(extern_address->items[i].symbol_name), file);
		fwrite("\t", 1, 1, file);
		fwrite(address_base32, 1, 2, file);
		fwrite("\n", 1, 1, file);
		
	}

	fclose(file);
}


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Bad parameter");
		return 1;
	}

	/*Contain all operations and value*/
	dictionary* operation_dict = create_operations_dict();
	/*Contain all data entries and binary code*/
	address_entries* data_table = initialize_address_table();
	/*Contain all code entries and binary code*/
	address_entries* code_table = initialize_address_table();
	/*Contain all registers and binary code*/
	dictionary* registers_dict = create_registers_dict();
	/*Contain entry and extern symbols only, to be used later for main symbols table*/
	dictionary* entry_external_dict = create_dictionary();
	/*Contains external symbols only with their addresses on code table*/
	symbol_table* external_symbols_address = create_table();
	
	char* buffer = 0;
	int length;
	/*Open file given as paramater at argv[1]*/
	FILE* file = fopen(argv[1], "rb");
	if (file == NULL)
	{
		printf("File not exist");
	}
	
	/*Point to end of file*/
	fseek(file, 0, SEEK_END);
	/*Get file size*/
	length = ftell(file);
	/*Point to beggining of file*/
	fseek(file, 0, SEEK_SET);
	/*Allocate memory for file*/
	buffer = malloc(length + 1);
	/*Read file to buffer*/
	fread(buffer, 1, length, file);
	buffer[length] = 0;
	fclose(file);

	/*pre processor*/
	char* expanded_output_file_name = expand_macro(buffer);

	FILE* expanded_output = fopen(expanded_output_file_name, "rt");
	
	/*Point to end of file*/
	fseek(expanded_output, 0, SEEK_END);
	/*Get file size*/
	length = ftell(file);
	return;
	/*Point to beggining of file*/
	fseek(expanded_output, 0, SEEK_SET);
	/*Allocate memory for file*/
	buffer = calloc(length + 1, 1);
	/*Read file to buffer*/
	fread(buffer, 1, length, expanded_output);
	fclose(expanded_output);

	char* second_buffer = strdup(buffer);
	/*Firest process*/
	symbol_table* sym_table = identify_symbols(buffer, operation_dict, data_table, code_table, registers_dict, entry_external_dict, external_symbols_address);
	/*Second process*/
	fill_address_table(sym_table, code_table, data_table, second_buffer, operation_dict, registers_dict, entry_external_dict);

	/*Sort code and data table in the correct order*/
	sort_by_address(code_table);
	sort_by_address(data_table);

	create_object_file(code_table, data_table);

	int extern_counter = 0;
	int entry_counter = 0;
	for (int i = 0; i < entry_external_dict->used_size; i++)
	{
		if (strcmp(entry_external_dict->items[i].value, "1"))
		{
			extern_counter++;
		}
		else
		{
			entry_counter++;
		}
	}

	/*If there's entry*/
	if (entry_counter != 0)
	{
		create_entry_file(sym_table);

	}
	/*If theres external*/
	if (extern_counter != 0)
	{
		create_extern_file(external_symbols_address);

	}

	delete_registers_dict(registers_dict);
	delete_operations_dict(operation_dict);
	free(buffer);
	free(second_buffer);
	delete_address_table(code_table);
	delete_address_table(data_table);
	delete_table(sym_table);
	delete_dictionary(entry_external_dict);
	delete_table(external_symbols_address);
	return 0;
}