#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctime>


class UlaznaKartica {
    private:
        char* tablica;
        char* pocetnoVrijeme;
        char* zona;
        char* dan;

    public:
        void setTablica()
        {
            tablica = (char*)malloc(10*sizeof(char));
            printf("Unesite tablicu: ");
            scanf("%s", tablica);
        }

        void setPocetnoVrijeme()
        {
            time_t timestamp = time(NULL);
            struct tm datetime = *localtime(&timestamp);

            char output[10];

            strftime(output, 50, "%H:%M:%S", &datetime);

            pocetnoVrijeme = strdup(output);
        }

        void setZona()
        {
            zona = (char*)malloc(6*sizeof(char));
            printf("Unesite zonu: ");
            scanf("%s", zona);
        }

        void setDan()
        {
            time_t timestamp = time(NULL);
            struct tm datetime = *localtime(&timestamp);

            char output[5];

            strftime(output, 50, "%a", &datetime);

            dan = strdup(output);
        }

        char* getTablica() const {return tablica;}
        char* getPocetnoVrijeme() const {return pocetnoVrijeme;}
        char* getDan() const {return dan;}
        char* getZona() const {return zona;}
};