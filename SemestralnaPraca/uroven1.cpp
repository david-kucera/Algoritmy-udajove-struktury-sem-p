// ReSharper disable CppClangTidyClangDiagnosticInvalidSourceEncoding
// ReSharper disable CppClangTidyClangDiagnosticInvalidUtf8
#include <iostream>
#include "Windows.h"
#include <libds/heap_monitor.h>

#include "Algoritmus.h"
#include "Input.h"
#include "Udaj.h"

// premenovanie z main ... kvoli novej urovni SP
int spusti1()
{
    // Inicializ�cia heap monitora - na kontrolu �nikov pam�te
    initHeapMonitor();
    /*
    * Pre spr�vne fungovanie diakritiky je potrebn� zahrn�� do projektu 2 riadky k�du ni��ie a zdrojov�mu s�boru nastavi� k�dovanie na ANSI (prek�dova�), napr. v NotePad++.
    */
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);

    std::cout << "==Demon�tr�cia 1. �rovne semestr�lnej pr�ce AUS1.==" << std::endl;

    /*
    * Vo�ba od u��vate�a, ktor� vstupn� s�bor chce pou�i� pre na��tanie.
    * Ak sa zad� nespr�vna vo�ba, automaticky sa na��ta s�bor obce.csv.
    */
    std::cout << "Druh s�boru  1 = kraje   2 = okresy  3 = obce" << std::endl;
    std::cout << "Zvol druh s�boru:";
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

    const char* s = subor.c_str();  // Pretypovanie na const char* kv�li triede Input

    /*
    * Trieda Input preber� s�bor a obsahuje met�du read(), ktor� vracia vector<Udaj>, t.j. v�etky na��tan� �daje z .csv s�boru.
    * D� sa pou�i� len s jedn�m s�borom naraz a v�stup len do nov�ho vectoru.
    */
    constexpr input input;
    std::vector<Udaj> udaje = input.read(s);
    std::vector<Udaj> splnujuce_predikat;

    /*
    * Vo�ba od u��vate�a, ktor� predik�t sa m� pou�i�.
    * Ak sa zad� nespr�vne ��slo, automaticky sa r�ta s predik�tom starts_with_str.
    */
    std::cout << "Typ predik�tu: starts_with_str = 1  contains_str = 2" << std::endl;
    std::cout << "Zvol typ predik�tu:";
    int typ_predikatu;
    std::cin >> typ_predikatu;
    if (typ_predikatu != 1 && typ_predikatu != 2) typ_predikatu = 1;

    std::cout << "Zadaj predik�t:";
    std::string predikat;
    std::cin >> predikat;

    if (typ_predikatu == 1)
    {
        Algoritmus::prehladaj(udaje.begin(), udaje.end(), [predikat](auto udaj)->bool
            {
                return Algoritmus::starts_with_str(udaj, predikat);
            }, [&splnujuce_predikat](const Udaj& udaj)->void
            {
                splnujuce_predikat.push_back(udaj);
            });

    }
    if (typ_predikatu == 2)
    {
        Algoritmus::prehladaj(udaje.begin(), udaje.end(), [predikat](auto udaj)->bool
            {
                return Algoritmus::contains_str(udaj, predikat);
            }, [&splnujuce_predikat](const Udaj& udaj)->void
            {
                splnujuce_predikat.push_back(udaj);
            });
    }

    /*
    * Vyhodnotenie na��tania a predik�tu a n�sledn� v�pis na konzolu.
    */
    if (splnujuce_predikat.empty())
    {
        std::cout << "�iaden �daj nespl�uje zadan� predik�t." << std::endl;
        return 0;
    }

    std::cout << std::endl;
    std::cout << "�daje spl�uj�ce predik�t:" << std::endl;

    const HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE); // Handler pre konzolu
    SetConsoleTextAttribute(h_console, 14);  // �lt� farba p�sma pre v�pis �dajov

    /*
     * V�pis �dajov na konzolu �ltou farbou, ktor� spl�uj� predik�t.
     */
    for (auto& udaj : splnujuce_predikat)
    {
        udaj.print();
    }

    SetConsoleTextAttribute(h_console, 7); // Defaultn� farba p�sma
    std::cout << std::endl;
    std::cout << "Po�et �dajov spl�uj�cich predik�t: " << splnujuce_predikat.size() << std::endl;

    return 0;
}