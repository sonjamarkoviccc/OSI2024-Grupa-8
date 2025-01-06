#include <iostream>
#include <stdlib.h>
#include <stdio.h>

class BankarskaKartica
{
    private:
        std::string idKartice;
        double stanje;

    public:
        BankarskaKartica(const std::string& id, double saldo)
        : idKartice(id), stanje(saldo) {}

        const std::string& getIdKartice() const {
            return idKartice;
        }

        double getStanje() const {
            return stanje;
        }

        bool jeValidna() const
        {
            if (idKartice.empty()) {
                return false;
            }
            for (char c : idKartice) {
                if (!isdigit(c)) {
                    return false;
                }
            }
            return true;
        }
};