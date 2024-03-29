#include "files.h"
#include "time_stamp.h"

/**
 * Sprawdzenie czy podany plik istnieje
 * Struktura sprawdzajaca prawdziwosc warunku
 *
 * @param podanyPlik w momencie wywolania funkcji przez parametr jest przekazywana nazwa pliku, ktory jest poddawany sprawdzeniu
 * @return zwracana jest wartosc typu logicznego aby dac informacje czy prawda jest, ze plik istnieje
 */
bool czyPlikIstnieje(const std::string& podanyPlik) {
    struct stat buf {};
    if (stat(podanyPlik.c_str(), &buf) != -1) {
        return true;
    }
    return false;
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