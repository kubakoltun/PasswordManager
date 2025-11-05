#include <string>
#include <iostream>
#include <limits>
#include "helperInputFunctions.h"
#include "password.h"

std::string prompt_line(const std::string& prompt) {
    std::string line;
    std::cout << prompt << std::endl << ">";
    std::getline(std::cin >> std::ws, line);
    
    return line;
}

int prompt_int(const std::string& prompt) {
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

bool prompt_accept_or_skip(const std::string& prompt) {
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

// todo inLineName -> tagName.substr(0, tagName.size() - 2)
void password_search_print_helper(std::string inLineName, std::string tagName, std::string mainFile) {
    std::string input = prompt_line("Wpisz " + inLineName + ", wedlug ktorej ma zostac wyszukane haslo:");
    std::cout << "Wyniki wyszukiwania dla " << input << ":" << std::endl;
    search_password(mainFile, input, tagName, true);
}

void default_choice_message(int from, int to, int userInputMainCommand) {
    std::cout << "Nie znaleziono Twojej komendy: \"" << userInputMainCommand << "\". \nSprobuj ponownie wprowadzic cyfre reprezentujaca dana komende, od " << from << " do " << to << "\n" << std::endl;
}

void initializae_sorting_by_params(std::string inLineName, std::string tagName, std::string mainFile) {
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

void print_tags_names(std::string skipTagName, bool shouldTrim) {
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
