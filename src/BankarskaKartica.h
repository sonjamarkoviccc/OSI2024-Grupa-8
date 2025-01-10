#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>

class BankarskaKartica
{
    private:
        std::string idKartice;
        std::string Ime;
        std::string Prezime;
        double stanje;

    public:
        BankarskaKartica() = default;

        const std::string& getIdKartice() const {
            return idKartice;
        }

        double getStanje() const {
            return stanje;
        }

        bool jeValidna() const
        {
            if (idKartice.empty()) {
                return false;
            }
            for (char c : idKartice) {
                if (!isdigit(c)) {
                    return false;
                }
            }
            return true;
        }

        bool imaRacun(std::string id)
        {
            if (id.substr(0,2) == "02")
            {
                std::ifstream file("../files/Banka1.txt");
                if (!file)
                {
                    std::cerr << "Greška prilikom otvaranja fajla.\n";
                    return;
                }

                while (file >> idKartice >> Ime >> Prezime >> stanje)
                {
                    if (idKartice == id)
                    return 1;
                }
            }

            if (id.substr(0,2) == "32")
            {
                std::ifstream file("../files/Banka2.txt");
                if (!file)
                {
                    std::cerr << "Greška prilikom otvaranja fajla.\n";
                    return;
                }

                while (file >> idKartice >> Ime >> Prezime >> stanje)
                {
                    if (idKartice == id)
                    return 1;
                }
            }

            return 0;
        }

        void placanje(double iznos)
        {
            if (stanje >= iznos)
            {
                stanje -= iznos;
            }
            else
            {
                std::cout << "Nemate dovoljno na stanju.\n" << std::endl;
            }
        }
};