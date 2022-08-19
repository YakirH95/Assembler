#pragma once

#include <stdio.h>
#include <string.h>
#include "dictionary.h"
#include "pre_proccessor.h"
#include "symbol_table.h"
#include "address_table.h"

symbol_table* identify_symbols(char* assembly_input, dictionary* operation_dict, address_entries* data_table, address_entries* code_table, dictionary* register_dict, dictionary* entry_external_dict, dictionary* external_symbols_address);
void extract_parameters(char* current_line, char* data_type, int* DC, address_entries* data_table);