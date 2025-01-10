#pragma once
#include <cstdio>
#include "Nalog.h"
#include "UpravljanjeNalozima.h"
#include "MjesecnaKartica.h"
#include "InvalidskaKartica.h"
#include "Izvjestaj.h"
#include "CjenovnikParkinga.h"

class Uprava
{
private:
    UpravljanjeNalozima upravljanjeNalozima;

public:
    Uprava() {}
    ~Uprava() {}

    void definisanjeCjenovnika(CjenovnikParkinga& cjenovnik)
    {
        cjenovnik.pokreniProgram();
    }
    void izvjestajORadu(Izvjestaj& izvjestaj)
    {
        izvjestaj.pokreniProgram();
    }
    void izdavanjeMjesecneKarte(MjesecnaKartica& mjesecna)
    {
        mjesecna.izdajaKartice();
        std::cout << "Uspjesno dodata mjesecna kartica.\n" << "Ime: " << mjesecna.getIme() << "\n"
                  << "Prezime: " << mjesecna.getPrezime() << "\n" << "Datum Izdaje: " << mjesecna.getDatumIzdaje() << "\n"
                  << "Datum Isteka: " << mjesecna.getDatumIsteka() << std::endl;
    }
    void izdavanjeInvalidskeKarte(InvalidskaKartica& invalidska)
    {
        invalidska.izdajaKartice();
        std::cout << "Uspjesno dodata invalidska kartica.\n" << "Ime: " << invalidska.getIme() << "\n"
                  << "Prezime: " << invalidska.getPrezime() << "\n" << "Datum Izdaje: " << invalidska.getDatumIzdaje() << std::endl;
    }
    void upravljanjeNalozimaOpcije(const char *fajl);
    void prijava(const char *fajl);
    void prikaziMogucnostiUprave();
};
