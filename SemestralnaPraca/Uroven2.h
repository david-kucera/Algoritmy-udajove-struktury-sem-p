#pragma once

#define VYMAZ system("cls") // makro pre vy�istenie obrazovky

class uroven2
{
public:
	static void spusti_uroven()
	{
        VYMAZ;

        // Vytvorenie hierarchie s pomyseln�m kore�om Slovenskom
        ds::amt::MultiWayExplicitHierarchy<Udaj> hierarchy{};
        // Nezadany-prazdny kod kvoli metode hasType v triede Algoritmus ... 
        hierarchy.emplaceRoot().data_ = Udaj("0", "", "Slovensko", "Slovensko", "Slovensko", "SK0");

        // Pole adries pre na��tanie triedou Input
        const auto paths = new std::string[3];
        paths[0] = "kraje.csv";
        paths[1] = "okresy.csv";
        paths[2] = "obce.csv";

        // Trieda Input na��ta v�etky �daje do pomyselnej hierarchie Slovenska, t.j. kore� je Slovensko, jej synovia s� kraje - ich synovia okresy - a ich synovia obce.
        constexpr Input input;
        input.read_files(&hierarchy, paths);
        delete[] paths;

        //Prehliadka hierarchiou ... za��name na koreni hierarchie
        ds::amt::MultiWayExplicitHierarchyBlock<Udaj>* current_node = (&hierarchy)->accessRoot();

        int option, index;
        std::cout << "Aktu�lny vrchol: " << current_node->data_.get_official_title() << std::endl;
        for (int i = 0; i < current_node->sons_->size(); ++i)
        {
            std::cout << "[" << i << "]" << current_node->sons_->access(i)->data_->data_.get_official_title() << std::endl;
        }
        std::cout << "Zvo� oper�ciu: " << std::endl;
        std::cout << "\t[1] - Presu� sa na nadraden� jednotku. " << std::endl;
        std::cout << "\t[2] - Presu� sa na podraden� jednotku. " << std::endl;
        std::cout << "\t[3] - Prejdi podraden� prvou �rov�ou. " << std::endl;
        std::cout << std::endl;
        std::cout << "\t[0] - Ukon�i program. " << std::endl;
        std::cout << "Vo�ba: ";
        std::cin >> option;

        while (option != 0)
        {
            switch (option)
            {
            case 1:
                // Ak existuje parent, tak ho spr�stupn�m, ak nie, opakujem vo�bu
                if (current_node->parent_ != nullptr) current_node = hierarchy.accessParent(*current_node);
                VYMAZ;
                std::cout << "Aktu�lny vrchol: " << current_node->data_.get_official_title() << std::endl;
                for (int i = 0; i < current_node->sons_->size(); ++i)
                {
                    std::cout << "[" << i << "]" << current_node->sons_->access(i)->data_->data_.get_official_title() << std::endl;
                }
                break;
            case 2:
                if (current_node->sons_->size() != 0)
                {
                    std::cout << "Zadaj index syna, na ktor�ho sa chce� presun��: ";
                    std::cin >> index;
                    VYMAZ;
                    current_node = hierarchy.accessSon(*current_node, index);
                }
                std::cout << "Aktu�lny vrchol: " << current_node->data_.get_official_title() << std::endl;
                for (int i = 0; i < current_node->sons_->size(); ++i)
                {
                    std::cout << "[" << i << "]" << current_node->sons_->access(i)->data_->data_.get_official_title() << std::endl;
                }
                break;
            case 3:
                VYMAZ;
                // Prejdenie prvou �rov�ou SP
                Algoritmus alg;

                std::cout << "Typ predik�tu: starts_with_str = 1 [string]  contains_str = 2 [string]  has_type = 3 [kraj/okres/obec]" << std::endl;

                std::cout << "Zvo� typ predik�tu: ";
                int typ_predikatu;
                std::cin >> typ_predikatu;

                std::cout << "Zvo� predik�t: ";
                string predikat;
                std::cin >> predikat;

                VYMAZ;

                // Nastav�m si iter�tor za�iatku
                const ds::amt::MultiWayExplicitHierarchy<Udaj>::PreOrderHierarchyIterator begin(&hierarchy, current_node);

                int pocet_splnujucich_predikat = 0;
                const HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE); // Handler pre konzolu
                SetConsoleTextAttribute(h_console, 14);  // �lt� farba p�sma pre v�pis �dajov

                // Podla typu predik�tu vykon�m potrebn� oper�cie
                switch (typ_predikatu)
                {
                case 1:
                    Algoritmus::prehladaj(begin, hierarchy.end(), [predikat, &alg](const Udaj& prehladavane)->bool
                        {
                            return Algoritmus::starts_with_str(prehladavane, predikat);
                        },
                        [&pocet_splnujucich_predikat](const Udaj& udaj)
                        {
                            udaj.print();
                            pocet_splnujucich_predikat++;
                        });
                    break;
                case 2:
                    Algoritmus::prehladaj(begin, hierarchy.end(), [predikat, &alg](const Udaj& prehladavane)->bool
                        {
                            return Algoritmus::contains_str(prehladavane, predikat);
                        },
                        [&pocet_splnujucich_predikat](const Udaj& udaj)
                        {
                            udaj.print();
                            pocet_splnujucich_predikat++;
                        });
                    break;
                case 3:
                    Algoritmus::prehladaj(begin, hierarchy.end(), [predikat, &alg](const Udaj& prehladavane)->bool
                        {
                            return Algoritmus::hasType(prehladavane, predikat);
                        },
                        [&pocet_splnujucich_predikat](const Udaj& udaj)
                        {
                            udaj.print();
                            pocet_splnujucich_predikat++;
                        });
                    break;
                }

                SetConsoleTextAttribute(h_console, 7); // Defaultn� farba p�sma

                std::cout << "Po�et �dajov spl�uj�cich predik�t je: ";
                SetConsoleTextAttribute(h_console, 12);  // �erven� farba p�sma pre v�pis po�tu
                std::cout << pocet_splnujucich_predikat << std::endl;
                SetConsoleTextAttribute(h_console, 7); // Defaultn� farba p�sma

                break;
            }

            std::cout << "Zvo� oper�ciu: " << std::endl;
            std::cout << "\t[1] - Presu� sa na nadraden� jednotku. " << std::endl;
            std::cout << "\t[2] - Presu� sa na podraden� jednotku. " << std::endl;
            std::cout << "\t[3] - Prejdi podraden� prvou �rov�ou. " << std::endl;
            std::cout << std::endl;
            std::cout << "\t[0] - Ukon�i program. " << std::endl;
            std::cout << "Vo�ba: ";
            std::cin >> option;
        }

        // Vymazanie hierarchie
        hierarchy.clear();

		std::cout << " Stla� ak�ko�vek kl�ves pre n�vrat do menu aplik�cie." << std::endl;
		auto ch = _getch();
	}
};