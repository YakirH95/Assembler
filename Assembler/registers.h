#pragma once

dictionary* create_registers_dict();
void delete_operations_dict(dictionary* dict);
int is_register(dictionary* registers_table, char* operand);

