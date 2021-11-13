#pragma once
#include <string>
#include <math.h>
#include "Base64.h"
#include <iostream>
#include <thread>
#include "MSK_Processor.h"
class Layout_comparator
{
private:
	double string_chance_comparator(const std::string& first_decoded_hash, const std::string& second_decoded_hash);
	double compare_hashes(const std::string& hash_1, const std::string& hash_2);
	double compare_matrix(bool** matrix_1, bool** matrix_2, const size_t size);
	int sqrt(const int num);
public:
	Layout_comparator();
	~Layout_comparator();
	double get_chance(const std::string& first_file_name, const std::string& second_file_name);
	double get_chance_from_hashes(const std::string& first_hash, const std::string& second_hash);
	
};


bool is_MSK(const char* str, const size_t size);


