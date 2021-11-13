#pragma once
#include <string>
#include "RLE.h"
#define UCHAR_MAX (CHAR_MAX-CHAR_MIN)
std::string RLE_encode(const std::string& str_to_encode)
{
	std::string encoded_str;
	for (size_t i = 0; i < str_to_encode.length(); i++)
	{
		size_t j = i;
		unsigned char counter_normal = 0;
		while (str_to_encode[i] == str_to_encode[j])
		{
	
			counter_normal++;
			if (UCHAR_MAX == counter_normal)
			{

				encoded_str += counter_normal;
				encoded_str += str_to_encode[j];
				counter_normal = 0;
			}
			i++;

		}
		encoded_str += counter_normal;
		encoded_str += str_to_encode[j];
		i--;

	}
	return encoded_str;
}
std::string RLE_decode(const std::string& str_to_decode)
{
	std::string decoded_str;
	for (size_t i = 0; i < str_to_decode.length() - 1; i += 2)
	{
		unsigned char counter_symb = str_to_decode[i];
		while (counter_symb != 0)
		{
			decoded_str += str_to_decode[i + 1];
			counter_symb--;
		}
	}
	return decoded_str;
}
