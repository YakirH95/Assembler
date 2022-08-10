#include <stdio.h>
#include <string.h>
#include "dictionary.h"

dictionary* create_operations_dict()
{
	dictionary* operations_table = create_dictionary();
	add_entry(operations_table, "mov", "0000");
	add_entry(operations_table, "cmp", "0001");
	add_entry(operations_table, "add", "0010");
	add_entry(operations_table, "sub", "0011");
	add_entry(operations_table, "not", "0100");
	add_entry(operations_table, "clr", "0101");
	add_entry(operations_table, "lea", "0110");
	add_entry(operations_table, "inc", "0111");
	add_entry(operations_table, "dec", "1000");
	add_entry(operations_table, "jmp", "1001");
	add_entry(operations_table, "bne", "1010");
	add_entry(operations_table, "get", "1011");
	add_entry(operations_table, "prn", "1100");
	add_entry(operations_table, "jsr", "1101");
	add_entry(operations_table, "rts", "1110");
	add_entry(operations_table, "hlt", "1111");

	return operations_table;
}

void delete_operations_dict(dictionary* dict)
{
	delete_dictionary(dict);
}


int is_operation(dictionary* operation_table, char* current_line)
{
	for (int i = 0; i < operation_table->used_size; i++)
	{
		if (strstr(current_line, get_key(operation_table, i)) != NULL)
		{
			return i;
		}
	}

	// if operation not found, return -1
	return -1;
}



