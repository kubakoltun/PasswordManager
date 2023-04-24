#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <vector>
#include <chrono>

#include "time_stamp.h"
#include "cypher.h"
#include "files.h"



/**
 * Metoda pobiera jako parametry wprowadzone przez uzytkownika zmienne informujace o wymiarach hasla
 * W zaleznosci od zmiennych uzytkownika haslo bedzie wzbogacane o dany znak ujety w przedziale petli jako znak ASCII
 * Seria warunkow ma za zadanie imitowac losowosc w efekcie czego zwrocic uzytkownikowi niepowtarzalne haslo
 *
 * @param ilosc_znakow dlugosc hasla jaka zadeklarowal uzytkownik
 * @param wielkie informacja czy haslo bedzie zawierac wielkie znaki
 * @param specjalne informacja czy haslo bedzie znaki specjalne
 * @param nazwa parametr decyzyjny, dlugosc podanej nazwy dla hasla jest jedna z podstaw do warunkow
 * @return zwracane jest haslo utworzone w oparciu o podane kryteria
 */
std::string imitowanieLosowosci_generowanie_hasla(const int ilosc_znakow, const bool wielkie, const bool specjalne, const std::string& nazwa) {
    size_t nazwa_dlugosc = nazwa.size();
    std::string losowe_haslo;
    int wprowadzone_znaki = 0;

    if (wielkie) {
        int wstrzymanie_wielkie = 0;
        for (int i = 65; i <= 90; i++) {
            if (wstrzymanie_wielkie == 3) {
                break;
            }
            if (ilosc_znakow % 2 == 0 && nazwa_dlugosc % 2 != 0 && i > 73 && ilosc_znakow > 0 && wstrzymanie_wielkie <= 3) {
                losowe_haslo += i + 2;
                wstrzymanie_wielkie++;
                wprowadzone_znaki++;
                i++;
            }
            if (ilosc_znakow % 2 == 0 && nazwa_dlugosc % 2 == 0 && i > 70 && ilosc_znakow > 1 && wstrzymanie_wielkie <= 3) {
                losowe_haslo += i + 3;
                wstrzymanie_wielkie++;
                wprowadzone_znaki++;
                i++;
            }
            if (ilosc_znakow % 2 != 0 && nazwa_dlugosc % 2 == 0 && i > 67 && ilosc_znakow > 2 && wstrzymanie_wielkie <= 3) {
                losowe_haslo += i + 4;
                wstrzymanie_wielkie++;
                wprowadzone_znaki++;
                i++;
            }
            if (ilosc_znakow % 2 != 0 && nazwa_dlugosc % 2 != 0 && i >= 65 && ilosc_znakow > 3 && wstrzymanie_wielkie <= 3) {
                losowe_haslo += i + 3;
                wstrzymanie_wielkie++;
                wprowadzone_znaki++;
                i++;
            }
        }
    }

    if (specjalne) {
        std::string specjalne_znk[32] = { "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+", "-", "=", "`", "~", "{", "}", "[", "]", ":", ";", "'", "\"", ",", ".", "/", "<", ">", "?", "|", "\\" };
        int wstrzymanie_specjalne = 0;
        for (int i = 0; i < 32; i++) {
            if (wstrzymanie_specjalne == 2) {
                break;
            }
            if (ilosc_znakow % 2 == 0 && nazwa_dlugosc % 2 != 0 && i > 8 && ilosc_znakow > 0 && wstrzymanie_specjalne <= 2) {
                losowe_haslo += specjalne_znk[i + 1];
                wstrzymanie_specjalne++;
                wprowadzone_znaki++;
                i++;
            }
            if (ilosc_znakow % 2 == 0 && nazwa_dlugosc % 2 == 0 && i > 6 && ilosc_znakow > 1 && wstrzymanie_specjalne <= 2) {
                losowe_haslo += specjalne_znk[i + 2];
                wstrzymanie_specjalne++;
                wprowadzone_znaki++;
                i++;
            }
            if (ilosc_znakow % 2 != 0 && nazwa_dlugosc % 2 == 0 && i > 4 && ilosc_znakow > 2 && wstrzymanie_specjalne <= 2) {
                losowe_haslo += specjalne_znk[i + 4];
                wstrzymanie_specjalne++;
                wprowadzone_znaki++;
                i++;
            }
            if (ilosc_znakow % 2 != 0 && nazwa_dlugosc % 2 != 0 && i > 0 && ilosc_znakow > 3 && wstrzymanie_specjalne <= 2) {
                losowe_haslo += specjalne_znk[i + 5];
                wstrzymanie_specjalne++;
                wprowadzone_znaki++;
                i++;
            }
        }
    }

    std::string cyfry[10] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };
    int wstrzymanie_cyfry = 0;
    for (int i = 0; i < 10; i++) {
        if (wstrzymanie_cyfry == 2) {
            break;
        }
        if (ilosc_znakow % 2 == 0 && nazwa_dlugosc % 2 != 0 && i > 3 && ilosc_znakow > 0 && wstrzymanie_cyfry <= 2) {
            losowe_haslo += cyfry[i + 1];
            wstrzymanie_cyfry++;
            wprowadzone_znaki++;
            i++;
        }
        if (ilosc_znakow % 2 == 0 && nazwa_dlugosc % 2 == 0 && i > 2 && ilosc_znakow > 1 && wstrzymanie_cyfry <= 2) {
            losowe_haslo += cyfry[i + 2];
            wstrzymanie_cyfry++;
            wprowadzone_znaki++;
            i++;
        }
        if (ilosc_znakow % 2 != 0 && nazwa_dlugosc % 2 == 0 && i > 1 && ilosc_znakow > 2 && wstrzymanie_cyfry <= 2) {
            losowe_haslo += cyfry[i + 2];
            wstrzymanie_cyfry++;
            wprowadzone_znaki++;
            i++;
        }
        if (ilosc_znakow % 2 != 0 && nazwa_dlugosc % 2 != 0 && i >= 0 && ilosc_znakow > 3 && wstrzymanie_cyfry <= 2) {
            losowe_haslo += cyfry[i + 3];
            wstrzymanie_cyfry++;
            wprowadzone_znaki++;
            i++;
        }
    }

    int ilosc_pozostalych = ilosc_znakow - wprowadzone_znaki;
    std::string alfabet[26] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };
    int ktora_litera = 0;
    int wstrzymanie_alfabet = 0;
    for (int i = 0; i < ilosc_pozostalych; i++) {
        if (ktora_litera >= 26) {
            ktora_litera = 1;
        }
        if (wstrzymanie_alfabet == ilosc_pozostalych) {
            break;
        }
        if (ilosc_znakow % 2 != 0 && nazwa_dlugosc % 2 != 0 && ilosc_pozostalych % 2 != 0) {
            losowe_haslo += alfabet[ktora_litera];
            ktora_litera += 8;
            wstrzymanie_alfabet++;
        }
        if (ilosc_znakow % 2 == 0 && nazwa_dlugosc % 2 == 0 && ilosc_pozostalych % 2 == 0) {
            losowe_haslo += alfabet[ktora_litera];
            ktora_litera += 8;
            wstrzymanie_alfabet++;
        }
        if (ilosc_znakow % 2 != 0 && nazwa_dlugosc % 2 == 0 && ilosc_pozostalych % 2 == 0) {
            losowe_haslo += alfabet[ktora_litera];
            ktora_litera += 8;
            wstrzymanie_alfabet++;
        }
        if (ilosc_znakow % 2 != 0 && nazwa_dlugosc % 2 != 0 && ilosc_pozostalych % 2 == 0) {
            losowe_haslo += alfabet[ktora_litera];
            ktora_litera += 8;
            wstrzymanie_alfabet++;
        }
        if (ilosc_znakow % 2 != 0 && nazwa_dlugosc % 2 == 0 && ilosc_pozostalych % 2 != 0) {
            losowe_haslo += alfabet[ktora_litera];
            ktora_litera += 8;
            wstrzymanie_alfabet++;
        }
        if (ilosc_znakow % 2 == 0 && nazwa_dlugosc % 2 == 0 && ilosc_pozostalych % 2 != 0) {
            losowe_haslo += alfabet[ktora_litera];
            ktora_litera += 8;
            wstrzymanie_alfabet++;
        }
        if (ilosc_znakow % 2 != 0 && nazwa_dlugosc % 2 == 0 && ilosc_pozostalych % 2 == 0) {
            losowe_haslo += alfabet[ktora_litera];
            ktora_litera += 8;
            wstrzymanie_alfabet++;
        }
        if (ilosc_znakow % 2 == 0 && nazwa_dlugosc % 2 != 0 && ilosc_pozostalych % 2 == 0) {
            losowe_haslo += alfabet[ktora_litera];
            ktora_litera += 8;
            wstrzymanie_alfabet++;
        }
    }

    return losowe_haslo;
}

/**
 * Haslo jest sprawdzane pod katem posiadania odpowiendihc znakow
 * Sumy znakow w hasle sa nastepnie sprawdzane wedlug kryteriow bezpieczenstwa
 *
 * @param haslo haslo ktorego sila jest sprawdzana
 * @return w zaleznosci od posiadanych przez haslo cech zwracany jest stopien jego bezpieczenstwa
 */
std::string sprawdzanieSilyHasla(std::string haslo) {
    std::string sila_hasla;
    int male_litery = 0;
    int wielkie_litery = 0;
    int znaki_specjalne = 0;
    int cyfry = 0;
    int znaki = 0;

    for (size_t i = 0; i < haslo.length(); i++) {
        if (haslo[i] >= 97 && haslo[i] <= 122) {
            male_litery++;
            znaki++;
        }
        if (haslo[i] >= 65 && haslo[i] <= 90) {
            wielkie_litery++;
            znaki++;
        }
        if (haslo[i] >= 48 && haslo[i] <= 57) {
            cyfry++;
            znaki++;
        }
        if ((haslo[i] >= 0 && haslo[i] <= 47) || (haslo[i] >= 58 && haslo[i] <= 64) || (haslo[i] >= 91 && haslo[i] <= 96) || (haslo[i] >= 123 && haslo[i] <= 127)) {
            znaki_specjalne++;
            znaki++;
        }
    }

    if (znaki >= 12 && male_litery > 3 && wielkie_litery > 3 && cyfry > 2 && znaki_specjalne >= 2) {
        sila_hasla = "Swietne";
    }
    else if (znaki >= 9 && male_litery > 2 && wielkie_litery > 2 && cyfry >= 2) {
        sila_hasla = "Dobre";
    }
    else if (znaki >= 8 && male_litery >= 1 && wielkie_litery >= 1 && cyfry >= 1) {
        sila_hasla = "Srednie";
    }
    else if (znaki > 4 && znaki < 8) {
        sila_hasla = "Slabe";
    }
    else {
        sila_hasla = "Niebezpieczne";
    }

    return sila_hasla;
}

/**
 * Po sprawdzeniu czy plik otworzyl sie poprawnie sprawdzane jest czy, ktorys z parametrow zostal pominiety
 * Do pliku wprowadzane sa wpisane przez uzytkownika biezaco szyfrowane parametry
 * Dana wartosc parametru jest poprzedzona rowniez szyfrowanym kluczem
 * Jako ze sa wykonywane operacje na danych do pliku jest rowniez wprowadzany timestamp
 *
 * @param nazwaPliku nazwa pliku, na ktorym beda wykonywane akcje
 * @param nazwa wprowadzona przez uzytkownika nazwa przypisana do hasla
 * @param haslo zadeklarowane przez uzytkownika haslo
 * @param kategoria kategoria ktora uzytkownik przypisal do hasla
 * @param login login podany przez uzytkownika
 * @param strona strona www przypisana do haslo przez uzytkownika
 * @return nazwa pliku, na ktorym zostala wykonana operacja jest zwracana jako czesc komunikatu
 */
std::string wpisanieDoPliku(std::string nazwaPliku, const std::string& nazwa, const std::string& haslo, std::string kategoria, const std::string& login, const std::string& strona) {

    if (czyPlikIstnieje(nazwaPliku)) {
        std::ofstream biezacyPlik;
        biezacyPlik.open(nazwaPliku);
        if (!nazwa.empty()) {
            biezacyPlik << szyfrujWejscie("Nazwa: ") << szyfrujWejscie(nazwa) << std::endl;
        }
        biezacyPlik << szyfrujWejscie("Kategoria: ") << szyfrujWejscie(std::move(kategoria)) << std::endl;
        if (strona != "-") {
            biezacyPlik << szyfrujWejscie("Strona WWW: ") << szyfrujWejscie(strona) << std::endl;
        }
        if (login != "-") {
            biezacyPlik << szyfrujWejscie("Login: ") << szyfrujWejscie(login) << std::endl;
        }
        if (!haslo.empty()) {
            biezacyPlik << szyfrujWejscie("Haslo: ") << szyfrujWejscie(haslo) << std::endl;
        }

        biezacyPlik.close();

        std::ifstream obecnyPlik;
        std::vector<std::string> linie;
        std::string obecnaLinia;
        obecnyPlik.open(nazwaPliku);

        while (getline(obecnyPlik, obecnaLinia)) {
            linie.push_back(obecnaLinia);
        }
        biezacyPlik.close();

        std::ofstream zapisDoPliku;
        zapisDoPliku.open(nazwaPliku);
        for (int i = 0; i < linie.size(); i++) {
            if (i == 11) {
                zapisDoPliku << sprawdzCzas("h") << std::endl;
            }
            if (i == 22) {
                zapisDoPliku << sprawdzCzas("m") << std::endl;
            }
            if (i == 33) {
                zapisDoPliku << sprawdzCzas("s") << std::endl;
            }
            zapisDoPliku << linie[i] << std::endl;
        }

        if (linie.size() < 33) {
            std::string zmie = "e";
            for (int i = linie.size(); i < 35; i++) {
                zmie += 2;
                if (i == 11) {
                    zapisDoPliku << sprawdzCzas("h") << std::endl;
                }
                if (i == 22) {
                    zapisDoPliku << sprawdzCzas("m") << std::endl;
                }
                if (i == 33) {
                    zapisDoPliku << sprawdzCzas("s") << std::endl;
                }
                zapisDoPliku << szyfrujWejscie("1nied3ozla2man4ia5") << szyfrujWejscie(zmie) << std::endl;
            }
        }
        zapisDoPliku.close();

        return nazwaPliku;
    }
    else {
        std::cout << "Błąd podczas otwierania pliku \"" << nazwaPliku << "\", sprawdz podana sciezke lub nazwe pliku." << std::endl;
    }
}

/**
 * Po otworzeniu pliku odczytywana jest jego tresc po kazdej linii
 * Linie pliku sa pushowane na koniec wektora
 * Uzytkownik dostaje liste parametrow, ktore chce usunac
 * Uzytkownik jest proszony o potwierdzenie wyboru nastepnie aby sfinalizowac zmiany wprowadzane sa zmiany do pliku
 * Linie, ktore wybral uzytkownik nie sa wprowadzane do pliku przez co zostaja usuniete
 * Ze wzgledu na wykonywanie operacji na danych do wpliku wprowadzane sa rowniez timestampy
 *
 * @param nazwaPliku plik, na ktorym bedzie wykonywana operacja
 * @param usuwanieHasla informacja dla metody czy usuwane bedzie haslo
 * @param usuwanieKategorii informacja czy nalezy wejsc w siezke usuwania kategorii
 * @return zwracany jest komunikat o pomyslnosci wykonanych operacji
 */
std::string odczytanieZawartosciPliku(const std::string& nazwaPliku, bool usuwanieHasla, bool usuwanieKategorii) {

    if (czyPlikIstnieje(nazwaPliku)) {
        std::ifstream obecnyPlik;
        std::vector<std::string> linie;
        std::string obecnaLinia;
        int potwierdzUsuwanie = 0;
        int numerLinii = 0;
        obecnyPlik.open(nazwaPliku);
        int wyswietlonaLinia = 1;

        while (getline(obecnyPlik, obecnaLinia)) {
            linie.push_back(obecnaLinia);
            if (usuwanieHasla) {
                if (obecnaLinia.find(szyfrujWejscie("Haslo: ")) != std::string::npos) {
                    std::string usuwanieZbednej;
                    for (int i = 7; i < obecnaLinia.length(); i++) {
                        usuwanieZbednej += obecnaLinia[i];
                    }
                    std::cout << wyswietlonaLinia << ". " << rozszyfrujFraze(obecnaLinia) << std::endl;
                }
            }
            if (usuwanieKategorii) {
                if (obecnaLinia.find(szyfrujWejscie("Kategoria: ")) != std::string::npos) {
                    std::cout << wyswietlonaLinia << ". " << rozszyfrujFraze(obecnaLinia) << std::endl;
                }
                if (obecnaLinia.find(szyfrujWejscie("Haslo: ")) != std::string::npos) {
                    std::cout << " " << rozszyfrujFraze(obecnaLinia) << std::endl;
                }
            }
            wyswietlonaLinia++;
        }
        if (usuwanieHasla) {
            std::cout << "Wpisz numer hasla, ktore chcesz usunac:" << std::endl;
            std::cout << ">";
            std::cin >> numerLinii;
            std::cout << "Usuwasz haslo numer: " << numerLinii << ", \naby potwierdzic wpisz: " << numerLinii << std::endl;
            std::cout << ">";
            std::cin >> potwierdzUsuwanie;
            if (numerLinii != potwierdzUsuwanie) {
                return "Nie udalo ci sie potwierdzic usuniecia hasla.";
            }
        }

        if (usuwanieKategorii) {
            std::cout << "Wpisz numer kategorii, ktora chcesz usunac (wraz z kategoria zostanie usuniete rowniez przypisane do niej haslo)." << std::endl;
            std::cout << ">";
            std::cin >> numerLinii;
            std::cout << "Usuwasz kategorie oraz haslo numer: " << numerLinii << ", \naby potwierdzic wpisz: " << numerLinii << std::endl;
            std::cout << ">";
            std::cin >> potwierdzUsuwanie;
            if (numerLinii != potwierdzUsuwanie) {
                return "Nie udalo ci sie potwierdzic usuniecia kategorii.";
            }
        }
        obecnyPlik.close();

        if (numerLinii > linie.size()) {
            std::cout << "Linia: " << numerLinii << ", nie znajduje sie w pliku." << std::endl;
        }

        std::ofstream zapisDoPliku;
        zapisDoPliku.open(nazwaPliku);
        numerLinii--;
        int numerLiniiWstecz = 0;

        if (usuwanieKategorii) {
            numerLiniiWstecz = numerLinii++;
        }

        for (int i = 0; i < linie.size(); i++) {
            if (usuwanieKategorii) {
                if (i != numerLiniiWstecz && i != numerLinii) {
                    if (i == 11) {
                        zapisDoPliku << sprawdzCzas("h") << std::endl;
                    }
                    if (i == 22) {
                        zapisDoPliku << sprawdzCzas("m") << std::endl;
                    }
                    if (i == 33) {
                        zapisDoPliku << sprawdzCzas("s") << std::endl;
                    }
                    zapisDoPliku << linie[i] << std::endl;

                }
            }
            else if (i != numerLinii) {
                if (i == 11) {
                    zapisDoPliku << sprawdzCzas("h") << std::endl;
                }
                if (i == 22) {
                    zapisDoPliku << sprawdzCzas("m") << std::endl;
                }
                if (i == 33) {
                    zapisDoPliku << sprawdzCzas("s") << std::endl;
                }
                zapisDoPliku << linie[i] << std::endl;
            }
        }

        if (linie.size() < 33) {
            std::string zmie = "g";
            for (int i = linie.size(); i < 35; i++) {
                zmie += 2;
                if (i == 11) {
                    zapisDoPliku << sprawdzCzas("h") << std::endl;
                }
                if (i == 22) {
                    zapisDoPliku << sprawdzCzas("m") << std::endl;
                }
                if (i == 33) {
                    zapisDoPliku << sprawdzCzas("s") << std::endl;
                }
                zapisDoPliku << szyfrujWejscie("1nied3ozla2man4ia5") << szyfrujWejscie(zmie) << std::endl;
            }
        }
        zapisDoPliku.close();

        return "Dokonano wprowadzonych zmian.";
    }
    else {
        std::cout << "Błąd podczas otwierania pliku \"" << nazwaPliku << "\", sprawdz podana sciezke lub nazwe pliku." << std::endl;
    }
}

/**
 * Zawartosc pliku jest wprowadzana do wektora
 * Jednoczesnie uzytkownikowi wyswietlana jest lista hasel
 * Uzytkownik staje przed wyborem edycji danego hasla, ktore bedzie zpaisane poprzez nadpisywanie istniejacej linii, linia nowa utworzona
 * Ze wzgledu na operacje na danych zapisywane sa timestapmy
 *
 * @param nazwaPliku nazwa pliku, na ktorym bedzie wykonywana operacja
 * @return zwracany jest komunikat o pomyslnosci dzialania
 */
std::string edycjaHasla(const std::string& nazwaPliku) {

    if (czyPlikIstnieje(nazwaPliku)) {
        std::ifstream obecnyPlik;
        std::vector<std::string> linie;
        std::string obecnaLinia;
        std::string edytowaneHaslo;
        int numerLinii = 0;
        obecnyPlik.open(nazwaPliku);
        int wyswietlonaLinia = 1;

        while (getline(obecnyPlik, obecnaLinia)) {
            linie.push_back(obecnaLinia);

            if (obecnaLinia.find(szyfrujWejscie("Haslo: ")) != std::string::npos) {
                std::string usuwanieZbednej;
                for (int i = 7; i < obecnaLinia.length(); i++) {
                    usuwanieZbednej += obecnaLinia[i];
                }
                std::cout << wyswietlonaLinia << ". " << rozszyfrujFraze(usuwanieZbednej) << std::endl;
            }
            wyswietlonaLinia++;
        }

        std::cout << "Wpisz numer hasla, ktore chcesz edytowac:" << std::endl;
        std::cout << ">";
        std::cin >> numerLinii;
        std::cout << "Edytujesz haslo numer: " << numerLinii << ", wprowadz zmiany:" << std::endl;
        std::cout << ">";
        std::cin >> edytowaneHaslo;

        obecnyPlik.close();

        if (numerLinii > linie.size()) {
            std::cout << "Linia: " << numerLinii << ", nie znajduje sie w pliku." << std::endl;
        }

        std::ofstream zapisDoPliku;
        zapisDoPliku.open(nazwaPliku);
        numerLinii--;

        for (int i = 0; i < linie.size(); i++) {

            if (i != numerLinii) {
                if (i == 11) {
                    zapisDoPliku << sprawdzCzas("h") << std::endl;
                }
                if (i == 22) {
                    zapisDoPliku << sprawdzCzas("m") << std::endl;
                }
                if (i == 33) {
                    zapisDoPliku << sprawdzCzas("s") << std::endl;
                }
                zapisDoPliku << linie[i] << std::endl;
            }
            else {
                if (i == 11) {
                    zapisDoPliku << sprawdzCzas("h") << std::endl;
                }
                if (i == 22) {
                    zapisDoPliku << sprawdzCzas("m") << std::endl;
                }
                if (i == 33) {
                    zapisDoPliku << sprawdzCzas("s") << std::endl;
                }
                zapisDoPliku << szyfrujWejscie(edytowaneHaslo) << std::endl;
            }
        }

        if (linie.size() < 33) {
            std::string zmie = "v";
            for (int i = linie.size(); i < 35; i++) {
                zmie += 2;
                if (i == 11) {
                    zapisDoPliku << sprawdzCzas("h") << std::endl;
                }
                if (i == 22) {
                    zapisDoPliku << sprawdzCzas("m") << std::endl;
                }
                if (i == 33) {
                    zapisDoPliku << sprawdzCzas("s") << std::endl;
                }
                zapisDoPliku << szyfrujWejscie("1nied3ozla2man4ia5") << szyfrujWejscie(zmie) << std::endl;
            }
        }
        zapisDoPliku.close();

        return "Dokonano wprowadzonych zmian.";
    }
    else {
        std::cout << "Błąd podczas otwierania pliku \"" << nazwaPliku << "\", sprawdz podana sciezke lub nazwe pliku." << std::endl;
    }
}

/**
 * W trakcie wprowadzania lini z pliku do wektora kazda linia zostaje przeszukana pod katem podanych wartosci szukania
 * Uzytkownikowi wyswietlana jest lista parametru oraz przynaleznych do niego hasel
 * Dane zostaja wyswietlane wiec jest pozostawiany timestamp
 *
 * @param nazwaPliku nazwa pliku, na ktorym bedzie wykonywana operacja
 * @param szukaneHaslo wartosc parametru, ze wzgledu na ktora bedzie przeszukiwany plik
 * @param parametr klucz wartosci parametru wprowadzony w zaleznosci od wybranej przez uzytkownika opcji szukania
 */
void wyszukajHaslo(const std::string& nazwaPliku, const std::string& szukaneHaslo, const std::string& parametr) {
    if (czyPlikIstnieje(nazwaPliku)) {
        std::ifstream obecnyPlik;
        std::vector<std::string> linie;
        std::string obecnaLinia;
        std::string wyswietlaneHaslo;
        std::string poszukiwany = parametr + szukaneHaslo;
        int numerLinii = 0;
        int wyswietlonaLinia = 1;
        obecnyPlik.open(nazwaPliku);
        std::string usuwanieZbednej;

        while (std::getline(obecnyPlik, obecnaLinia)) {
            linie.push_back(obecnaLinia);

            if (obecnaLinia.find(szyfrujWejscie(poszukiwany)) != std::string::npos) {
                std::cout << wyswietlonaLinia << ". " << rozszyfrujFraze(obecnaLinia) << std::endl;
                usuwanieZbednej = "";
            }
            if (obecnaLinia.find(szyfrujWejscie("Haslo: ")) != std::string::npos && usuwanieZbednej.empty()) {
                for (int i = 7; i < obecnaLinia.length(); i++) {
                    usuwanieZbednej += obecnaLinia[i];
                }
                std::cout << wyswietlonaLinia << ". " << rozszyfrujFraze(usuwanieZbednej) << std::endl;
            }
            wyswietlonaLinia++;
        }
        obecnyPlik.close();

        std::ofstream zapisDoPliku;
        zapisDoPliku.open(nazwaPliku);
        numerLinii--;

        for (int i = 0; i < linie.size(); i++) {
            if (i != numerLinii) {
                if (i == 11) {
                    zapisDoPliku << sprawdzCzas("h") << std::endl;
                }
                if (i == 22) {
                    zapisDoPliku << sprawdzCzas("m") << std::endl;
                }
                if (i == 33) {
                    zapisDoPliku << sprawdzCzas("s") << std::endl;
                }
                zapisDoPliku << linie[i] << std::endl;
            }
        }

        if (linie.size() < 33) {
            std::string zmie = "e";
            for (int i = linie.size(); i < 35; i++) {
                zmie += 2;
                if (i == 11) {
                    zapisDoPliku << sprawdzCzas("h") << std::endl;
                }
                if (i == 22) {
                    zapisDoPliku << sprawdzCzas("m") << std::endl;
                }
                if (i == 33) {
                    zapisDoPliku << sprawdzCzas("s") << std::endl;
                }
                zapisDoPliku << szyfrujWejscie("1nied3ozla2man4ia5") << szyfrujWejscie(zmie) << std::endl;
            }
        }
        zapisDoPliku.close();
    }
    else {
        std::cout << "Błąd podczas otwierania pliku \"" << nazwaPliku << "\", sprawdz podana sciezke lub nazwe pliku." << std::endl;
    }
}

/**
 * W trakcie tworzenia wektora trzymajacego tresc pliku sprawdzane sa wystapienia hasla podanego przez uzytkownika
 * Prace w obrebie hasla wymagaja zapisania timestampow
 *
 * @param nazwaPliku plik, na ktorym wykonywana jest operacja
 * @param szukaneHaslo haslo podane przez uztykownika, ktorego wartosc jest wyszukiwana w innych liniach pliku
 * @return zwracany jest komunikat o ilosci wystapien podanego hasla w danym pliku
 */
std::string wyszukajWszystkieHasla(const std::string& nazwaPliku, const std::string& szukaneHaslo) {
    std::string komunikat;
    if (czyPlikIstnieje(nazwaPliku)) {
        std::ifstream obecnyPlik;
        std::vector<std::string> linie;
        std::string obecnaLinia;
        std::string wyswietlaneHaslo;
        int wyswietlonaLinia = 1;
        int ileRazy = 0;
        obecnyPlik.open(nazwaPliku);
        std::string usuwanieZbednej;

        while (std::getline(obecnyPlik, obecnaLinia)) {
            linie.push_back(obecnaLinia);

            if (obecnaLinia.find(szyfrujWejscie("Haslo: ")) != std::string::npos) {
                for (int i = 7; i < obecnaLinia.length(); i++) {
                    usuwanieZbednej += obecnaLinia[i];
                }
                if (rozszyfrujFraze(usuwanieZbednej) == szukaneHaslo) {
                    ileRazy++;
                }
            }
            wyswietlonaLinia++;
        }

        if (ileRazy == 1) {
            komunikat = "Wprowadzono haslo, ktore jeszcze nie wystepuje w tym pliku.";
        }
        else if (ileRazy == 1) {
            komunikat = "Wprowadzono haslo, ktore pojawilo sie juz raz w pliku.";
        }
        else if (ileRazy > 1) {
            komunikat = &"Wprowadzono haslo, ktore pojawilo sie w pliku - "[ileRazy];
            komunikat += " razy.";
        }
        obecnyPlik.close();

        std::ofstream zapisDoPliku;
        zapisDoPliku.open(nazwaPliku);

        for (int i = 0; i < linie.size(); i++) {
            if (i == 11) {
                zapisDoPliku << sprawdzCzas("h") << std::endl;
            }
            if (i == 22) {
                zapisDoPliku << sprawdzCzas("m") << std::endl;
            }
            if (i == 33) {
                zapisDoPliku << sprawdzCzas("s") << std::endl;
            }
            zapisDoPliku << linie[i] << std::endl;
        }

        if (linie.size() < 33) {
            std::string zmie = "l";
            for (int i = linie.size(); i < 35; i++) {
                zmie += '2';
                if (i == 11) {
                    zapisDoPliku << sprawdzCzas("h") << std::endl;
                }
                if (i == 22) {
                    zapisDoPliku << sprawdzCzas("m") << std::endl;
                }
                if (i == 33) {
                    zapisDoPliku << sprawdzCzas("s") << std::endl;
                }
                zapisDoPliku << szyfrujWejscie("1nied3ozla2man4ia5") << szyfrujWejscie(zmie) << std::endl;
            }
        }
        zapisDoPliku.close();
    }
    else {
        std::cout << "Błąd podczas otwierania pliku \"" << nazwaPliku << "\", sprawdz podana sciezke lub nazwe pliku." << std::endl;

    }
    return komunikat;
}

/**
 * Metoda zapisuje wartosc pliku do wektora, ktory nastepnie jest przeszukiwany w petli
 * W petli poszukiwane sa parametry wprowadzone przez uzytkownika, dla ktorych pokaza sie hasla
 *
 * @param nazwaPliku plik, na ktrym bedzie wykonywana operacja
 * @param parametr klucz wartosci parametru podany ze wzgledu na wybor uzytkownika
 * @param parametrDrugi w przypadku sortowania po dwoch parametrach podany przez uzytkownika klucz wartosci parametru
 * @param wprowadzono wartosc parametru wprowadzona przez uzytkownika
 * @param wprowadzonoDwa wartosc drugiego parametru podanego przez uzytkownika
 */
void sortowaniePoParametrach(const std::string& nazwaPliku, const std::string& parametr, const std::string& parametrDrugi, const std::string& wprowadzono, const std::string& wprowadzonoDwa) {
    if (czyPlikIstnieje(nazwaPliku)) {
        std::ifstream obecnyPlik;
        std::vector<std::string> linie;
        std::string obecnaLinia;
        std::string wyswietlaneHaslo;
        std::string poszukiwany = parametr + wprowadzono;
        std::string poszukiwanyDrugi = parametrDrugi + wprowadzonoDwa;
        int numerLinii = 0;
        int wyswietlonaLinia = 1;
        obecnyPlik.open(nazwaPliku);
        std::string przesuniecie;

        while (std::getline(obecnyPlik, obecnaLinia)) {
            linie.push_back(obecnaLinia);
            wyswietlonaLinia++;
        }
        std::string znaleziono;
        for (const auto& i : linie) {
            if (i.find(szyfrujWejscie(poszukiwany)) != std::string::npos || i.find(szyfrujWejscie(poszukiwanyDrugi)) != std::string::npos) {
                przesuniecie = "1";
                znaleziono = "0";
                std::cout << rozszyfrujFraze(i) << std::endl;
            }
            if (obecnaLinia.find(szyfrujWejscie("Haslo: ")) != std::string::npos && przesuniecie == "1" && znaleziono == "0") {
                przesuniecie = "2";
                std::cout << rozszyfrujFraze(i) << std::endl;
            }
            if ((i.find(szyfrujWejscie(parametr)) != std::string::npos || i.find(szyfrujWejscie(parametrDrugi)) != std::string::npos) && znaleziono == "0" && przesuniecie == "2") {
                std::cout << i << std::endl;
            }
            if (i.find(szyfrujWejscie("Haslo: ")) != std::string::npos && znaleziono == "0" && przesuniecie == "2") {
                std::cout << i << std::endl;
            }
        }
        obecnyPlik.close();

        std::ofstream zapisDoPliku;
        zapisDoPliku.open(nazwaPliku);

        for (int i = 0; i < linie.size(); i++) {
            if (i == 11) {
                zapisDoPliku << sprawdzCzas("h") << std::endl;
            }
            if (i == 22) {
                zapisDoPliku << sprawdzCzas("m") << std::endl;
            }
            if (i == 33) {
                zapisDoPliku << sprawdzCzas("s") << std::endl;
            }
            zapisDoPliku << linie[i] << std::endl;
        }

        if (linie.size() < 33) {
            std::string zmie;
            for (int i = linie.size(); i < 35; i++) {
                zmie += 2;
                if (i == 11) {
                    zapisDoPliku << sprawdzCzas("h") << std::endl;
                }
                if (i == 22) {
                    zapisDoPliku << sprawdzCzas("m") << std::endl;
                }
                if (i == 33) {
                    zapisDoPliku << sprawdzCzas("s") << std::endl;
                }
                zapisDoPliku << "1nied3ozla2man4ia5" << szyfrujWejscie(zmie) << std::endl;
            }
        }
        zapisDoPliku.close();
    }
    else {
        std::cout << "Błąd podczas otwierania pliku \"" << nazwaPliku << "\", sprawdz podana sciezke lub nazwe pliku." << std::endl;
    }
}


int main()
{
    bool powtorz = false;
    std::string glownyPlik;

    do {
        powtorz = false;
        std::cout << "Podaj nazwe pliku znajdujacego sie w obecnym folderze lub sciezke absolutna, aby skorzystac z programu:" << std::endl;
        std::cout << ">";
        std::getline(std::cin >> std::ws, glownyPlik);

        if (!czyPlikIstnieje(glownyPlik)) {
            std::cout << "Wprowadzona nazwa lub sciezka pliku nie istnieje: \"" << glownyPlik << "\" wprowadz poprawna nazwe lub sicezke pliku." << std::endl;
            powtorz = true;
        }
        else {
            powtorz = false;
        }
    } while (powtorz);

    do {
        powtorz = false;
        std::string x;
        std::cout << "Wybierz interesujaca Cie komende, wpisujac jej numer: \n 1. Wyszukaj hasla \n 2. Posortuj hasla \n 3. Dodaj haslo \n 4. Edytuj haslo \n 5. Usun haslo \n 6. Dodaj kategorie \n 7. Usun kategorie \n 0. Wyjscie" << std::endl;
        std::cout << ">";
        std::cin >> x;

        if (x == "1" || x == "1.") {

            do {
                powtorz = false;
                std::string wyszukaj_hasla;
                std::cout << "Wybierz zgodnie z czym chesz wyszukac swoje haslo:" << std::endl;
                std::cout << " 1. Wyszukaj hasla po nazwie" << std::endl;
                std::cout << " 2. Wyszukaj hasla po kategorii" << std::endl;
                std::cout << " 3. Wyszukaj hasla po stronie WWW" << std::endl;
                std::cout << " 4. Wyszukaj hasla po loginie" << std::endl;
                std::cout << ">";
                std::cin >> wyszukaj_hasla;

                if (wyszukaj_hasla == "1" || wyszukaj_hasla == "1.") {
                    std::string wh_nazwa;
                    std::cout << "Wpisz nazwe, wedlug ktorej ma zostac wyszukane haslo:" << std::endl;
                    std::cout << ">";
                    std::getline(std::cin >> std::ws, wh_nazwa);

                    std::cout << "Wyniki wyszukiwania:" << std::endl;
                    wyszukajHaslo(glownyPlik, wh_nazwa, "Nazwa: ");

                }
                else if (wyszukaj_hasla == "2" || wyszukaj_hasla == "2.") {
                    std::string wh_kategoria;
                    std::cout << "Wpisz kategorie, wedlug ktorej ma zostac wyszukane haslo:" << std::endl;
                    std::cout << ">";
                    std::getline(std::cin >> std::ws, wh_kategoria);

                    std::cout << "Wyniki wyszukiwania:" << std::endl;
                    wyszukajHaslo(glownyPlik, wh_kategoria, "Kategoria: ");

                }
                else if (wyszukaj_hasla == "3" || wyszukaj_hasla == "3.") {

                    std::string wh_strona;
                    std::cout << "Wpisz strone, wedlug ktorej ma zostac wyszukane haslo:" << std::endl;
                    std::cout << ">";
                    std::getline(std::cin >> std::ws, wh_strona);

                    std::cout << "Wyniki wyszukiwania:" << std::endl;
                    wyszukajHaslo(glownyPlik, wh_strona, "Strona WWW: ");

                }
                else if (wyszukaj_hasla == "4" || wyszukaj_hasla == "4.") {
                    std::string wh_login;
                    std::cout << "Wpisz login, wedlug ktorego ma zostac wyszukane haslo:" << std::endl;
                    std::cout << ">";
                    std::getline(std::cin >> std::ws, wh_login);

                    std::cout << "Wyniki wyszukiwania:" << std::endl;
                    wyszukajHaslo(glownyPlik, wh_login, "Login: ");

                }
                else {
                    std::cout << "Nie znaleziono Twojej komendy: \"" << wyszukaj_hasla << "\". \nSprobuj ponownie wprowadzic cyfre reprezentujaca dana komende.\n" << std::endl;
                    powtorz = true;
                }
            } while (powtorz);
            powtorz = true;
        }
        else if (x == "2" || x == "2.") {

            do {
                powtorz = false;
                std::string parametr_sorotwania;
                std::string parametr_sorotwaniaDwa;
                std::string nazwa_sorotwania;
                std::string kategoria_sorotwania;
                std::string strona_sorotwania;
                std::string login_sorotwania;
                std::string wartosc_parametru;
                std::string kolejny_parametr;

                std::cout << "Wybierz wobec jakich parametrow chcesz posortowac hasla:" << std::endl;
                std::cout << " 1. Nazwa" << std::endl;
                std::cout << " 2. Kategoria" << std::endl;
                std::cout << " 3. Strona WWW" << std::endl;
                std::cout << " 4. Login" << std::endl;
                std::cout << ">";
                std::cin >> parametr_sorotwania;

                if (parametr_sorotwania == "1" || parametr_sorotwania == "1.") {
                    std::cout << "Wpisz naze, wedlug ktorej maja zostac posotrowane hasla:" << std::endl;
                    std::cout << ">";
                    std::getline(std::cin >> std::ws, nazwa_sorotwania);

                    do {
                        powtorz = false;
                        std::cout << "Czy dodac drugi parametr sortowania? Wpisz \"tak\", aby wprowadzic lub \"-\", aby pominac." << std::endl;
                        std::cout << ">";
                        std::cin >> kolejny_parametr;
                        if (kolejny_parametr == "tak") {
                            do {
                                powtorz = false;
                                std::cout << "Wpisz parametr wobec, ktorego maja byc sortowane hasla (\"Kategoria\", \"Strona WWW\", \"Login\")." << std::endl;
                                std::cout << ">";
                                std::getline(std::cin >> std::ws, parametr_sorotwaniaDwa);
                                if (parametr_sorotwaniaDwa == "kategoria" || parametr_sorotwaniaDwa == "Kategoria") {
                                    parametr_sorotwaniaDwa = "Kategoria: ";
                                }
                                else if (parametr_sorotwaniaDwa == "Strona" || parametr_sorotwaniaDwa == "strona" || parametr_sorotwaniaDwa == "Strona WWW" || parametr_sorotwaniaDwa == "strona www") {
                                    parametr_sorotwaniaDwa = "Strona WWW: ";
                                }
                                else if (parametr_sorotwaniaDwa == "Login" || parametr_sorotwaniaDwa == "login") {
                                    parametr_sorotwaniaDwa = "Login: ";
                                }
                                else {
                                    std::cout << "Wprowadzono bledny parametr, zwroc uwage na wypisane w nawiasie dostepne parametry." << std::endl;
                                    powtorz = true;
                                }
                            } while (powtorz);
                            std::cout << "Wpisz wartosc podanego parametru:" << std::endl;
                            std::cout << ">";
                            std::getline(std::cin >> std::ws, wartosc_parametru);
                        }
                        else if (kolejny_parametr != "tak" && kolejny_parametr != "-") {
                            std::cout << "Nie rozmozpano Twojej komendy \"" << kolejny_parametr << "\", zwroc uwage aby nie wpisywac znakow specjalnych." << std::endl;
                            powtorz = true;
                        }
                    } while (powtorz);
                    std::cout << "Posortowana lista: " << std::endl;
                    sortowaniePoParametrach(glownyPlik, "Nazwa: ", parametr_sorotwaniaDwa, nazwa_sorotwania, wartosc_parametru);
                }
                else if (parametr_sorotwania == "2" || parametr_sorotwania == "2.") {
                    std::cout << "Wpisz kategorie, wedlug ktorej maja zostac posotrowane hasla:" << std::endl;
                    std::cout << ">";
                    std::getline(std::cin >> std::ws, kategoria_sorotwania);

                    do {
                        powtorz = false;
                        std::cout << "Czy dodac drugi parametr sortowania? Wpisz \"tak\", aby wprowadzic lub \"-\", aby pominac." << std::endl;
                        std::cout << ">";
                        std::cin >> kolejny_parametr;
                        if (kolejny_parametr == "tak") {

                            do {
                                powtorz = false;
                                std::cout << "Wpisz parametr wobec, ktorego maja byc sortowane hasla (\"Nazwa\", \"Strona WWW\", \"Login\")." << std::endl;
                                std::cout << ">";
                                std::getline(std::cin >> std::ws, parametr_sorotwaniaDwa);
                                if (parametr_sorotwaniaDwa == "nazwa" || parametr_sorotwaniaDwa == "Nazwa") {
                                    parametr_sorotwaniaDwa = "Nazwa: ";
                                }
                                else if (parametr_sorotwaniaDwa == "Strona" || parametr_sorotwaniaDwa == "strona" || parametr_sorotwaniaDwa == "Strona WWW" || parametr_sorotwaniaDwa == "strona www") {
                                    parametr_sorotwaniaDwa = "Strona WWW: ";
                                }
                                else if (parametr_sorotwaniaDwa == "Login" || parametr_sorotwaniaDwa == "login") {
                                    parametr_sorotwaniaDwa = "Login: ";
                                }
                                else {
                                    std::cout << "Wprowadzono bledny parametr, zwroc uwage na wypisane w nawiasie dostepne parametry." << std::endl;
                                    powtorz = true;
                                }
                            } while (powtorz);
                            std::cout << "Wpisz wartosc podanego parametru:" << std::endl;
                            std::cout << ">";
                            std::getline(std::cin >> std::ws, wartosc_parametru);
                        }
                        else if (kolejny_parametr != "tak" && kolejny_parametr != "-") {
                            std::cout << "Nie rozmozpano Twojej komendy \"" << kolejny_parametr << "\", zwroc uwage aby nie wpisywac znakow specjalnych." << std::endl;
                            powtorz = true;
                        }
                    } while (powtorz);
                    std::cout << "Posortowana lista: " << std::endl;
                    sortowaniePoParametrach(glownyPlik, "Kategoria: ", parametr_sorotwaniaDwa, nazwa_sorotwania, wartosc_parametru);
                }
                else if (parametr_sorotwania == "3" || parametr_sorotwania == "3.") {
                    std::cout << "Wpisz strone, wedlug ktorej maja zostac posotrowane hasla:" << std::endl;
                    std::cout << ">";
                    std::getline(std::cin >> std::ws, strona_sorotwania);

                    do {
                        powtorz = false;
                        std::cout << "Czy dodac drugi parametr sortowania? Wpisz \"tak\", aby wprowadzic lub \"-\", aby pominac." << std::endl;
                        std::cout << ">";
                        std::cin >> kolejny_parametr;
                        if (kolejny_parametr == "tak") {

                            do {
                                powtorz = false;
                                std::cout << "Wpisz parametr wobec, ktorego maja byc sortowane hasla (\"Nazwa\", \"Kategoria\", \"Login\")." << std::endl;
                                std::cout << ">";
                                std::getline(std::cin >> std::ws, parametr_sorotwaniaDwa);
                                if (parametr_sorotwaniaDwa == "kategoria" || parametr_sorotwaniaDwa == "Kategoria") {
                                    parametr_sorotwaniaDwa = "Kategoria: ";
                                }
                                else if (parametr_sorotwaniaDwa == "Nazwa" || parametr_sorotwaniaDwa == "nazwa") {
                                    parametr_sorotwaniaDwa = "Nazwa: ";
                                }
                                else if (parametr_sorotwaniaDwa == "Login" || parametr_sorotwaniaDwa == "login") {
                                    parametr_sorotwaniaDwa = "Login: ";
                                }
                                else {
                                    std::cout << "Wprowadzono bledny parametr, zwroc uwage na wypisane w nawiasie dostepne parametry." << std::endl;
                                    powtorz = true;
                                }
                            } while (powtorz);
                            std::cout << "Wpisz wartosc podanego parametru:" << std::endl;
                            std::cout << ">";
                            std::getline(std::cin >> std::ws, wartosc_parametru);
                        }
                        else if (kolejny_parametr != "tak" && kolejny_parametr != "-") {
                            std::cout << "Nie rozmozpano Twojej komendy \"" << kolejny_parametr << "\", zwroc uwage aby nie wpisywac znakow specjalnych." << std::endl;
                            powtorz = true;
                        }
                    } while (powtorz);
                    std::cout << "Posortowana lista: " << std::endl;
                    sortowaniePoParametrach(glownyPlik, "Strona WWW: ", parametr_sorotwaniaDwa, nazwa_sorotwania, wartosc_parametru);
                }
                else if (parametr_sorotwania == "4" || parametr_sorotwania == "4.") {
                    std::cout << "Wpisz login, wedlug ktorego maja zostac posotrowane hasla:" << std::endl;
                    std::cout << ">";
                    std::getline(std::cin >> std::ws, login_sorotwania);

                    do {
                        powtorz = false;
                        std::cout << "Czy dodac drugi parametr sortowania? Wpisz \"tak\", aby wprowadzic lub \"-\", aby pominac." << std::endl;
                        std::cout << ">";
                        std::cin >> kolejny_parametr;
                        if (kolejny_parametr == "tak") {
                            do {
                                powtorz = false;
                                std::cout << "Wpisz parametr wobec, ktorego maja byc sortowane hasla (\"Nazwa\", \"Kategoria\", \"Strona WWW\")." << std::endl;
                                std::cout << ">";
                                std::getline(std::cin >> std::ws, parametr_sorotwaniaDwa);
                                if (parametr_sorotwaniaDwa == "kategoria" || parametr_sorotwaniaDwa == "Kategoria") {
                                    parametr_sorotwaniaDwa = "Kategoria: ";
                                }
                                else if (parametr_sorotwaniaDwa == "Nazwa" || parametr_sorotwaniaDwa == "nazwa") {
                                    parametr_sorotwaniaDwa = "Nazwa: ";
                                }
                                else if (parametr_sorotwaniaDwa == "Strona" || parametr_sorotwaniaDwa == "strona" || parametr_sorotwaniaDwa == "Strona WWW" || parametr_sorotwaniaDwa == "strona www") {
                                    parametr_sorotwaniaDwa = "Strona WWW: ";
                                }
                                else {
                                    std::cout << "Wprowadzono bledny parametr, zwroc uwage na wypisane w nawiasie dostepne parametry." << std::endl;
                                    powtorz = true;
                                }
                            } while (powtorz);
                            std::cout << "Wpisz wartosc podanego parametru:" << std::endl;
                            std::cout << ">";
                            std::getline(std::cin >> std::ws, wartosc_parametru);
                        }
                        else if (kolejny_parametr != "tak" && kolejny_parametr != "-") {
                            std::cout << "Nie rozmozpano Twojej komendy \"" << kolejny_parametr << "\", zwroc uwage aby nie wpisywac znakow specjalnych." << std::endl;
                            powtorz = true;
                        }
                    } while (powtorz);
                    std::cout << "Posortowana lista: " << std::endl;
                    sortowaniePoParametrach(glownyPlik, "Login: ", parametr_sorotwaniaDwa, nazwa_sorotwania, wartosc_parametru);
                }
                else {
                    std::cout << "Nie znaleziono Twojej komendy: \"" << parametr_sorotwania << "\". \nSprobuj ponownie wprowadzic cyfre reprezentujaca dana komende.\n" << std::endl;
                    powtorz = true;
                }
            } while (powtorz);
            powtorz = true;
        }
        else if (x == "3" || x == "3.") {
            std::string nazwa;
            std::string kategoria;
            std::string strona;
            std::string login;
            std::string haslo;

            std::string czy_wygenerowac_haslo;
            int ilosc_znakow_generowanego_hasla = 0;
            std::string wielkie_znaki_generowane_haslo;
            bool czy_wielkie_znaki = false;
            std::string specjalne_znaki_generowane_haslo;
            bool czy_specjalne_znaki = false;

            std::cout << "Podaj nazwe dla hasla:" << std::endl;
            std::cout << ">";
            std::getline(std::cin >> std::ws, nazwa);
            std::cout << "Podaj kategorie, w ktorej ma znalezc sie wpis hasla:" << std::endl;
            std::cout << ">";
            std::getline(std::cin >> std::ws, kategoria);
            std::cout << "Podaj adres WWW strony (opcjonalne, wprowadz \"-\" aby pominac):" << std::endl;
            std::cout << ">";
            std::getline(std::cin >> std::ws, strona);
            std::cout << "Podaj login do portalu (opcjonalne, wprowadz \"-\" aby pominac):" << std::endl;
            std::cout << ">";
            std::getline(std::cin >> std::ws, login);

            do {
                powtorz = false;
                std::cout << "Czy wygenerowac haslo?\nWpisz \"tak\" jezeli chcesz aby Twoje haslo zostalo wygenerowane, aby pominac wpisz \"-\":" << std::endl;
                std::cout << ">";
                std::cin >> czy_wygenerowac_haslo;

                if (czy_wygenerowac_haslo == "tak") {
                    std::cout << "Podaj ilosc znakow hasla:" << std::endl;
                    std::cout << ">";
                    std::cin >> ilosc_znakow_generowanego_hasla;
                    do {
                        powtorz = false;
                        std::cout << "Czy haslo ma zawierac wielkie i male litery, \"tak\" aby uwzglednic, \"-\", aby pominac:" << std::endl;
                        std::cout << ">";
                        std::cin >> wielkie_znaki_generowane_haslo;
                        if (wielkie_znaki_generowane_haslo == "tak") {
                            czy_wielkie_znaki = true;
                        }
                        else if (wielkie_znaki_generowane_haslo != "tak" && wielkie_znaki_generowane_haslo != "-") {
                            std::cout << "Nie rozpoznano Twojej komendy \"" << wielkie_znaki_generowane_haslo << "\", wpisz \"tak\" aby uwzglednic male i wielkie litrey, \"-\", aby pominac." << std::endl;
                            powtorz = true;
                        }
                    } while (powtorz);
                    do {
                        powtorz = false;
                        std::cout << "Czy haslo ma zawierac znaki specjalne, \"tak\" aby uwzglednic, \"-\" aby pominac:" << std::endl;
                        std::cout << ">";
                        std::cin >> specjalne_znaki_generowane_haslo;
                        if (specjalne_znaki_generowane_haslo == "tak") {
                            czy_specjalne_znaki = true;
                        }
                        else if (specjalne_znaki_generowane_haslo != "tak" && specjalne_znaki_generowane_haslo != "-") {
                            std::cout << "Nie rozpoznano Twojej komendy \" " << specjalne_znaki_generowane_haslo << "\", wpisz \"tak\" aby uwzglednic male i wielkie litrey, \"-\", aby pominac." << std::endl;
                            powtorz = true;
                        }
                    } while (powtorz);

                    haslo = imitowanieLosowosci_generowanie_hasla(ilosc_znakow_generowanego_hasla, czy_wielkie_znaki, czy_specjalne_znaki, nazwa);
                    std::cout << "Wygenerowane haslo: " << haslo << std::endl;
                    std::cout << "Haslo jest " << sprawdzanieSilyHasla(haslo) << "!" << std::endl;


                }
                else if (czy_wygenerowac_haslo == "-") {
                    std::cout << "Podaj Swoje haslo:" << std::endl;
                    std::cout << ">";
                    std::cin >> haslo;
                    std::cout << "Haslo jest " << sprawdzanieSilyHasla(haslo) << "!" << std::endl;
                    std::cout << wyszukajWszystkieHasla(glownyPlik, haslo) << std::endl;
                }
                else {
                    std::cout << "Nie rozpoznano komendy \"" << czy_wygenerowac_haslo << "\", aby wygenerowac haslo wpisz \"tak\", aby pominac wpisz \"-\"." << std::endl;
                    powtorz = true;
                }
            } while (powtorz);

            std::cout << "Pomyslnie wprowadzono haslo do pliku: " << wpisanieDoPliku(glownyPlik, nazwa, haslo, kategoria, login, strona) << std::endl;
            powtorz = true;
        }
        else if (x == "4" || x == "4.") {
            std::cout << "Lista Twoich hasel: " << std::endl;
            std::cout << edycjaHasla(glownyPlik) << std::endl;
            powtorz = true;
        }
        else if (x == "5" || x == "5.") {
            std::string usuniecie_hasla;
            std::cout << "Lista Twoich hasel: " << std::endl;
            std::cout << odczytanieZawartosciPliku(glownyPlik, true, false) << std::endl;
            powtorz = true;
        }
        else if (x == "6" || x == "6.") {
            std::string nowa_kategoria;
            std::cout << "Wprowadz nazwe nowej kategorii:" << std::endl;
            std::cout << ">";
            std::getline(std::cin >> std::ws, nowa_kategoria);
            std::cout << "Wprowadzono nowa kategorie do pliku: " << wpisanieDoPliku(glownyPlik, "", "", nowa_kategoria, "-", "-");
            powtorz = true;
        }
        else if (x == "7" || x == "7.") {
            std::cout << "Lista Twoich kategorii wraz z przypisanymi do nich haslami: " << std::endl;
            std::cout << odczytanieZawartosciPliku(glownyPlik, false, true) << std::endl;
            powtorz = true;
        }
        else if (x == "0" || x == "0.") {
            powtorz = false;
        }
        else {
            std::cout << "Nie znaleziono Twojej komendy: \"" << x << "\". \nSprobuj ponownie wprowadzic cyfre reprezentujaca dana komende.\n" << std::endl;
            powtorz = true;
        }
    } while (powtorz);
}
