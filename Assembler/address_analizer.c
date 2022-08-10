#include "address_analizer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operations_table.h"
#include "symbol_table.h"
#include "data_image.h"
#include "dictionary.h"
#include "registers.h"

char* analize_operands(dictionary* operation_table, char* operation_name, char* current_line, symbol_table* s_t,dictionary* registers_dict, int L)
{
    char binary_num[10] = { 0 };
	char* first_operand = NULL;
	char* second_operand = NULL;
    int first_is_register = 0;

    char* value = get_value(operation_table, operation_name);

    //First 4 bits
    strncpy(binary_num, value, 4);
    

    first_operand = get_first_operand(current_line, operation_name);
    char* dot_address = strchr(first_operand, '.');
    
    if (strchr(first_operand, '#'))
    {
        L++;
        binary_num[4] = '0';
        binary_num[5] = '0';
    }

    else if (symbol_exists(s_t, first_operand) == 1)
    {
        L++;
        binary_num[4] = '0';
        binary_num[5] = '1';
    }
    else if (strchr(first_operand, '.'))
    {
        L += 2;
        binary_num[4] = '1';
        binary_num[5] = '0';
    }

    else if (is_register(registers_dict, first_operand) == 1)
    {
        first_is_register = 1;
        L++;
        value = get_value(registers_dict, first_operand);
        strncpy(binary_num, value, 4);
    }

    char* comma_ptr = strchr(first_operand , ',');
    int length = comma_ptr - first_operand;
    char* parameter = calloc(length + 1, 1);
    second_operand = get_second_operand(current_line);
    
    if (second_operand != NULL)
    {
        if (strchr(second_operand, '#'))
        {
            L++;
            binary_num[6] = '0';
            binary_num[7] = '0';
        }

        else if (symbol_exists(s_t, first_operand) == 1)
        {
            L++;
            binary_num[6] = '0';
            binary_num[7] = '1';
        }
        else if (strchr(first_operand, '.'))
        {
            L += 2;
            binary_num[6] = '1';
            binary_num[7] = '0';
        }

        else if (is_register(registers_dict, second_operand) == 1)
        {
            if (first_is_register == 0)
            {
                L++;
            }

            value = get_value(registers_dict, second_operand);
            strncpy(binary_num[4], value, 4);
        }

        binary_num[8] = '0';
        binary_num[9] = '0';
    }

    return binary_num;
}

void dec_to_binary(int decimal_num, int* output)
{
	for (int i = 9; decimal_num > 0; i--)
	{
		output[i] = decimal_num % 2;
		decimal_num = decimal_num / 2;
	}
}

void ndec_to_binary(int decimal_num, int* output)
{
    int i = 0;
    unsigned int u_i = 0;
    int j = 0;
    int b[10] = { 0 }; 

    i = decimal_num;

    u_i = (unsigned int)i;

    for (j = 9; j >= 0; j--) {
        output[j] = u_i & 0x1;
        u_i = u_i >> 1;
    }
}

char* get_first_operand(char* current_line, char* operation_name)
{
   char* start_from_first_operand = strstr(current_line, operation_name) + strlen(operation_name);
   char* comma_ptr = strchr(start_from_first_operand, ',');
   int length = comma_ptr - start_from_first_operand;
   char* first_operand = NULL;

   strncpy(first_operand, start_from_first_operand, length);
   return first_operand;
}

char* get_second_operand(char* current_line)
{
    char* coma_ptr = strchr(current_line, ',') + 1;
    int length = strlen(coma_ptr);
    char* second_operand = NULL;
    strncpy(second_operand, coma_ptr, length);
    return second_operand;
}