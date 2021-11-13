#pragma once
struct Point//Класс точка
{
	int x;
	int y;
	Point() :x(0), y(0)
	{}
	Point(int x, int y);
	Point(const Point& cpy);
};

