#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

class UlaznaKartica {
private:
    std::string tablica;
    std::string pocetnoVrijeme;
    std::string zona;
    std::string dan;

public:
    UlaznaKartica() = default;
    ~UlaznaKartica() = default;

    void setKartica()
    {
        std::cout << "Unesite tablicu: ";
        std::cin >> tablica;

        time_t vrijeme = time(nullptr);
        struct tm datetime = *localtime(&vrijeme);
        char vr[10];
        strftime(vr, sizeof(vr), "%H:%M:%S", &datetime);
        pocetnoVrijeme = vr;

        std::cout << "Unesite zonu: ";
        std::cin >> zona;

        char d[5];
        strftime(d, sizeof(d), "%a", &datetime);
        dan = d;

        std::ofstream spisakTablica("../files/tablice.txt", std::ios::app);
        if (!spisakTablica) {
            std::cerr << "Greska pri otvaranju datoteke." << std::endl;
            return;
        }
        spisakTablica << tablica << " " << zona << " " << dan << " " << pocetnoVrijeme << "\n";
    }

    std::string getTablica() const { return tablica; }
    std::string getPocetnoVrijeme() const { return pocetnoVrijeme; }
    std::string getDan() const { return dan; }
    std::string getZona() const { return zona; }
};