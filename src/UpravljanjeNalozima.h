#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Nalog.h"

class UpravljanjeNalozima
{
private:
    std::vector<Nalog> nalozi;

public:
    static bool jeValidanStatus(const char *status)
    {
        return (std::strcmp(status, "uprava") == 0 || std::strcmp(status, "operater") == 0);
    }

    static void dodajNalog(const char *fajl, const Nalog &nalog)
    {
        if (!jeValidanStatus(nalog.getStatus()))
        {
            std::cerr << "Greska: Nevalidan status! Dozvoljeni statusi su: 'uprava' ili 'operater'.\n";
            return;
        }

        std::ofstream file(fajl, std::ios::app);
        if (!file.is_open())
        {
            std::cerr << "Greska prilikom otvaranja fajla!" << std::endl;
            return;
        }
        file << std::endl;
        file << nalog.getKorisnickoIme() << " " << nalog.getSifra() << " " << nalog.getStatus() << std::endl;
        file.close();
    }

    static bool korisnickoImePostoji(const char *fajl, const char *ime)
    {
        std::ifstream file(fajl);
        if (!file.is_open())
        {
            std::cerr << "Greska prilikom otvaranja fajla!" << std::endl;
            return false;
        }

        std::string fileIme, fileSifra, fileStatus;
        while (file >> fileIme >> fileSifra >> fileStatus)
        {
            if (fileIme == ime)
            {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }

    static void prikaziNaloge(const char *fajl)
    {
        std::ifstream file(fajl);
        if (!file.is_open())
        {
            std::cerr << "Greska prilikom otvaranja fajla!" << std::endl;
            return;
        }

        std::string fileIme, fileSifra, fileStatus;
        std::cout << "Postojeći nalozi:\n";
        while (file >> fileIme >> fileSifra >> fileStatus)
        {
            std::cout << "Korisnicko ime: " << fileIme << ", Status: " << fileStatus << std::endl;
        }
        file.close();
    }

    static void obrisiNalog(const char *fajl, const char *imeZaBrisanje)
    {
        std::ifstream file(fajl);
        if (!file.is_open())
        {
            std::cerr << "Greska prilikom otvaranja fajla za citanje!" << std::endl;
            return;
        }

        std::vector<std::string> nalozi;
        std::string fileIme, fileSifra, fileStatus;
        bool nalogPronadjen = false;

        while (file >> fileIme >> fileSifra >> fileStatus)
        {
            if (fileIme == imeZaBrisanje && fileStatus != "admin")
            {
                nalogPronadjen = true;
                continue;
            }
            nalozi.push_back(fileIme + " " + fileSifra + " " + fileStatus);
        }

        file.close();

        if (!nalogPronadjen)
        {
            std::cout << "Nalog sa korisnickim imenom '" << imeZaBrisanje << "' nije pronadjen ili je administrator.\n";
            return;
        }

        std::ofstream outFile(fajl, std::ios::trunc);
        if (!outFile.is_open())
        {
            std::cerr << "Greska prilikom otvaranja fajla za pisanje!" << std::endl;
            return;
        }

        for (const auto &nalog : nalozi)
        {
            outFile << nalog << std::endl;
        }

        outFile.close();
        std::cout << "Nalog '" << imeZaBrisanje << "' je uspesno obrisan.\n";
    }

    static void azurirajNalog(const char *fajl, const char *korisnickoIme)
    {
        std::ifstream file(fajl);
        if (!file.is_open())
        {
            std::cerr << "Greska prilikom otvaranja fajla!" << std::endl;
            return;
        }

        std::vector<std::string> nalozi;
        std::string fileIme, fileSifra, fileStatus;
        bool nalogPronadjen = false;

        while (file >> fileIme >> fileSifra >> fileStatus)
        {
            if (fileIme == korisnickoIme)
            {
                nalogPronadjen = true;

                int opcija;
                std::cout << "Sta zelite da promjenite?\n";
                std::cout << "1. Promjeni korisnicko ime\n";
                std::cout << "2. Promjeni sifru\n";
                std::cout << "3. Promjeni status\n";
                std::cout << "0. Nazad\n";
                std::cout << "Izbor: ";
                std::cin >> opcija;

                if (opcija == 0)
                {
                    return;
                }

                if (opcija == 1)
                {
                    char novoIme[50];
                    std::cout << "Unesite novo korisnicko ime: ";
                    std::cin >> novoIme;

                    if (korisnickoImePostoji(fajl, novoIme))
                    {
                        std::cout << "Greska: Korisnicko ime '" << novoIme << "' je vec zauzeto.\n";
                        continue;
                    }

                    fileIme = novoIme;
                }
                else if (opcija == 2)
                {
                    char novaSifra[50];
                    std::cout << "Unesite novu sifru: ";
                    std::cin >> novaSifra;
                    fileSifra = novaSifra;
                }
                else if (opcija == 3)
                {
                    char noviStatus[20];
                    std::cout << "Unesite novi status (upravna ili operater): ";
                    std::cin >> noviStatus;

                    if (!jeValidanStatus(noviStatus))
                    {
                        std::cout << "Greska: Nevalidan status! Dozvoljeni statusi su: 'upravna' ili 'operater'.\n";
                        continue;
                    }

                    fileStatus = noviStatus;
                }
                else
                {
                    std::cout << "Nepoznat izbor.\n";
                    continue;
                }
            }
            nalozi.push_back(fileIme + " " + fileSifra + " " + fileStatus);
        }

        file.close();

        if (!nalogPronadjen)
        {
            std::cout << "Nalog sa korisnickim imenom '" << korisnickoIme << "' nije pronadjen.\n";
            return;
        }

        std::ofstream outFile(fajl, std::ios::trunc);
        if (!outFile.is_open())
        {
            std::cerr << "Greska prilikom otvaranja fajla za pisanje!" << std::endl;
            return;
        }

        for (const auto &nalog : nalozi)
        {
            outFile << nalog << std::endl;
        }

        outFile.close();
        std::cout << "Nalog je uspesno azuriran.\n";
    }

    void prikaziMeni(const char *fajl)
    {
        int izbor;
        do
        {
            std::cout << "\n1. Dodaj nalog\n";
            std::cout << "2. Obrisi nalog\n";
            std::cout << "3. Azuriraj nalog\n";
            std::cout << "4. Izlaz\n";
            std::cout << "Izbor: ";
            std::cin >> izbor;

            switch (izbor)
            {
            case 1:
            {
                char ime[50], sifra[50], status[20];
                std::cout << "\nUnesite korisnicko ime (ili 0 za nazad): ";
                std::cin >> ime;

                if (std::strcmp(ime, "0") == 0)
                {
                    break;
                }

                std::cout << "Unesite sifru: ";
                std::cin >> sifra;

                std::cout << "Unesite status: ";
                std::cin >> status;

                if (korisnickoImePostoji(fajl, ime))
                {
                    std::cout << "Korisnicko ime vec postoji!" << std::endl;
                }
                else
                {
                    Nalog noviNalog(ime, sifra, status);
                    dodajNalog(fajl, noviNalog);
                    std::cout << "Nalog uspesno dodat!" << std::endl;
                }
                break;
            }
            case 2:
            {
                prikaziNaloge(fajl);
                char imeZaBrisanje[50];
                std::cout << "Unesite korisnicko ime za brisanje (ili 0 za nazad): ";
                std::cin >> imeZaBrisanje;
                if (std::strcmp(imeZaBrisanje, "0") == 0)
                {
                    break;
                }
                obrisiNalog(fajl, imeZaBrisanje);
                break;
            }
            case 3:
            {
                prikaziNaloge(fajl);
                char korisnickoIme[50];
                std::cout << "Unesite korisnicko ime za azuriranje (ili 0 za nazad): ";
                std::cin >> korisnickoIme;
                if (std::strcmp(korisnickoIme, "0") == 0)
                {
                    break;
                }
                azurirajNalog(fajl, korisnickoIme);
                break;
            }
            case 4:
                std::cout << "Izlaz iz upravljanja nalozima.\n";
                break;
            default:
                std::cout << "Nepostojeca opcija!\n";
            }
        } while (izbor != 4);
    }
};
