#pragma once
#include "dictionary.h"
#include "first_process.h"
#include "pre_proccessor.h"
#include <stdio.h>
#include <string.h>
#include "symbol_table.h"
#include "operations_table.h"

symbol_table* identify_symbols(char* assembly_input);
void define_extern_symbol(symbol_table* symbol_table, char* current_line);
void define_symbol(symbol_table* symbol_table, char* symbol_name, char* current_line, int IC_DC);
int is_operation(dictionary* operation_table, char* current_line);
