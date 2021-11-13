#include "Rectangle.h"
Rectangle::Rectangle(const std::string& enter)
{
	this->height = 0;
	this->material_type = Type::undefined;
	this->width = 0;
	int counter = 0;
	std::string temp;


	for (size_t i = 0; i < enter.length(); i++)//Проходим по всей строке с substr=REC
	{
		if (isdigit(enter[i])||enter[i]=='-')//Попали на число-записываем его в строку
		{
			counter++;
			while (isdigit(enter[i])||enter[i] == '-')
			{
				temp += enter[i];
				i++;
			}
		}
		switch (counter)//Приводим строку к double
		{
		case 1:
			left_bot.x = std::stoi(temp);
			temp.clear();
			break;
		case 2:
			left_bot.y = std::stoi(temp);
			temp.clear();
			break;
		case 3:
			width = std::stoi(temp);
			temp.clear();
			break;
		case 4:
			height = std::stoi(temp);
			temp.clear();
			break;
		}
		if (4 == counter)//Если все координаты заполнены-заполняем тип вещества
		{
			if (enter[i] == ',' and isalpha(enter[i + 1]))
			{
				i++;
				while (enter[i] != ')')
				{
					temp += enter[i];
					i++;
				}
				if ("ME" == temp)
				{
					material_type = Type::ME;
				}
				else if ("NW" == temp)
				{
					material_type = Type::NW;
				}
				else if ("DP" == temp)
				{
					material_type = Type::DP;
				}
				else if ("DN" == temp)
				{
					material_type = Type::DN;
				}
				else if ("CO" == temp)
				{
					material_type = Type::CO;
				}
				else if ("PO" == temp)
				{
					material_type = Type::PO;
				}
				else if ("VI" == temp)
				{
					material_type = Type::VI;
				}
				else if ("M2" == temp)
				{
					material_type = Type::M2;
				}
				else if ("M3" == temp)
				{
					material_type = Type::M3;
				}
				else if ("V2" == temp)
				{
					material_type = Type::V2;
				}
				else std::cout << "\tProgramm has met undefined type >" << temp << "<\n\tPlease add it to type class\n";


			}
		}
	}
}
void Rectangle::input_type(const char* str)
{
	
		if (strcmp("ME",str)==0)
		{
			material_type = Type::ME;
		}
		else if (strcmp("NW",str)==0)
		{
			material_type = Type::NW;
		}
		else if (strcmp("DP",str)==0)
		{
			material_type = Type::DP;
		}
		else if (strcmp("DN",str)==0)
		{
			material_type = Type::DN;
		}
		else if (strcmp("CO", str)==0)
		{
			material_type = Type::CO;
		}
		else if (strcmp("PO", str)==0)
		{
			material_type = Type::PO;
		}
		else if (strcmp("VI", str)==0)
		{
			material_type = Type::VI;
		}
		else if (strcmp("M2", str)==0)
		{
			material_type = Type::M2;
		}
		else if (strcmp("M3", str)==0)
		{
			material_type = Type::M3;
		}
		else if (strcmp("V2", str)==0)
		{
			material_type = Type::V2;
		}
		else std::cout << "\tProgramm has met undefined type >" << str << "<\n\tPlease add it to type class\n";


	
}