#pragma once
#include <cstdio>
#include "Konflikt.h"
#include "Nalog.h"
#include "Parking.h"

class Operater
{
private:
    Konflikt konflikt;
    Nalog nalog;
    Parking parking;

    // void prijava(const char* fajl);

public:
    Operater() : konflikt("../files/zalbe.txt"), parking(10, "ZONA1") {}

    void prijava(const char *fajl);
    void prikazParkiranihVozila();
    void rjesavanjeKonflikta();
    void prikaziMogucnostiOperatera();
};