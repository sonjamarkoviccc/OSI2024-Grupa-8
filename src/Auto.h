#pragma once
#include <string>

class Auto{
    private:
        std::string registracija;

    
    public:
        Auto(std::string registracija): registracija(registracija){}

        std:: string getRegistracija()const {return registracija; }
};