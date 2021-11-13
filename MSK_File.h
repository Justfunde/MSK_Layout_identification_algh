#pragma once
#define CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#include <fstream>
#include "Rectangle.h"
#include "Bounding_Box.h"
#include <stdio.h>
class MSK_File
{
private:
	std::string file_name;
	Bounding_Box BB;
	std::vector<Rectangle> Recs;
	bool correct_input;
	
	bool read_file();
	
public:
	MSK_File()
	{
		file_name = '\0';
		correct_input = false;
	}
	MSK_File(const std::string& file_name);
	void input_file(const std::string &file_name);


	friend class MSK_Processor;
};