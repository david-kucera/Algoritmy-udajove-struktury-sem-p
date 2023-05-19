#pragma once
#include <conio.h>
#include <iostream>
#include "Windows.h"
#include "Algoritmus.h"
#include "Input.h"
#include "Udaj.h"
#include "Uroven4.h"

#define VYMAZ system("cls") // makro pre vyèistenie obrazovky

class uroven1
{
public:
	static void spusti_uroven()
	{
        VYMAZ;
        /*
		* Vo¾ba od uívate¾a, ktorı vstupnı súbor chce poui pre naèítanie.
		* Ak sa zadá nesprávna vo¾ba, automaticky sa naèíta súbor obce.csv.
		*/
        std::cout << "Druh súboru  1 = kraje   2 = okresy  3 = obce" << std::endl;
        std::cout << "Zvol druh súboru:";
        int type_subor;
        std::cin >> type_subor;

        std::string subor;
        switch (type_subor)
        {
        case 1:
            subor = "kraje.csv";
            break;
        case 2:
            subor = "okresy.csv";
            break;
        default:
            subor = "obce.csv";
            break;
        }

        const char* s = subor.c_str();  // Pretypovanie na const char* kvôli triede Input

        /*
		* Trieda Input preberá súbor a obsahuje metódu read(), ktorá vracia ImplicitSequence<Udaj>, t.j. všetky naèítané údaje z .csv súboru.
		* Dá sa poui len s jednım súborom naraz a vıstup len do novej implicitnej sekvencie.
		*/
        constexpr input input;
        ds::amt::ImplicitSequence<Udaj> udaje = input.read(s);
        ds::amt::ImplicitSequence<Udaj> splnujuce_predikat;

        /*
        * Vo¾ba od uívate¾a, ktorı predikát sa má poui.
        * Ak sa zadá nesprávne èíslo, automaticky sa ráta s predikátom starts_with_str.
        */
        std::cout << "Typ predikátu: starts_with_str = 1  contains_str = 2" << std::endl;
        std::cout << "Zvol typ predikátu:";
        int typ_predikatu;
        std::cin >> typ_predikatu;
        if (typ_predikatu != 1 && typ_predikatu != 2) typ_predikatu = 1;

        std::cout << "Zadaj predikát:";
        std::string predikat;
        std::cin >> predikat;

        if (typ_predikatu == 1)
        {
            Algoritmus::prehladaj(udaje.begin(), udaje.end(), [predikat](auto udaj)->bool
            {
                return Algoritmus::starts_with_str(udaj, predikat);
            }, [&splnujuce_predikat](const Udaj& udaj)->void
            {
                splnujuce_predikat.insertLast().data_ = udaj;
            });

        }
        if (typ_predikatu == 2)
        {
            Algoritmus::prehladaj(udaje.begin(), udaje.end(), [predikat](auto udaj)->bool
            {
                return Algoritmus::contains_str(udaj, predikat);
            }, [&splnujuce_predikat](const Udaj& udaj)->void
            {
                splnujuce_predikat.insertLast().data_ = udaj;
            });
        }

        /*
        * Vyhodnotenie naèítania a predikátu a následnı vıpis na konzolu.
        */
        if (splnujuce_predikat.size() == 0)
        {
            std::cout << "iaden údaj nesplòuje zadanı predikát." << std::endl;
            std::cout << " Stlaè akıko¾vek kláves pre návrat do menu aplikácie." << std::endl;
            auto ch = _getch();
            return;
        }

        std::cout << std::endl;
        std::cout << "Údaje splòujúce predikát:" << std::endl;

        const HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE); // Handler pre konzolu
        SetConsoleTextAttribute(h_console, 14);  // ltá farba písma pre vıpis údajov

        /*
         * Vıpis údajov na konzolu ltou farbou, ktoré splòujú predikát.
         */
        for (auto& udaj : splnujuce_predikat)
        {
            udaj.print();
        }

        SetConsoleTextAttribute(h_console, 7); // Defaultná farba písma
        std::cout << std::endl;
        std::cout << "Poèet údajov splòujúcich predikát: " << splnujuce_predikat.size() << std::endl;

        std::cout << "Chceš sortova vısledky? Stlaè [1] pre áno" << std::endl;
        std::cout << "Stlaè akıko¾vek inı kláves pre návrat do hierarchie." << std::endl;
        int volba;
        std::cin >> volba;
        if (volba == 1)
        {
            uroven4::spusti_uroven(splnujuce_predikat);
            return;
        }


        std::cout << " Stlaè akıko¾vek kláves pre návrat do menu aplikácie." << std::endl;
        auto ch = _getch();
	}
};