#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "address_analizer.h"
#include "operations_table.h"
#include "symbol_table.h"
#include "address_table.h"
#include "dictionary.h"
#include "registers.h"

char* analize_operands(dictionary* operation_table, address_entries* a_e, char* operation_name, char* current_line, 
    symbol_table* s_t,dictionary* registers_dict, int L, int IC)
{
    char binary_num[10] = { 0 };
	char* first_operand = NULL;
	char* second_operand = NULL;
    int first_is_register = 0;
    //5 4 bits
    first_operand = get_first_operand(current_line, operation_name);

    char* comma_ptr = strchr(first_operand, ',');
    int length = comma_ptr - first_operand;
    char* parameter = calloc(length + 1, 1);
    //3 2 bits
    second_operand = get_second_operand(current_line);

    char* value = get_value(operation_table, operation_name);

    //9 8 7 6 bits
    strncpy(binary_num, value, 4);
    
    
    
    //its number
    if (strchr(first_operand, '#'))
    {
        //Encode first row of command
        L++;
        binary_num[4] = '0';
        binary_num[5] = '0';


        //Encode given number in next row
        int output = {0};
        if (strstr(first_operand, "-"))
        {
            int* num_ptr = (int*)first_operand + 2;
            ndec_to_binary(num_ptr, output);
            output = output << 2; // CHECK
        }

        else
        {
            int* num_ptr = (int*)first_operand + 1;
            dec_to_binary(num_ptr, output);
        }
        char binary_char[10] = { 0 };
        sprintf(binary_char, "%d", output);
        insert_address_entry(a_e, IC + 1, output);
    }

    //Its symbol
    else if (symbol_exists(s_t, first_operand) != -1)
    {
        if (second_operand == NULL)
        {
            binary_num[4] = '0';
            binary_num[5] = '0';
            binary_num[6] = '1';
            binary_num[7] = '0';
        }
        else
        {
            binary_num[4] = '0';
            binary_num[5] = '1';
        }
        L++;
    }
    
    //It's struct
    else if (strchr(first_operand, '.'))
    {
        //Encode struct's field
        char* dot_ptr = strchr(first_operand, '.');
        char* struct_field = dot_ptr + 1;
        if (strcmp( struct_field, "1"))
        {
            insert_address_entry(a_e, IC + 2, "0000000100");
        }
        else
        {
            insert_address_entry(a_e, IC + 2, "0000001000");
        }
        L += 2;

        //Encode first row
        binary_num[4] = '1';
        binary_num[5] = '0';
    }

    //It's register
    else if (is_register(registers_dict, first_operand) != -1)
    {
        //Encode first row of command
        first_is_register = 1;
        L++;
        value = get_value(registers_dict, first_operand);
        strncpy(binary_num, value, 4);

        //Encode register number in next row
        int register_num = is_register(registers_dict, first_operand);
        char* register_binary = NULL;
        //Get binary code of certain register and add 0's
        strncpy(register_binary, registers_dict->items[register_num].value, 4);
        strcat(register_binary, "000000");
        insert_address_entry(a_e, IC + 1, register_binary);
    
    }

   
    
    if (second_operand != NULL)
    {
        //It's number
        if (strchr(second_operand, '#'))
        {
            L++;
            binary_num[6] = '0';
            binary_num[7] = '0';

            //Encode given number in next row
            int output = { 0 };
            if (strstr(second_operand, "-"))
            {
                int* num_ptr = (int*)second_operand + 2;
                ndec_to_binary(num_ptr, output);
                output = output << 2; // CHECK
            }

            else
            {
                int* num_ptr = (int*)first_operand + 1;
                dec_to_binary(num_ptr, output);
            }
            char binary_char[10] = { 0 };
            sprintf(binary_char, "%d", output);
            insert_address_entry(a_e, IC + 1, output);
        }

        //It's symbol
        else if (symbol_exists(s_t, first_operand) != -1)
        {
            L++;
            binary_num[6] = '0';
            binary_num[7] = '1';
        }

        //It's struct
        else if (strchr(first_operand, '.'))
        {
            L += 2;
            binary_num[6] = '1';
            binary_num[7] = '0';

            //Encode struct's field
            char* dot_ptr = strchr(first_operand, '.');
            char* struct_field = dot_ptr + 1;
            if (strcmp(struct_field, "1"))
            {
                insert_address_entry(a_e, IC + 2, "0000000100");
            }
            else
            {
                insert_address_entry(a_e, IC + 2, "0000001000");
            }
        }

        //It's register
        else if (is_register(registers_dict, second_operand) == 1)
        {
            if (first_is_register == 0)
            {
                L++;
            }

            value = get_value(registers_dict, second_operand);
            strncpy(binary_num[4], value, 4);

            //Encode register number in next row
            int register_num = is_register(registers_dict, first_operand);
            char* register_binary = NULL;
            //Get binary code of certain register and add 0's
            strncpy(register_binary, registers_dict->items[register_num].value, 4);
            strcat(register_binary, "000000");
            insert_address_entry(a_e, IC + 1, register_binary);
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