#include <Windows.h>

#include "Udaj.h"
#include "Input.h"
#include "libds/adt/table.h"

int main()
{
	// Inicializácia heap monitora - na kontrolu únikov pamäte
	initHeapMonitor();

	// Pre správne fungovanie diakritiky je potrebné zahrnú do projektu 2 riadky kódu nišie a zdrojovému súboru nastavi kódovanie na ANSI (prekódova), napr. v NotePad++.
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);

	std::cout << "===Demonštrácia 3. úrovne SP z AUS1===" << std::endl;
	std::cout << "Zvo¾ si tabu¾ku, z ktorej chceš vypísat hodnoty: 1 - kraje 2 - okresy 3 - obce" << std::endl;
	int volba;
	std::cin >> volba;

	const auto paths = new std::string[3];
	paths[0] = "kraje.csv";
	paths[1] = "okresy.csv";
	paths[2] = "obce.csv";
	constexpr Input input;

	ds::adt::SortedSequenceTable<std::string, Udaj> table;

	switch (volba)
	{
	case 1:
		// kraje
		input.read_files(&table, paths[0]);
		break;
	case 2:
		// okresy
		input.read_files(&table, paths[1]);
		break;
	case 3:
		// obce
		input.read_files(&table, paths[2]);
		break;
	default:
		return 0;
	}
	delete[] paths;

	//string hladane;
	//std::cout << "Zadaj h¾adanı k¾úè (short title): ";
	//std::cin >> hladane;

	//const string postfix[] = { "1", "2" };
	//try
	//{
	//	table.find(hladane).print();
	//}
	//catch (ds::adt::structure_error)
	//{
	//	std::cout << "Takıto k¾úè sa nenachádza v tabu¾ke" << std::endl;
	//}

	////Prehladam aj vsetky mozne postfixy short_title-ov
	//for (int i = 0; i < 2; i++)
	//{
	//	string new_hladane = hladane + postfix[i];
	//	try
	//	{
	//		table.find(new_hladane).print();
	//	}
	//	catch (ds::adt::structure_error)
	//	{
	//		std::cout << "Viac záznamov neexistuje v tabu¾ke." << std::endl;
	//	}
	//}

	table.find("Višòové").print();
	table.find("Višòové1").print();
	table.find("Višòové2").print();

	table.clear();

	return 0;
}
