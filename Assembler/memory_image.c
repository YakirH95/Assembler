#include <stdio.h>
#include <string.h>
#include "memory_image.h"

cell memory_arr[256] = { 0 };

cell get_cell(int cell_num)
{
	return memory_arr[cell_num];
}

void set_cell(int cell_num, cell value)
{
	memory_arr[cell_num] = value;
}
