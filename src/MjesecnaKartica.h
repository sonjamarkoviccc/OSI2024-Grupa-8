#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <limits>

class MjesecnaKartica {
private:
    std::string ime;
    std::string prezime;
    std::string datumIzdaje;
    std::string datumIsteka;

public:
    MjesecnaKartica() = default;

    ~MjesecnaKartica() = default;

    void izdajaKartice()
    {
        time_t dIzdaje = time(nullptr);
        struct tm datum1 = *localtime(&dIzdaje);

        std::ostringstream temp1;
        temp1 << std::setw(2) << std::setfill('0') << datum1.tm_mday
              << std::setw(2) << std::setfill('0') << datum1.tm_mon + 1
              << std::to_string(datum1.tm_year + 1900).substr(2);
        datumIzdaje = temp1.str();

        datum1.tm_mon += 1;
        mktime(&datum1);

        std::ostringstream temp2;
        temp2 << std::setw(2) << std::setfill('0') << datum1.tm_mday
              << std::setw(2) << std::setfill('0') << datum1.tm_mon + 1
              << std::to_string(datum1.tm_year + 1900).substr(2);
        datumIsteka = temp2.str();

        std::cout << "Unesite ime: ";
        std::cin >> ime;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Unesite prezime: ";
        std::getline(std::cin, prezime);

        std::ofstream bazaMjesecne("../files/mjesecneKartice.txt", std::ios::app);
        if (!bazaMjesecne) {
            std::cerr << "Greska pri otvaranju datoteke." << std::endl;
            return;
        }
        bazaMjesecne << ime << " " << prezime << " " << datumIzdaje << " " << datumIsteka << std::endl;
    }

    bool jeValidna() const {
        struct tm datum = {};
        datum.tm_mday = std::stoi(datumIsteka.substr(0, 2));
        datum.tm_mon = std::stoi(datumIsteka.substr(2, 2)) - 1;
        datum.tm_year = std::stoi("20" + datumIsteka.substr(4, 2)) - 1900;

        time_t istDate = mktime(&datum);
        time_t now = time(nullptr);

        return now <= istDate;
    }

    std::string getIme() const { return ime; }
    std::string getPrezime() const { return prezime; }
    std::string getDatumIzdaje() const { return datumIzdaje; }
    std::string getDatumIsteka() const { return datumIsteka; }

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

    void setDatumIsteka(std::string dIsteka)
    {
        datumIsteka = dIsteka;
    }

    void getKartica(std::string& uIme, std::string& uPrezime)
    {
        std::ifstream mjesecne("../files/mjesecneKartice.txt");
        if (!mjesecne) {
            std::cerr << "Greska pri otvaranju datoteke." << std::endl;
            return;
        }

        std::string line;

        while (std::getline(mjesecne, line))
        {
            std::stringstream ss(line);

            ss >> ime >> prezime >> datumIzdaje >> datumIsteka;

            if (!ime.compare(uIme) && !prezime.compare(uPrezime))
            {
                break;
            }
        }

    }
};