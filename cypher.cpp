#include "cypher.h"
#include <string>

/**
 * Impementacja metody szyfrowania
 * Przekazany string trafia do petli, w ktorej kazdy jego znak ASCII zostaje przesuniety
 *
 * @param fraza przekazany string staje sie baza do wprowadzenia szyfru
 * @return zwracany zostaje poddany szyfrowaniu ciag znakow
 */
std::string szyfrujWejscie(std::string fraza) {
    size_t rozmiar_hasla = fraza.length();
    std::string szyfr;
    char trzym = ' ';
    for (size_t i = 0; i < rozmiar_hasla; i++) {
        trzym = fraza[i];
        trzym += 1;
        szyfr += trzym;
    }

    return szyfr;
}

/**
 * Przekazywana jest zaszyfrowana tresc
 * String zostaje odszyfrowany
 * Petla przesuwa znaki ASCII stringa do przed szyfrowaniem
 *
 * @param rozFraza string ktory ma zostac rozszyfrowany
 * @return zwracany jest rozszyfrowany coag znakow
 */
std::string rozszyfrujFraze(std::string rozFraza) {
    size_t rozmiar_hasla = rozFraza.length();
    std::string rozszyfrowane;
    char otrzym = ' ';
    for (size_t i = 0; i < rozmiar_hasla; i++) {
        otrzym = rozFraza[i];
        otrzym -= 1;
        rozszyfrowane += otrzym;
    }

    return rozszyfrowane;
}