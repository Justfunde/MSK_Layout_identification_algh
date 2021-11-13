#include <iostream>
#include <string>
#include "Base64_comparator.h";
#include <Windows.h>
using namespace std;

int main(int argc, char* argv[])
{

	//std::string  byte;
	//byte.push_back(0b01011010);
	//const std::string s_byte = "01011010";
	//std::cout << "BASE 64 from byte:" << base64_encode(byte, 0) << std::endl;
	//std::cout << "Base64 from string:" << base64_encode(s_byte, 0);
	MSK_Processor generator;
	//
	Layout_comparator comparator;
	
	SetConsoleOutputCP(1251);
	switch (argc)
	{
	case 3:
		if (strcmp(argv[argc - 2], "--hash") != 0)
		{
			cout << "\nUNKNOWN COMMAND\n";
			break;
		}
	
		generator.input_file(argv[argc - 1], true);
		cout << generator.get_hash();
		break;
	case 5:
		if (strcmp(argv[argc - 4], "--compare") != 0)
		{
			cout << "\nUNKNOWN COMMAND\n";
			break;
		}
		if (strcmp(argv[argc - 3], "msk") == 0 || strcmp(argv[argc - 3], "MSK") == 0)
		{ 
			cout << "\nCOMPATIBILITY CHANCE:" << comparator.get_chance(argv[argc - 2], argv[argc - 1]) << endl;
			break;
		}
		else if (strcmp(argv[argc - 3], "hash") == 0)
		{
			cout << "\nCOMPATIBILITY CHANCE:" << comparator.get_chance_from_hashes(argv[argc - 2], argv[argc - 1]) << endl;
			
			break;
		}
		else cout << "\nUNKNOWN COMMAND\n";
	
		break;
	
		//--compare msk Dmitriev1.MSK Mul44.MSK
		
		
	default:
		cout << "\nUNKNOWN COMMAND\n";
		
		break;
	}
	return 0;

}



