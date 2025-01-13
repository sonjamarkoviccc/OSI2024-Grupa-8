#include <iostream>
#include <string>
#include "UlaznaKartica.h"
#include "Parking.h"
#include "Auto.h"
#include "Konflikt.h"

int main()
{
    // Dobar dan, na parkingu ima X praznih mjesta - Parking.h
    Parking parking(50, "ZONA1");
    // Unesite broj tablice
    UlaznaKartica kartica;
    kartica.setKartica(parking);
    auto auto1 = std::make_shared<Auto>(kartica.getTablica());
    // Ulazak na parking
    parking.parkiraj(50, auto1);
    std::string izlaz;
    // Kada korisnik bude htio izaci unese "da", "1", mozda klikne "Enter"???
    while(izlaz.empty() || izlaz != "Da" || izlaz != "Yes")
    {
        std::cout << "Da li izlazite? (Da/Yes): ";
        std::cin >> izlaz;
    }
    // Hvala na posjeti????? Da li imate nekih zalbi, ako da mozete ih ovdje podnijeti
    std::string zalbe;
    std::cout << "Hvala na posjeti da li imate neke zalbe? (Da/Ne)";
    std::cin >> zalbe;
    if (zalbe == "Da")
    {

    }
    // Obracunava cijenu i pita za nacin placanja
    // Bankarska kartica
    // Mjesecna kartica
    // Invalidska kartica
    return 0;
}