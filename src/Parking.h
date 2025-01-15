#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Auto.h"

class Parking
{
private:
    int ukupnoMjesta;
    int slobodnaMjesta;
    std:: string parkingZona;
    std::vector<std::shared_ptr<Auto>> parkingMjesta;

public:
    Parking(int ukupnoMjesta, std::string parkingZona)
        : ukupnoMjesta(ukupnoMjesta), parkingZona(parkingZona),  slobodnaMjesta(ukupnoMjesta), parkingMjesta(ukupnoMjesta, nullptr) {}

    bool parkiraj(int brojMjesta, std::shared_ptr<Auto> &autoPtr)
    {
        if (brojMjesta < 0 || brojMjesta >= ukupnoMjesta)
        {
            std::cout << "Nevalidan broj parking mjesta" << std::endl;
            return false;
        }

        if (parkingMjesta[brojMjesta] != nullptr)
        {
            std::cout << "Mjesto " << brojMjesta << "je vec zauzeto." << std::endl;
            return false;
        }
        parkingMjesta[brojMjesta] = autoPtr;
        slobodnaMjesta--;
        std::cout << "Vozilo sa registracijom " << autoPtr->getRegistracija()
                  << " je parkirano na mjesto " << brojMjesta << std::endl;
        return true;
    }

    bool isparkiraj(int mjesto, std::string registracija)
    {
        if (mjesto < 0 || mjesto >= ukupnoMjesta)
        {
            std::cout << "Nevalidan broj parking mjesta" << std::endl;
            return false;
        }

        if (parkingMjesta[mjesto] == nullptr)
        {
            std::cout << "Mjesto " << mjesto << "je vec slobodno." << std::endl;
            return false;
        }
        parkingMjesta[mjesto] = nullptr;
        slobodnaMjesta++;
        std::cout << "Vozilo sa registracijom " << registracija
                  << " je isparkirano sa mjesta " << mjesto << std::endl;
        return true;
    }

    void prikazSlobodnih() const
    {
        std::ifstream inFile("../files/parking.txt");

        if (!inFile) {
            std::cerr << "Greska prilikom otvaranja fajla.\n";
            return;
        }

        std::string line;

        while (std::getline(inFile, line)) {
            std::cout << line << std::endl;
        }

        inFile.close();
    }

    std::string getZona() const { return parkingZona; }
    int getSlobodnaMjesta() const { return slobodnaMjesta; }
    int getUkupnoMjesta() const { return ukupnoMjesta; }
};