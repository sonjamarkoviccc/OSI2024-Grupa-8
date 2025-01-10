#include "Nalog.h"
#include "Operater.h"
#include "Uprava.h"

int main()
{
    const char *fajl = "../files/korisnici.txt";

    Operater operater;
    Uprava uprava;

    while (true)
    {
        char tipKorisnika[20];
        char korisnickoIme[50];
        char sifra[50];

        std::cout << "Unesite status: ";
        std::cin >> tipKorisnika;

        std::cout << "Unesite korisnicko ime: ";
        std::cin >> korisnickoIme;

        Nalog nalog;
        nalog.unesiLozinku(sifra, sizeof(sifra));

        if (nalog.login(korisnickoIme, sifra, tipKorisnika, fajl))
        {
            std::cout << "Prijava uspjesna! Dobrodosli, " << korisnickoIme << " (" << nalog.getStatus() << ").\n";

            if (strcmp(nalog.getStatus(), "uprava") == 0 || strcmp(nalog.getStatus(), "admin") == 0)
            {
                uprava.prikaziMogucnostiUprave();
            }
            else if (strcmp(nalog.getStatus(), "operater") == 0)
            {
                operater.prikaziMogucnostiOperatera();
            }
            else
            {
                std::cout << "Nepoznat status: " << nalog.getStatus() << ".\n";
            }
        }
        else
        {
            std::cout << "Pogresno korisnicko ime ili sifra. Pokusajte ponovo.\n";
        }
    }

    return 0;
}