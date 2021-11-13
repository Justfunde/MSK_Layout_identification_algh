#pragma once
#include "Point.h"
#include <string>
struct Bounding_Box
{
	Point left_bot;
	Point right_top;
	void fill_BB_from_str(const std::string& enter_BB_str);//Заполняем основу ББ из строки(стоит ли так делать?)
	
};
