#pragma once
#include <cstdio>
#include <string>
#include "Nalog.h"
#include "UpravljanjeNalozima.h"
#include "MjesecnaKartica.h"
#include "InvalidskaKartica.h"
#include "Izvjestaj.h"
#include "CjenovnikParkinga.h"

class Uprava
{
private:
    UpravljanjeNalozima upravljanjeNalozima;

public:
    Uprava() {}
    ~Uprava() {}

    void definisanjeCjenovnika(CjenovnikParkinga& cenovnik)
    {
         int izbor;
        do {
            cenovnik.prikaziMeni();
            std::cin >> izbor;
            std::cin.ignore();

            if (izbor == 1) {
                std::string zona, dan, vrijeme, cijena;
                std::cout << "Unesite zonu: ";
                std::getline(std::cin, zona);
                std::cout << "Unesite dan (radni, vikend, praznik): ";
                std::getline(std::cin, dan);
                std::cout << "Unesite vrijeme (u formatu HH:MM:SS): ";
                std::getline(std::cin, vrijeme);  
                std::cout << "Unesite cijenu: ";
                std::getline(std::cin, cijena);

                cenovnik.postaviCijenu(zona, dan, vrijeme, cijena);

            } else if (izbor == 2) {
                std::string zona, dan, vrijeme;
                std::cout << "Unesite zonu: ";
                std::getline(std::cin, zona);
                std::cout << "Unesite dan (radni, vikend, praznik): ";
                std::getline(std::cin, dan);
                std::cout << "Unesite vrijeme (u formatu HH:MM:SS): ";
                std::getline(std::cin, vrijeme);

                cenovnik.nadjiCijenu(zona, dan, vrijeme);

            } else if (izbor != 3) {
                std::cout << "Nepoznata opcija.\n";
            }
        } while (izbor != 3);
    }
    void izvjestajORadu(Izvjestaj& izvestaj){
    int opcija;
    do {
        izvestaj.prikaziMeni();
        std::cin >> opcija;

        switch (opcija) {
            case 1: {
                std::string datum;
                std::cout << "Unesite datum (DD.MM.YYYY): ";
                std::cin >> datum;
                izvestaj.generisiDnevniIzvjestaj(datum);
                break;
            }
            case 2: {
                std::string startDatum, endDatum;
                std::cout << "Unesite pocetni datum (DD.MM.YYYY): ";
                std::cin >> startDatum;
                std::cout << "Unesite krajnji datum (DD.MM.YYYY): ";
                std::cin >> endDatum;
                izvestaj.generisiNedeljniIzvjestaj(startDatum, endDatum);
                break;
            }
            case 3: {
                int mjesec, godina;
                std::cout << "Unesite mjesec (1-12): ";
                std::cin >> mjesec;
                std::cout << "Unesite godinu (YYYY): ";
                std::cin >> godina;
                izvestaj.generisiMjesecniIzvjestaj(mjesec, godina);
                break;
            }
            case 4:
                std::cout << "Izlaz...\n";
                break;
            default:
                std::cout << "Nepoznata opcija. Pokusajte ponovo.\n";
                break;
        }
    } while (opcija != 4);
}

    void izdavanjeMjesecneKarte(MjesecnaKartica& mjesecna)
    {
        mjesecna.izdajaKartice();
        std::cout << "Uspjesno izdata mjesecna kartica.\n" << "Ime: " << mjesecna.getIme() << "\n"
                  << "Prezime: " << mjesecna.getPrezime() << "\n" << "Datum Izdaje: " << mjesecna.getDatumIzdaje() << "\n"
                  << "Datum Isteka: " << mjesecna.getDatumIsteka() << std::endl;
    }
    void izdavanjeInvalidskeKarte(InvalidskaKartica& invalidska)
    {
        invalidska.izdajaKartice();
        std::cout << "Uspjesno izdata invalidska kartica.\n" << "Ime: " << invalidska.getIme() << "\n"
                  << "Prezime: " << invalidska.getPrezime() << "\n" << "Datum Izdaje: " << invalidska.getDatumIzdaje() << std::endl;
    }
    void upravljanjeNalozimaOpcije(const char *fajl);
    void prijava(const char *fajl);
    void prikaziMogucnostiUprave();
};
