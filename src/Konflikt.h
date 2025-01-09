#pragma once
#include <cstdio>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

class Konflikt
{
private:
    struct Zalba
    {
        int id;
        std::string tekst;
        std::string status;
        std::string odgovor;
    };

    std::vector<Zalba> zalbe;
    std::string fajlZalbi;

public:
    Konflikt(const std::string &fajl) : fajlZalbi(fajl)
    {
        ucitajZalbe();
    }

    // Funkcija za ucitavanje zalbi sa fajla
    void ucitajZalbe()
    {
        std::ifstream file(fajlZalbi);
        if (!file)
        {
            printf("Greska pri otvaranju fajla: %s\n", fajlZalbi.c_str());
            return;
        }

        std::string linija;
        while (std::getline(file, linija))
        {
            std::istringstream iss(linija);
            Zalba zalba;
            std::getline(iss, linija, '|');
            zalba.id = std::stoi(linija);
            std::getline(iss, zalba.tekst, '|');
            std::getline(iss, zalba.status, '|');
            std::getline(iss, zalba.odgovor);
            zalbe.push_back(zalba);
        }
        file.close();
    }

    // Funkcija za cuvanje zalbi u fajl
    void sacuvajZalbe() const
    {
        std::ofstream file(fajlZalbi);
        if (!file)
        {
            printf("Greska pri pisanju u fajl: %s\n", fajlZalbi.c_str());
            return;
        }

        for (const auto &zalba : zalbe)
        {
            file << zalba.id << "|" << zalba.tekst << "|" << zalba.status << "|" << zalba.odgovor << "\n";
        }
        file.close();
    }

    // Funkcija za prikaz zalbi
    void prikaziZalbe() const
    {
        printf("%-5s | %-60s | %-12s | %s\n", "ID", "Tekst", "Status", "Odgovor");
        printf("%s\n", std::string(80, '-').c_str());

        for (const auto &zalba : zalbe)
        {
            printf("%-5d | %-60s | %-12s | %s\n",
                   zalba.id,
                   zalba.tekst.c_str(),
                   zalba.status.c_str(),
                   zalba.odgovor.c_str());
        }
    }

    // Funkcija za rešavanje žalbi
    void rijesiZalbu(int id)
    {
        for (auto &zalba : zalbe)
        {
            if (zalba.id == id)
            {
                if (zalba.status == "aktivna")
                {
                    printf("Unesite odgovor na zalbu: ");
                    std::getline(std::cin, zalba.odgovor); // Uzmite odgovor sa std::getline
                    zalba.status = "rijesena";
                    printf("Zalba uspjesno rijesena!\n");
                }
                else
                {
                    printf("Greska: Zalba je vec rijesena.\n");
                }
                return;
            }
        }
        printf("Greska: Zalba sa ID %d ne postoji.\n", id);
    }

    // Funkcija za rešavanje konflikta
    void rjesavanjeKonflikta()
    {
        int brojZalbe;

        prikaziZalbe();

        printf("Unesite broj zalbe koju zelite da rijesite: ");
        scanf("%d", &brojZalbe);
        std::cin.ignore();

        rijesiZalbu(brojZalbe);
        sacuvajZalbe();
    }
};
