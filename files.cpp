#include "files.h"
#include "time_stamp.h"
#include "password.h"
#include <sys/stat.h>

/**
 * Checking whether the file passed in parameter exists via POSIX structure
 *
 * @param file file passed in argument
 * @return bool tells whether the file exists or not
 */
bool does_file_exist(const std::string& file) {
    struct stat buf;
    return (stat(file.c_str(), &buf) == 0);
}

/**
 * Reads all lines from the given file into memory, displays them to the user,
 * and allows the user to remove a selected password or category entry
 *
 * @param fileName the name of the file to operate on
 * @param isPasswordRemoval if true, password entries are listed and can be removed
 * @param isCategoryRemoval if true, categories (and their related passwords) are listed and can be removed
 * @return a message describing the outcome of the operation
 */
std::string read_file_content(const std::string& fileName, bool isPasswordRemoval, bool isCategoryRemoval) {
    if (!validate_whether_the_file_exists(fileName)) return "";

    std::ifstream currentFile(fileName);
    std::vector<std::string> lines;
    std::string currentLine;
    int lineNumber = 0;
    int shownLine = 1;
    int confirmationInput = 0;

    while (getline(currentFile, currentLine)) {
        lines.push_back(currentLine);
        if (isPasswordRemoval) {
            if (currentLine.find(encrypt_decrypt_input(DEFAULT_TAG)) != std::string::npos) {
                std::string clearLineWithoutTag;
                for (int i = DEFAULT_TAG.size(); i < currentLine.length(); i++) {
                    clearLineWithoutTag += currentLine[i];
                }
                std::cout << shownLine << ". " << encrypt_decrypt_input(clearLineWithoutTag, false) << std::endl;
            }
        }
        if (isCategoryRemoval) {
            if (currentLine.find(encrypt_decrypt_input("Kategoria: ")) != std::string::npos) {
                std::cout << shownLine << ". " << encrypt_decrypt_input(currentLine, false) << std::endl;
            }
            if (currentLine.find(encrypt_decrypt_input(DEFAULT_TAG)) != std::string::npos) {
                std::cout << " " << encrypt_decrypt_input(currentLine, false) << std::endl;
            }
        }
        shownLine++;
    }
    if (isPasswordRemoval) {
        std::cout << "Wpisz numer hasla, ktore chcesz usunac:" << std::endl;
        std::cout << ">";
        std::cin >> lineNumber;
        std::cout << "Usuwasz haslo numer: " << lineNumber << ", \naby potwierdzic wpisz: " << lineNumber << std::endl;
        std::cout << ">";
        std::cin >> confirmationInput;
        if (lineNumber != confirmationInput) {
            return "Nie udalo ci sie potwierdzic usuniecia hasla.";
        }
    }

    if (isCategoryRemoval) {
        std::cout << "Wpisz numer kategorii, ktora chcesz usunac (wraz z kategoria zostanie usuniete rowniez przypisane do niej haslo)." << std::endl;
        std::cout << ">";
        std::cin >> lineNumber;
        std::cout << "Usuwasz kategorie oraz haslo numer: " << lineNumber << ", \naby potwierdzic wpisz: " << lineNumber << std::endl;
        std::cout << ">";
        std::cin >> confirmationInput;
        if (lineNumber != confirmationInput) {
            return "Nie udalo ci sie potwierdzic usuniecia kategorii.";
        }
    }
    currentFile.close();

    if (lineNumber > lines.size()) {
        std::cout << "Linia: " << lineNumber << ", nie znajduje sie w pliku." << std::endl;
    }

    write_to_file(fileName, lines, 0, "", true);

    return "Dokonano wprowadzonych zmian.";
}

/**
 * Writes a new password record to the specified file
 * Po sprawdzeniu czy plik otworzyl sie poprawnie sprawdzane jest czy, ktorys z parametrow zostal pominiety
 * Do pliku wprowadzane sa wpisane przez uzytkownika biezaco szyfrowane parametry
 * Dana wartosc parametru jest poprzedzona rowniez szyfrowanym kluczem
 * Jako ze sa wykonywane operacje na danych do pliku jest rowniez wprowadzany timestamp
 *
 * @param fileName the file where data should be stored
 * @param name the name assigned to the password
 * @param password the password value
 * @param category the category assigned by the user
 * @param login the login associated with the password (optional)
 * @param page the website associated with the password (optional)
 * @return a message confirming that the record was saved
 */
std::string enter_record_into_file(std::string fileName, const std::string& name, const std::string& password, std::string category, const std::string& login, const std::string& page) {
    if (!validate_whether_the_file_exists(fileName)) return "";

    std::ofstream currentFile(fileName, std::ios::app);
    if (!name.empty()) {
        currentFile << encrypt_decrypt_input("Nazwa: ") << encrypt_decrypt_input(name) << std::endl;
    }
    currentFile << encrypt_decrypt_input("Kategoria: ") << encrypt_decrypt_input(std::move(category)) << std::endl;
    if (page != "-") {
        currentFile << encrypt_decrypt_input("Strona WWW: ") << encrypt_decrypt_input(page) << std::endl;
    }
    if (login != "-") {
        currentFile << encrypt_decrypt_input("Login: ") << encrypt_decrypt_input(login) << std::endl;
    }
    if (!password.empty()) {
        currentFile << encrypt_decrypt_input(DEFAULT_TAG) << encrypt_decrypt_input(password) << std::endl;
    }

    return fileName;
}

/**
 * Searches for passwords in the given file based on one or two search parameters (tags and their values) and displays matching records
 *
 * @param fileName the file to read from
 * @param categoryTag the primary search key (e.g., "Kategoria: ")
 * @param secondaryCategoryTag an optional secondary key for combined filtering
 * @param searchedTagValue the value to search for in the primary category
 * @param searchedSecondTagValue the value to search for in the secondary category
 */
void sort_and_show_passwords_per_input(const std::string& fileName, const std::string& categoryTag, const std::string& secondaryCategoryTag, const std::string& searchedTagValue, const std::string& searchedSecondTagValue) {
    if (!validate_whether_the_file_exists(fileName)) return; // No file so skip the logic - exit early

    std::ifstream currentFile(fileName);
    std::vector<std::string> lines;
    std::string currentLine;
    std::string wholeSearchedPhrase = categoryTag + searchedTagValue;
    std::string secondWholeSearchedPhrase = secondaryCategoryTag + searchedSecondTagValue;
    SearchState searchState = SearchState::Searching;
    bool isFound = false;
    int lineNumber = 0;
    int shownLine = 1;

    while (std::getline(currentFile, currentLine)) {
        lines.push_back(currentLine);
        shownLine++;
    }

    for (const auto& line : lines) {
        if (line.find(encrypt_decrypt_input(wholeSearchedPhrase)) != std::string::npos || line.find(encrypt_decrypt_input(secondWholeSearchedPhrase)) != std::string::npos) {
            searchState = SearchState::FoundFirstMatch;
            isFound = true;
            std::cout << encrypt_decrypt_input(line, false) << std::endl;
        }
        if (currentLine.find(encrypt_decrypt_input(DEFAULT_TAG)) != std::string::npos && searchState == SearchState::FoundFirstMatch && isFound) {
            searchState = SearchState::FoundAfterTag;
            std::cout << encrypt_decrypt_input(line, false) << std::endl;
        }
        if ((line.find(encrypt_decrypt_input(categoryTag)) != std::string::npos || line.find(encrypt_decrypt_input(secondaryCategoryTag)) != std::string::npos) && isFound && searchState == SearchState::FoundAfterTag) {
            std::cout << line << std::endl;
        }
        if (line.find(encrypt_decrypt_input(DEFAULT_TAG)) != std::string::npos && isFound && searchState == SearchState::FoundAfterTag) {
            std::cout << line << std::endl;
        }
    }
    currentFile.close();

    write_to_file(fileName, lines);
}

/**
 * Writes all given lines back to a file, optionally removing or modifying specific ones
 * 
 * @param fileName the file to write to
 * @param lines the list of existing file lines
 * @param lineNumber the line to modify or remove
 * @param editedPassword the replacement password (if editing a line)
 * @param isCategoryRemoval if true, removes both a category and its password
 */
void write_to_file(const std::string& fileName, std::vector<std::string> lines, int lineNumber = 0, std::string editedPassword = "", bool isCategoryRemoval = false) {
    std::ofstream writeToFile(fileName);
    lineNumber--;
    int previousLineNumber = isCategoryRemoval ? lineNumber++ : 0;

    for (int i = 0; i < lines.size(); i++) {
        // Skip lines if removing a category
        if (isCategoryRemoval && (i == previousLineNumber || i == lineNumber)) {
            continue;
        }

        if (i == lineNumber) {
            write_line(writeToFile, encrypt_decrypt_input(editedPassword), i);
        }
        else {
            write_line(writeToFile, lines[i], i);
        }
    }

    // Making some more noise if the line is to short
    if (lines.size() < 33) {
        for (int i = lines.size(); i < 35; i++) {
            std::string randomStr = generate_random_string(rand() % 10);
            write_line(writeToFile, encrypt_decrypt_input(randomStr), i);
        }
    }
    writeToFile.close();
}

bool validate_whether_the_file_exists(const std::string& fileName) {
    if (!does_file_exist(fileName)) {
        std::cout << "Błąd podczas otwierania pliku \"" << fileName << "\", sprawdz podana sciezke lub nazwe pliku." << std::endl;
        return false;
    }

    return true;
}

bool is_timestamp_line(int i) {
    static const int timestamps[] = {11, 22, 33};
    return std::find(std::begin(timestamps), std::end(timestamps), i) != std::end(timestamps);
}

void write_line(std::ofstream& out, const std::string& text, int i) {
    if (is_timestamp_line(i))
        out << simulate_noise(i) << '\n';
    out << text << '\n';
}
