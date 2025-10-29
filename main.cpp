#include <iostream>
#include <string>
#include "password.h"

bool retry = false;
std::string mainFile;

// todo main logic return
int main() {
    do {
        retry = false;
        std::cout << "Podaj nazwe pliku znajdujacego sie w obecnym folderze lub sciezke absolutna, aby skorzystac z programu:" << std::endl;
        std::cout << ">";
        std::getline(std::cin >> std::ws, mainFile);

        // todo master password
        if (!does_file_exist(mainFile)) {
            std::cout << "Wprowadzona nazwa lub sciezka pliku nie istnieje: \"" << mainFile << "\" wprowadz poprawna nazwe lub sicezke pliku." << std::endl;
            retry = true;
        }
        else {
            retry = false;
        }
    } while (retry);

    do {
        retry = false;
        int userInputMainCommand;
        std::cout << "Wybierz interesujaca Cie komende, wpisujac jej numer:" << std::endl;
        std::cout << "1. Wyszukaj hasla" << std::endl;
        std::cout << "2. Posortuj hasla" << std::endl;
        std::cout << "3. Dodaj haslo" << std::endl;
        std::cout << "4. Edytuj haslo" << std::endl;
        std::cout << "5. Usun haslo" << std::endl;
        std::cout << "6. Dodaj kategorie" << std::endl;
        std::cout << "7. Usun kategorie" << std::endl;
        std::cout << "0. Wyjscie" << std::endl;
        userInputMainCommand = prompt_int("");

        switch(userInputMainCommand) {
            case 1: 
                search_password();
                break;
            case 2: 
                sort_password();
                break;
            case 3: 
                add_password();
                break;
            case 4: 
                edit_password();
                break;
            case 5: 
                delete_entry(true);
                break;
            case 6: 
                add_category();
                break;
            case 7: 
                delete_entry(false);
                break;
            case 0: 
                retry = false;
                break;
            default: 
                std::cout << "Nie znaleziono Twojej komendy: \"" << userInputMainCommand << "\". \nSprobuj ponownie wprowadzic cyfre reprezentujaca dana komende, od 0 do 7\n" << std::endl;
                break;
        }
    } while (retry);
}

void sort_password() {
    do {
        retry = false;
        std::string sortingParameterOne;
        std::string sortingParameterTwo;
        std::string valueThatWillBeSortedBy;
        std::string sortingCategory;
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
        std::cin >> sortingParameterOne;

        if (sortingParameterOne == "1" || sortingParameterOne == "1.") {
            std::cout << "Wpisz nazwe, wedlug ktorej maja zostac posotrowane hasla:" << std::endl;
            std::cout << ">";
            std::getline(std::cin >> std::ws, valueThatWillBeSortedBy);

            do {
                retry = false;
                std::cout << "Czy dodac drugi parametr sortowania? Wpisz \"tak\", aby wprowadzic lub \"nie\", aby pominac." << std::endl;
                std::cout << ">";
                std::cin >> kolejny_parametr;
                if (kolejny_parametr == "tak") {
                    do {
                        retry = false;
                        std::cout << "Wpisz parametr wobec, ktorego maja byc sortowane hasla (\"Kategoria\", \"Strona WWW\", \"Login\")." << std::endl;
                        std::cout << ">";
                        std::getline(std::cin >> std::ws, sortingParameterTwo);
                        if (sortingParameterTwo == "kategoria" || sortingParameterTwo == "Kategoria") {
                            sortingParameterTwo = "Kategoria: ";
                        }
                        else if (sortingParameterTwo == "Strona" || sortingParameterTwo == "strona" || sortingParameterTwo == "Strona WWW" || sortingParameterTwo == "strona www") {
                            sortingParameterTwo = "Strona WWW: ";
                        }
                        else if (sortingParameterTwo == "Login" || sortingParameterTwo == "login") {
                            sortingParameterTwo = "Login: ";
                        } 
                        else {
                            std::cout << "Wprowadzono bledny parametr, zwroc uwage na wypisane w nawiasie dostepne parametry." << std::endl;
                            retry = true;
                        }
                    } while (retry);
                    std::cout << "Wpisz wartosc podanego parametru:" << std::endl;
                    std::cout << ">";
                    std::getline(std::cin >> std::ws, wartosc_parametru);
                }
                else if (kolejny_parametr != "tak" && kolejny_parametr != "nie") {
                    std::cout << "Nie rozmozpano Twojej komendy \"" << kolejny_parametr << "\", zwroc uwage aby nie wpisywac znakow specjalnych." << std::endl;
                    retry = true;
                }
            } while (retry);
            std::cout << "Posortowana lista: " << std::endl;
            sort_and_show_passwords_per_input(mainFile, "Nazwa: ", sortingParameterTwo, valueThatWillBeSortedBy, wartosc_parametru);
        }
        else if (sortingParameterOne == "2" || sortingParameterOne == "2.") {
            std::cout << "Wpisz kategorie, wedlug ktorej maja zostac posotrowane hasla:" << std::endl;
            std::cout << ">";
            std::getline(std::cin >> std::ws, sortingCategory);

            do {
                retry = false;
                std::cout << "Czy dodac drugi parametr sortowania? Wpisz \"tak\", aby wprowadzic lub \"-\", aby pominac." << std::endl;
                std::cout << ">";
                std::cin >> kolejny_parametr;
                if (kolejny_parametr == "tak") {

                    do {
                        retry = false;
                        std::cout << "Wpisz parametr wobec, ktorego maja byc sortowane hasla (\"Nazwa\", \"Strona WWW\", \"Login\")." << std::endl;
                        std::cout << ">";
                        std::getline(std::cin >> std::ws, sortingParameterTwo);
                        if (sortingParameterTwo == "nazwa" || sortingParameterTwo == "Nazwa") {
                            sortingParameterTwo = "Nazwa: ";
                        }
                        else if (sortingParameterTwo == "Strona" || sortingParameterTwo == "strona" || sortingParameterTwo == "Strona WWW" || sortingParameterTwo == "strona www") {
                            sortingParameterTwo = "Strona WWW: ";
                        }
                        else if (sortingParameterTwo == "Login" || sortingParameterTwo == "login") {
                            sortingParameterTwo = "Login: ";
                        }
                        else {
                            std::cout << "Wprowadzono bledny parametr, zwroc uwage na wypisane w nawiasie dostepne parametry." << std::endl;
                            retry = true;
                        }
                    } while (retry);
                    std::cout << "Wpisz wartosc podanego parametru:" << std::endl;
                    std::cout << ">";
                    std::getline(std::cin >> std::ws, wartosc_parametru);
                }
                else if (kolejny_parametr != "tak" && kolejny_parametr != "-") {
                    std::cout << "Nie rozmozpano Twojej komendy \"" << kolejny_parametr << "\", zwroc uwage aby nie wpisywac znakow specjalnych." << std::endl;
                    retry = true;
                }
            } while (retry);
            std::cout << "Posortowana lista: " << std::endl;
            sort_and_show_passwords_per_input(mainFile, "Kategoria: ", sortingParameterTwo, valueThatWillBeSortedBy, wartosc_parametru);
        }
        else if (sortingParameterOne == "3" || sortingParameterOne == "3.") {
            std::cout << "Wpisz strone, wedlug ktorej maja zostac posotrowane hasla:" << std::endl;
            std::cout << ">";
            std::getline(std::cin >> std::ws, strona_sorotwania);

            do {
                retry = false;
                std::cout << "Czy dodac drugi parametr sortowania? Wpisz \"tak\", aby wprowadzic lub \"-\", aby pominac." << std::endl;
                std::cout << ">";
                std::cin >> kolejny_parametr;
                if (kolejny_parametr == "tak") {

                    do {
                        retry = false;
                        std::cout << "Wpisz parametr wobec, ktorego maja byc sortowane hasla (\"Nazwa\", \"Kategoria\", \"Login\")." << std::endl;
                        std::cout << ">";
                        std::getline(std::cin >> std::ws, sortingParameterTwo);
                        if (sortingParameterTwo == "kategoria" || sortingParameterTwo == "Kategoria") {
                            sortingParameterTwo = "Kategoria: ";
                        }
                        else if (sortingParameterTwo == "Nazwa" || sortingParameterTwo == "nazwa") {
                            sortingParameterTwo = "Nazwa: ";
                        }
                        else if (sortingParameterTwo == "Login" || sortingParameterTwo == "login") {
                            sortingParameterTwo = "Login: ";
                        } 
                        else {
                            std::cout << "Wprowadzono bledny parametr, zwroc uwage na wypisane w nawiasie dostepne parametry." << std::endl;
                            retry = true;
                        }
                    } while (retry);
                    std::cout << "Wpisz wartosc podanego parametru:" << std::endl;
                    std::cout << ">";
                    std::getline(std::cin >> std::ws, wartosc_parametru);
                }
                else if (kolejny_parametr != "tak" && kolejny_parametr != "-") {
                    std::cout << "Nie rozmozpano Twojej komendy \"" << kolejny_parametr << "\", zwroc uwage aby nie wpisywac znakow specjalnych." << std::endl;
                    retry = true;
                }
            } while (retry);
            std::cout << "Posortowana lista: " << std::endl;
            sort_and_show_passwords_per_input(mainFile, "Strona WWW: ", sortingParameterTwo, valueThatWillBeSortedBy, wartosc_parametru);
        }
        else if (sortingParameterOne == "4" || sortingParameterOne == "4.") {
            std::cout << "Wpisz login, wedlug ktorego maja zostac posotrowane hasla:" << std::endl;
            std::cout << ">";
            std::getline(std::cin >> std::ws, login_sorotwania);

            do {
                retry = false;
                std::cout << "Czy dodac drugi parametr sortowania? Wpisz \"tak\", aby wprowadzic lub \"-\", aby pominac." << std::endl;
                std::cout << ">";
                std::cin >> kolejny_parametr;
                if (kolejny_parametr == "tak") {
                    do {
                        retry = false;
                        std::cout << "Wpisz parametr wobec, ktorego maja byc sortowane hasla (\"Nazwa\", \"Kategoria\", \"Strona WWW\")." << std::endl;
                        std::cout << ">";
                        std::getline(std::cin >> std::ws, sortingParameterTwo);
                        if (sortingParameterTwo == "kategoria" || sortingParameterTwo == "Kategoria") {
                            sortingParameterTwo = "Kategoria: ";
                        }
                        else if (sortingParameterTwo == "Nazwa" || sortingParameterTwo == "nazwa") {
                            sortingParameterTwo = "Nazwa: ";
                        }
                        else if (sortingParameterTwo == "Strona" || sortingParameterTwo == "strona" || sortingParameterTwo == "Strona WWW" || sortingParameterTwo == "strona www") {
                            sortingParameterTwo = "Strona WWW: ";
                        }
                        else {
                            std::cout << "Wprowadzono bledny parametr, zwroc uwage na wypisane w nawiasie dostepne parametry." << std::endl;
                            retry = true;
                        }
                    } while (retry);
                    std::cout << "Wpisz wartosc podanego parametru:" << std::endl;
                    std::cout << ">";
                    std::getline(std::cin >> std::ws, wartosc_parametru);
                }
                else if (kolejny_parametr != "tak" && kolejny_parametr != "-") {
                    std::cout << "Nie rozmozpano Twojej komendy \"" << kolejny_parametr << "\", zwroc uwage aby nie wpisywac znakow specjalnych." << std::endl;
                    retry = true;
                }
            } while (retry);
            std::cout << "Posortowana lista: " << std::endl;
            sort_and_show_passwords_per_input(mainFile, "Login: ", sortingParameterTwo, valueThatWillBeSortedBy, wartosc_parametru);
        }
        else {
            std::cout << "Nie znaleziono Twojej komendy: \"" << sortingParameterOne << "\". \nSprobuj ponownie wprowadzic cyfre reprezentujaca dana komende.\n" << std::endl;
            retry = true;
        }
    } while (retry);
    retry = true;
}

void search_password() {
    do {
        retry = false;
        std::string userInputSearch;
        std::cout << "Wybierz zgodnie z czym chesz wyszukac swoje haslo:" << std::endl;
        std::cout << " 1. Wyszukaj hasla po nazwie" << std::endl;
        std::cout << " 2. Wyszukaj hasla po kategorii" << std::endl;
        std::cout << " 3. Wyszukaj hasla po stronie WWW" << std::endl;
        std::cout << " 4. Wyszukaj hasla po loginie" << std::endl;
        std::cout << ">";
        std::cin >> userInputSearch;

        if (userInputSearch == "1" || userInputSearch == "1.") {
            std::string wh_nazwa;
            std::cout << "Wpisz nazwe, wedlug ktorej ma zostac wyszukane haslo:" << std::endl;
            std::cout << ">";
            std::getline(std::cin >> std::ws, wh_nazwa);

            std::cout << "Wyniki wyszukiwania:" << std::endl;
            search_password(mainFile, wh_nazwa, "Nazwa: ");

        }
        else if (userInputSearch == "2" || userInputSearch == "2.") {
            std::string wh_kategoria;
            std::cout << "Wpisz kategorie, wedlug ktorej ma zostac wyszukane haslo:" << std::endl;
            std::cout << ">";
            std::getline(std::cin >> std::ws, wh_kategoria);

            std::cout << "Wyniki wyszukiwania:" << std::endl;
            search_password(mainFile, wh_kategoria, "Kategoria: ");

        }
        else if (userInputSearch == "3" || userInputSearch == "3.") {

            std::string wh_strona;
            std::cout << "Wpisz strone, wedlug ktorej ma zostac wyszukane haslo:" << std::endl;
            std::cout << ">";
            std::getline(std::cin >> std::ws, wh_strona);

            std::cout << "Wyniki wyszukiwania:" << std::endl;
            search_password(mainFile, wh_strona, "Strona WWW: ");

        }
        else if (userInputSearch == "4" || userInputSearch == "4.") {
            std::string wh_login;
            std::cout << "Wpisz login, wedlug ktorego ma zostac wyszukane haslo:" << std::endl;
            std::cout << ">";
            std::getline(std::cin >> std::ws, wh_login);

            std::cout << "Wyniki wyszukiwania:" << std::endl;
            search_password(mainFile, wh_login, "Login: ");

        } 
        else {
            std::cout << "Nie znaleziono Twojej komendy: \"" << userInputSearch << "\". \nSprobuj ponownie wprowadzic cyfre reprezentujaca dana komende.\n" << std::endl;
            retry = true;
        }
    } while (retry);
    retry = true;
}

void add_password() {
    std::string passwordName;
    std::string category;
    std::string page;
    std::string login;
    std::string password;

    bool userInputDecision;
    int ilosc_znakow_generowanego_hasla = 0;
    bool agreedForCapitalLetters = false;
    bool agreedForSpecialChars = false;

    passwordName = prompt_line("Podaj nazwe dla hasla:");
    category = prompt_line("Podaj kategorie, w ktorej ma znalezc sie wpis hasla:");
    page = prompt_line("Podaj adres WWW strony (opcjonalne, wprowadz \"-\" aby pominac):");
    login = prompt_line("Podaj login do portalu (opcjonalne, wprowadz \"-\" aby pominac):");
    userInputDecision = prompt_accept_or_skip("Czy wygenerowac haslo?");

    if (userInputDecision) {
        ilosc_znakow_generowanego_hasla = prompt_int("Podaj ilosc znakow hasla:");
        agreedForCapitalLetters = prompt_accept_or_skip("Czy haslo ma zawierac wielkie i male litery?");
        agreedForSpecialChars = prompt_accept_or_skip("Czy haslo ma zawierac znaki specjalne?");

        password = generate_password(ilosc_znakow_generowanego_hasla, agreedForCapitalLetters, agreedForSpecialChars, passwordName);
        std::cout << "Wygenerowane haslo: " << password << std::endl;
        std::cout << "Haslo jest " << password_strength_verifier(password) << "!" << std::endl;
    }
    else {
        password = prompt_line("Podaj swoje haslo:");
        std::cout << "Haslo jest " << password_strength_verifier(password) << "!" << std::endl;
        std::cout << search_password(mainFile, password, "Haslo: ", false) << std::endl;
    }

    std::cout << "Pomyslnie wprowadzono haslo do pliku: " << enter_record_into_file(mainFile, passwordName, password, category, login, page) << std::endl;
}

void edit_password() {
    std::cout << "Lista Twoich hasel: " << std::endl;
    std::cout << password_edition(mainFile) << std::endl;
    retry = true;
}

void delete_entry(bool isPasswordDel) {
    std::string terminalMessage = isPasswordDel ? "Lista Twoich hasel: " : "Lista Twoich kategorii wraz z przypisanymi do nich haslami: ";

    std::cout << terminalMessage << std::endl;
    std::cout << read_file_content(mainFile, isPasswordDel, !isPasswordDel) << std::endl;
    retry = true;
}

void add_category() {
    std::string newCategory;
    std::cout << "Wprowadz nazwe nowej kategorii:" << std::endl;
    std::cout << ">";
    std::getline(std::cin >> std::ws, newCategory);
    std::cout << "Wprowadzono nowa kategorie do pliku: " << enter_record_into_file(mainFile, "", "", newCategory, "-", "-");
    retry = true;
}

static std::string prompt_line(const std::string& prompt) {
    std::string line;
    std::cout << prompt << std::endl << ">";
    std::getline(std::cin >> std::ws, line);
    
    return line;
}

static int prompt_int(const std::string& prompt) {
    int value;

    while (true) {
        std::cout << prompt << std::endl << ">";
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Nieprawidlowy numer. Sprobuj ponownie." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

static bool prompt_accept_or_skip(const std::string& prompt) {
    char input;
    std::string fullPrompt = prompt + "\nWpisz \"(t)ak\" jezeli chcesz wyrazic zgode, aby pominac wpisz \"(n)ie\":";
    
    while (true) {
        std::cout << fullPrompt << std::endl << ">";
        if (!(std::cin >> input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        char lowerInput = static_cast<char>(std::tolower(static_cast<unsigned char>(input)));
        if (lowerInput == 't') return true;
        if (lowerInput == 'n') return false;

        std::cout << "Nie rozpoznano komendy \"" << input << "\", wpisz \"(t)ak\" aby wyrazic zgode lub \"(n)ie\", aby pominac." << std::endl;
    }
}
