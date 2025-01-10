#include "Uprava.h"
#include "Operater.h"
#include "Nalog.h"
#include <iostream>
#include <cstring>

void Uprava::definisanjeCenovnika()
{
    printf("Definisanje cjenovnika...\n");
}

void Uprava::izvestajORadu()
{
    printf("Dobijanje izvestaja o radu parkinga...\n");
}

void Uprava::upravljanjeNalozimaOpcije(const char *fajl)
{
    upravljanjeNalozima.prikaziMeni(fajl);
}

void Uprava::prijava(const char *fajl)
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
                Operater operater;
                operater.prikaziMogucnostiOperatera();
            }
            else if (std::strcmp(nalog.getStatus(), "uprava") == 0)
            {
                prikaziMogucnostiUprave();
            }

            break;
        }
        else
        {
            std::cout << "Pogresno korisnicko ime ili sifra. Pokusajte ponovo.\n";
        }
    }
}

void Uprava::prikaziMogucnostiUprave()
{
    int izbor;
    const char *fajl = "../files/korisnici.txt";
    do
    {
        printf("\n1. Definisanje cjenovnika\n");
        printf("2. Dobijanje izvestaja o radu parkinga\n");
        printf("3. Izdavanje mjesecne karte\n");
        printf("4. Izdavanje invalidske karte\n");
        printf("5. Upravljanje nalozima\n");
        printf("6. Odjava\n");

        printf("Izaberite opciju: ");
        scanf("%d", &izbor);

        switch (izbor)
        {
        case 1:
            definisanjeCenovnika();
            break;
        case 2:
            izvestajORadu();
            break;
        case 3: {
            MjesecnaKartica mk;
            izdavanjeMjesecneKarte(mk);
            break;
        }
        case 4: {
            InvalidskaKartica ik;
            izdavanjeInvalidskeKarte(ik);
            break;
        }
        case 5:
            upravljanjeNalozimaOpcije(fajl);
            break;
        case 6:
            char confirm;
            printf("Da li ste sigurni da želite da se odjavite? (y/n): ");
            scanf(" %c", &confirm);
            if (confirm == 'y' || confirm == 'Y')
            {
                printf("Odjava uspješna. Ponovno prijavljivanje.\n");
                prijava(fajl);
            }
            break;
        default:
            printf("Nepostojeca opcija!\n");
            break;
        }
    } while (izbor != 0);
}
