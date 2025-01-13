#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <iomanip>

class InvalidskaKartica {
private:
    std::string ime;
    std::string prezime;
    std::string datumIzdaje;

public:
    InvalidskaKartica() = default;

    ~InvalidskaKartica() = default;

    void izdajaKartice()
    {
        time_t now = time(nullptr);
        tm localTime = *localtime(&now);
        std::ostringstream dateStream;
        dateStream << std::setw(2) << std::setfill('0') << localTime.tm_mday
                   << std::setw(2) << std::setfill('0') << (localTime.tm_mon + 1)
                   << std::setw(2) << std::setfill('0') << (localTime.tm_year % 100);
        datumIzdaje = dateStream.str();

        std::cout << "Unesite ime: ";
        std::getline(std::cin, ime);
        std::cout << "Unesite prezime: ";
        std::getline(std::cin, prezime);

        std::ofstream bazaInvalida("../files/invalidskeKartice.txt", std::ios::app);
        if (!bazaInvalida) {
            std::cerr << "Greska pri otvaranju datoteke." << std::endl;
            return;
        }

        bazaInvalida << std::left << std::setw(16) << ime 
                     << std::setw(20) << prezime 
                     << std::setw(12) << datumIzdaje 
                     << '\n';
    }

    bool jeValidna() {
        std::ifstream baza("../files/invalidskeKartice.txt");
        if (!baza) {
            std::cerr << "Greska pri otvaranju datoteke." << std::endl;
            return false;
        }

        std::string iIme, iPrezime, iDatum;
        std::cout << "Unesite informacije vase kartice: \n";
        std::cout << "Ime: ";
        std::getline(std::cin, iIme);
        std::cout << "Prezime: ";
        std::getline(std::cin, iPrezime);
        std::cout << "Datum Izdaje: ";
        std::getline(std::cin, iDatum);

        std::string line;
        std::getline(baza, line);
        std::getline(baza, line);

        while (std::getline(baza, line)) {
            std::string name = line.substr(0, 16);
            std::string surname = line.substr(16, 20);
            std::string date = line.substr(36, 6);

            name.erase(name.find_last_not_of(' ') + 1);
            surname.erase(surname.find_last_not_of(' ') + 1);

            if (name == iIme && surname == iPrezime && date == iDatum) {
                return true;
            }
        }

        return false;
    }

    const std::string& getIme() const { return ime; }
    const std::string& getPrezime() const { return prezime; }
    const std::string& getDatumIzdaje() const { return datumIzdaje; }

    void setIme(std::string uIme)
    {
        ime = uIme;
    }

    void setPrezime(std::string uPrezime)
    {
        prezime = uPrezime;
    }

    void setDatumIzdaje(std::string dIzdaje)
    {
        datumIzdaje = dIzdaje;
    }
};