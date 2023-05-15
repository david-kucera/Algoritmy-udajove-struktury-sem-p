#include "Uroven1.h"
#include "Uroven2.h"
#include "Uroven3.h"
#include <iostream>
#include <conio.h>

int main()
{
	// Inicializácia heap monitora - na kontrolu únikov pamäte
	initHeapMonitor();
	/*
	* Pre správne fungovanie diakritiky je potrebné zahrnú do projektu 2 riadky kódu nišie a zdrojovému súboru nastavi kódovanie na ANSI (prekódova), napr. v NotePad++.
	*/
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);

	while (true)
	{
		system("cls");
		std::cout << "ALGORITMY A ÚDAJOVÉ ŠTRUKTÚRY 1\tSemestrálna práca\tDavid Kuèera 2023" << std::endl;
		std::cout << "\n" << std::endl;
		std::cout << "Vyber si úroveò semestrálnej práce, ktorú chceš zapnú: " << std::endl;

		const HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE); 
		SetConsoleTextAttribute(h_console, 14);  
		std::cout << "1 - prvá úroveò (vrámci nej je obsiahnutá aj 4. úroveò)" << std::endl;
		SetConsoleTextAttribute(h_console, 7); 
		std::cout << " Naèítanie údajov o obciach, okresoch a krajoch, spracovanie údajov splòujúcich zadanı predikát." << std::endl;

		SetConsoleTextAttribute(h_console, 14); 
		std::cout << "2 - druhá úroveò (vrámci nej je obsiahnutá aj 4. úroveò)" << std::endl;
		SetConsoleTextAttribute(h_console, 7);
		std::cout << " Vytvorenie pomyselnej hierarchie Slovenskej republiky a navigácia vrámci nej." << std::endl;

		SetConsoleTextAttribute(h_console, 14); 
		std::cout << "3 - tretia úroveò" << std::endl;
		SetConsoleTextAttribute(h_console, 7);
		std::cout << " Efektívne vyh¾adávanie územnıch jednotiek pomocou názvu." << std::endl;

		std::cout << std::endl;

		std::cout << " Stlaè kláves Escape pre ukonèenie aplikácie." << std::endl;
		auto ch = _getch();

		// Volba úrovne, alebo ukonèenie aplikácie.
		if (ch == 27) return 0;
		if (ch == 49) uroven1::spusti_uroven();
		if (ch == 50) uroven2::spusti_uroven();
		if (ch == 51) uroven3::spusti_uroven();
	}
}
