#include "data_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


data_entry* initialize_data_image()
{
	data_entry* d_i = malloc(sizeof(data_entry));
	d_i->data_image = (int*)malloc(sizeof(int)*10);
	d_i->used_size = 0;
	d_i->allocated_size = 5;
	return d_i;
}

code_entry* initialize_code_image()
{
	code_entry* d_i = malloc(sizeof(code_entry));
	d_i->code_image = (int*)malloc(sizeof(int) * 10);
	d_i->used_size = 0;
	d_i->allocated_size = 5;
	return d_i;
}

void insert_data_image(code_entry* d_i, int value, int DC) 
{
	if (d_i->used_size == d_i->allocated_size)
	{
		d_i->allocated_size += 5;
		d_i->code_image = realloc(d_i->code_image, d_i->allocated_size);
	}

	
	*(d_i->code_image + DC) = value;
}



void insert_code_image(data_entry* d_i, char value, int IC)
{
	if (d_i->used_size == d_i->allocated_size)
	{
		d_i->allocated_size += 5;
		d_i->data_image = realloc(d_i->data_image, d_i->allocated_size);
	}


	*(d_i->data_image + IC) = value;
}