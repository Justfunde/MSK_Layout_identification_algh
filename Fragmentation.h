#pragma once
#include "Bounding_Box.h"
#include "Base64.h"
#include "Rectangle.h"
#include "RLE.h"
#include <vector>
#include<intrin.h>
#include<time.h>




class Fragmentation
{
private:
	Bounding_Box curr_box;
	std::string curr_hash;
	std::vector <Rectangle*> recs_in_this_frag;
	bool** matrix;
	bool correct_hash;
	const static int matrix_size=64;
	bool is_hash_generated;

	bool** allocate_dynamic_sq_matrix();
	void deallocate_dynamic_sq_matrix(bool **);
	double calculate_delta(const Point& p1, const Point& p2, const double size, const char* type);
	bool is_point_in_range(const double x, const double x_dx, const double y, const double y_dy, const Rectangle& rec);
	void fill_matrix(bool** matrix);
	void make_hash();
	void make_matrix();
	void print_matrix( bool** matrix);
	std::string matrix_to_str( bool** matrix);
	

public:
	Fragmentation();
	~Fragmentation();
	std::string get_hash()
	{
		return curr_hash;
	};

	friend class MSK_Processor;
	friend class Layout_comparator;

};
