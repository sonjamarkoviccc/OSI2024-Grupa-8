#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <memory>
#include "BankarskaKartica.h"
#include "MjesecnaKartica.h"
#include "InvalidskaKartica.h"
#include "Parking.h"

using namespace std;


class Izlaz
{
private:
    string imeFajla;
    void izlazakSaMjesta(const std::string& registracija, int spot)
    {
        std::string p = "../files/parking.txt";
        std::string temp = "../files/tempParking.txt";
        std::ifstream inFile(p);
        std::ofstream outFile(temp);

        if (!inFile || !outFile) {
            std::cerr << "Greska prilikom otvaranja fajlova.\n";
            return;
        }

        std::string line;
        std::string updatedLine;
        bool found = false;

        while (std::getline(inFile, line))
        {
            size_t pos = line.find("Mjesto " + std::to_string(spot) + " : zauzeto (registracija: " + registracija + ")");
            
            if (pos != std::string::npos) {
                updatedLine = "Mjesto " + std::to_string(spot) + " : slobodno";
                outFile << updatedLine << std::endl;
                found = true;
            } else {
                outFile << line << std::endl;
            }
        }

        if (!found) {
            std::cout << "Nije pronadjen automobil sa registracijom: " << registracija << "\n";
        }

        inFile.close();
        outFile.close();

        if (remove(p.c_str()) != 0 || rename("../files/tempParking.txt", p.c_str()) != 0)
        {
            std::cerr << "Greška prilikom ažuriranja fajla.\n";
            exit(EXIT_FAILURE);
        }
    }
    void azuriraj(int duration, double cost, std::string registracija)
    {
        std::string filename = "../files/podaci.txt";
        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            std::cerr << "Error: Neuspjeno otvaranje datoteke.\n";
            return;
        }

        std::ofstream tempFile("../files/tempPodaci.txt");
        if (!tempFile.is_open()) {
            std::cerr << "Error: Neuspjesno otvaranje temp datoteke.\n";
            inputFile.close();
            return;
        }

        std::string line;
        bool updated = false;

        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            std::string plate, date, time;
            int existingDuration;
            double existingPrice;

            iss >> plate >> date >> time;

            if (plate == registracija) {
                tempFile << plate << " " << date << " " << time << " " 
                        << duration << " " << cost << "\n";
                updated = true;
            } else {
                tempFile << line << "\n";
            }
        }

        inputFile.close();
        tempFile.close();

        if (updated) {
            if (remove(filename.c_str()) != 0 || rename("../files/tempPodaci.txt", filename.c_str()) != 0)
            {
                std::cerr << "Greška prilikom ažuriranja fajla.\n";
                exit(EXIT_FAILURE);
            }
        } else {
            std::cerr << "Error: Registracija nije pronadjena.\n";
            std::remove("../files/tempPodaci.txt");
        }
    }

public:
    // Konstruktor za inicijalizaciju fajla
    Izlaz(const string &fajl) : imeFajla(fajl) {}

    // Metod za pretragu po imenu tablice
    void pretraziTablicu(const string &imeTablice, Parking &parking)
    {
        ifstream fajl(imeFajla);
        if (!fajl.is_open())
        {
            cerr << "Greska: Problem sa otvaranjem fajla. " << imeFajla << endl;
            return;
        }

        string linija;
        bool pronadjeno = false;
        while (getline(fajl, linija))
        {
            stringstream ss(linija);
            string ime, zona, dan, vrijeme;
            int mjesto;
            ss >> ime >> zona >> dan >> vrijeme >> mjesto;

            if (ime == imeTablice)
            {
                cout << "Kartica uspjesno ucitana: " << linija << endl;

                // Calculate parking fee
                auto sada = chrono::system_clock::now();
                time_t trenutnoVrijeme = chrono::system_clock::to_time_t(sada);
                tm *trenutnoVrijemeTm = localtime(&trenutnoVrijeme);

                int vrijemeProvedenoSekunde = izracunajVrijeme(vrijeme, trenutnoVrijemeTm);
                if (vrijemeProvedenoSekunde < 0)
                {
                    cerr << "Greska: Vrijeme na parkingu nije validno." << endl;
                    return;
                }

                string tipDana = (dan == "Sat" || dan == "Sun") ? "VIKEND" : "RADNI";
                double cijena = pronadjiCijenu(zona, tipDana, vrijemeProvedenoSekunde);

                if (cijena >= 0)
                {
                    cout << "Cijena parkinga: " << fixed << setprecision(2) << cijena << " KM" << endl;

                    bool placeno = false;

                    while (!placeno)
                    {
                        izborPlacanja(cijena, placeno);
                    }
                    
                    time_t vrijemePlacanja = chrono::system_clock::to_time_t(chrono::system_clock::now());
                    bool izlazakMoguc;
                    std::string izlaz;

                    if (placeno)
                    {
                        while (izlaz.empty() || izlaz != "Da")
                        {
                            std::cout << "Da li ste spremni da izadjete? (Da/Ne): ";
                            std::cin >> izlaz;
                        }
                        izlazakMoguc = provjeriIzlazak(vrijemePlacanja);
                    }
                    else {
                        izlazakMoguc = false;
                    }

                    if (izlazakMoguc)
                    {
                        parking.isparkiraj(mjesto, imeTablice);
                        izlazakSaMjesta(imeTablice, mjesto);
                        azuriraj(vrijemeProvedenoSekunde, cijena, imeTablice);
                    }
                    else
                    {
                        cout << "Morate ponovo platiti za izlazak." << endl;
                    }
                }
                else
                {
                    cout << "Cijena nije pronadjena u cjenovniku." << endl;
                }

                pronadjeno = true;
                break;
            }
        }

        if (!pronadjeno)
        {
            cout << "Tablica sa imenom " << imeTablice << " nije pronadjena." << endl;
        }

        fajl.close();
    }

    // Pomocni metod za racunanje vremena na parkingu
    static int izracunajVrijeme(const string &vrijemeFajla, tm *trenutnoVrijemeTm)
    {
        tm vrijemeIzFajla = {};
        istringstream ss(vrijemeFajla);
        ss >> get_time(&vrijemeIzFajla, "%H:%M:%S");

        if (ss.fail())
        {
            cerr << "Greska: Ne mogu da izvucem vrijeme iz fajla. Provjerite format!" << endl;
            return -1;
        }

        int vrijemeFajlaSekunde = vrijemeIzFajla.tm_hour * 3600 + vrijemeIzFajla.tm_min * 60 + vrijemeIzFajla.tm_sec;
        int trenutnoVrijemeSekunde = trenutnoVrijemeTm->tm_hour * 3600 + trenutnoVrijemeTm->tm_min * 60 + trenutnoVrijemeTm->tm_sec;

        int razlikaSekunde = trenutnoVrijemeSekunde - vrijemeFajlaSekunde;

        if (razlikaSekunde < 0)
        {
            razlikaSekunde += 24 * 3600;
        }

        int sati = razlikaSekunde / 3600;
        int minute = (razlikaSekunde % 3600) / 60;
        int sekunde = razlikaSekunde % 60;

        cout << "Vrijeme provedeno na parkingu: " << sati << " sati, " << minute << " minuta i " << sekunde << " sekundi." << endl;

        return razlikaSekunde;
    }

    // Metod za pronalazak cijene u cjenovniku
    static double pronadjiCijenu(const string &zona, const string &tipDana, int vrijemeProvedenoSekunde)
    {
        ifstream cjenovnik("../files/cjenovnik.txt");
        if (!cjenovnik.is_open())
        {
            cerr << "Greska: Problem sa otvaranjem datoteke." << endl;
            return -1;
        }

        string linija;
        double cijenaZaJedanSat = -1;
        while (getline(cjenovnik, linija))
        {
            stringstream ss(linija);
            string zonaCjenovnik, tipDanaCjenovnik, trajanje;
            double cijena;
            ss >> zonaCjenovnik >> tipDanaCjenovnik >> trajanje >> cijena;

            // Provjera zone i tipa dana
            if (zonaCjenovnik == zona && tipDanaCjenovnik == tipDana)
            {
                int min;
                try
                {
                    min = stoi(trajanje.substr(0, trajanje.find('m')));
                }
                catch (const invalid_argument &e)
                {
                    cerr << "Greska: Nevalidan format trajanja u cjenovniku." << endl;
                    continue;
                }

                int trajanjeSekunde = min * 60;

                if (vrijemeProvedenoSekunde <= trajanjeSekunde)
                {
                    cjenovnik.close();
                    return cijena;
                }

                // Ako je trajanje 1h, zapamti cijenu za vise od 3h
                if (min == 1)
                {
                    cijenaZaJedanSat = cijena;
                }
            }
        }

        cjenovnik.close();

        // Ako je vrijeme vece od 3 sata, racunamo kao broj sati * cijena za 1h
        if (vrijemeProvedenoSekunde > 3 * 60 && cijenaZaJedanSat > 0)
        {
            int brojMin = (vrijemeProvedenoSekunde + 59) / 60; // Zaokruzi na sledeci sat
            return brojMin * cijenaZaJedanSat;
        }

        return -1; 
    }
    // Funkcija za proveru izlaska sa parkinga
    static bool provjeriIzlazak(const time_t &vrijemePlacanja)
    {
        
        // Trenutno vrijeme
        auto sada = chrono::system_clock::now();
        time_t trenutnoVrijeme = chrono::system_clock::to_time_t(sada);

        // Razlika u sekundama između trenutnog vremena i vremena plaćanja
        int protekloVrijemeSekunde = difftime(trenutnoVrijeme, vrijemePlacanja);

        if (protekloVrijemeSekunde <= 30)
        {
            cout << "Izlazak sa parkinga dozvoljen. Rampa se diže." << endl;
            // izlazak sa parkinga
            return true;
        }
        else
        {
            cout << "Izlazak nije moguć. Ponovno izvršite plaćanje." << endl;
            return false;
        }
    }


    
    // Metod za generisanje računa
   static void generisiRacun(const string& izborPlacanja, double cijena) {
    // Dobavljanje trenutnog vremena
    auto sada = chrono::system_clock::now();
    time_t trenutnoVrijeme = chrono::system_clock::to_time_t(sada);
    tm *trenutnoVrijemeTm = localtime(&trenutnoVrijeme);

    // Otvorite fajl za upis računa
    ofstream racunFile("../files/racun.txt");
    if (!racunFile) {
        cerr << "Greska prilikom otvaranja fajla za upis računa.\n";
        return;
    }

    // Formatirajte datum i vreme
    stringstream racunContent;
    racunContent << "Račun za plaćanje parkinga\n";
    racunContent << "--------------------------------\n";
    racunContent << "Datum i vrijeme: " << put_time(trenutnoVrijemeTm, "%d-%m-%Y %H:%M:%S") << "\n";
    racunContent << "Nacin naplate: " << izborPlacanja << "\n";
    racunContent << "Cijena parkinga: " << fixed << setprecision(2) << cijena << " KM\n";
    racunContent << "Hvala Vam na posjeti!\n";

    cout << racunContent.str() << endl;

    // Upisivanje računa u fajl
    racunFile << racunContent.str();
    racunFile.close();
}
static void izborPlacanja(double cijena, bool& placeno)
{
    cout << "Odaberite nacin placanja:\n1. Bankarska kartica\n2. Gotovina\n3. Mjesecna karta\n4. Invalidska kartica\nIzbor: ";
    int izbor;
    cin >> izbor;

    switch (izbor)
    {
    case 1:
    {
        cout << "Unesite ID kartice: ";
        string idKartice;
        cin >> idKartice;

        BankarskaKartica kartica;

        if (!kartica.imaRacun(idKartice))
        {
            cout << "Kartica nije registrovana u banci." << endl;
            placeno = false;
            return;
        }

        if (!kartica.jeValidna())
        {
            cout << "Kartica nije validna." << endl;
            placeno = false;
            return;
        }

        placeno = kartica.placanje(cijena);
        generisiRacun("Bankarska kartica", cijena);

        break;
    }
    case 2:
    {
        double uplaceniIznos;
        double preostaliIznos = cijena;

        do
        {
            cout << "Unesite iznos koji ste ubacili: ";
            cin >> uplaceniIznos;

            if (uplaceniIznos < preostaliIznos)
            {
                preostaliIznos -= uplaceniIznos;
                cout << "Nedovoljno novca. Potrebno je jos " << fixed << setprecision(2) << preostaliIznos << " KM." << endl;
            }
            else
            {
                cout << "Placanje uspjesno. Kusur: " << fixed << setprecision(2) << uplaceniIznos - preostaliIznos << " KM." << endl;
                preostaliIznos = 0;
                generisiRacun("Gotovina", cijena);
            }

        } while (preostaliIznos > 0);
        placeno = true;
        break;
    }
    case 3:
    {
        MjesecnaKartica mKarta;
        std::string uIme, uPrezime;

        std::cout << "Unesite ime: ";
        std::cin >> uIme;
        std::cout << "Unesite prezime: ";
        std::cin >> uPrezime;

        mKarta.getKartica(uIme, uPrezime);
        if (!mKarta.jeValidna())
        {
            cout << "Karta nije validna. Izaberite drugi nacin placanja" << endl;
            placeno = false;
            return;
        }
        if (mKarta.jeValidna())
        {
            cout << "Placanje uspjesno." << endl;
            placeno = true;
            generisiRacun("Mjesecna kartica", cijena);
        }
        break;
    }
    case 4:
    {
        InvalidskaKartica iKarta;
        std::string uIme, uPrezime;

        std::cout << "Unesite ime: ";
        std::cin >> uIme;
        std::cout << "Unesite prezime: ";
        std::cin >> uPrezime;
        bool imaKarte = iKarta.getKartica(uIme, uPrezime);
        if (!imaKarte)
        {
            cout << "Karta nije validna. Izaberite drugi nacin placanja." << endl;
            placeno = false;
            return;
        }
        if (imaKarte)
        {
            cout << "Placanje uspjesno." << endl;
            placeno = true;
            generisiRacun("Invalidska kartica", cijena);
        }
        break;
    }
    default:
        cout << "Nepoznata opcija." << endl;
        placeno = false;
    }
}



    
        
};
