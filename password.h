#ifndef PASSWORD_MANAGER_PASSWORD_H
#define PASSWORD_MANAGER_PASSWORD_H

#include <string>

std::string imitowanieLosowosci_generowanie_hasla(const int ilosc_znakow, const bool wielkie, const bool specjalne, const std::string& nazwa);
std::string sprawdzanieSilyHasla(std::string haslo);
std::string edycjaHasla(const std::string& nazwaPliku);
void wyszukajHaslo(const std::string& nazwaPliku, const std::string& szukaneHaslo, const std::string& parametr);
std::string wyszukajWszystkieHasla(const std::string& nazwaPliku, const std::string& szukaneHaslo);

#endif //PASSWORD_MANAGER_PASSWORD_H
