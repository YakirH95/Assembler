#pragma once
#include "symbol_table.h"
#include "address_table.h"

void fill_address_table(symbol_table* symbol_table, address_entries* code_table, address_entries* data_table, 
	                    char* assembly_input, dictionary* operation_table);
