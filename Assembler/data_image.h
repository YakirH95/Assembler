#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Line 
typedef struct
{
	int decimal_address;
	char binary_code[10];
}   data_image;

//All gruops
typedef struct
{
	data_image* entries;
	int used_size;
	int allocated_size;
}   image_entries;

image_entries* initialize_data_image();
void insert_data_image(image_entries* i_e, int decimal_address, char* binary_num);
