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

        bazaInvalida << ime << " " << prezime << " " << datumIzdaje << " " << std::endl;
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

    bool getKartica(std::string& uIme, std::string& uPrezime)
    {
        std::ifstream invalidske("../files/invalidskeKartice.txt");
        if (!invalidske) {
            std::cerr << "Greska pri otvaranju datoteke." << std::endl;
            return false;
        }

        std::string line;

        while (std::getline(invalidske, line))
        {
            std::stringstream ss(line);

            ss >> ime >> prezime >> datumIzdaje;

            if (!ime.compare(uIme) && !prezime.compare(uPrezime))
            {
                return true;
            }
        }
        return false;
    }
};