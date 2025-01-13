#include <iostream>
#include <string>
#include "UlaznaKartica.h"
#include "Parking.h"
#include "Auto.h"
#include "Konflikt.h"
#include "Izlaz.h"
#include "PodnosenjeZalbi.h"

int main()
{
    Parking parking(50, "ZONA1");
    PodnosenjeZalbi zalba;

    std::string izbor;

    while (izbor.empty() || izbor != "1" || izbor != "2" || izbor != "0")
    {
        parking.prikazSlobodnih();
        std::cout << "Da li ulazite ili izlazite sa parkinga? ((1) Ulazak/(2) Izlazak): ";
        std::cin >> izbor;

        if (izbor == "1")
        {
            UlaznaKartica kartica;
            kartica.setKartica(parking);
            auto auto1 = std::make_shared<Auto>(kartica.getTablica());
            int slobodnoMjesto = rand() % parking.getSlobodnaMjesta();
            while (!parking.parkiraj(slobodnoMjesto, auto1))
            {
                slobodnoMjesto = rand() % parking.getSlobodnaMjesta();
            }
            kartica.pisiKarticu(slobodnoMjesto);
        }
        else if (izbor == "2")
        {
            Izlaz izlaz("../files/tablice.txt");
            string tablice;
            std::cout << "Molim Vas unesite tablice: ";
            std::cin >> tablice;
            izlaz.pretraziTablicu(tablice, parking);
            std::string odgovor;
            std::cout << "Da li imate ikakvih zalbi? (Da/Ne): ";
            if (odgovor == "Da")
            {
                zalba.unesiZalbu();
            }
        }
        else if (izbor == "0")
        {
            if (parking.getSlobodnaMjesta() == parking.getUkupnoMjesta())
            {
                std::cout << "Kraj rada parkinga." << std::endl;
                system("pause");
                return 0;
            }
            else {
                std::cout << "Ima jos auta na parkingu, sacekajte jos malo." << std::endl;
            }
        }
        else
        {
            cout << "Nepoznata opcija. Pokusajte ponovo." << endl;
        }
    }
    return 0;
}