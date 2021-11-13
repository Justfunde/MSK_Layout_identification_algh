#include "MSK_Processor.h"


MSK_Processor::MSK_Processor()
{
	file_itself = new MSK_File;
	allocate_fragments();

}
MSK_Processor::~MSK_Processor()
{	
	deallocate_fragments();
	delete file_itself;
	file_itself = nullptr;
	for (size_t i = 0; i < recs_of_metals.size(); i++)
	{
		if (!recs_of_metals[i])
		{
			delete recs_of_metals[i];
			recs_of_metals[i] = nullptr;
		}
	}
}

void MSK_Processor::init_pointers_vect()
{
	
	for (size_t i = 0; i < file_itself->Recs.size(); i++)
	{
		if (file_itself->Recs[i].material_type == Type::ME)
		{
			recs_of_metals.push_back(&(*file_itself).Recs[i]);
		}
	}
	return;


}
int MSK_Processor::input_file(const std::string& file_name, const bool do_generate_hash )
{
	file_itself->input_file(file_name);
	if (file_itself->correct_input == false)
	{
		std::cout << "File cannot be read!";
		return -1;
	}
	init_pointers_vect();
	set_coords_for_fragments();
	push_recs_into_frags();
	switch (do_generate_hash)
	{
	case true:
		for (int i = 0; i < fragments_size; i++)
		{
			for (int j = 0; j < fragments_size; j++)
			{
				fragments[i][j].make_hash();
				total_hash += fragments[i][j].curr_hash + '|';
			}
		}
		break;
	case false:
		for (int i = 0; i < fragments_size; i++)
		{
			for (int j = 0; j < fragments_size; j++)
			{
			
				fragments[i][j].make_matrix();
			}
		}
		break;
	}
	
	return 0;
}
void MSK_Processor::set_file_from_MSK( const MSK_File& FILE)
{
	if (FILE.correct_input == false)
	{
		std::cout << std::endl << "MSK_Processor cannot read file!" << std::endl;
	}
	
	*file_itself = FILE;
	init_pointers_vect();
	set_coords_for_fragments();
	for (int i = 0; i < fragments_size; i++)
	{
		for (int j = 0; j < fragments_size; j++)
		{
			fragments[i][j].make_hash();
			total_hash += fragments[i][j].curr_hash+"|";
		}
	}
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	return ;
}
void MSK_Processor::push_recs_into_frags()
{
	size_t curr_size = recs_of_metals.size();
	for (size_t k = 0; k < recs_of_metals.size(); k++)
	{
			const Rectangle &curr_rec = *(recs_of_metals[k]);
			
			int curr_frag_j_left_bot_ind = (curr_rec.left_bot.x - file_itself->BB.left_bot.x) / dx;
			int curr_frag_i_left_bot_ind = (file_itself->BB.right_top.y - curr_rec.left_bot.y) / dy;
			int curr_frag_j_right_top_ind = ((curr_rec.left_bot.x + curr_rec.width) - file_itself->BB.left_bot.x) / dx;
			int curr_frag_i_right_top_ind = (file_itself->BB.right_top.y - (curr_rec.left_bot.y + curr_rec.height)) / dy;


			if (curr_frag_j_left_bot_ind >= fragments_size)
			{
				while (curr_frag_j_left_bot_ind >= fragments_size)
				{
					curr_frag_j_left_bot_ind--;
				}
		
			}
			
			if (curr_frag_i_left_bot_ind >= fragments_size)
			{
				while (curr_frag_i_left_bot_ind >= fragments_size)
				{
					curr_frag_i_left_bot_ind--;
				}
				
			}
	

			if (curr_frag_j_right_top_ind >= fragments_size)
			{
				while (curr_frag_j_right_top_ind >= fragments_size)
				{
					curr_frag_j_right_top_ind--;
				}
		
			}
			
			
			if (curr_frag_i_right_top_ind >= fragments_size)
			{
				while (curr_frag_i_right_top_ind >= fragments_size)
				{
					curr_frag_i_right_top_ind--;
				}
				
			}
	
			if (curr_frag_i_left_bot_ind == curr_frag_i_right_top_ind && curr_frag_j_left_bot_ind == curr_frag_j_right_top_ind)//Случай, когда диагональные точки лежат в одном фрагменте
			{
				
				fragments[curr_frag_i_left_bot_ind][curr_frag_j_left_bot_ind].recs_in_this_frag.push_back(recs_of_metals[k]);
	
			}
			else//случай,когда диагональные точки лежат в разных фрагментах
			{
				for (int i = curr_frag_i_right_top_ind; i <= curr_frag_i_left_bot_ind; i++)
				{
					for (int j = curr_frag_j_left_bot_ind; j <= curr_frag_j_right_top_ind; j++)
					{
						fragments[i][j].recs_in_this_frag.push_back(recs_of_metals[k]);
					}
				}
	
			}
	
	
	
	
			
	
	}


}
double MSK_Processor::calculate_delta(const Point &p1,const  Point &p2, const int size, const char* type)
{
	if ("x" == type)
	{
		if (p1.x < 0 && p2.x>0)
		{
			return (p2.x - p1.x) / size;
		}
		return abs((abs(p1.x) - abs(p2.x))) / size;
	}
	else if ("y" == type)
	{
		if (p1.y < 0 && p2.y>0)
		{
			return (p2.y - p1.y) / size;
		}
		return abs((abs(p1.y) - abs(p2.y))) / size;
	}
	else return -1;


}
void MSK_Processor::allocate_fragments()
{
	fragments = new Fragmentation * [fragments_size];
	for (int i = 0; i < fragments_size; i++)
	{
		fragments[i] = new Fragmentation[fragments_size];
	}
				
}
void MSK_Processor::deallocate_fragments()
{
	for (int i = 0; i < fragments_size; i++)
	{
		delete[] fragments[i];
		fragments[i] = nullptr;
	}
	delete[] fragments;
	fragments = nullptr;


}
void MSK_Processor::set_coords_for_fragments()
{
	dx = calculate_delta(file_itself->BB.left_bot, file_itself->BB.right_top,fragments_size,"x");
	dy = calculate_delta(file_itself->BB.left_bot, file_itself->BB.right_top, fragments_size, "y");
	for (int i = 0; i < fragments_size; i++)
	{
		for (int j = 0; j < fragments_size; j++)
		{
			fragments[i][j].curr_box.left_bot.x = file_itself->BB.left_bot.x + dx * j;
			fragments[i][j].curr_box.left_bot.y = file_itself->BB.right_top.y - dy * (i+1);
			fragments[i][j].curr_box.right_top.x = file_itself->BB.left_bot.x + dx * (j + 1);
			fragments[i][j].curr_box.right_top.y=file_itself->BB.right_top.y-dy*i;
		}
	}




}
