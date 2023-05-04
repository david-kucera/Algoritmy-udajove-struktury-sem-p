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
	 * Met�da pou��van� len pri 1. �rovni SP.
	 * Na��ta �daje zo zvolen�ho s�boru a na��ta ich do vectora.
	 * Vracia vector naplnen� na��tan�mi hodnotami �dajov.
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
	 * Met�da pou��van� pri 2. �rovni SP.
	 * Ako parameter preber� dan� hierarchiu a adresy vstupn�ch s�borov.
	 * Ka�d� s�bor prejde pr�ve raz a do hierarchie zapisuje na��tan� �daje.
	 */
	void read_files(ds::amt::MultiWayExplicitHierarchy<Udaj>* hierarchy, std::string* paths) const
	{
		for (int index_of_input_file = 0; index_of_input_file < 3; ++index_of_input_file)
		{
			std::fstream file;
			file.open(paths[index_of_input_file], std::ios::in);

			// Ka�d� s�bor sa pre��ta pr�ve raz
			if (file.is_open())
			{
				std::vector<string> row;
				string line, word, sort_number, code, official_title, medium_title, short_title, note;

				// Indexujem v�dy od 0
				size_t index_syna = 0;
				size_t index_kraju = 0;
				size_t index_okresu = 0;
				ds::amt::MultiWayExplicitHierarchyBlock<Udaj>* kraj = hierarchy->accessRoot();
				ds::amt::MultiWayExplicitHierarchyBlock<Udaj>* okres = hierarchy->accessRoot();

				while (std::getline(file, line))
				{
					row.clear();
					std::stringstream str(line);

					// Prv� riadok odfiltujem od zvy�ku �dajov
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

					// �prava �dajov pre zahrani�ie - kraj
					

					Udaj udaj(sort_number, code, official_title, medium_title, short_title, note);

					// -------------------------
					// KRAJE
					// -------------------------

					if (index_of_input_file == 0) 
					{
						// Kraje maj� ako parenta Slovensko,- �i�e kore� hierarchie.
						hierarchy->emplaceSon(*hierarchy->accessRoot(), index_syna).data_ = udaj;		
						index_syna++;
					}

					// -------------------------
					// OKRESY a OBCE
					// -------------------------

					// Zmena �dajov v .csv s�boroch pre posledn� �daje - "zahrani�ie" - aby boli korektne rozdelen� na kraje,okresy a obce

					else
					{
						kraj = hierarchy->accessSon(*hierarchy->accessRoot(), index_kraju);

						// Okres patr� kraju pr�ve vtedy, ak substring za poslednou '-' v note kraja sa zhoduje so za�iatkom code-u okresu
						string note_kraja = kraj->data_.get_note();
						size_t index_last_dash = note_kraja.find_last_of('-');	 // Z�skam index posledn�ho '-'

						// Tu sa spolieha na to, �e nasleduj�ce �daje bu� spadaj� pod rovnak� kraj/okres
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

								// Obec patr� okresu pr�ve vtedy, ak code obce sa za��na code-om okresu
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
						// alebo patria �al�iemu kraju/okresu v porad�
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
	 * Met�da pou��van� len pri 3. �rovni SP.
	 * Na��ta �daje zo zvolen�ho s�boru a na��ta ich do tabulky.
	 * Vracia tabulku naplnenu na��tan�mi hodnotami �dajov.
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

