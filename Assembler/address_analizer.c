#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "address_analizer.h"
#include "operations_table.h"
#include "symbol_table.h"
#include "address_table.h"
#include "dictionary.h"
#include "registers.h"

/*Encode row of operation, also encode numbers, struct fields, and registers
Using insert_address function with NULL value where need to be filled in second process*/
char* analize_operands(dictionary* operation_table, address_entries* a_e, char* operation_name, char* current_line, 
    symbol_table* s_t, dictionary* registers_dict, int* L, int IC, char* binary_num)
{
	char* first_operand = NULL;
	char* second_operand = NULL;
    char* second_operand_without_spaces = NULL;
    int first_is_register = 0;
    int first_register = -1;
    /*5 4 bits*/
    first_operand = get_first_operand(current_line, operation_name);

    char* comma_ptr = strchr(first_operand, ',');
    int length = comma_ptr - first_operand;
    /*3 2 bits*/
    second_operand = get_second_operand(current_line);

    char* value = get_value(operation_table, operation_name);

    strncpy(binary_num, "0000000000", 10);

    /*9 8 7 6 bits*/
    strncpy(binary_num, value, 4);
    
    /*its number*/
    if (strchr(first_operand, '#'))
    {
        /*Encode first row of command*/
        (*L)++;
        binary_num[4] = '0';
        binary_num[5] = '0';


        /*Encode given number in next row*/
        int output[10] = {0};
        char* num_ptr = first_operand + 1;
        int num = atoi(num_ptr);

        if (num >= 0)
        {
            dec_to_binary(num, output);
        }
        else
        {
            ndec_to_binary(num, output);
        }

        for (int i = 0; i < 8; i++)
        {
            output[i] = output[i + 2];
        }

        output[8] = 0;
        output[9] = 0;

        char binary_char[10] = { 0 };
        for (int i = 0; i < 10; i++)
        {
            binary_char[i] = '0' + output[i];
        }

        insert_address_entry(a_e, IC + 1, binary_char);
    }

    /*Its symbol*/
    else if (symbol_exists(s_t, first_operand) != -1)
    {
        if (second_operand == NULL)
        {
            binary_num[4] = '0';
            binary_num[5] = '0';
            binary_num[6] = '0';
            binary_num[7] = '1';
        }
        else
        {
            binary_num[4] = '0';
            binary_num[5] = '1';
        }
        (* L)++;
        insert_address_entry(a_e, IC + (*L), "?");
    }
    
    /*It's struct*/
    else if (strchr(first_operand, '.'))
    {
        /*Create empty field for structs address, to be filled later*/
        insert_address_entry(a_e, IC + 1, "?");

        /*Encode struct's field*/
        char* dot_ptr = strchr(first_operand, '.');
        char* struct_field = dot_ptr + 1;
        if (strstr( struct_field, "1") != NULL)
        {
            insert_address_entry(a_e, IC + 2, "0000000100");
        }
        else
        {
            insert_address_entry(a_e, IC + 2, "0000001000");
        }
        (* L) += 2;

        /*Encode first row*/
        binary_num[4] = '1';
        binary_num[5] = '0';
    }

    /*It's register*/
    else if (is_register(registers_dict, first_operand) != -1)
    {
        /*Encode first row of command*/
        first_is_register = 1;
        (* L)++;
        binary_num[4] = '1';
        binary_num[5] = '1';

        /*Encode register number in next row*/
        int register_num = is_register(registers_dict, first_operand);
        char* register_binary = calloc(10, 1);
        first_register = register_num;

        /*Get binary code of certain register and add 0's*/
        strncpy(register_binary, registers_dict->items[register_num].value, 4);
        for (int i = 4; i < 10; i++)
        {
            register_binary[i] = "0";
        }

        insert_address_entry(a_e, IC + 1, register_binary);
        free(register_binary);
    }
    else
    {
        (*L)++;
        insert_address_entry(a_e, IC + *L, "?");
        binary_num[6] = '0';
        binary_num[7] = '1';
    }

    if (second_operand != NULL)
    {
        second_operand_without_spaces = second_operand;
        while (*second_operand_without_spaces == ' ')
        {
            second_operand_without_spaces++;
        }

        /*It's number*/
        if (strchr(second_operand_without_spaces, '#'))
        {
            (* L)++;
            binary_num[6] = '0';
            binary_num[7] = '0';

            /*Encode given number in next row*/
            int output = { 0 };
            if (strstr(second_operand_without_spaces, "-"))
            {
                int* num_ptr = (int*)second_operand_without_spaces + 2;
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

        /*It's known symbol*/
        else if (symbol_exists(s_t, second_operand_without_spaces) != -1)
        {
            (* L)++;
            binary_num[6] = '0';
            binary_num[7] = '1';

            insert_address_entry(a_e, IC + (* L), "?");
        }

        /*It's struct*/
        else if (strchr(second_operand_without_spaces, '.'))
        {
            (* L) += 2;
            binary_num[6] = '1';
            binary_num[7] = '0';

            /*Encode struct's field*/
            char* dot_ptr = strchr(second_operand_without_spaces, '.');
            char* struct_field = dot_ptr + 1;
            if (strcmp(struct_field, "1"))
            {
                insert_address_entry(a_e, IC + (*L), "0000000100");
            }
            else
            {
                insert_address_entry(a_e, IC + (*L), "0000001000");
            }

            /*To be filled in second process*/
            insert_address_entry(a_e, IC + (*L) -1, "?");
        }

        /*It's register*/
        else if (is_register(registers_dict, second_operand_without_spaces) != -1)
        {
            int second_register_num = is_register(registers_dict, second_operand_without_spaces);
            char* second_register_binary = calloc(11, 1);

            if (first_is_register == 0)
            {
                (* L)++;

                /*Get binary code of certain register and add 0's*/
                strncpy(second_register_binary, "0000", 4);
                strcat(second_register_binary, registers_dict->items[second_register_num].value);
                strcat(second_register_binary, "00");

                insert_address_entry(a_e, IC + *L, second_register_binary);
            }

            else
            {
                strncpy(second_register_binary, registers_dict->items[first_register].value, 4);
                strcat(second_register_binary, registers_dict->items[second_register_num].value);
                strcat(second_register_binary, "00");

                set_address_binary_num(a_e, IC + 1, second_register_binary);
            }
            free(second_register_binary);

            binary_num[6] = '1';
            binary_num[7] = '1';
        }
        else
        {
            (*L)++;
            insert_address_entry(a_e, IC + *L, "?");
            binary_num[6] = '0';
            binary_num[7] = '1';

        }

        binary_num[8] = '0';
        binary_num[9] = '0';
    }

    free(first_operand);
    free(second_operand);

    return binary_num;
}

void analize_remaining_address(address_entries* a_e, char* current_line, symbol_table* s_t,
                               int* L, int IC, dictionary* operation_table, dictionary* registers_dict)
{
    char* first_operand = NULL;
    char* second_operand = NULL;
    int first_is_register = 0;
    int operation_index = is_operation(operation_table, current_line);
    char* operation_name = get_key(operation_table, operation_index);
   
    first_operand = get_first_operand(current_line, operation_name);
    second_operand = get_second_operand(current_line);

    /*Its symbol*/
    if (symbol_exists(s_t, first_operand) != -1)
    {
        (*L)++;
        int symbol_value = get_symbol_address(s_t, first_operand);
        int binary_num[10] = { 0 };
        dec_to_binary(symbol_value, binary_num);
        for (int i = 0; i < 8; i++)
        {
            binary_num[i] = binary_num[i + 2];
        }
        binary_num[8] = 1;
        binary_num[9] = 0;

        char char_output[10] = {0};
        for (int i = 0; i < 10; i++)
        {
            char_output[i] = '0' + binary_num[i];
        }

        set_address_binary_num(a_e, IC + *L, char_output);
    }

    /*It's struct*/
    else if (strchr(first_operand, '.'))
    {
        (*L) += 2;
        char* dot_pointer = strchr(first_operand, '.');
        int length = dot_pointer - first_operand;
        int symbol_address = get_symbol_address(s_t, first_operand);
        int binary_num[10] = {0};
        char char_to_add[10] = {0};

        dec_to_binary(symbol_address, binary_num);

        for (int i = 0; i < 8; i++)
        {
            binary_num[i] = binary_num[i + 2];
        }
        binary_num[8] = 1;
        binary_num[9] = 0;
        
        for (int i = 0; i < 10; i++)
        {
            char_to_add[i] = '0' + binary_num[i];
        }
       
        set_address_binary_num(a_e, IC + *L - 1, char_to_add);
    }
    else if (is_register(registers_dict, first_operand))
    {
        (*L)++;
        first_is_register = 1;
    }
    
    if (second_operand != NULL)
    {
        /*It's symbol*/
        if (symbol_exists(s_t, second_operand) != -1)
        {
            (*L)++;
            int symbol_value = get_symbol_address(s_t, second_operand);

            int binary_num[10] = { 0 };
            char char_to_add[10] = { 0 };

            dec_to_binary(symbol_value, binary_num);

            for (int i = 0; i < 8; i++)
            {
                binary_num[i] = binary_num[i + 2];
            }
            binary_num[8] = 1;
            binary_num[9] = 0;

            for (int i = 0; i < 10; i++)
            {
                char_to_add[i] = '0' + binary_num[i];
            }
            
            set_address_binary_num(a_e, IC + *L, char_to_add);
        }

        /*It's struct*/
        else if (strchr(second_operand, '.'))
        {
            (*L) += 2;
            int symbol_value = get_value(s_t, first_operand);
            int binary_num[10] = { 0 };

            dec_to_binary(symbol_value, binary_num);
            for (int i = 0; i < 8; i++)
            {
                binary_num[i] = binary_num[i + 2];
            }
            binary_num[8] = 1;
            binary_num[9] = 0;

            char char_output[10] = { 0 };
            for (int i = 0; i < 10; i++)
            {
                char_output[i] = '0' + binary_num[i];
            }

            set_address_binary_num(a_e, IC + *L - 1, char_output);
        }
        else if (is_register(registers_dict, second_operand))
        {
            if (first_is_register == 0)
            {
                (*L)++;
            }
        }
    }
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
   while (*start_from_first_operand == ' ')
   {
       start_from_first_operand++;
   }

   char* comma_ptr = strchr(start_from_first_operand, ',');
   if (comma_ptr != NULL)
   {
       int length = comma_ptr - start_from_first_operand;
       char* first_operand = calloc(length + 1, 1);

       strncpy(first_operand, start_from_first_operand, length);
       return first_operand;
   }
   else
   {
       return strdup(start_from_first_operand);
   }
}

char* get_second_operand(char* current_line)
{
    char* coma_ptr = strchr(current_line, ',');
    if (coma_ptr != NULL)
    {
        coma_ptr++;
        int length = strlen(coma_ptr);
        char* second_operand = calloc(length + 1, 1);
        strncpy(second_operand, coma_ptr, length);
        
        return second_operand;
    }
    else
    {
        return NULL;
    }
}

void int_to_char(int num_int, char* num_char)
{

}