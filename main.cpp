#include <iostream>
#include <string>
#include "password.h"

std::string mainFile;
const std::vector<std::string> ALL_TAGS = {
    "Nazwa: ",
    "Kategoria: ",
    "Strona WWW: ",
    "Login: "
};

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
            case 0: 
                std::cout << "Zamykam program..." << std::endl;
                return 0;
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
            initializae_sorting_by_params("nazwe", "Nazwa: ");
            break;
        case 2:
            initializae_sorting_by_params("kategorie", "Kategoria: ");
            break;
        case 3:
            initializae_sorting_by_params("strone", "Strona WWW: ");
            break;
        case 4:
            initializae_sorting_by_params("nazwe uzytkownika (login)", "Login: ");
            break;
        default:
            default_choice_message(1, 4, inputDecision);
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
            password_search_print_helper("nazwe", "Nazwa: ");
            break;
        case 2: 
            password_search_print_helper("kategorie", "Kategoria: ");
            break;
        case 3:
            password_search_print_helper("strone", "Strona WWW: ");
            search_password(mainFile, input, "Strona WWW: ");
            break;
        case 4:
            password_search_print_helper("nazwe uzytkownika (login)", "Login: ");
        default:
            default_choice_message(1, 4, userInputSearch);
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

static void password_search_print_helper(std::string inLineName, std::string tagName) {
    std::string input = prompt_line("Wpisz " + inLineName + ", wedlug ktorej ma zostac wyszukane haslo:");
    std::cout << "Wyniki wyszukiwania dla " << input << ":" << std::endl;
    search_password(mainFile, input, tagName);
}

void default_choice_message(int from, int to, int userInputMainCommand) {
    std::cout << "Nie znaleziono Twojej komendy: \"" << userInputMainCommand << "\". \nSprobuj ponownie wprowadzic cyfre reprezentujaca dana komende, od " << from << " do " << to << "\n" << std::endl;
}

void initializae_sorting_by_params(std::string inLineName, std::string tagName) {
    std::string valueOfTheFirstTagToSortBy = prompt_line("Wpisz " + inLineName + ", wedlug ktorej maja zostac posotrowane hasla:");
    std::string secondaryTagName = "";
    std::string valueOfTheSecondTagToSortBy = "";

    if (prompt_accept_or_skip("Czy dodac drugi parametr sortowania?")) {
        secondaryTagName = choose_secondary_tag(tagName);
        valueOfTheSecondTagToSortBy = prompt_line("Wpisz wartosc podanego parametru:");
    }

    std::cout << "Posortowana lista: " << std::endl;
    sort_and_show_passwords_per_input(mainFile, tagName, secondaryTagName, valueOfTheFirstTagToSortBy, valueOfTheSecondTagToSortBy);
}

void print_tags_names(std::string skipTagName = "", bool shouldTrim = false) {
    int optionIndex = 1;
    for (const auto& tag : ALL_TAGS) {
        if (tag != skipTagName) {
            std::cout << " " << optionIndex << ". " << (shouldTrim ? tag.substr(0, tag.size() - 2) : tag) << std::endl;
        }
        ++optionIndex;
    }
}

std::string choose_secondary_tag(const std::string& tagName) {
    std::vector<std::string> availableTags;
    for (const auto& tag : ALL_TAGS) {
        if (tag != tagName) availableTags.push_back(tag);
    }

    std::cout << "Wybierz wobec jakich parametrow chcesz posortowac hasla:" << std::endl;
    print_tags_names(tagName);

    int secondaryTagChoice = prompt_int("");
    if (secondaryTagChoice < 1 || secondaryTagChoice > static_cast<int>(availableTags.size())) {
        default_choice_message(1, availableTags.size(), secondaryTagChoice);
        return "";
    }

    return availableTags[secondaryTagChoice - 1]; 
}
