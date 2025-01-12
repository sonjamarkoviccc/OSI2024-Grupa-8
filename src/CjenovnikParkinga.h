#include <iostream>
#include <fstream>
#include <string>


class CjenovnikParkinga {
private:
    struct Cjenovnik {
    std::string zona;
    std::string dan;
    std::string vrijeme; 
    std::string cijena;
};
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
        
        std::cout << "Cijena nije pronadjena.\n";
    }

    void prikaziMeni() const {
        std::cout << "\n--- Upravljanje cjenovnikom ---\n"
                  << "1. Postavi cijenu\n"
                  << "2. Pronađi cijenu\n"
                  << "3. Izlaz\n"
                  << "Izaberite opciju: ";
    }

   
};





