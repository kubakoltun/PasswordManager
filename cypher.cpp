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