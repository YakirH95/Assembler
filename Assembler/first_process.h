#pragma once
#include "dictionary.h"
#include "first_process.h"
#include "pre_proccessor.h"
#include <stdio.h>
#include <string.h>
#include "symbol_table.h"
#include "operations_table.h"
#include "data_image.h"

symbol_table* identify_symbols(char* assembly_input, dictionary* operation_dict, data_entry* data_image, code_entry* code_image);
void extract_parameters(char* current_line, char* data_type, int DC, data_entry* data_entry);

