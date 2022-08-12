#include "base32.h"
#include <stdio.h>
#include <stdio.h>
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>

/*char base32_table[32] = {'!','@','#','$','%','^','&','*','<','>','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v'};
char* initialize_data_image()
{
	base32_table =  {'!','@','#','$','%','^','&','*','<','>','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v'};
	
	return base32_table;
}

void delete_data_image(base32_table* b32_t)
{
	free(b32_t->items);
	free(b32_t);
}

void add_entry(base32_table* b32_t, int decimal, char* base32)
{
	if (b32_t->used_size == b32_t->allocated_size)
	{
		b32_t->allocated_size += 5;
		b32_t->items = realloc(b32_t->items, b32_t->allocated_size * sizeof(entry));
	}

	b32_t->items[b32_t->used_size].decimal_value = decimal;
	strncpy(b32_t->items[b32_t->used_size].base32_value, base32, 1);
	b32_t->used_size++;
}
base32_table* create_base32_table()
{
	base32_table* base32_dict = create_dictionary();
	add_entry(base32_dict, 0, '!');
	add_entry(base32_dict, 1, '@');
	add_entry(base32_dict, 2, '#');
	add_entry(base32_dict, 3, '$');
	add_entry(base32_dict, 4, '%');
	add_entry(base32_dict, 5, '^');
	add_entry(base32_dict, 6, '&');
	add_entry(base32_dict, 7, '*');
	add_entry(base32_dict, 8, '<');
	add_entry(base32_dict, 9, '>');
	add_entry(base32_dict, 10, 'a');
	add_entry(base32_dict, 11, 'b');
	add_entry(base32_dict, 12, 'c');
	add_entry(base32_dict, 13, 'd');
	add_entry(base32_dict, 14, 'e');
	add_entry(base32_dict, 15, 'f');
	add_entry(base32_dict, 16, 'g');
	add_entry(base32_dict, 17, 'h');
	add_entry(base32_dict, 18, 'i');
	add_entry(base32_dict, 19, 'j');
	add_entry(base32_dict, 20, 'k');
	add_entry(base32_dict, 21, 'l');
	add_entry(base32_dict, 22, 'm');
	add_entry(base32_dict, 23, 'n');
	add_entry(base32_dict, 24, 'o');
	add_entry(base32_dict, 25, 'p');
	add_entry(base32_dict, 26, 'q');
	add_entry(base32_dict, 27, 'r');
	add_entry(base32_dict, 28, 's');
	add_entry(base32_dict, 29, 't');
	add_entry(base32_dict, 30, 'u');
	add_entry(base32_dict, 31, 'v');

	return base32_dict;
}
*/