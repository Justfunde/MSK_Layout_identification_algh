#pragma once
#include "Point.h"
#include <string>
#include <iostream>
enum class Type
{
	undefined = 0,
	ME,
	NW,
	DP,
	DN,
	CO,
	PO,
	VI,
	M2,
	M3,
	V2
};
struct Rectangle//Класс для прямоугольника элемента
{
	Point left_bot;
	int width;
	int height;
	Type material_type;//Тип элемента
	Rectangle() : width(0), height(0), material_type(Type::undefined)
	{
	}
	Rectangle(const std::string& enter);
	void input_type(const char* str);



};
