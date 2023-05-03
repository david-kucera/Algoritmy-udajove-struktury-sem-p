// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyClangDiagnosticInvalidUtf8
#pragma once
#include <functional>

#include "Udaj.h"
/*
 * Samostatn� objekt pre algoritmus, ktor� prechadza �daje a zis�uje �i spl�uj� zadan� predik�t.
 */
class Algoritmus
{
public:
	static void prehladaj(auto zaciatok, auto koniec, std::function<bool(Udaj predikat)> predikat, std::function<void(Udaj udaj)> splnujuci)
	{
		while (zaciatok != koniec)	// Prech�dzame �dajovu �trukt�ru od za�iatku po koniec cez iter�tory begin a end
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
		return udaj.get_short_title().starts_with(predikat);	// Ak zadan� re�azec sa nach�dza na za�iatku n�zvu
	}

	static bool contains_str(auto udaj, auto predikat)
	{
		if (udaj.get_short_title().find(predikat) != -1)	// Ak sa n�jde re�azec v n�zve
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

