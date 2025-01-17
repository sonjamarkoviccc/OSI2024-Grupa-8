#include <iostream>
#include <string>
#include "UlaznaKartica.h"
#include "Parking.h"
#include "Auto.h"
#include "Izlaz.h"
#include "Konflikt.h"

void park(int spot, const std::string& registracija)
{
    std::string p = "../files/parking.txt";
    std::string temp = "../files/tempParking.txt";
    std::ifstream inFile(p);
    std::ofstream outFile(temp);

    if (!inFile || !outFile) {
        std::cerr << "Greska prilikom otvaranja fajlova.\n";
        return;
    }

    std::string line;
    std::string targetLine = "Mjesto " + std::to_string(spot) + " : slobodno";
    std::string updatedLine = "Mjesto " + std::to_string(spot) + " : zauzeto (registracija: " + registracija + ")";


    while (std::getline(inFile, line))
    {
        
        if (line == targetLine)
        {
            outFile << updatedLine << std::endl;
        }
        else
        {
            
            outFile << line << std::endl;
        }
    }

    inFile.close();
    outFile.close();

    if (remove(p.c_str()) != 0 || rename("../files/tempParking.txt", p.c_str()) != 0)
    {
        std::cerr << "Greska prilikom azuriranja fajla.\n";
        exit(EXIT_FAILURE);
    }
}

void unesiPodatke(const std::string tablice, const std::string datum, const std::string vrijeme)
{
    std::ofstream dat("../files/podaci.txt", std::ios::app);
    if (!dat.is_open())
    {
        std::cerr << "Error: Neuspjesno otvaranje datoteke.\n";
        return;
    }

    dat << tablice << " " << datum << " " << vrijeme << std::endl;

    dat.close();
}

std::string getFormattedDate()
{
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    std::ostringstream dateStream;
    dateStream << std::setw(2) << std::setfill('0') << now->tm_mday << "."
               << std::setw(2) << std::setfill('0') << (now->tm_mon + 1) << "."
               << (now->tm_year + 1900);

    return dateStream.str();
}

std::string getFormattedTime()
{
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    std::ostringstream timeStream;
    timeStream << std::setw(2) << std::setfill('0') << now->tm_hour << ":"
               << std::setw(2) << std::setfill('0') << now->tm_min << ":"
               << std::setw(2) << std::setfill('0') << now->tm_sec;

    return timeStream.str();
}

bool jeNoviDan()
{
    time_t now = time(0);
    tm *currentTime = localtime(&now);
    int currentDay = currentTime->tm_mday;
    int currentMonth = currentTime->tm_mon + 1;
    int currentYear = currentTime->tm_year + 1900;

    std::ifstream inFile("../files/last_run_date.txt");
    int savedDay, savedMonth, savedYear;

    if (inFile.is_open()) {
        inFile >> savedDay >> savedMonth >> savedYear;
        inFile.close();

        if (currentYear > savedYear || currentMonth > savedMonth || currentDay > savedDay)
        {
            std::ofstream outFile("../files/last_run_date.txt");
            outFile << currentDay << " " << currentMonth << " " << currentYear;
            outFile.close();
            return true;
        } else {
            return false;
        }
    } else {
        std::ofstream outFile("../files/last_run_date.txt");
        outFile << currentDay << " " << currentMonth << " " << currentYear;
        outFile.close();
        return true;
    }
}

int main()
{
    Parking parking(50, "ZONA1");
    Konflikt konflikt;

    std::string izbor;

    if (jeNoviDan())
    {
        std::ofstream file("../files/tablice.txt", std::ios::trunc);
        file.close();
    }

    while (izbor.empty() || izbor != "1" || izbor != "2" || izbor != "3" || izbor != "0")
    {
        std::cout << "\nSlobodnih mjesta je: " << parking.getSlobodnaMjesta() << std::endl;
        std::cout << "Izaberite opciju:\n1. Ulazak\n2. Izlazak\n3. Podnosenje zalbi\nIzbor: ";
        std::cin >> izbor;

        if (izbor == "1")
        {
            UlaznaKartica kartica;
            kartica.setKartica(parking);
            auto auto1 = std::make_shared<Auto>(kartica.getTablica());
            int slobodnoMjesto = rand() % parking.getSlobodnaMjesta();
            while (!parking.parkiraj(slobodnoMjesto, auto1))
            {
                slobodnoMjesto = rand() % parking.getSlobodnaMjesta();
            }
            kartica.pisiKarticu(slobodnoMjesto);
            park(slobodnoMjesto, kartica.getTablica());
            time_t timestamp = time(NULL);
            struct tm datetime = *localtime(&timestamp);
            std::string date = getFormattedDate();
            std::string time = getFormattedTime();
            unesiPodatke(kartica.getTablica(), date, time);
        }
        else if (izbor == "2")
        {
            if (parking.getSlobodnaMjesta() < 50)
            {
                Izlaz izlaz("../files/tablice.txt");
                string tablice;
                std::cout << "Molim Vas unesite tablice: ";
                std::cin >> tablice;
                izlaz.pretraziTablicu(tablice, parking);
            }
            else {
                std::cout << "Parking je prazan." << std::endl;
            }
        }
        else if (izbor == "3")
        {
            konflikt.dodajZalbu();
        }
        else if (izbor == "0")
        {
            if (parking.getSlobodnaMjesta() == parking.getUkupnoMjesta())
            {
                std::cout << "Kraj rada parkinga." << std::endl;
                system("pause");
                return 0;
            }
            else {
                std::cout << "Ima jos auta na parkingu, sacekajte jos malo." << std::endl;
            }
        }
        else
        {
            cout << "Nepoznata opcija. Pokusajte ponovo." << endl;
        }
    }
    return 0;
}