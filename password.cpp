#include "cypher.cpp"
#include "files.h"
#include "files.cpp"
#include "time_stamp.h"
#include "time_stamp.cpp"

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