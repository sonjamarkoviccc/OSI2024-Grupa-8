#pragma once
#include <cstdio>
#include "Nalog.h"
#include "UpravljanjeNalozima.h"

class Uprava
{
private:
    UpravljanjeNalozima upravljanjeNalozima;

public:
    Uprava() {}
    ~Uprava() {}

    void definisanjeCenovnika();
    void izvestajORadu();
    void izdavanjeMjesecneGodisnjeKarte();
    void upravljanjeNalozimaOpcije(const char *fajl);
    void prijava(const char *fajl);
    void prikaziMogucnostiUprave();
};
