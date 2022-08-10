#pragma once

void dec_to_binary(int decimal_num, int* output);
void ndec_to_binary(int decimal_num, int* output);
char* analize_operands(dictionary* operation_table, char* operation_name, char* current_line, symbol_table* s_t, dictionary* registers_dict, int L);
char* get_first_operand(char* current_line, char* operation_name);
char* get_second_operand(char* current_line);



