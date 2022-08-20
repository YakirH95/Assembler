#include "base32.h"
#include <stdio.h>
#include <stdio.h>
#include "dictionary.h"
#include <stdlib.h>
#include <math.h>
#include "address_analizer.h"
#include <string.h>

char base32_table[32] = { '!','@','#','$','%','^','&','*','<','>','a','b','c','d','e','f',
						 'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v' };

/*Convert binary to decimal*/
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

	return dec;
}

/*Conver decimal address*/
void address_to_base32(int bin_num, char* base32_address)
{
	int bin_num_char[10] = { 0 };

	dec_to_binary(bin_num, bin_num_char);

	char first_binary_half[6] = { 0 };
	for (int i = 0; i < 5; i++)
	{
		first_binary_half[i] = '0' + bin_num_char[i];
	}

	int first_dec_half = bin_to_dec(first_binary_half);
	char first_base32 = base32_table[first_dec_half];

	char second_binary_half[6] = { 0 };
	for (int i = 0; i < 5; i++)
	{
		second_binary_half[i] = '0' + bin_num_char[i + 5];
	}

	int second_dec_half = bin_to_dec(second_binary_half);
	char second_base32 = base32_table[second_dec_half];

	base32_address[0] = first_base32;
	base32_address[1] = second_base32;
}

/*Convert binary code*/
void binary_to_base32(char* bin_num, char* base32_address)
{
	char first_binary_half[6] = { 0 };
	for (int i = 0; i < 5; i++)
	{
		first_binary_half[i] = bin_num[i];
	}

	int first_dec_half = bin_to_dec(first_binary_half);
	char first_base32 = base32_table[first_dec_half];

	char second_binary_half[6] = { 0 };
	for (int i = 0; i < 5; i++)
	{
		second_binary_half[i] = bin_num[i + 5];
	}

	int second_dec_half = bin_to_dec(second_binary_half);
	char second_base32 = base32_table[second_dec_half];

	base32_address[0] = first_base32;
	base32_address[1] = second_base32;
}