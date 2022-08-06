#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int* data_image;
	int used_size;
	int allocated_size;
}   data_entry;

typedef struct
{
	char* code_image;
	int used_size;
	int allocated_size;
}   code_entry;

data_entry* initialize_data_image();
code_entry* initialize_code_image();
void insert_data_image(data_entry* d_i, int value, int DC);
void insert_code_image(code_entry* d_i, char value, int IC);
