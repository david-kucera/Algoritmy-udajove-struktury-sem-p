#pragma once
#include "Udaj.h"
#include "SortingAlgoritmus.h"
#include "libds/adt/sorts.h"
#include "libds/amt/implicit_sequence.h"
#include <conio.h>

#define VYMAZ system("cls") // makro pre vy�istenie obrazovky

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
				VYMAZ;
				sorting_algo::sort_compare_alphabetical(&is);
				vypis_vysledok(is);
				break;
			}
			if (volba == 50)
			{
				VYMAZ;
				sorting_algo::sort_compare_vowels_count(&is);
				vypis_hodnoty_porovnavania(is);
				break;
			}
		}

		is.clear();

		std::cout << " Stla� ak�ko�vek kl�ves pre n�vrat do menu aplik�cie." << std::endl;
		auto ch = _getch();
		return;
	}

	static void vypis_vysledok(ds::amt::ImplicitSequence<Udaj> is)
	{
		std::cout << "V�sledok po sortovan� �dajov:" << std::endl;
		for (auto& i : is)
		{
			i.print();
		}
	}

	static void vypis_hodnoty_porovnavania(ds::amt::ImplicitSequence<Udaj> is)
	{
		std::cout << "V�sledok po sortovan� �dajov:" << std::endl;
		for (auto& i : is)
		{
			i.print();
			std::cout << std::to_string(sorting_algo::count_vowels(i.get_official_title())) << std::endl;
		}
	}
};
