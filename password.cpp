#include "cypher.h"
#include "files.h"
#include "time_stamp.h"
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <cctype>

/**
 * Generates a random password according to user defined rules (arguments).
 *
 * @param length lenght of the password decaler by the user
 * @param use_uppercase tells whether the password should contain capital letters
 * @param use_special tells whether  the password should contain special characters
 * @param name name of the password
 * @return a random generated password is returned
 */
std::string generate_password(int length, bool use_uppercase, bool use_special, const std::string& name) {
    if (length <= 0) return "";

    // Base character sets
    const std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    const std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string digits    = "0123456789";
    const std::string special   = "!@#$%^&*()_+-=`~{}[]:;'\".,/<>?|\\";
    
    std::string pool = lowercase + digits;

    if (use_uppercase) pool += uppercase;
    if (use_special) pool += special;

    // RNG setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, pool.size() - 1);

    std::string password;
    password.reserve(length);

    // Ensure at least one of each required category
    if (use_uppercase) password += uppercase[dist(gen) % uppercase.size()];
    if (use_special)   password += special[dist(gen) % special.size()];
    password += digits[dist(gen) % digits.size()];
    password += lowercase[dist(gen) % lowercase.size()];

    // Fill remaining characters
    while ((int)password.size() < length) {
        password += pool[dist(gen)];
    }

    // Shuffle so guarantees arent at the front
    std::shuffle(password.begin(), password.end(), gen);

    return password;
}

/**
 * Veryfing the password strenght based on some general criteria
 *
 * @param password password that is beign verified
 * @return quality of the password in a string 
 */
std::string password_strength_verifier(std::string password) {
    const int STRONG_LEN = 12;
    const int GOOD_LEN   = 9;
    const int MIN_LEN    = 8;
    const int BAD_LEN    = 4;
    int lowercaseCount   = 0;
    int uppercaseCount   = 0;
    int digitCount       = 0;
    int specialCount     = 0;

    for (unsigned char ch : password) {
        if (std::islower(ch)) {
            ++lowercaseCount;
        } 
        else if (std::isupper(ch)) {
            ++uppercaseCount;
        } 
        else if (std::isdigit(ch)) {
            ++digitCount;
        } 
        else if (std::isprint(ch) && !std::isalnum(ch)) {
            ++specialCount;
        }
    }

    const int password_length = password.size();

    if (password_length >= STRONG_LEN && lowercaseCount > 3 && uppercaseCount > 3 && digitCount > 2 && specialCount >= 2) {
        return "Excelent";
    }
    if (password_length >= GOOD_LEN && lowercaseCount > 2 && uppercaseCount > 2 && digitCount >= 2) {
        return "Good";
    }
    if (password_length >= MIN_LEN && lowercaseCount >= 1 && uppercaseCount >= 1 && digitCount >= 1) {
        return "Bad";
    }
    if (password_length > BAD_LEN && password_length < MIN_LEN) {
        return "Terrible";
    }

    return "Dangerous";
}

/**
 * Password chosen by the user can be edited. After edition the password is saved back to the file
 *
 * @param fileName name of the file that will be searched
 * @return message stating summary of the operation
 */
std::string password_edition(const std::string& fileName) {
    if (does_file_exist(fileName)) {
        std::ifstream currentFile;
        std::vector<std::string> lines;
        std::string currentLine;
        std::string editedPassword;
        int lineNumber = 0;
        currentFile.open(fileName);
        int lineIndicatorForFile = 1;

        while (getline(currentFile, currentLine)) {
            lines.push_back(currentLine);

            if (currentLine.find(encrypt_decrypt_input("Haslo: ")) != std::string::npos) {
                std::string clearLineWithoutTag;
                for (int i = 7; i < currentLine.length(); i++) {
                    clearLineWithoutTag += currentLine[i];
                }
                std::cout << lineIndicatorForFile << ". " << encrypt_decrypt_input(clearLineWithoutTag, false) << std::endl;
            }
            lineIndicatorForFile++;
        }

        std::cout << "Wpisz numer hasla, ktore chcesz edytowac:" << std::endl;
        std::cout << ">";
        std::cin >> lineNumber;
        std::cout << "Edytujesz haslo numer: " << lineNumber << ", wprowadz zmiany:" << std::endl;
        std::cout << ">";
        std::cin >> editedPassword;

        currentFile.close();

        if (lineNumber > lines.size()) {
            std::cout << "Linia: " << lineNumber << ", nie znajduje sie w pliku." << std::endl;
        }

        write_to_file(fileName, lines, lineNumber, editedPassword);

        return "Zapisano wprowadzone zmiany.";
    }
    else {
        std::cout << "Błąd podczas otwierania pliku \"" << fileName << "\", sprawdz podana sciezke lub nazwe pliku." << std::endl;
    }
}

/**
 * Function opens a file and looks through it line by line in serach of a password with a tag passed in parameters
 *
 * @param fileName name of the file that will be searched
 * @param searchedPassword phrase that will be searched for
 * @param startOfLineTag a tag that starts the line and tells its kind, some exemplary tags: "Strona WWW:", "Hasło:", etc.
 */
void search_password(const std::string& fileName, const std::string& searchedPassword, const std::string& startOfLineTag) {
    if (does_file_exist(fileName)) {
        std::ifstream currentFile;
        std::vector<std::string> lines;
        std::string currentLine;
        std::string wholeSearchedPhraseTagAndPassword = startOfLineTag + searchedPassword;
        int lineIndicatorForFile = 1;
        currentFile.open(fileName);

        while (std::getline(currentFile, currentLine)) {
            std::string clearLineWithoutTag;
            lines.push_back(currentLine);

            if (currentLine.find(encrypt_decrypt_input(wholeSearchedPhraseTagAndPassword)) != std::string::npos) {
                std::cout << lineIndicatorForFile << ". " << encrypt_decrypt_input(currentLine, false) << std::endl;
                clearLineWithoutTag = "";
            }
            if (currentLine.find(encrypt_decrypt_input("Haslo: ")) != std::string::npos && clearLineWithoutTag.empty()) {
                for (int i = 7; i < currentLine.length(); i++) {
                    clearLineWithoutTag += currentLine[i];
                }
                std::cout << lineIndicatorForFile << ". " << encrypt_decrypt_input(clearLineWithoutTag, false) << std::endl;
            }
            lineIndicatorForFile++;
        }
        currentFile.close();

        write_to_file(fileName, lines);
    }
    else {
        std::cout << "Błąd podczas otwierania pliku \"" << fileName << "\", sprawdz podana sciezke lub nazwe pliku." << std::endl;
    }
}

/**
 * Function opens a file and looks through it line by line in serach of a password passed in parameters
 *
 * @param fileName name of the file that will be searched
 * @param searchedPassword password that will be searched for
 * @return message stating how many times was the password found in the file
 */
// todo these should be the same function
std::string search_all_passwords(const std::string& fileName, const std::string& searchedPassword) {
    std::string endMessage;
    if (does_file_exist(fileName)) {
        std::ifstream currentFile;
        std::vector<std::string> lines;
        std::string currentLine;
        int howManyTimesWasThePasswordFound = 0;

        currentFile.open(fileName);
        while (std::getline(currentFile, currentLine)) {
            lines.push_back(currentLine);

            if (currentLine.find(encrypt_decrypt_input("Haslo: ")) != std::string::npos) {
                std::string clearLineWithoutTag;

                for (int i = 7; i < currentLine.length(); i++) {
                    clearLineWithoutTag += currentLine[i];
                }
                if (encrypt_decrypt_input(clearLineWithoutTag, false) == searchedPassword) {
                    howManyTimesWasThePasswordFound++;
                }
            }
        }
        endMessage = "Wprowadzono haslo, ktore pojawilo sie w pliku - " 
           + std::to_string(howManyTimesWasThePasswordFound)
           + " razy.";
        currentFile.close();

        write_to_file(fileName, lines);
    }
    else {
        std::cout << "Błąd podczas otwierania pliku \"" << fileName << "\", sprawdz podana sciezke lub nazwe pliku." << std::endl;
    }

    return endMessage;
}

void write_to_file(const std::string& fileName, std::vector<std::string> lines, int lineNumber = 0, std::string editedPassword = "") {
    std::ofstream writeToFile;
    writeToFile.open(fileName);
    lineNumber--;

    for (int i = 0; i < lines.size(); i++) {
        if (i != lineNumber) {
            if (i == 11 || i == 22 || i == 33) {
                writeToFile << simulate_noise(i) << std::endl;
            }
            writeToFile << lines[i] << std::endl;
        }
        else {
            if (i == 11 || i == 22 || i == 33) {
                writeToFile << simulate_noise(i) << std::endl;
            }
            writeToFile << encrypt_decrypt_input(editedPassword) << std::endl;
        }
    }

    if (lines.size() < 33) {
        for (int i = lines.size(); i < 35; i++) {
            if (i == 11 || i == 22 || i == 33) {
                writeToFile << simulate_noise(i) << std::endl;
            }
            writeToFile << encrypt_decrypt_input(generate_random_string(rand() % 10)) << std::endl;
        }
    }
    writeToFile.close();
}
