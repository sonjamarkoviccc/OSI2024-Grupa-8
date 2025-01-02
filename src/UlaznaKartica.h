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
        UlaznaKartica()
        {
            tablica = nullptr;
            pocetnoVrijeme = nullptr;
            zona = nullptr;
            dan = nullptr;
        }
        ~UlaznaKartica()
        {
            free(tablica);
            free(zona);
            free(dan);
            free(pocetnoVrijeme);
        }
        void setKartica()
        {
            tablica = (char*)malloc(10*sizeof(char));
            printf("Unesite tablicu: ");
            scanf("%s", tablica);

            time_t vrijeme = time(NULL);
            struct tm datetime = *localtime(&vrijeme);
            char vr[10];
            strftime(vr, sizeof(vr), "%H:%M:%S", &datetime);
            pocetnoVrijeme = strdup(vr);

            zona = (char*)malloc(6*sizeof(char));
            printf("Unesite zonu: ");
            scanf("%s", zona);

            time_t day = time(NULL);
            struct tm datum = *localtime(&day);
            char d[5];
            strftime(d, sizeof(d), "%a", &datum);
            dan = strdup(d);

            FILE* spisakTablica = fopen("../files/tablice.txt", "a");
            if (!spisakTablica) {
                perror("Error opening file");
                return;
            }
            fseek(spisakTablica, 0, SEEK_END);
            fprintf(spisakTablica, "%s %s %s %s\n", tablica, zona, dan, pocetnoVrijeme);

            fclose(spisakTablica);
        }

        char* getTablica() const {return tablica;}
        char* getPocetnoVrijeme() const {return pocetnoVrijeme;}
        char* getDan() const {return dan;}
        char* getZona() const {return zona;}
};