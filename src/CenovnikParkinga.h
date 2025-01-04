#include <iostream>
#include <fstream>
#include <string>

struct Cenovnik {
    std::string zona;
    std::string dan;
    std::string vreme;
    std::string cena;
};

class CenovnikParkinga {
private:
    const std::string ime_fajla = "cenovnik.txt";
    Cenovnik* cene; 
    int kapacitivnost;      
    int velicina;         

    void ucitajIzFajla() {
        std::ifstream ulazniFajl(ime_fajla);
        if (!ulazniFajl) {
            std::cerr << "Greška prilikom otvaranja fajla.\n";
            return;
        }

        while (velicina < kapacitivnost && ulazniFajl >> cene[velicina].zona >> cene[velicina].dan >> cene[velicina].vreme >> cene[velicina].cena) {
            velicina++;
        }
        
        std::cout << "Cenovnik uspešno učitan.\n";
    }

    void sacuvajUFajl() const {
        std::ofstream izlazniFajl(ime_fajla);
        if (!izlazniFajl) {
            std::cerr << "Greška prilikom čuvanja u fajl.\n";
            return;
        }

        for (int i = 0; i < velicina; ++i) {
            izlazniFajl << cene[i].zona << " " << cene[i].dan << " " << cene[i].vreme << " " << cene[i].cena << "\n";
        }
        
        std::cout << "Cenovnik uspešno sačuvan.\n";
    }

public:
    CenovnikParkinga() : kapacitivnost(10), velicina(0) {
        cene = new Cenovnik[kapacitivnost]; 
        ucitajIzFajla();
    }

    ~CenovnikParkinga() {
        delete[] cene; 
    }

    void postaviCenu(const std::string& zona, const std::string& dan, const std::string& vreme, const std::string& cena) {
        if (velicina >= kapacitivnost) { 
            kapacitivnost *= 2; 
            Cenovnik* new_cene = new Cenovnik[kapacitivnost];
            for (int i = 0; i < velicina; ++i) {
                new_cene[i] = cene[i]; 
            }
            delete[] cene; 
            cene = new_cene; 
        }

        cene[velicina++] = {zona, dan, vreme, cena}; 
        sacuvajUFajl(); 
    }

    void nadjiCenu(const std::string& zona, const std::string& dan, const std::string& vreme) const {
        for (int i = 0; i < velicina; ++i) {
            if (cene[i].zona == zona && cene[i].dan == dan && cene[i].vreme == vreme) {
                std::cout << "Cena: " << cene[i].cena << "\n";
                return;
            }
        }
        
        std::cout << "Cena nije pronađena.\n";
    }

    void prikaziMeni() const {
        std::cout << "\n--- Upravljanje cenovnikom ---\n"
                  << "1. Postavi cenu\n"
                  << "2. Pronađi cenu\n"
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
                std::string zona, dan, vreme, cena;
                std::cout << "Unesite zonu: ";
                std::getline(std::cin, zona);
                std::cout << "Unesite dan (radni, vikend, praznik): ";
                std::getline(std::cin, dan);
                std::cout << "Unesite vreme: ";
                std::getline(std::cin, vreme);
                std::cout << "Unesite cenu: ";
                std::getline(std::cin, cena);

                postaviCenu(zona, dan, vreme, cena);

            } else if (izbor == 2) {
                std::string zona, dan, vreme;
                std::cout << "Unesite zonu: ";
                std::getline(std::cin, zona);
                std::cout << "Unesite dan (radni, vikend, praznik): ";
                std::getline(std::cin, dan);
                std::cout << "Unesite vreme: ";
                std::getline(std::cin, vreme);

                nadjiCenu(zona, dan, vreme);

            } else if (izbor != 3) {
                std::cout << "Nepoznata opcija.\n";
            }
        } while (izbor != 3);
    }
};

