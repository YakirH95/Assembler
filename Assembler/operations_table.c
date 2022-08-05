#include <stdio.h>
#include <string.h>
#include "dictionary.h"

dictionary* create_operations_dict()
{
	dictionary* operations_table = create_dictionary();
	add_entry(operations_table, "mov", "0");
	add_entry(operations_table, "cmp", "1");
	add_entry(operations_table, "add", "2");
	add_entry(operations_table, "sub", "3");
	add_entry(operations_table, "not", "4");
	add_entry(operations_table, "clr", "5");
	add_entry(operations_table, "lea", "6");
	add_entry(operations_table, "inc", "7");
	add_entry(operations_table, "dec", "8");
	add_entry(operations_table, "jmp", "9");
	add_entry(operations_table, "bne", "10");
	add_entry(operations_table, "get", "11");
	add_entry(operations_table, "prn", "12");
	add_entry(operations_table, "jsr", "13");
	add_entry(operations_table, "rts", "14");
	add_entry(operations_table, "hlt", "15");

	return operations_table;
}

dictionary* delete_operations_dict(dictionary* dict)
{
	delete_dictionary(dict);
}


int is_operation(dictionary* operation_table, char* current_line)
{
	for (int i = 0; i < operation_table->used_size; i++)
	{
		if (strstr(current_line, get_key(operation_table, i)) != NULL)
		{
			return 1;
		}
	}

	return 0;
}

