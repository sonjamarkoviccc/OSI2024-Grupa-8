#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "Parking.h"

class UlaznaKartica {
private:
    std::string tablica;
    std::string pocetnoVrijeme;
    std::string zona;
    std::string dan;
    int parkingMjesto;

public:
    UlaznaKartica() : parkingMjesto(-1) {};
    ~UlaznaKartica() = default;

    void setKartica(const Parking& p)
    {
        while (tablica.empty())
        {
            std::cout << "Unesite tablicu: ";
            std::cin >> tablica;

            bool valid = true;
            for (char ch : tablica)
            {
                if (!(isdigit(ch) || isalpha(ch) || ch == '-'))
                {
                    valid = false;
                    break;
                }
            }

            if (!valid)
            {
                std::cout << "Tablica moze sadrzavati samo slova, brojeve ili '-'! Pokusajte ponovno.\n";
                tablica.clear();
            }
        }

        time_t vrijeme = time(nullptr);
        struct tm datetime = *localtime(&vrijeme);
        char vr[10];
        strftime(vr, sizeof(vr), "%H:%M:%S", &datetime);
        pocetnoVrijeme = vr;

        zona = p.getZona();

        char d[5];
        strftime(d, sizeof(d), "%a", &datetime);
        dan = d;
    }

    void pisiKarticu(int mjesto)
    {
        parkingMjesto = mjesto;
        std::ofstream spisakTablica("../files/tablice.txt", std::ios::app);
        if (!spisakTablica) {
            std::cerr << "Greska pri otvaranju datoteke." << std::endl;
            return;
        }
        spisakTablica << tablica << " " << zona << " " << dan << " " << pocetnoVrijeme << " " << parkingMjesto << "\n";
    }

    std::string getTablica() const { return tablica; }
    std::string getPocetnoVrijeme() const { return pocetnoVrijeme; }
    std::string getDan() const { return dan; }
    std::string getZona() const { return zona; }
};