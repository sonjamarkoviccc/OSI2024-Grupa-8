#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

const int MAX_KORISNIKA = 100;
const int MAX_ZONA = 10; // maksimalan broj zona
const int MAX_TIP = 2;   // RADNI ili VIKEND
const int MAX_VREMENSKISLOT = 2; // 1 ili 24 sata


class Izvjestaj {
private:
struct Korisnik {
    std::string registarskaTablica;                   
    std::string datum;
    std::string vrijeme;                          
    int trajanje;
    double iznos;                
};

// struct Cjenovnik {
//     std::string zona;   
//     std::string tip;    
//     int trajanje;       
//     double cijena;     
// };

    Korisnik korisnici[MAX_KORISNIKA];
    int brojKorisnika;
    // Cjenovnik cjenovnik[MAX_ZONA * MAX_TIP * MAX_VREMENSKISLOT];  

    // void ucitajCjenovnik() {
    //     std::ifstream ulazCjenovnik("../files/cjenovnik.txt");
    //     if (!ulazCjenovnik) {
    //         std::cerr << "Greska prilikom otvaranja fajla cjenovnik.txt.\n";
    //         return;
    //     }

    //     std::string zona, tip, vrijeme;
    //     double cijena;
    //     int index = 0;
    //     while (ulazCjenovnik >> zona >> tip >> vrijeme >> cijena) {
    //         int trajanje = timeToMinutes(vrijeme);  // konvertovanje h:m:s u minute
    //         cjenovnik[index++] = {zona, tip, trajanje, cijena};
    //     }
    //     ulazCjenovnik.close();
    // }

    // bool isWeekend(const std::string& dayType) {
    //     return dayType == "Sat" || dayType == "Sun";
    // }

    // int timeToMinutes(const std::string& timeStr) {
    //     int hours, minutes, seconds;
    //     char colon;
    //     std::istringstream ss(timeStr);
    //     ss >> hours >> colon >> minutes >> colon >> seconds;

    //     return hours * 60 + minutes;  
    // }

    // double calculatePrice(const std::string& zona, bool isWeekend, int trajanje) {
    //     std::string vrijeme = isWeekend ? "VIKEND" : "RADNI";
    //     double price = 0.0;

    //     for (int i = 0; i < MAX_ZONA * MAX_TIP * MAX_VREMENSKISLOT; ++i) {
    //         if (cjenovnik[i].zona == zona && cjenovnik[i].tip == vrijeme) {
    //             if ((trajanje < 60 && cjenovnik[i].trajanje == 60) || (trajanje >= 60 && cjenovnik[i].trajanje == 1440)) {
    //                 price = cjenovnik[i].cijena;
    //                 break;
    //             }
    //         }
    //     }

    //     if (price == 0.0) {
    //         std::cerr << "Cijena nije pronadjena u zoni " << zona << " za trajanje " << trajanje << " minuta.\n";
    //     } else {
    //         std::cout << "Cijena za zonu " << zona << " za " << trajanje << " minuta: " << price << " KM\n";
    //     }

    //     return price;
    // }

    void ucitajKorisnike() {
        std::ifstream ulazTablice("../files/podaci.txt");
        if (!ulazTablice) {
            std::cerr << "Greska prilikom otvaranja fajla tablice.txt.\n";
            return;
        }

        brojKorisnika = 0;
        std::string linija;
        while (std::getline(ulazTablice, linija) && brojKorisnika < MAX_KORISNIKA) {
            std::istringstream iss(linija);
            std::string tablica, datum, vr;
            int duration;
            double iznos;

            if (!(iss >> tablica >> datum >> vr >> duration >> iznos)) {
                std::cerr << "Greska prilikom parsiranja linije: " << linija << "\n";
                continue;
            }

            korisnici[brojKorisnika] = {tablica, datum, vr, duration, iznos};
            brojKorisnika++;
        }
        ulazTablice.close();

        std::cout << "Korisnici uspjesno ucitani. Ukupan broj korisnika: " << brojKorisnika << "\n";
    }

    void sacuvajIzvjestajUFajl(const std::string& naslov, int brojKorisnika, double ukupnaZarada) const {
        std::ofstream izvjestajFajl("../files/izvjestaj.txt");
        if (!izvjestajFajl) {
            std::cerr << "Greska prilikom otvaranja fajla za pisanje.\n";
            return;
        }

        izvjestajFajl << naslov << "\n"
                      << "Ukupan broj korisnika: " << brojKorisnika << "\n"
                      << "Ukupna zarada: " << ukupnaZarada << " KM\n\n";

        izvjestajFajl.close();
    }

    bool isDatumInRange(const std::string& datum, const std::string& startDatum, const std::string& endDatum) const {
        return datum >= startDatum && datum <= endDatum;
    }

    std::string convertDateFormat(const std::string& date)
    {
        std::istringstream iss(date);
        std::string day, month, year;

        std::getline(iss, day, '.');
        std::getline(iss, month, '.');
        std::getline(iss, year);

        return day + month + year.substr(2);
    }

public:
    Izvjestaj() : brojKorisnika(0) {
        // ucitajCjenovnik();
        ucitajKorisnike();
    }

    void generisiDnevniIzvjestaj(const std::string& datum) const {
        double ukupnaZarada = 0.0;
        int brojPregledanih = 0;

        for (int i = 0; i < brojKorisnika; ++i) {
            if (korisnici[i].datum == datum) {
                ukupnaZarada += korisnici[i].iznos;
                brojPregledanih++;
            }
        }

        std::string naslov = "Dnevni_izvjestaj:_" + datum;
        std::cout << naslov << "\n"
                  << "Ukupan broj korisnika: " << brojPregledanih << "\n"
                  << "Ukupna zarada: " << ukupnaZarada << " KM\n";

        std::string filepath = "../files/" + naslov;

        sacuvajIzvjestajUFajl(filepath, brojPregledanih, ukupnaZarada);
    }

    void generisiNedeljniIzvjestaj(const std::string& startDatum, const std::string& endDatum) const {
        double ukupnaZarada = 0.0;
        int brojPregledanih = 0;

        for (int i = 0; i < brojKorisnika; ++i) {
            if (isDatumInRange(korisnici[i].datum, startDatum, endDatum)) {
                ukupnaZarada += korisnici[i].iznos;
                brojPregledanih++;
            }
        }

        std::string naslov = "Nedeljni_izvjestaj:_" + startDatum + "_" + endDatum;
        std::cout << naslov << "\n"
                  << "Ukupan broj korisnika: " << brojPregledanih << "\n"
                  << "Ukupna zarada: " << ukupnaZarada << " KM\n";
        
        std::string filepath = "../files/" + naslov;

        sacuvajIzvjestajUFajl(filepath, brojPregledanih, ukupnaZarada);
    }

    void generisiMjesecniIzvjestaj(int mjesec, int godina) const {
        double ukupnaZarada = 0.0;
        int brojPregledanih = 0;

        for (int i = 0; i < brojKorisnika; ++i) {
            int d, m, y;
            sscanf(korisnici[i].datum.c_str(), "%d.%d.%d", &d, &m, &y);
            if (m == mjesec && y == godina) {
                ukupnaZarada += korisnici[i].iznos;
                brojPregledanih++;
            }
        }

        std::string naslov = "Mjesecni_izvjestaj:_" + std::to_string(mjesec) + "_godina:_" + std::to_string(godina);
        std::cout << naslov << "\n"
                  << "Ukupan broj korisnika: " << brojPregledanih << "\n"
                  << "Ukupna zarada: " << ukupnaZarada << " KM\n";

        std::string filepath = "../files/" + naslov;

        sacuvajIzvjestajUFajl(filepath, brojPregledanih, ukupnaZarada);
    }

    void prikaziMeni() const {
        std::cout << "\n--- Izvjestaji ---\n"
                  << "1. Dnevni izvjestaj\n"
                  << "2. Nedeljni izvjestaj\n"
                  << "3. Mjesecni izvjestaj\n"
                  << "4. Izlaz\n"
                  << "Odaberite opciju: ";
    }
    
    
};






