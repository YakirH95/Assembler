#pragma once

typedef struct
{
	char* string;
	int allocated_size;
}   dynamic_string;

dynamic_string* create_dynamic_string();
void delete_dynamic_string(dynamic_string* d);
void add_string(dynamic_string* d_s, char* string);
char* get_internal_string(dynamic_string* d_s);

