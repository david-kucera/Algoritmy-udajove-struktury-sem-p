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
		std::cout << "Mo�nosti sortovania �dajov: [1] compareAlphabetical [2] compareVowelsCount" << std::endl;
		

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

		std::cout << " Stla� ak�ko�vek kl�ves pre n�vrat do menu aplik�cie." << std::endl;
		auto ch = _getch();
		return;
	}
};
