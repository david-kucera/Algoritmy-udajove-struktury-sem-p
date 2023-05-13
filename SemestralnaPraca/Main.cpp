#include "Uroven1.h"
#include "Uroven2.h"
#include "Uroven3.h"
#include <iostream>
#include <conio.h>

int main()
{
	// Inicializ�cia heap monitora - na kontrolu �nikov pam�te
	initHeapMonitor();
	/*
	* Pre spr�vne fungovanie diakritiky je potrebn� zahrn�� do projektu 2 riadky k�du ni��ie a zdrojov�mu s�boru nastavi� k�dovanie na ANSI (prek�dova�), napr. v NotePad++.
	*/
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);

	while (true)
	{
		system("cls");
		std::cout << "ALGORITMY A �DAJOV� �TRUKT�RY 1\tSemestr�lna pr�ca\tDavid Ku�era 2023" << std::endl;
		std::cout << "\n" << std::endl;
		std::cout << "Vyber si �rove� semestr�lnej pr�ce, ktor� chce� zapn��: " << std::endl;

		std::cout << "1 - prv� �rove�" << std::endl;
		std::cout << " Na��tanie �dajov o obciach, okresoch a krajoch, spracovanie �dajov spl�uj�cich zadan� predik�t." << std::endl;
		// TODO doplnit do dokumentacie UML diagram aktivit univerzalneho algoritmu a programatorsku prirucku

		std::cout << "2 - druh� �rove� (vr�mci nej je obsiahnut� aj 4. �rove�)" << std::endl;
		std::cout << " Vytvorenie pomyselnej hierarchie Slovenskej republiky a navig�cia vr�mci nej." << std::endl;
		// TODO dokumenatcia vysvetlit sposob nacitania udajov a zlozitost

		std::cout << "3 - tretia �rove�" << std::endl;
		std::cout << " Efekt�vne vyh�ad�vanie �zemn�ch jednotiek pomocou n�zvu." << std::endl;
		// TODO analyza casovej zlozitosti

		std::cout << std::endl;

		std::cout << " Stla� kl�ves Escape pre ukon�enie aplik�cie." << std::endl;
		auto ch = _getch();

		// Volba �rovne, alebo ukon�enie aplik�cie.
		if (ch == 27) return 0;
		if (ch == 49) uroven1().spusti_uroven();
		if (ch == 50) uroven2().spusti_uroven();
		if (ch == 51) uroven3().spusti_uroven();
	}
}
