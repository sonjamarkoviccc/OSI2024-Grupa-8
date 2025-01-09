#include <iostream>
#include <fstream>
#include <string>

struct Cjenovnik {
    std::string zona;
    std::string dan;
    std::string vrijeme;
    std::string cijena;
};

class CjenovnikParkinga {
private:
    const std::string ime_fajla = "cjenovnik.txt";
    Cjenovnik* cijene; 
    int kapacitivnost;      
    int velicina;         

    void ucitajIzFajla() {
        std::ifstream ulazniFajl(ime_fajla);
        if (!ulazniFajl) {
            std::cerr << "Greška prilikom otvaranja fajla.\n";
            return;
        }

        while (velicina < kapacitivnost && ulazniFajl >> cijene[velicina].zona >> cijene[velicina].dan >> cijene[velicina].vrijeme >> cijene[velicina].cijena) {
            velicina++;
        }
        
        std::cout << "Cjenovnik uspješno učitan.\n";
    }

    void sacuvajUFajl() const {
        std::ofstream izlazniFajl(ime_fajla);
        if (!izlazniFajl) {
            std::cerr << "Greška prilikom čuvanja u fajl.\n";
            return;
        }

        for (int i = 0; i < velicina; ++i) {
            izlazniFajl << cijene[i].zona << " " << cijene[i].dan << " " << cijene[i].vrijeme << " " << cijene[i].cijena << "\n";
        }
        
        std::cout << "Cjenovnik uspješno sačuvan.\n";
    }

public:
    CjenovnikParkinga() : kapacitivnost(10), velicina(0) {
        cijene = new Cjenovnik[kapacitivnost]; 
        ucitajIzFajla();
    }

    ~CjenovnikParkinga() {
        delete[] cijene; 
    }

    void postaviCijenu(const std::string& zona, const std::string& dan, const std::string& vrijeme, const std::string& cijena) {
        if (velicina >= kapacitivnost) { 
            kapacitivnost *= 2; 
            Cjenovnik* new_cijene = new Cjenovnik[kapacitivnost];
            for (int i = 0; i < velicina; ++i) {
                new_cijene[i] = cijene[i]; 
            }
            delete[] cijene; 
            cijene = new_cijene; 
        }

        cijene[velicina++] = {zona, dan, vrijeme, cijena}; 
        sacuvajUFajl(); 
    }

    void nadjiCijenu(const std::string& zona, const std::string& dan, const std::string& vrijeme) const {
        for (int i = 0; i < velicina; ++i) {
            if (cijene[i].zona == zona && cijene[i].dan == dan && cijene[i].vrijeme == vrijeme) {
                std::cout << "Cijena: " << cijene[i].cijena << "\n";
                return;
            }
        }
        
        std::cout << "Cijena nije pronađena.\n";
    }

    void prikaziMeni() const {
        std::cout << "\n--- Upravljanje cjenovnikom ---\n"
                  << "1. Postavi cijenu\n"
                  << "2. Pronađi cijenu\n"
                  << "3. Izlaz\n"
                  << "Izaberite opciju: ";
    }

    void pokreniProgram() {
        int izbor;
        do {
            prikaziMeni();
            std::cin >> izbor;
            std::cin.ignore();

            if (izbor == 1) {
                std::string zona, dan, vrijeme, cijena;
                std::cout << "Unesite zonu: ";
                std::getline(std::cin, zona);
                std::cout << "Unesite dan (radni, vikend, praznik): ";
                std::getline(std::cin, dan);
                std::cout << "Unesite vrijeme: ";
                std::getline(std::cin, vreme);
                std::cout << "Unesite cijenu: ";
                std::getline(std::cin, cijena);

                postaviCijenu(zona, dan, vrijeme, cijena);

            } else if (izbor == 2) {
                std::string zona, dan, vrijeme;
                std::cout << "Unesite zonu: ";
                std::getline(std::cin, zona);
                std::cout << "Unesite dan (radni, vikend, praznik): ";
                std::getline(std::cin, dan);
                std::cout << "Unesite vrijeme: ";
                std::getline(std::cin, vrijeme);

                nadjiCijenu(zona, dan, vrijeme);

            } else if (izbor != 3) {
                std::cout << "Nepoznata opcija.\n";
            }
        } while (izbor != 3);
    }
};

