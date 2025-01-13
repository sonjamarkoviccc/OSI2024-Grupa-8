#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class PodnosenjeZalbi
{
public:
    void unesiZalbu()
    {
        std::string tekstZalbe;
        std::cout << "Unesite tekst zalbe: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, tekstZalbe);

        std::ofstream file("../files/zalbe.txt", std::ios::app); 
        if (!file)
        {
            std::cerr << "Greska pri otvaranju fajla!" << std::endl;
            return;
        }

        int poslednjiBroj = dobaviPoslednjiBroj();

        std::stringstream ss;
        ss << poslednjiBroj + 1 << " | " << tekstZalbe << " | aktivna |\n";

        file << ss.str();
        file.close();

        std::cout << "Zalba je uspjesno unijeta!" << std::endl;
    }

private:
    int dobaviPoslednjiBroj()
    {
        std::ifstream file("../files/zalbe.txt");
        if (!file)
        {
            return 1; 
        }

        int poslednjiBroj = 0;
        std::string line;
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            int broj;
            ss >> broj;
            if (ss && broj > poslednjiBroj)
            {
                poslednjiBroj = broj;
            }
        }
        file.close();
        return poslednjiBroj;
    }
};