#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Auto.h"

class Parking
{
private:
    int ukupnoMjesta;
    int slobodnaMjesta;
    std::vector<std::shared_ptr<Auto>> parkingMjesta;

public:
    Parking(int ukupnoMjesta)
        : ukupnoMjesta(ukupnoMjesta), slobodnaMjesta(ukupnoMjesta), parkingMjesta(ukupnoMjesta, nullptr) {}

    bool parkiraj(int brojMjesta, const std::shared_ptr<Auto> &autoPtr)
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

    bool isparkiraj(int brojMjesta)
    {
        if (brojMjesta < 0 || brojMjesta >= ukupnoMjesta)
        {
            std::cout << "Nevalidan broj parking mjesta" << std::endl;
            return false;
        }

        if (parkingMjesta[brojMjesta] == nullptr)
        {
            std::cout << "Mjesto " << brojMjesta << "je vec slobodno." << std::endl;
            return false;
        }
        parkingMjesta[brojMjesta] = nullptr;
        slobodnaMjesta++;
        std::cout << "Vozilo sa registracijom " << parkingMjesta[brojMjesta]->getRegistracija()
                  << " je isparkirano sa mjesta " << brojMjesta << std::endl;
        return true;
    }

    void prikazSlobodnih() const
    {
        std::cout << "Slobodnih mjesta: " << slobodnaMjesta << std::endl;

        for (int i = 0; i < ukupnoMjesta; i++)
        {
            if (parkingMjesta[i] == nullptr)
            {
                std::cout << "Mjesto " << i << " : slobodno" << std::endl;
            }
            else
            {
                std::cout << "Mjesto " << i << ": Zauzeto (Registracija: " << parkingMjesta[i]->getRegistracija()
                          << ")" << std::endl;
            }
        }
    }
};