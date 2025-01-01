#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctime>


class UlaznaKartica {
    private:
        char* tablica;
        char* pocetnoVrijeme;
        char zona[10];
        char* dan;

    public:
        void setTablica(char* tab)
        {
            tablica = strdup(tab);
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
            printf("Unesite zonu: ");
            std::cin.getline(zona, 10);
        }

        void setDan()
        {
            time_t timestamp = time(NULL);
            struct tm datetime = *localtime(&timestamp);

            char output[5];

            strftime(output, 50, "%a", &datetime);

            dan = strdup(output);
        }
};