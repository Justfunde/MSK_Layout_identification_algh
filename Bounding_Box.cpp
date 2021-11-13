#include "Bounding_Box.h"
void Bounding_Box::fill_BB_from_str(const std::string& enter_BB_str)//Заполняем основу ББ из строки
{
	int counter = 0;
	std::string temp;





	for (size_t i = 0; i < enter_BB_str.length(); i++)
	{

		if (isdigit(enter_BB_str[i]) || enter_BB_str[i] == '-')
		{
			counter++;
			while (isdigit(enter_BB_str[i]) || enter_BB_str[i] == '-')
			{
				temp += enter_BB_str[i];
				i++;
			}
		}
		switch (counter)
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
			right_top.x = std::stoi(temp);
			temp.clear();
			break;
		case 4:
			right_top.y = std::stoi(temp);
			temp.clear();
			break;
		}
	}

}