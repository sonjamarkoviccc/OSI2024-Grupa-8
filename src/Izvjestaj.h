#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

const int MAX_KORISNIKA = 100; 

struct Korisnik {
    std::string registarskaTablica; // Registarska oznaka korisnika
    double iznos;                   // Iznos zarađen od ovog korisnika
    std::string datum;              // Datum transakcije (u formatu DD MM YYYY)
};

class Izvjestaj {
private:
    Korisnik korisnici[MAX_KORISNIKA]; 
    int brojKorisnika;                   

    bool ValidanDatum(int dan, int mjesec, int godina) const {
        if (mjesec < 1 || mjesec > 12 || dan < 1 || godina < 2000) return false;
        int daniUMjesecu[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if ((godina % 4 == 0 && godina % 100 != 0) || godina % 400 == 0) daniUMjesecu[1] = 29; 
        return dan <= daniUMjesecu[mjesec - 1];
    }

    void ucitajKorisnike() {
        std::ifstream ulazniFajl("bazapodataka.txt");
        if (!ulazniFajl) {
            std::cerr << "Greska prilikom otvaranja fajla.\n";
            return;
        }
        
        /*
        Podaci potrebni za izvjestaj se nalaze u datoteci formata:
        
        BRTABLICA CENAPARKINGA DAN MJESEC GODINA
        :
        :
        */

        brojKorisnika = 0;
        while (ulazniFajl >> korisnici[brojKorisnika].registarskaTablica >> korisnici[brojKorisnika].iznos) {
            std::string dan, mjesec, godina;
            ulazniFajl >> dan >> mjesec >> godina;
            korisnici[brojKorisnika].datum = dan + " " + mjesec + " " + godina;
            brojKorisnika++;
            if (brojKorisnika >= MAX_KORISNIKA) break;
        }
        std::cout << "Korisnici uspješno ucitani.\n";
    }

    double zbirZarada(const std::string& tablica, const std::string& startDatum, const std::string& endDatum) const {
        double total = 0.0;
        for (int i = 0; i < brojKorisnika; ++i) {
            if (korisnici[i].registarskaTablica == tablica && korisnici[i].datum >= startDatum && korisnici[i].datum <= endDatum) {
                total += korisnici[i].iznos;
            }
        }
        return total;
    }

    bool tablicaVecPostoji(const std::string& tablica, const std::string pregledane[], int brojPregledanih) const {
        for (int i = 0; i < brojPregledanih; ++i) {
            if (pregledane[i] == tablica) {
                return true;
            }
        }
        return false;
    }

    void sacuvajIzvjestajUFajl(const std::string& naslov, int brojKorisnika, double ukupnaZarada) const {
        std::ofstream izvjestajFajl("izvjestaj.txt");
        if (!izvjestajFajl) {
            std::cerr << "Greška prilikom otvaranja fajla za pisanje.\n";
            return;
        }
        izvjestajFajl << naslov << "\n"
                     << "Ukupan broj korisnika: " << brojKorisnika << "\n"
                     << "Ukupna zarada: " << ukupnaZarada << " KM\n\n";
    }

public:
    Izvjestaj() : brojKorisnika(0) {
        ucitajKorisnike();
    }

    void generisiDnevniIzvjestaj(int dan, int mjesec, int godina) const {
        if (!ValidanDatum(dan, mjesec, godina)) {
            std::cerr << "Neispravan datum.\n";
            return;
        }

        std::string pregledaneTablice[MAX_KORISNIKA];
        int brojPregledanih = 0;
        double ukupnaZarada = 0.0;

        std::string datum = (dan < 10 ? "0" : "") + std::to_string(dan) + " " + (mjesec < 10 ? "0" : "") + std::to_string(mjesec) + " " + std::to_string(godina);

        for (int i = 0; i < brojKorisnika; ++i) {
            if (!tablicaVecPostoji(korisnici[i].registarskaTablica, pregledaneTablice, brojPregledanih)) {
                if (korisnici[i].datum == datum) {
                    pregledaneTablice[brojPregledanih++] = korisnici[i].registarskaTablica;
                    ukupnaZarada += korisnici[i].iznos;
                }
            }
        }

        std::string naslov = "Izvjestaj za datum: " + datum;
        std::cout << naslov << "\n"
                  << "Ukupan broj korisnika: " << brojPregledanih << "\n"
                  << "Ukupna zarada: " << ukupnaZarada << " KM\n";

        sacuvajIzvjestajUFajl(naslov, brojPregledanih, ukupnaZarada);
    }

    void generisiNedeljniIzvjestaj(int nedelja, int godina) const {
        struct tm startDate = {};
        startDate.tm_year = godina - 2000;
        startDate.tm_mday = (nedelja - 1) * 7 + 1;
        startDate.tm_mon = 0; 
        mktime(&startDate);

        char buffer[11];
        strftime(buffer, sizeof(buffer), "%d %m %Y", &startDate);
        std::string startDatum = buffer;

        struct tm endDate = startDate;
        endDate.tm_mday += 6;
        mktime(&endDate);
        strftime(buffer, sizeof(buffer), "%d %m %Y", &endDate);
        std::string endDatum = buffer;

        std::string pregledaneTablice[MAX_KORISNIKA];
        int brojPregledanih = 0;
        double ukupnaZarada = 0.0;

        for (int i = 0; i < brojKorisnika; ++i) {
            if (!tablicaVecPostoji(korisnici[i].registarskaTablica, pregledaneTablice, brojPregledanih)) {
                if (korisnici[i].datum >= startDatum && korisnici[i].datum <= endDatum) {
                    pregledaneTablice[brojPregledanih++] = korisnici[i].registarskaTablica;
                    ukupnaZarada += korisnici[i].iznos;
                }
            }
        }

        std::string naslov = "Izvjestaj za nedelju: " + std::to_string(nedelja) + ", godina: " + std::to_string(godina);
        std::cout << naslov << "\n"
                  << "Ukupan broj korisnika: " << brojPregledanih << "\n"
                  << "Ukupna zarada: " << ukupnaZarada << " KM\n";

        sacuvajIzvjestajUFajl(naslov, brojPregledanih, ukupnaZarada);
    }

    void generisiMjesecniIzvjestaj(int mjesec, int godina) const {
        std::string pregledaneTablice[MAX_KORISNIKA];
        int brojPregledanih = 0;
        double ukupnaZarada = 0.0;

        for (int i = 0; i < brojKorisnika; ++i) {
            int d, m, y;
            sscanf(korisnici[i].datum.c_str(), "%d %d %d", &d, &m, &y);
            if (m == mjesec && y == godina && !tablicaVecPostoji(korisnici[i].registarskaTablica, pregledaneTablice, brojPregledanih)) {
                pregledaneTablice[brojPregledanih++] = korisnici[i].registarskaTablica;
                ukupnaZarada += korisnici[i].iznos;
            }
        }

        std::string naslov = "Izvjestaj za mesec: " + std::to_string(mjesec) + ", godina: " + std::to_string(godina);
        std::cout << naslov << "\n"
                  << "Ukupan broj korisnika: " << brojPregledanih << "\n"
                  << "Ukupna zarada: " << ukupnaZarada << " KM\n";

        sacuvajIzvjestajUFajl(naslov, brojPregledanih, ukupnaZarada);
    }

    void prikaziMeni() const {
        std::cout << "\n--- Izvjestaji ---\n"
                  << "1. Dnevni izvjestaj\n"
                  << "2. Nedeljni izvjestaj\n"
                  << "3. Mjesecni izvjestaj\n"
                  << "4. Izlaz\n"
                  << "Izaberite opciju: ";
    }

    void pokreniProgram() {
        int izbor;
        do {
            prikaziMeni();
            std::cin >> izbor;

            if (izbor == 1) {
                int dan, mjesec, godina;
                std::cout << "Unesite datum (DD MM YYYY): ";
                std::cin >> dan >> mjesec >> godina;
                generisiDnevniIzvjestaj(dan, mjesec, godina);
            } else if (izbor == 2) {
                int nedelja, godina;
                std::cout << "Unesite nedelju i godinu (WW YYYY): ";
                std::cin >> nedelja >> godina;
                generisiNedeljniIzvjestaj(nedelja, godina);
            } else if (izbor == 3) {
                int mjesec, godina;
                std::cout << "Unesite mjesec i godinu (MM YYYY): ";
                std::cin >> mjesec >> godina;
                generisiMjesecniIzvjestaj(mjesec, godina);
            } else if (izbor != 4) {
                std::cout << "Nepoznata opcija.\n";
            }
        } while (izbor != 4);
    }
};

