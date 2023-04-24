#include "files.h"
/**
 * Sprawdzenie czy podany plik istnieje
 * Struktura sprawdzajaca prawdziwosc warunku
 *
 * @param podanyPlik w momencie wywolania funkcji przez parametr jest przekazywana nazwa pliku, ktory jest poddawany sprawdzeniu
 * @return zwracana jest wartosc typu logicznego aby dac informacje czy prawda jest, ze plik istnieje
 */
bool czyPlikIstnieje(const std::string& podanyPlik)
{
    struct stat buf {};
    //somehow i managed to replaced it with a stream
//    if (stat(podanyPlik.c_str(), &buf) != -1) {
//        return true;
//    }
    return false;
}