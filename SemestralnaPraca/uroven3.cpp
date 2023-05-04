#include <Windows.h>

#include "Udaj.h"
#include "Input.h"
#include "libds/adt/table.h"

int main()
{
	// Inicializ�cia heap monitora - na kontrolu �nikov pam�te
	initHeapMonitor();

	// Pre spr�vne fungovanie diakritiky je potrebn� zahrn�� do projektu 2 riadky k�du ni��ie a zdrojov�mu s�boru nastavi� k�dovanie na ANSI (prek�dova�), napr. v NotePad++.
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);

	std::cout << "===Demon�tr�cia 3. �rovne SP z AUS1===" << std::endl;
	std::cout << "Zvo� si tabu�ku, z ktorej chce� vyp�sat hodnoty: 1 - kraje 2 - okresy 3 - obce" << std::endl;
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
	//std::cout << "Zadaj h�adan� k��� (short title): ";
	//std::cin >> hladane;

	//const string postfix[] = { "1", "2" };
	//try
	//{
	//	table.find(hladane).print();
	//}
	//catch (ds::adt::structure_error)
	//{
	//	std::cout << "Tak�to k��� sa nenach�dza v tabu�ke" << std::endl;
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
	//		std::cout << "Viac z�znamov neexistuje v tabu�ke." << std::endl;
	//	}
	//}

	table.find("Vi��ov�").print();
	table.find("Vi��ov�1").print();
	table.find("Vi��ov�2").print();

	table.clear();

	return 0;
}
