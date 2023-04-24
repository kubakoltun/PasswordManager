#pragma once
#include "password.cpp"
#include "cypher.h"
#include "files.h"
#include "time_stamp.h"
#include <string>

std::string imitowanieLosowosci_generowanie_hasla(const int ilosc_znakow, const bool wielkie, const bool specjalne, const std::string& nazwa);
std::string sprawdzanieSilyHasla(std::string haslo);
std::string edycjaHasla(const std::string& nazwaPliku);
void wyszukajHaslo(const std::string& nazwaPliku, const std::string& szukaneHaslo, const std::string& parametr);
std::string wyszukajWszystkieHasla(const std::string& nazwaPliku, const std::string& szukaneHaslo);
