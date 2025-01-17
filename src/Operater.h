#pragma once
#include <cstdio>
#include <vector>
#include "Konflikt.h"
#include "Nalog.h"
#include "Parking.h"

class Operater
{
private:
    Konflikt konflikt;
    Nalog nalog;
    Parking parking;

    struct Zalba {
            int id;
            std::string text;
            std::string email;
            std::string date;
            std::string answer;
        };

public:
    Operater() : parking(10, "ZONA1") {}

    void prikazParkiranihVozila()
    {
        printf("Prikaz trenutno parkiranih vozila:\n");
        parking.prikazSlobodnih();
    }

    void rjesavanjeKonflikta()
    {
        konflikt.rijesiKonflikt();
    }

    int prikaziMogucnostiOperatera()
    {
        int izbor;
        const char *fajl = "../files/korisnici.txt";

        do
        {
            printf("\n1. Prikaz trenutno parkiranih vozila\n");
            printf("2. Rjesavanje konflikata\n");
            printf("3. Odjava\n");
            printf("4. Izlazak iz programa\n");
            printf("Izaberite opciju: ");
            scanf("%d", &izbor);

            switch (izbor)
            {
            case 1:
                prikazParkiranihVozila();
                break;
            case 2:
                rjesavanjeKonflikta();
                break;
            case 3:
            {
                char confirm;
                printf("Da li ste sigurni da zelite da se odjavite? (y/n): ");
                scanf(" %c", &confirm);
                if (confirm == 'y' || confirm == 'Y')
                {
                    printf("Odjava uspjesna. Ponovno prijavljivanje.\n");
                    izbor = 0;
                }
                break;
            }
            case 4:
                return 0;
            default:
                printf("Nepostojeca opcija!\n");
                break;
            }
        } while (izbor != 0);
        return 1;
    }
};