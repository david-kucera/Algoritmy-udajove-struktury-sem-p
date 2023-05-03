#include "Udaj.h"
#include "Input.h"
#include "libds/adt/table.h"

int main()
{
	ds::adt::SortedSequenceTable<std::string, Udaj> table;
	const auto paths = new std::string[3];
	paths[0] = "kraje.csv";
	paths[1] = "okresy.csv";
	paths[2] = "obce.csv";
	constexpr input input;
	input.read_files(&table, paths);
	delete[] paths;
	std::cout << table.size() << std::endl;
	return 0;
}
