#include "MSK_File.h"
#define CRT_SECURE_NO_WARNINGS

bool MSK_File::read_file()
{	
	std::string ERROR_MSG;
	bool first_input_BB = false;
	const std::string file_format = ".msk";







	try
	{
		bool correct_name = false;
		std::string input_file_format = file_name.substr(file_name.length() - file_format.length(), file_format.length());



		for (size_t i = 0; i < file_format.length(); i++)
		{
			if (input_file_format[i] != file_format[i] && input_file_format[i] != toupper(file_format[i]))
			{
				throw ERROR_MSG = "INCORRECT FILE FORMAT!";
			}
		}



		FILE* file;
		if ((file = fopen(file_name.c_str(), "r"))==NULL)
		{
			throw ERROR_MSG = "FILE WAS NOT OPENED";
		
		}

		char buf[512];
		char layer_name[32];

		while (!feof(file))
		{
			fgets(buf, 511, file);
			if (strncmp(buf, "REC", 3) == 0)
			{
				Rectangle temp;
				sscanf(buf, "REC(%d,%d,%d,%d,%s)", &temp.left_bot.x, &temp.left_bot.y, &temp.width, &temp.height, layer_name);
				layer_name[strlen(layer_name) - 1] = '\0';
				temp.input_type(layer_name);
				Recs.push_back(temp);
			
			}
			else if (strncmp(buf, "BB", 2)==0)
			{
				
				sscanf(buf, "BB(%d,%d,%d,%d)", &BB.left_bot.x, &BB.left_bot.y, &BB.right_top.x, &BB.right_top.y);
			}
			
			
		}
		if (Recs.empty())
		{
			throw ERROR_MSG = "File do not contain any rectangle!";
		}

	}
	
	catch (std::string ERROR_MSG)
	{
		std::cout << ERROR_MSG << std::endl;
		return 0;
	}
	
	return 1;

}
MSK_File::MSK_File(const std::string& file_name)
{
	this->file_name = file_name;
	if (read_file() == 1)
	{
		correct_input = true;
	}
	
	
}
void MSK_File::input_file(const std::string &file_name)
{
	this->file_name = file_name;
	if (read_file() == 1)
	{
		correct_input = true;
	}
}