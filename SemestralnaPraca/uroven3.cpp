#include <Windows.h>

#include "Udaj.h"
#include "Input.h"
#include "libds/adt/table.h"

int main()
{
	// Pre spr�vne fungovanie diakritiky je potrebn� zahrn�� do projektu 2 riadky k�du ni��ie a zdrojov�mu s�boru nastavi� k�dovanie na ANSI (prek�dova�), napr. v NotePad++.
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);
	ds::adt::SortedSequenceTable<std::string, Udaj> kraje_table;
	ds::adt::SortedSequenceTable<std::string, Udaj> okresy_table;
	ds::adt::SortedSequenceTable<std::string, Udaj> obce_table;
	const auto paths = new std::string[3];
	paths[0] = "kraje.csv";
	paths[1] = "okresy.csv";
	paths[2] = "obce.csv";
	constexpr Input input;
	input.read_files(&kraje_table, paths[0]);
	input.read_files(&okresy_table, paths[1]);
	input.read_files(&obce_table, paths[2]);
	delete[] paths;


	std::cout << kraje_table.size() << std::endl;
	std::cout << okresy_table.size() << std::endl;
	std::cout << obce_table.size() << std::endl;

	return 0;
}
