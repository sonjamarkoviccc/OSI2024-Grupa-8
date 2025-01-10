#pragma once
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>

class Nalog
{
private:
    char korisnickoIme[50];
    char sifra[50];
    char status[20];

public:
    const char *fajl = "../files/korisnici.txt";
    Nalog()
    {
        korisnickoIme[0] = '\0';
        sifra[0] = '\0';
        status[0] = '\0';
    }

    Nalog(const char *ime, const char *pass, const char *stat)
    {
        setKorisnickoIme(ime);
        setSifra(pass);
        setStatus(stat);
    }

    ~Nalog() {}

    void setKorisnickoIme(const char *ime)
    {
        strncpy(korisnickoIme, ime, sizeof(korisnickoIme) - 1);
        korisnickoIme[sizeof(korisnickoIme) - 1] = '\0';
    }

    void setSifra(const char *pass)
    {
        strncpy(sifra, pass, sizeof(sifra) - 1);
        sifra[sizeof(sifra) - 1] = '\0';
    }

    void setStatus(const char *stat)
    {
        strncpy(status, stat, sizeof(status) - 1);
        status[sizeof(status) - 1] = '\0';
    }

    const char *getKorisnickoIme() const
    {
        return korisnickoIme;
    }

    const char *getSifra() const
    {
        return sifra;
    }

    const char *getStatus() const
    {
        return status;
    }

    bool login(const char *ime, const char *pass, const char *stat, const char *fajl)
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
            if (fileIme == ime && fileSifra == pass && fileStatus == stat)
            {
                strncpy(status, fileStatus.c_str(), sizeof(status) - 1);
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }

    void unesiLozinku(char *lozinka, int maxDuzina)
    {
        int i = 0;
        char c;

        std::cout << "Unesite sifru: ";
        while ((c = getch()) != '\r' && i < maxDuzina - 1)
        {
            if (c == '\b' && i > 0)
            {
                std::cout << "\b \b";
                i--;
            }
            else if (c != '\b')
            {
                lozinka[i++] = c;
                std::cout << "*";
            }
        }
        lozinka[i] = '\0';
        std::cout << std::endl;
    }
};