#pragma once

#define VYMAZ system("cls") // makro pre vyèistenie obrazovky

class uroven3
{
public:
	static void spusti_uroven()
	{
		VYMAZ;
		std::cout << "Zvo¾ si tabu¾ku, z ktorej chceš vypísat hodnoty: 1 - kraje 2 - okresy 3 - obce" << std::endl;
		auto volba = _getch();

		const auto paths = new std::string[3];
		paths[0] = "kraje.csv";
		paths[1] = "okresy.csv";
		paths[2] = "obce.csv";
		constexpr input input;

		// Použitý typ tabu¾ky pre túto úroveò semestrálnej práce
		ds::adt::SortedSequenceTable<std::string, Udaj*> table;

		switch (volba)
		{
		case 49:
			// kraje
			input.read_files(&table, paths[0]);
			break;
		case 50:
			// okresy
			input.read_files(&table, paths[1]);
			break;
		case 51:
			// obce
			input.read_files(&table, paths[2]);
			break;
		default:
			// ako default sa zoberie obec
			input.read_files(&table, paths[2]);
			break;
		}
		delete[] paths;


		string hladane;
		std::cout << "Zadaj h¾adaný k¾úè (official title): ";
		std::cin >> std::ws;
		getline(std::cin, hladane);

		try
		{
			table.find(hladane)->print();
		}
		catch (std::out_of_range)
		{
			// vyhadzovalo random exceptions
		}
		catch (ds::adt::structure_error)
		{
			std::cout << "Takýto k¾úè sa nenachádza v tabu¾ke" << std::endl;
		}

		//Prehladam aj vsetky mozne postfixy short_title-ov
		string new_hladane = hladane;
		for (int i = 0; i < 3; i++)
		{
			new_hladane.append("_");
			try
			{
				table.find(new_hladane)->print();
			}
			catch (std::out_of_range)
			{
				// vyhadzovalo random exceptions
			}
			catch (ds::adt::structure_error)
			{
				// dont print anything
			}
		}

		for (auto& i : table)
		{
			delete i.data_;
		}

		table.clear();

		std::cout << " Stlaè kláves ENTER pre návrat do menu aplikácie." << std::endl;
		auto ch = _getch();
	}
};