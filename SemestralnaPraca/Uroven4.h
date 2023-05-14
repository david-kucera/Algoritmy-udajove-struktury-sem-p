#pragma once
#include "Udaj.h"
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
				//ss.sort(is, compareAlphabetical);
				std::cout << "Porovnavam alphabetical" << std::endl;
				break;
			}
			if (volba == 50)
			{
				//ss.sort(is, compareVowelsCount);
				std::cout << "Porovnavam vowels count" << std::endl;
				break;
			}
		}

		std::cout << " Stlaè akýko¾vek kláves pre návrat do menu aplikácie." << std::endl;
		auto ch = _getch();
		return;
	}
};
