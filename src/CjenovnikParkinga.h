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
    const std::string ime_fajla = "../files/cjenovnik.txt";
    Cjenovnik* cijene; 
    int kapacitivnost;      
    int velicina;         

    void ucitajIzFajla() {
        std::ifstream ulazniFajl(ime_fajla);
        if (!ulazniFajl) {
            std::cerr << "Greska prilikom otvaranja fajla.\n";
            return;
        }

        while (velicina < kapacitivnost && ulazniFajl >> cijene[velicina].zona >> cijene[velicina].dan >> cijene[velicina].vrijeme >> cijene[velicina].cijena) {
            velicina++;
        }
        
        std::cout << "Cjenovnik uspjesno ucitan.\n";
    }

    void sacuvajUFajl() const {
        std::ofstream izlazniFajl(ime_fajla);
        if (!izlazniFajl) {
            std::cerr << "Greska prilikom cuvanja u fajl.\n";
            return;
        }

        for (int i = 0; i < velicina; ++i) {
            izlazniFajl << cijene[i].zona << " " << cijene[i].dan << " " << cijene[i].vrijeme << " " << cijene[i].cijena << "\n";
        }
        
        std::cout << "Cjenovnik uspjesno sacuvan.\n";
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

    void prikaziCjenovnik()
    {
        for (int i = 0; i < velicina; i++)
        {
            std::cout << "Zona: " << cijene[i].zona << " "
                      << "Dan: " << cijene[i].dan << " "
                      << "Vrijeme: " << cijene[i].vrijeme << " "
                      << "Cijena: " << cijene[i].cijena << std::endl;
        }
    }

    void azurirajCijenu()
    {
        prikaziCjenovnik();
        std::string uZona, uDan, uVrijeme, uCijena;
        std::cout << "Unesite podatke cijene koju hocete da promijenite:\n";
        std::cout << "Zona: ";
        std::cin >> uZona;
        std::cout << "Dan: ";
        std::cin >> uDan;
        std::cout << "Vrijeme: ";
        std::cin >> uVrijeme;
        bool found = false;

        for (int i = 0; i < velicina; i++)
        {
            if (cijene[i].zona == uZona && cijene[i].dan == uDan && cijene[i].vrijeme == uVrijeme)
            {
                found = true;
                std::cout << "Unesite novu cijenu: ";
                std::cin >> uCijena;
                cijene[i].cijena = uCijena;
                std::cout << "Cijena uspjesno azurirana.\n";
                break;
            }
        }

        if (!found)
        {
            std::cout << "Stavka nije pronadjena.";
        }

        sacuvajUFajl();
    }

    void prikaziMeni() const {
        std::cout << "\n--- Upravljanje cjenovnikom ---\n"
                  << "1. Postavi cijenu\n"
                  << "2. Pronadji cijenu\n"
                  << "3. Azuriraj cijenu\n"
                  << "4. Izlaz\n"
                  << "Izaberite opciju: ";
    }

   
};





