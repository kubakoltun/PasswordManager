#include <iostream>
#include <string>

#include "password.h"

int main() {
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
        } else {
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

                } else {
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
                                } else {
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
                                } else {
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
