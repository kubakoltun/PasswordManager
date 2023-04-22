#include "time_stamp.h"
#include <chrono>
#include <ctime>

/**
 * Metoda odczytuje obecna date i czas, zawsze w tym samym formacie
 * Odpowiednia czesc godziny jest ujmowana jako zmienna
 *
 * @param przelacznik Na podstawie przekazanego parametru zapada decyzja, ktora czesc godziny jest zwracana
 * @return Zwracana jest dany fragment godziny z dopiskiem DDDD zaleznie od parametru
 * W przypadku nie podania parametru podawana jest informacja o niepoprawnym wywolaniu metody
 */
std::string sprawdzCzas(const std::string& przelacznik) {
    auto start = std::chrono::system_clock::now();
    auto legacyStart = std::chrono::system_clock::to_time_t(start);
    char tmBuff[30];
    ctime_s(tmBuff, sizeof(tmBuff), &legacyStart);

    std::string time = tmBuff;
    std::string h;
    std::string m;
    std::string s;
    h += time[11];
    h += time[12];
    m += time[14];
    m += time[15];
    s += time[17];
    s += time[18];
    if (przelacznik == "h") {
        h += "DDDD";
        return h;
    }
    if (przelacznik == "m") {
        m += "DDDD";
        return m;
    }
    if (przelacznik == "s") {
        s += "DDDD";
        return s;
    }
    else {

        return "blednie wczytano parametry";
    }
}