#pragma once
#include "Udaj.h"
#include "SortingAlgoritmus.h"
#include "libds/adt/sorts.h"
#include "libds/amt/implicit_sequence.h"

class uroven4
{
public:
	static void spusti_uroven(ds::amt::ImplicitSequence<Udaj> is)
	{
		VYMAZ;
		for (auto& i : is)
		{
			i.print();
		}
		std::cout << "Možnosti sortovania údajov: [1] compareAlphabetical [2] compareVowelsCount" << std::endl;
		

		while (true)
		{
			auto volba = _getch();
			if (volba == 49)
			{
				std::cout << "Porovnavam alphabetical" << std::endl;
				sorting_algo::sort_compareAlphabetical(&is);
				break;
			}
			if (volba == 50)
			{
				std::cout << "Porovnavam vowels count" << std::endl;
				sorting_algo::sort_compareVowelsCount(&is);
				break;
			}
		}

		std::cout << "Výsledok po sortovaní údajov:" << std::endl;
		for (auto& i : is)
		{
			i.print();
		}

		std::cout << " Stlaè akýko¾vek kláves pre návrat do menu aplikácie." << std::endl;
		auto ch = _getch();
		return;
	}
};
