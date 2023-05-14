#pragma once

#define VYMAZ system("cls") // makro pre vy�istenie obrazovky

class uroven3
{
public:
	static void spusti_uroven()
	{
		VYMAZ;
		std::cout << "Zvo� si tabu�ku, z ktorej chce� vyp�sat hodnoty: 1 - kraje 2 - okresy 3 - obce" << std::endl;
		int volba;
		std::cin >> volba;

		const auto paths = new std::string[3];
		paths[0] = "kraje.csv";
		paths[1] = "okresy.csv";
		paths[2] = "obce.csv";
		constexpr Input input;

		// Pou�it� typ tabu�ky pre t�to �rove� semestr�lnej pr�ce
		ds::adt::SortedSequenceTable<std::string, Udaj*> table;

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
			// ako default sa zoberie obec
			input.read_files(&table, paths[2]);
			break;
		}
		delete[] paths;


		string hladane;
		std::cout << "Zadaj h�adan� k��� (official title): ";
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
			std::cout << "Tak�to k��� sa nenach�dza v tabu�ke" << std::endl;
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

		for (auto i = table.begin(); i != table.end(); ++i)
		{
			delete (*i).data_;
		}

		table.clear();

		std::cout << " Stla� ak�ko�vek kl�ves pre n�vrat do menu aplik�cie." << std::endl;
		auto ch = _getch();
	}
};