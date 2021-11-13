
#pragma once
#pragma warning (disable :4244)
#pragma warning (disable :26451)
#include "MSK_File.h"
#include "Fragmentation.h"
#include <iostream>
#include <thread>
class MSK_Processor
{
private:
	MSK_File *file_itself;
	std::vector<Rectangle*> recs_of_metals;
	Fragmentation** fragments;
	const static int fragments_size = 32;
	std::string total_hash;
	double dx;
	double dy;
	void allocate_fragments();
	void deallocate_fragments();
	void init_pointers_vect();
	void push_recs_into_frags();
	void set_coords_for_fragments();
	double calculate_delta(const Point &p1, const Point &p2, const int size, const char* type);



public:
	MSK_Processor();
	~MSK_Processor();
	int input_file(const std::string& file_name, const bool do_generate_hash);
	void set_file_from_MSK(const MSK_File& FILE);
	std::string get_hash() const
	{
		return total_hash;
	}
	//Суммарный хеш
	friend class Layout_comparator;
	friend void input_file_threaded( MSK_Processor& process, const std::string& file_name, const bool do_generate_hash);

};
//input_file_threaded(const MSK_Processor& process, const std::string& file_name, const bool do_generate_hash);
