#pragma once
#include "dictionary.h"
#include "symbol_table.h"
#include "address_table.h"


void dec_to_binary(int decimal_num, int* output);
void ndec_to_binary(int decimal_num, int* output);
char* analize_operands(dictionary* operation_table, address_entries* a_e, char* operation_name, char* current_line,
	                   symbol_table* s_t, dictionary* registers_dict, int* L, int IC, char* binary_num, dictionary* entry_extern_dict, symbol_table* external_symbols_address);
void analize_remaining_address(address_entries* a_e, char* current_line, symbol_table* s_t, int* L, int IC, dictionary* operation_table,
	dictionary* registers_dict);

char* get_first_operand(char* current_line, char* operation_name);
char* get_second_operand(char* current_line);



