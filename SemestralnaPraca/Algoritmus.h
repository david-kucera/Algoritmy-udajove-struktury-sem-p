// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyClangDiagnosticInvalidUtf8
#pragma once
#include <functional>

#include "Udaj.h"
/*
 * Samostatnı objekt pre algoritmus, ktorı prechadza údaje a zisuje èi splòujú zadanı predikát.
 */
class Algoritmus
{
public:
	static void prehladaj(auto zaciatok, auto koniec, std::function<bool(Udaj predikat)> predikat, std::function<void(Udaj udaj)> splnujuci)
	{
		while (zaciatok != koniec)	// Prechádzame údajovu štruktúru od zaèiatku po koniec cez iterátory begin a end
		{
			if (predikat(*zaciatok))
			{
				splnujuci(*zaciatok);
			}
			++zaciatok;
		}
	}

	static bool starts_with_str(auto udaj, auto predikat)
	{
		return udaj.get_short_title().starts_with(predikat);	// Ak zadanı reazec sa nachádza na zaèiatku názvu
	}

	static bool contains_str(auto udaj, auto predikat)
	{
		if (udaj.get_short_title().find(predikat) != -1)	// Ak sa nájde reazec v názve
		{
			return true;
		}
		return false;
	}

	static bool hasType(auto udaj, auto predikat)
	{
		std::string typ;
		if (udaj.get_code().length() == 12) typ = "obec";
		else if (udaj.get_code().length() == 1) typ = "kraj";
		else typ = "okres";
		return typ._Equal(predikat);
	}
};

