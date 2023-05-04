#include <Windows.h>

#include "Udaj.h"
#include "Input.h"
#include "libds/adt/table.h"

int main()
{
	// Pre správne fungovanie diakritiky je potrebné zahrnú do projektu 2 riadky kódu nišie a zdrojovému súboru nastavi kódovanie na ANSI (prekódova), napr. v NotePad++.
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
