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

    std::string sedamDanaKasnije(const std::string& date_str)
    {
        std::tm date = {};
        std::istringstream ss(date_str);
        ss >> std::get_time(&date, "%d.%m.%Y");
        
        if (ss.fail()) {
            throw std::invalid_argument("Nije validan datum");
        }

        std::time_t time = std::mktime(&date);
        time += 7 * 24 * 60 * 60;

        std::tm* new_date = std::localtime(&time);
        std::ostringstream os;
        os << std::put_time(new_date, "%d.%m.%Y");
        return os.str();
    }


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
                std::cout << "Unesite dan (radni, vikend): ";
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
                std::cout << "Unesite dan (radni, vikend): ";
                std::getline(std::cin, dan);
                std::cout << "Unesite vrijeme (u formatu HH:MM:SS): ";
                std::getline(std::cin, vrijeme);

                cenovnik.nadjiCijenu(zona, dan, vrijeme);
            } else if (izbor == 3){
                cenovnik.azurirajCijenu();
            } else if (izbor != 4) {
                std::cout << "Nepoznata opcija.\n";
            }
        } while (izbor != 4);
    }
    void izvjestajORadu(Izvjestaj& izvestaj)
    {
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
                    endDatum = sedamDanaKasnije(startDatum);
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
    void upravljanjeNalozimaOpcije(const char *fajl)
    {
        upravljanjeNalozima.prikaziMeni(fajl);
    }

    int prikaziMogucnostiUprave()
    {
        int izbor;
        const char *fajl = "../files/korisnici.txt";
        do
        {
            printf("\n1. Definisanje cjenovnika\n");
            printf("2. Dobijanje izvestaja o radu parkinga\n");
            printf("3. Izdavanje mjesecne karte\n");
            printf("4. Izdavanje invalidske karte\n");
            printf("5. Upravljanje nalozima\n");
            printf("6. Odjava\n");
            printf("7. Izlazak iz programa\n");

            printf("Izaberite opciju: ");
            scanf("%d", &izbor);

            switch (izbor)
            {
            case 1: {
                CjenovnikParkinga cenovnik;
                definisanjeCjenovnika(cenovnik);
                break;
            }    
            case 2: {
                Izvjestaj izvestaj;
                izvjestajORadu(izvestaj);
                break;
            }  
            case 3: {
                MjesecnaKartica mk;
                izdavanjeMjesecneKarte(mk);
                break;
            }
            case 4: {
                InvalidskaKartica ik;
                izdavanjeInvalidskeKarte(ik);
                break;
            }
            case 5:
                upravljanjeNalozimaOpcije(fajl);
                break;
            case 6:
                char confirm;
                printf("Da li ste sigurni da zelite da se odjavite? (y/n): ");
                scanf(" %c", &confirm);
                if (confirm == 'y' || confirm == 'Y')
                {
                    printf("Odjava uspjesna. Ponovno prijavljivanje.\n");
                    izbor = 0;
                }
                break;
            case 7:
                return 0;
            default:
                printf("Nepostojeca opcija!\n");
                break;
            }
        } while (izbor != 0);
        return 1;
    }
};
