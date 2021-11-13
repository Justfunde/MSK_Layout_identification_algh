#include "Fragmentation.h"
Fragmentation::Fragmentation()
{
	
	curr_hash = '\0';
	matrix = allocate_dynamic_sq_matrix();
	is_hash_generated = false;

}
Fragmentation::~Fragmentation()
{
	if (is_hash_generated == false)
	{
		deallocate_dynamic_sq_matrix(matrix);
	}

}

void Fragmentation::print_matrix(bool** matrix)
{
	for (int i = 0; i < matrix_size; i++)
	{
		for (int j = 0; j < matrix_size; j++)
		{
			std::cout << matrix[i][j] << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
bool** Fragmentation::allocate_dynamic_sq_matrix()
{
	bool** temp = new bool* [matrix_size];
	for (int i = 0; i < matrix_size; i++)
	{
		temp[i] = new bool[matrix_size];
	}
	for (int i = 0; i < matrix_size; i++)
	{
		for (int j = 0; j < matrix_size; j++)
		{
			temp[i][j] = 0;
		}
	}
	return temp;
}
void Fragmentation::deallocate_dynamic_sq_matrix(bool **matrix)
{
	for (int i = 0; i < matrix_size; i++)
	{
		delete[] matrix[i];
		matrix[i] = nullptr;
	}
	delete[] matrix;
	matrix = nullptr;
}

double Fragmentation::calculate_delta(const Point &p1, const Point &p2, const double size, const char* type)
{
	if ("x" == type)
	{
		if (p1.x < 0 && p2.x>0)
		{
			return (double)(p2.x - p1.x) / size;
		}
		return abs((double)(abs(p1.x) - abs(p2.x))) / size;
	}
	else if ("y" == type)
	{
		if (p1.y < 0 && p2.y>0)
		{
			return (double)(p2.y - p1.y) / size;
		}
		return abs((double)(abs(p1.y) - abs(p2.y))) / size;
	}
	else return -1;
}
bool Fragmentation::is_point_in_range(const double x, const double x_dx, const double y, const double y_dy, const Rectangle& rec)
{
	
	if (rec.left_bot.x < x + x_dx && rec.left_bot.x + rec.width > (double)x + x_dx)
	{
		if (rec.left_bot.y < (double)y - y_dy && rec.left_bot.y + rec.height > (double)y - y_dy)
		{
			return true;
		}
	}
	return false;
}
void Fragmentation::fill_matrix(bool** matrix)
{
	double start_x = curr_box.left_bot.x;
	double start_y = curr_box.right_top.y;
	double dx = calculate_delta(curr_box.left_bot, curr_box.right_top, matrix_size, "x");
	double dy = calculate_delta(curr_box.left_bot, curr_box.right_top, matrix_size, "y");


	//нужно подправить-пробегать по всем ректам и определять область сразу
	for (int i = 0; i < matrix_size; i++)
	{
		for (int j = 0; j < matrix_size; j++)
		{

			for (size_t t = 0; t < recs_in_this_frag.size(); t++)
			{
				const Rectangle &rec = *recs_in_this_frag[t];


					if (is_point_in_range(start_x, dx / 2 + dx * j, start_y, dy / 2 + dy * i, rec))
					{
						matrix[i][j] = true;
						break;

					}

				
		
			}

		}


	}
	return;

}
std::string Fragmentation::matrix_to_str(bool** matrix)
{
	std::string temp_str;
	for (int i = 0; i < matrix_size; i++)
	{
		for (int j = 0; j < matrix_size; j++)
		{
			if (matrix[i][j] == false)
			{
				temp_str += '0';
			}
			else temp_str += '1';
		}
	}
	return temp_str;

}
void Fragmentation::make_hash()
{
	fill_matrix(matrix);
	is_hash_generated = true;

	curr_hash=matrix_to_str(matrix);

	curr_hash = RLE_encode(curr_hash);
	curr_hash=base64_encode(curr_hash,false);
	deallocate_dynamic_sq_matrix(matrix);
	

	return;

}
void Fragmentation::make_matrix()
{
	fill_matrix(matrix);
}

