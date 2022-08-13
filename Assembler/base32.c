#include "base32.h"
#include <stdio.h>
#include <stdio.h>
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>

char base32_table[32] = {'!','@','#','$','%','^','&','*','<','>','a','b','c','d','e','f',
                         'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v'};

/*Conver decimal address*/
char* address_to_base32(int* bin_num)
{
	char* char_bin_num = NULL;
	sprintf(char_bin_num, "%d", bin_num);
	char first_binary_half[5] = { 0 };
	for (int i = 0; i < 5; i++)
	{
		strncat(first_binary_half, char_bin_num[i], 5);
	}

	int first_dec_half = bin_to_dec(first_binary_half);
	char first_base32 = base32_table[first_dec_half];

	char second_binary_half[5] = { 0 };
	for (int i = 5; i < 10; i++)
	{
		strncat(second_binary_half, char_bin_num[i], 5);
	}

	int second_dec_half = bin_to_dec(second_binary_half);
	char second_base32 = base32_table[second_dec_half];

	char base32_address[2] = { 0 };
	base32_address[0] = first_base32;
	base32_address[1] = second_base32;
	return base32_address;
}

/*Convert binary code*/
char* binary_to_base32(char* bin_num)
{
	char first_binary_half[5] = { 0 };
	for (int i = 0; i < 5; i++)
	{
		strncpy(first_binary_half, bin_num[i], 5);
	}

	int first_dec_half = bin_to_dec(first_binary_half);
	char first_base32 = base32_table[first_dec_half];

	char second_binary_half[5] = { 0 };
	for (int i = 5; i < 10; i++)
	{
		strncpy(second_binary_half, bin_num[i], 5);
	}

	int second_dec_half = bin_to_dec(second_binary_half);
	char second_base32 = base32_table[second_dec_half];

	char base32_code[2] = { 0 };
	base32_code[0] = first_base32;
	base32_code[1] = second_base32;
	return base32_code;
}


int bin_to_dec(char* bin)
{
	int bin_int = atoi(bin);
	int dec = 0, i = 0, rem;

	while (bin_int != 0) 
	{
		rem = bin_int % 10;
		bin_int /= 10;
		dec += rem * pow(2, i);
		++i;
	}
}
