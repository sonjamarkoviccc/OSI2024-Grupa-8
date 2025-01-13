#include "Operater.h"
#include "Uprava.h"
#include <iostream>
#include <cstring>

void Operater::prikazParkiranihVozila()
{
    printf("Prikaz trenutno parkiranih vozila:\n");
    parking.prikazSlobodnih();
}

void Operater::rjesavanjeKonflikta()
{
    konflikt.rjesavanjeKonflikta();
}

void Operater::prijava(const char *fajl)
{
    char tipKorisnika[20];
    char korisnickoIme[50];
    char sifra[50];

    while (true)
    { 
        std::cout << "Unesite status: ";
        std::cin >> tipKorisnika;

        std::cout << "Unesite korisnicko ime: ";
        std::cin >> korisnickoIme;

        Nalog nalog;
        nalog.unesiLozinku(sifra, sizeof(sifra));

        if (nalog.login(korisnickoIme, sifra, tipKorisnika, fajl))
        {
            std::cout << "Prijava uspjesna! Dobrodosli, " << korisnickoIme << " (" << nalog.getStatus() << ").\n";

            if (std::strcmp(nalog.getStatus(), "operater") == 0)
            {
                prikaziMogucnostiOperatera();
            }
            else if (std::strcmp(nalog.getStatus(), "uprava") == 0)
            {
                Uprava uprava;
                uprava.prikaziMogucnostiUprave(); 
            }

            break;
        }
        else
        {
            std::cout << "Pogresno korisnicko ime ili sifra. Pokusajte ponovo.\n";
        }
    }
}

void Operater::prikaziMogucnostiOperatera()
{
    int izbor;
    const char *fajl = "../files/korisnici.txt";

    do
    {
        printf("\n1. Prikaz trenutno parkiranih vozila\n");
        printf("2. Rjesavanje konflikata\n");
        printf("3. Odjava\n");
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
            printf("Da li ste sigurni da želite da se odjavite? (y/n): ");
            scanf(" %c", &confirm);
            if (confirm == 'y' || confirm == 'Y')
            {
                printf("Odjava uspješna. Ponovno prijavljivanje.\n");
                prijava(fajl);
            }
            break;
        }
        default:
            printf("Nepostojeca opcija!\n");
            break;
        }
    } while (izbor != 0);
}
