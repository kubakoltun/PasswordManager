#include <iostream>
#include <string>
#include "password.h"
#include "helperInputFunctions.h"

std::string mainFile;
void begin_password_search();
void sort_password();
void add_password();
void edit_password();
void delete_entry(bool isPasswordDel);
void add_category();

int main() {
    while (true) {
        mainFile = prompt_line("Podaj nazwe pliku znajdujacego sie w obecnym folderze lub sciezke absolutna, aby skorzystac z programu:");

        // todo master password
        if (does_file_exist(mainFile)) {
            break;
        }
        std::cout << "Wprowadzona nazwa lub sciezka pliku nie istnieje: \"" << mainFile << "\" wprowadz poprawna nazwe lub sicezke pliku." << std::endl;
    }

    while (true) {
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
            case 0: 
                std::cout << "Zamykam program..." << std::endl;
                return 0;
            case 1: 
                begin_password_search();
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
            default: 
                default_choice_message(0, 7, userInputMainCommand);
                break;
        }
    }
}

void sort_password() {
    std::string sortingParameterOne;
    std::string sortingParameterTwo;
    std::string valueThatWillBeSortedBy;
    std::string sortingCategory;
    std::string strona_sorotwania;
    std::string login_sorotwania;
    std::string wartosc_parametru;
    std::string kolejny_parametr;

    std::cout << "Wybierz wobec jakich parametrow chcesz posortowac hasla:" << std::endl;
    print_tags_names("", true);
    int inputDecision = prompt_int("");

    switch(inputDecision) {
        case 1:
            initializae_sorting_by_params("nazwe", ALL_TAGS[0], mainFile);
            break;
        case 2:
            initializae_sorting_by_params("kategorie", ALL_TAGS[1], mainFile);
            break;
        case 3:
            initializae_sorting_by_params("strone", ALL_TAGS[2], mainFile);
            break;
        case 4:
            initializae_sorting_by_params("nazwe uzytkownika (login)", ALL_TAGS[3], mainFile);
            break;
        default:
            default_choice_message(1, ALL_TAGS.size(), inputDecision);
            break;
    }
}

void begin_password_search() {
    std::string input;
    std::cout << "Wybierz zgodnie z czym chesz wyszukac swoje haslo:" << std::endl;
    print_tags_names("", true);
    int userInputSearch = prompt_int("");

    switch(userInputSearch) {
        case 1:
            password_search_print_helper("nazwe", ALL_TAGS[0], mainFile);
            break;
        case 2: 
            password_search_print_helper("kategorie", ALL_TAGS[1], mainFile);
            break;
        case 3:
            password_search_print_helper("strone", ALL_TAGS[2], mainFile);
            break;
        case 4:
            password_search_print_helper("nazwe uzytkownika (login)", ALL_TAGS[3], mainFile);
            break;
        default:
            default_choice_message(1, ALL_TAGS.size(), userInputSearch);
            break;
    }
}

void add_password() {
    std::string passwordName;
    std::string category;
    std::string page;
    std::string login;
    std::string password;
    int charNumberForGeneratedPassword = 0;
    bool userInputDecision;
    bool agreedForCapitalLetters = false;
    bool agreedForSpecialChars = false;

    passwordName = prompt_line("Podaj nazwe dla hasla:");
    category = prompt_line("Podaj kategorie, w ktorej ma znalezc sie wpis hasla:");
    page = prompt_line("Podaj adres WWW strony (opcjonalne, wprowadz \"-\" aby pominac):");
    login = prompt_line("Podaj login do portalu (opcjonalne, wprowadz \"-\" aby pominac):");
    userInputDecision = prompt_accept_or_skip("Czy wygenerowac haslo?");

    if (userInputDecision) {
        charNumberForGeneratedPassword = prompt_int("Podaj ilosc znakow hasla:");
        agreedForCapitalLetters = prompt_accept_or_skip("Czy haslo ma zawierac wielkie i male litery?");
        agreedForSpecialChars = prompt_accept_or_skip("Czy haslo ma zawierac znaki specjalne?");

        password = generate_password(charNumberForGeneratedPassword, agreedForCapitalLetters, agreedForSpecialChars, passwordName);
        std::cout << "Wygenerowane haslo: " << password << std::endl;
        std::cout << "Haslo jest " << password_strength_verifier(password) << "!" << std::endl;
    }
    else {
        password = prompt_line("Podaj swoje haslo:");
        std::cout << "Haslo jest " << password_strength_verifier(password) << "!" << std::endl;
        std::cout << search_password(mainFile, password, "Haslo: ", false) << std::endl;
    }

    enter_record_into_file(mainFile, passwordName, password, category, login, page);
    std::cout << "Pomyslnie wprowadzono haslo do pliku: " << mainFile << std::endl;
}

void edit_password() {
    std::cout << "Lista Twoich hasel: " << std::endl;
    std::cout << password_edition(mainFile) << std::endl;
}

void delete_entry(bool isPasswordDel) {
    std::string terminalMessage = isPasswordDel ? "Lista Twoich hasel: " : "Lista Twoich kategorii wraz z przypisanymi do nich haslami: ";
    std::cout << terminalMessage << std::endl;
    std::cout << read_file_content(mainFile, isPasswordDel, !isPasswordDel) << std::endl;
}

void add_category() {
    std::string newCategory = prompt_line("Wprowadz nazwe nowej kategorii:");
    enter_record_into_file(mainFile, "", "", newCategory, "-", "-");
    std::cout << "Wprowadzono nowa kategorie do pliku: " << mainFile;
}
