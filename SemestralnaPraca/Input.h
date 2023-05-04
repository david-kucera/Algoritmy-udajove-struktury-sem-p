// ReSharper disable CppClangTidyClangDiagnosticInvalidSourceEncoding
// ReSharper disable CppClangTidyClangDiagnosticInvalidUtf8
// ReSharper disable CppClangTidyClangDiagnosticSignCompare
#pragma once
#include <fstream>
#include <vector>
#include "Udaj.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "libds/adt/table.h"
#include "libds/amt/explicit_hierarchy.h"

using string = std::string;

class Input
{
public:
	/*
	 * Metóda používaná len pri 1. úrovni SP.
	 * Naèíta údaje zo zvoleného súboru a naèíta ich do vectora.
	 * Vracia vector naplnený naèítanými hodnotami údajov.
	 */
	std::vector<Udaj> read(const char* input_file) const
	{
		std::fstream file;
		file.open(input_file, std::ios::in);
		std::vector<Udaj> udaje;

		if (file.is_open())
		{
			std::vector<string> row;
			string line, word, sort_number, code, official_title, medium_title, short_title, note;

			while (std::getline(file, line))
			{
				row.clear();
				std::stringstream str(line);

				// Prvy riadok odfiltujeme od zvysku udajov
				if (line.find("sortNumber;code;officialTitle;mediumTitle;shortTitle;note") != -1)  continue;
				
				while (std::getline(str, word, ';'))
				{
					row.push_back(word);
				}

				// Tu row obsahuje vsetky informacie o danej uzemnej jednotke
				sort_number = row[0];
				code = row[1];
				official_title = row[2];
				medium_title = row[3];
				short_title = row[4];
				if (row.size() == 6) note = row[5]; // FIX kvoli zahraniciu
				else if (row.size() == 5) note = "";

				Udaj udaj(sort_number, code, official_title, medium_title, short_title, note);
				udaje.push_back(udaj);
				
			}
		}
		else
		{
			throw std::runtime_error("Could not open input file");
		}
		file.close();

		return udaje;
	}

	/*
	 * Metóda používaná pri 2. úrovni SP.
	 * Ako parameter preberá danú hierarchiu a adresy vstupných súborov.
	 * Každý súbor prejde práve raz a do hierarchie zapisuje naèítané údaje.
	 */
	void read_files(ds::amt::MultiWayExplicitHierarchy<Udaj>* hierarchy, std::string* paths) const
	{
		for (int index_of_input_file = 0; index_of_input_file < 3; ++index_of_input_file)
		{
			std::fstream file;
			file.open(paths[index_of_input_file], std::ios::in);

			// Každý súbor sa preèíta práve raz
			if (file.is_open())
			{
				std::vector<string> row;
				string line, word, sort_number, code, official_title, medium_title, short_title, note;

				// Indexujem vždy od 0
				size_t index_syna = 0;
				size_t index_kraju = 0;
				size_t index_okresu = 0;
				ds::amt::MultiWayExplicitHierarchyBlock<Udaj>* kraj = hierarchy->accessRoot();
				ds::amt::MultiWayExplicitHierarchyBlock<Udaj>* okres = hierarchy->accessRoot();

				while (std::getline(file, line))
				{
					row.clear();
					std::stringstream str(line);

					// Prvý riadok odfiltujem od zvyšku údajov
					if (line.find("sortNumber;code;officialTitle;mediumTitle;shortTitle;note") != -1) continue;

					while (std::getline(str, word, ';'))
					{
						row.push_back(word);
					}
					sort_number = row[0];
					code = row[1];
					official_title = row[2];
					medium_title = row[3];
					short_title = row[4];
					if (row.size() == 6) note = row[5]; 
					else if (row.size() == 5) note = "";

					// Úprava údajov pre zahranièie - kraj
					

					Udaj udaj(sort_number, code, official_title, medium_title, short_title, note);

					// -------------------------
					// KRAJE
					// -------------------------

					if (index_of_input_file == 0) 
					{
						// Kraje majú ako parenta Slovensko,- èiže koreò hierarchie.
						hierarchy->emplaceSon(*hierarchy->accessRoot(), index_syna).data_ = udaj;		
						index_syna++;
					}

					// -------------------------
					// OKRESY a OBCE
					// -------------------------

					// Zmena údajov v .csv súboroch pre posledné údaje - "zahranièie" - aby boli korektne rozdelené na kraje,okresy a obce

					else
					{
						kraj = hierarchy->accessSon(*hierarchy->accessRoot(), index_kraju);

						// Okres patrí kraju práve vtedy, ak substring za poslednou '-' v note kraja sa zhoduje so zaèiatkom code-u okresu
						string note_kraja = kraj->data_.get_note();
						size_t index_last_dash = note_kraja.find_last_of('-');	 // Získam index posledného '-'

						// Tu sa spolieha na to, že nasledujúce údaje buï spadajú pod rovnaký kraj/okres
						if (string predikat = note_kraja.substr(index_last_dash + 1, note_kraja.length() - index_last_dash); udaj.get_code().starts_with(predikat))
						{
							// Okresy
							if (index_of_input_file == 1)
							{
								hierarchy->emplaceSon(*kraj, index_syna).data_ = udaj;
								index_syna++;
							}

							//Obce
							else
							{
								okres = hierarchy->accessSon(*kraj, index_okresu);

								// Obec patrí okresu práve vtedy, ak code obce sa zaèína code-om okresu
								if (udaj.get_code().starts_with(okres->data_.get_code()))
								{
									hierarchy->emplaceSon(*okres, index_syna).data_ = udaj;
									index_syna++;
								}
								else
								{
									index_okresu++;
									index_syna = 0;
									okres = hierarchy->accessSon(*kraj, index_okresu);
									hierarchy->emplaceSon(*okres, index_syna).data_ = udaj;
									index_syna++;
								}
							}
						}
						// alebo patria ïalšiemu kraju/okresu v poradí
						else
						{
							index_kraju++;
							index_okresu = 0;
							index_syna = 0;
							kraj = hierarchy->accessSon(*hierarchy->accessRoot(), index_kraju);
							if (index_of_input_file == 1) hierarchy->emplaceSon(*kraj, index_syna).data_ = udaj;
							else
							{
								okres = hierarchy->accessSon(*kraj, index_okresu);
								hierarchy->emplaceSon(*okres, index_syna).data_ = udaj;
							}
							index_syna++;
						}
					}
				}
				file.close();
			}
		}
	}

	/*
	 * Metóda používaná len pri 3. úrovni SP.
	 * Naèíta údaje zo zvoleného súboru a naèíta ich do tabulky.
	 * Vracia tabulku naplnenu naèítanými hodnotami údajov.
	 */
	void read_files(ds::adt::SortedSequenceTable<std::string, Udaj>* table, const string& path) const
	{
		string postfix[] = {"1", "2", "3", "4", "5"};
		int index_postfix = 0;
		std::fstream file;
		file.open(path, std::ios::in);

		if (file.is_open())
		{
			std::vector<string> row;
			string line, word, sort_number, code, official_title, medium_title, short_title, note;

			while (std::getline(file, line))
			{
				row.clear();
				std::stringstream str(line);

				// Prvy riadok odfiltujeme od zvysku udajov
				if (line.find("sortNumber;code;officialTitle;mediumTitle;shortTitle;note") != -1)  continue;

				while (std::getline(str, word, ';'))
				{
					row.push_back(word);
				}

				// Tu row obsahuje vsetky informacie o danej uzemnej jednotke
				sort_number = row[0];
				code = row[1];
				official_title = row[2];
				medium_title = row[3];
				short_title = row[4];
				if (row.size() == 6) note = row[5]; // FIX kvoli zahraniciu
				else if (row.size() == 5) note = "";

				Udaj udaj(sort_number, code, official_title, medium_title, short_title, note);
				if (table->contains(official_title))
				{
					string official_title_fixed = official_title.append(postfix[index_postfix]);
					while (table->contains(official_title_fixed))
					{
						index_postfix++;
						official_title_fixed = official_title.append(postfix[index_postfix]);
					}
					index_postfix = 0;
				}
				else
				{
					table->insert(official_title, udaj);
				}
			}
		}
		else
		{
			throw std::runtime_error("Could not open input file");
		}
		file.close();
	}
};

