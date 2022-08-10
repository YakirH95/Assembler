#include "dictionary.h"

dictionary* create_registers_dict()
{
	dictionary* registers_table = create_dictionary();
	add_entry(registers_table, "r0", "0000");
	add_entry(registers_table, "r1", "0001");
	add_entry(registers_table, "r2", "0010");
	add_entry(registers_table, "r3", "0011");
	add_entry(registers_table, "r4", "0100");
	add_entry(registers_table, "r5", "0101");
	add_entry(registers_table, "r6", "0110");
	add_entry(registers_table, "r7", "0111");
	add_entry(registers_table, "r8", "1000");

	return registers_table;
}

void delete_operations_dict(dictionary* dict)
{
	delete_dictionary(dict);
}


int is_register(dictionary* registers_table, char* operand)
{
	for (int i = 0; i < registers_table->used_size; i++)
	{
		if (strcmp(registers_table->items[i].key, operand) == 0)
		{
			return 1;
		}
	}

	return 0;
}

