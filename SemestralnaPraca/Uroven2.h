#pragma once

#define VYMAZ system("cls") // makro pre vyèistenie obrazovky

class uroven2
{
public:
	static void spusti_uroven()
	{
        VYMAZ;

        // Vytvorenie hierarchie s pomyselným koreòom Slovenskom
        ds::amt::MultiWayExplicitHierarchy<Udaj> hierarchy{};
        // Nezadany-prazdny kod kvoli metode hasType v triede Algoritmus ... 
        hierarchy.emplaceRoot().data_ = Udaj("0", "", "Slovensko", "Slovensko", "Slovensko", "SK0");

        // Pole adries pre naèítanie triedou Input
        const auto paths = new std::string[3];
        paths[0] = "kraje.csv";
        paths[1] = "okresy.csv";
        paths[2] = "obce.csv";

        // Trieda Input naèíta všetky údaje do pomyselnej hierarchie Slovenska, t.j. koreò je Slovensko, jej synovia sú kraje - ich synovia okresy - a ich synovia obce.
        constexpr Input input;
        input.read_files(&hierarchy, paths);
        delete[] paths;

        //Prehliadka hierarchiou ... zaèíname na koreni hierarchie
        ds::amt::MultiWayExplicitHierarchyBlock<Udaj>* current_node = (&hierarchy)->accessRoot();

        int option, index;
        std::cout << "Aktuálny vrchol: " << current_node->data_.get_official_title() << std::endl;
        for (int i = 0; i < current_node->sons_->size(); ++i)
        {
            std::cout << "[" << i << "]" << current_node->sons_->access(i)->data_->data_.get_official_title() << std::endl;
        }
        std::cout << "Zvo¾ operáciu: " << std::endl;
        std::cout << "\t[1] - Presuò sa na nadradenú jednotku. " << std::endl;
        std::cout << "\t[2] - Presuò sa na podradenú jednotku. " << std::endl;
        std::cout << "\t[3] - Prejdi podradené prvou úrovòou. " << std::endl;
        std::cout << std::endl;
        std::cout << "\t[0] - Ukonèi program. " << std::endl;
        std::cout << "Vo¾ba: ";
        std::cin >> option;

        while (option != 0)
        {
            switch (option)
            {
            case 1:
                // Ak existuje parent, tak ho sprístupním, ak nie, opakujem vo¾bu
                if (current_node->parent_ != nullptr) current_node = hierarchy.accessParent(*current_node);
                VYMAZ;
                std::cout << "Aktuálny vrchol: " << current_node->data_.get_official_title() << std::endl;
                for (int i = 0; i < current_node->sons_->size(); ++i)
                {
                    std::cout << "[" << i << "]" << current_node->sons_->access(i)->data_->data_.get_official_title() << std::endl;
                }
                break;
            case 2:
                if (current_node->sons_->size() != 0)
                {
                    std::cout << "Zadaj index syna, na ktorého sa chceš presunú: ";
                    std::cin >> index;
                    VYMAZ;
                    current_node = hierarchy.accessSon(*current_node, index);
                }
                std::cout << "Aktuálny vrchol: " << current_node->data_.get_official_title() << std::endl;
                for (int i = 0; i < current_node->sons_->size(); ++i)
                {
                    std::cout << "[" << i << "]" << current_node->sons_->access(i)->data_->data_.get_official_title() << std::endl;
                }
                break;
            case 3:
                VYMAZ;
                // Prejdenie prvou úrovòou SP
                Algoritmus alg;

                std::cout << "Typ predikátu: starts_with_str = 1 [string]  contains_str = 2 [string]  has_type = 3 [kraj/okres/obec]" << std::endl;

                std::cout << "Zvo¾ typ predikátu: ";
                int typ_predikatu;
                std::cin >> typ_predikatu;

                std::cout << "Zvo¾ predikát: ";
                string predikat;
                std::cin >> predikat;

                VYMAZ;

                // Nastavím si iterátor zaèiatku
                const ds::amt::MultiWayExplicitHierarchy<Udaj>::PreOrderHierarchyIterator begin(&hierarchy, current_node);

                int pocet_splnujucich_predikat = 0;
                const HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE); // Handler pre konzolu
                SetConsoleTextAttribute(h_console, 14);  // Žltá farba písma pre výpis údajov

                // Podla typu predikátu vykonám potrebné operácie
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

                SetConsoleTextAttribute(h_console, 7); // Defaultná farba písma

                std::cout << "Poèet údajov splòujúcich predikát je: ";
                SetConsoleTextAttribute(h_console, 12);  // Èervená farba písma pre výpis poètu
                std::cout << pocet_splnujucich_predikat << std::endl;
                SetConsoleTextAttribute(h_console, 7); // Defaultná farba písma

                break;
            }

            std::cout << "Zvo¾ operáciu: " << std::endl;
            std::cout << "\t[1] - Presuò sa na nadradenú jednotku. " << std::endl;
            std::cout << "\t[2] - Presuò sa na podradenú jednotku. " << std::endl;
            std::cout << "\t[3] - Prejdi podradené prvou úrovòou. " << std::endl;
            std::cout << std::endl;
            std::cout << "\t[0] - Ukonèi program. " << std::endl;
            std::cout << "Vo¾ba: ";
            std::cin >> option;
        }

        // Vymazanie hierarchie
        hierarchy.clear();

		std::cout << " Stlaè akýko¾vek kláves pre návrat do menu aplikácie." << std::endl;
		auto ch = _getch();
	}
};