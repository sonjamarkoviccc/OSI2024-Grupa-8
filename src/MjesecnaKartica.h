#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctime>

class MjesecnaKartica
{
    private:
        char* ime;
        char* prezime;
        char* datumIzdaje;
        char* datumIsteka;

    public:
        MjesecnaKartica()
        {
            datumIzdaje = nullptr;
            datumIsteka = nullptr;
            ime = nullptr;
            prezime = nullptr;
        }
        ~MjesecnaKartica()
        {
            free(datumIzdaje);
            free(datumIsteka);
            free(ime);
            free(prezime);
        }

        void izdajaKartice()
        {

            datumIzdaje = (char*)malloc(10 * sizeof(char));
            datumIsteka = (char*)malloc(10 * sizeof(char));
            ime = (char*)malloc(20 * sizeof(char));
            prezime = (char*)malloc(20 * sizeof(char));

            time_t dIzdaje = time(NULL);
            char temp1[20];
            struct tm datum1 = *localtime(&dIzdaje);
            strftime(temp1, sizeof(temp1), "%d%m%y", &datum1);
            datumIzdaje = strdup(temp1);

            datum1.tm_mon += 1;
            mktime(&datum1);
            char temp2[20];
            strftime(temp2, sizeof(temp2), "%d%m%y", &datum1);
            datumIsteka = strdup(temp2);
            
            printf("Unesite ime: ");
            fgets(ime, 20, stdin);
            ime[strcspn(ime, "\n")] = '\0';

            printf("Unesite prezime: ");
            fgets(prezime, 20, stdin);
            prezime[strcspn(prezime, "\n")] = '\0';

            FILE* bazaMjesecne = fopen("../files/mjesecneKartice.txt", "a");
            if (!bazaMjesecne) {
                perror("Greska pri otvaranju datoteke.");
                return;
            }
            fseek(bazaMjesecne, 0, SEEK_END);
            fprintf(bazaMjesecne, "%-16s%-20s%-12s%-12s\n", ime, prezime, datumIzdaje, datumIsteka);

            fclose(bazaMjesecne);
        }

        bool jeValidna()
        {
            struct tm datum;
            memset(&datum, 0, sizeof(datum));

            char* dan = substr(datumIsteka, 0, 2);
            char* mjesec = substr(datumIsteka, 2, 2);
            char* godina = substr(datumIsteka, 2, 2);

            int day = parseInt(dan);
            int month = parseInt(mjesec);
            int year = parseInt(godina);

            datum.tm_mday = day;
            datum.tm_mon = month;
            datum.tm_year = year;

            time_t istDate = mktime(&datum);
            time_t now = time(NULL);

            return now > istDate;
        }

        char* getIme () const { return ime;}
        char* getPrezime () const { return prezime;}
        char* getDatumIzdaje () const { return datumIzdaje;}
        char* getDatumIsteka () const { return datumIsteka;}

    private:
        char* substr(char* str, int start, int length)
        {
            if (str == nullptr || start < 0 || length < 0) {
                return nullptr;
            }

            int strLength = strlen(str);
            if (start + length > strLength) {
                length = strLength - start;
            }

            char* result = new char[length + 1];
            strncpy(result, str + start, length);
            result[length] = '\0';

            return result;
        }

        int parseInt(char* chars)
        {
            int sum = 0;
            int len = strlen(chars);
            for (int x = 0; x < len; x++)
            {
                int n = chars[len - (x + 1)] - '0';
                sum = sum + powInt(n, x);
            }
            return sum;
        }

        int powInt(int x, int y)
        {
            for (int i = 0; i < y; i++)
            {
                x *= 10;
            }
            return x;
        }
};