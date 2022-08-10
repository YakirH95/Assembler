#pragma once

dictionary* create_registers_dict();
void delete_registers_dict(dictionary* dict);
int is_register(dictionary* registers_table, char* operand);

