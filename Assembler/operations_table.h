#pragma once
#include "dictionary.h"

dictionary* create_operations_dict();
int is_operation(dictionary* operation_table, char* current_line);
void delete_operations_dict(dictionary* dict);
