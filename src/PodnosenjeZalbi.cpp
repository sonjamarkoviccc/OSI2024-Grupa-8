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
        std::getline(std::cin, tekstZalbe);

        std::ofstream file("../files/zalbe.txt", std::ios::app); 
        if (!file)
        {
            std::cerr << "Greška pri otvaranju fajla!" << std::endl;
            return;
        }

        int poslednjiBroj = dobaviPoslednjiBroj();

        // Formatiraj novu zalbu
        std::stringstream ss;
        ss << poslednjiBroj + 1 << "|" << tekstZalbe << "|aktivna|\n";

        // Upisivanje nove zalbe u fajl
        file << ss.str();
        file.close();

        std::cout << "Zalba je uspješno unijeta!" << std::endl;
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

/*int main()
{
    PodnosenjeZalbi zalba;
    zalba.unesiZalbu();

    return 0;
}*/
