#include <stdio.h>
#include "dictionary.h"

/*Const dictioany for registers*/
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

	return registers_table;
}

/*Destructor*/
void delete_registers_dict(dictionary* dict)
{
	delete_dictionary(dict);
}

/*Search register, return its index*/
int is_register(dictionary* registers_table, char* operand)
{
	int key_index = key_exists(registers_table, operand);
	if (key_index != -1)
	{
		return key_index;
	}
	else
	{
		printf("Invalid register\n");
		return -1;
	}
}
