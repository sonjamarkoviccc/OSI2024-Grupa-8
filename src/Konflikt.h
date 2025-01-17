#include <cstdio>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

class Konflikt
{
    private:
        struct Zalba {
            int id;
            std::string text;
            std::string email;
            std::string date;
            std::string answer;
        };

        int sljedeciID(const std::vector<Zalba>& Zalbas)
        {
            int maxID = 0;
            for (const auto& Zalba : Zalbas) {
                if (Zalba.id > maxID) {
                    maxID = Zalba.id;
                }
            }
            return maxID + 1;
        }

        std::string danasnjiDatum()
        {
            std::time_t t = std::time(nullptr);
            std::tm tm = *std::localtime(&t);

            std::ostringstream oss;
            oss << std::put_time(&tm, "%d.%m.%Y");
            return oss.str();
        }

    public:
        std::vector<Zalba> ucitajZalbe() {
            std::vector<Zalba> zalbe;
            std::ifstream file("../files/zalbe.txt");
            std::string line;

            while (std::getline(file, line)) {
                std::istringstream iss(line);
                Zalba Zalba;
                std::getline(iss, line, '|');
                Zalba.id = std::stoi(line);
                std::getline(iss, Zalba.text, '|');
                std::getline(iss, Zalba.email, '|');
                std::getline(iss, Zalba.date, '|');
                std::getline(iss, Zalba.answer);

                zalbe.push_back(Zalba);
            }

            return zalbe;
        }

        void sacuvajZalbe(const std::vector<Zalba>& zalbe) {
            std::ofstream file("../files/zalbe.txt");
            for (const auto& Zalba : zalbe) {
                file << Zalba.id << " | " << Zalba.text << " | "
                    << Zalba.email << " | " << Zalba.date << " | "
                    << Zalba.answer << "\n";
            }
        }

        void prikaziZalbe(const std::vector<Zalba>& zalbe) {
            std::cout << "\nZalbe:\n";
            std::cout << "------------------------------" << std::endl;
            for (const auto& Zalba : zalbe) {
                std::cout << "ID: " << Zalba.id
                        << "\nTekst: " << Zalba.text
                        << "\nEmail: " << Zalba.email
                        << "\nDatum: " << Zalba.date << "\n\n";
            }
        }

        void dodajZalbu()
        {
            std::vector<Zalba> zalbe = ucitajZalbe();
            Zalba newZalba;
            newZalba.id = sljedeciID(zalbe);

            std::cout << "Unesite zalbu: ";
            std::cin.ignore();
            std::getline(std::cin, newZalba.text);

            std::cout << "Unesite email: ";
            std::getline(std::cin, newZalba.email);

            newZalba.date = danasnjiDatum();

            newZalba.answer = "";
            zalbe.push_back(newZalba);

            sacuvajZalbe(zalbe);

            std::cout << "Zalba dodata" << "\n";
        }

        void rijesiKonflikt()
        {
            std::vector<Zalba> zalbe = ucitajZalbe();
            if (sljedeciID(zalbe) > 1)
            {
                prikaziZalbe(zalbe);
                int id;
                std::cout << "Unesite broj zalbe koju hocete da rijesite: ";
                std::cin >> id;

                bool found = false;
                for (auto it = zalbe.begin(); it != zalbe.end(); ++it) {
                    if (it->id == id) {
                        found = true;
                        std::cout << "To: " << it->email << std::endl;
                        std::cout << "Unesite odgovor: ";
                        std::cin.ignore();
                        std::getline(std::cin, it->answer);

                        zalbe.erase(it);
                        sacuvajZalbe(zalbe);
                        std::cout << "Zalba je uspjesno rijesena.\n";
                        break;
                    }
                }

                if (!found) {
                    std::cout << "Zalba sa ID " << id << " nije pronadjena.\n";
                }
            }
            else {
                std::cout << "Nema aktivnih zalbi." << std::endl;
            }
        }
};