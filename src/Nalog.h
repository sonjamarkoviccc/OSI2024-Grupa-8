#include <cstdio>
#include <cstring>
#include <conio.h>

class Nalog {
private:
    char korisnickoIme[50];
    char sifra[50];

public:
    Nalog() {
        korisnickoIme[0] = '\0';
        sifra[0] = '\0';
    }

    ~Nalog() {}

    void setKorisnickoIme(const char* ime) {
        strncpy(korisnickoIme, ime, sizeof(korisnickoIme) - 1);
        korisnickoIme[sizeof(korisnickoIme) - 1] = '\0';
    }

    void setSifra(const char* pass) {
        strncpy(sifra, pass, sizeof(sifra) - 1);
        sifra[sizeof(sifra) - 1] = '\0';
    }

    const char* getKorisnickoIme() const {
        return korisnickoIme;
    }

    const char* getSifra() const {
        return sifra;
    }

    bool login(const char* ime, const char* pass, const char* fajl) {
        FILE* file = fopen(fajl, "r");
        if (!file) {
            printf("Greska prilikom otvaranja fajla!\n");
            return false;
        }

        char fileIme[50], fileSifra[50];
        while (fscanf(file, "%s %s", fileIme, fileSifra) == 2) {
            if (strcmp(fileIme, ime) == 0 && strcmp(fileSifra, pass) == 0) {
                fclose(file);
                return true;
            }
        }

        fclose(file);
        return false;
    }

    void unesiLozinku(char* lozinka, int maxDuzina) {
        int i = 0;
        char c;

        printf("Unesite sifru: ");
        while ((c = getch()) != '\r' && i < maxDuzina - 1) { 
            if (c == '\b' && i > 0) { 
                printf("\b \b"); 
                i--;
            } else if (c != '\b') {
                lozinka[i++] = c;
                printf("*");
            }
        }
        lozinka[i] = '\0';
        printf("\n");
    }
};
