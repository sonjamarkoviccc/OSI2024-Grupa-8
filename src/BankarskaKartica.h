#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iomanip>

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
                    exit(EXIT_FAILURE);
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
                    exit(EXIT_FAILURE);
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
                std::string fileName = (idKartice.substr(0, 2) == "02") ? "../files/Banka1.txt" : "../files/Banka2.txt";

                std::ifstream inputFile(fileName);
                if (!inputFile)
                {
                    std::cerr << "Greška prilikom otvaranja fajla za čitanje.\n";
                    exit(EXIT_FAILURE);
                }

                std::ofstream tempFile("../files/temp.txt");
                if (!tempFile)
                {
                    std::cerr << "Greška prilikom otvaranja fajla za pisanje.\n";
                    exit(EXIT_FAILURE);
                }

                std::string fileIdKartice, fileIme, filePrezime;
                double fileStanje;
                while (inputFile >> fileIdKartice >> fileIme >> filePrezime >> fileStanje)
                {
                    if (fileIdKartice == idKartice)
                    {
                        fileStanje = stanje;
                    }
                    tempFile << fileIdKartice << " " << fileIme << " " << filePrezime << " " << fileStanje << "\n";
                }

                inputFile.close();
                tempFile.close();

                if (remove(fileName.c_str()) != 0 || rename("../files/temp.txt", fileName.c_str()) != 0)
                {
                    std::cerr << "Greška prilikom ažuriranja fajla.\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                std::cout << "Nemate dovoljno na stanju.\n";
            }

        }
};