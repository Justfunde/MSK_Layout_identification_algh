#pragma warning (disable:4244)
#include "Base64_comparator.h"
Layout_comparator::Layout_comparator()
{
}
void print_matrix(const std::string &matrix_string)//оепедекюрэ
{
	size_t size = sqrt(matrix_string.length());
	for (size_t i = 0; i < matrix_string.length(); i++)
	{
		if (i % size == 0 && i != 0)
		{
			std::cout << std::endl;
		}
		std::cout << matrix_string[i] << " ";
		
	}
	std::cout << std::endl;
}
Layout_comparator::~Layout_comparator()
{

}
int Layout_comparator::sqrt(const int num)
{
	int res = 0;
	while (res * res < num)
	{
		res++;
	}
	return res;
}


double Layout_comparator::string_chance_comparator(const std::string& first_decoded_hash, const std::string &second_decoded_hash)
{
	int counter = 0;
	for (size_t i = 0; i < first_decoded_hash.length(); i++)
	{
		if (first_decoded_hash[i] == second_decoded_hash[i])
		{
			counter++;
		}
	}


	return (double)counter / (double)first_decoded_hash.length();
}
double Layout_comparator::compare_hashes(const std::string& hash_1, const std::string& hash_2)
{
	
	
	std::string first_decoded_str = base64_decode(hash_1, false);
	first_decoded_str = RLE_decode(first_decoded_str);
	


	
	std::string second_decoded_str = base64_decode(hash_2, false);
	second_decoded_str = RLE_decode(second_decoded_str);
	
;

	
	double chance = string_chance_comparator(first_decoded_str, second_decoded_str);
	return chance;
}

void input_fileThreaded(MSK_Processor* process, const std::string& file_name, const bool do_generate_hash)
{
	process->input_file(file_name, do_generate_hash);
}
double Layout_comparator::get_chance_from_hashes(const std::string& first_hash, const std::string& second_hash)
{

	double chance = 0;
	std::string first_hash_part, second_hash_part;
	bool is_first_part_filled = 0,is_second_part_filled=0;
	int count_compared_str = 0;
	size_t i, j;
	i = j = 0;



	while (j < second_hash.length() || i < first_hash.length())
	{
		if (!is_first_part_filled && i < first_hash.length())
		{
			switch (first_hash[i])
			{
			
			case '|':
				is_first_part_filled = true;
				break;
			default:
				first_hash_part += first_hash[i];
				i++;
				break;
			}
		}
		if (!is_second_part_filled && j < second_hash.length())
		{

			switch (second_hash[j])
			{
			
			case '|':
				is_second_part_filled = true;
				break;
			default:
				second_hash_part += second_hash[j];
				j++;
				break;
			}
		}
		if (is_first_part_filled && is_second_part_filled)
		{
			
			chance+=compare_hashes(first_hash_part, second_hash_part);
			


			count_compared_str++;



			first_hash_part.clear();
			second_hash_part.clear();



			is_first_part_filled = false;
			is_second_part_filled = false;



			i++;
			j++;
		}
	}
	std::cout << std::endl;
	return chance / count_compared_str;

}

double Layout_comparator::get_chance(const std::string& first_file_name, const std::string& second_file_name)
{	
		MSK_Processor *first_processed_file = new MSK_Processor;
		MSK_Processor *second_processed_file = new MSK_Processor;

		//first_processed_file->input_file(first_file_name, 0);
		//second_processed_file->input_file(second_file_name, 0);
		std::thread first(input_fileThreaded,first_processed_file, std::cref(first_file_name), 0);
		std::thread second(input_fileThreaded, second_processed_file, std::cref(second_file_name), 0);
		
		if (first.joinable())
		{
			first.join();
		}
		if (second.joinable())
		{
			second.join();
		}


		


		double chance = 0;
		int counter = 0;


		//if (first_processed_file->fragments_size != second_processed_file->fragments_size || first_processed_file->fragments[0][0].matrix_size != second_processed_file->fragments[0][0].matrix_size)
		//{
		//	std::cout << std::endl << "Comparator can not compare files with different splitting!" << std::endl;
		//}




		
		for (int i = 0; i < first_processed_file->fragments_size; i++)
		{
			for (int j = 0; j < first_processed_file->fragments_size; j++)
			{
				
				chance += compare_matrix(first_processed_file->fragments[i][j].matrix, second_processed_file->fragments[i][j].matrix,Fragmentation::matrix_size);
				counter++;
				
			}

		}




		delete first_processed_file;
		first_processed_file = nullptr;
		delete second_processed_file;
		second_processed_file = nullptr;
		
		return chance / counter;
	
}

double Layout_comparator::compare_matrix(bool** matrix_1, bool** matrix_2, const size_t size)
{
	double counter = 0;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (matrix_1[i][j] == matrix_2[i][j])
			{
				counter++;
			}
		}
	}
	return counter / (double)(size * size);
}

bool is_MSK(const char* str, const size_t size)
{
	std::string correct_file_format = ".MSK";
	if (size < correct_file_format.length() + 1)
	{
		return false;
	}
	for (size_t i = size - 4,j=0; i < size; i++,j++)
	{
		if (str[i] != correct_file_format[j] && str[i] != tolower(correct_file_format[j]))
		{
			return false;
		}
	}
	return true;
	
}

