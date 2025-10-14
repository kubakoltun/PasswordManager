#include "cypher.h"
#include "files.h"
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

            if (currentLine.find(encrypt_decrypt_input(DEFAULT_TAG)) != std::string::npos) {
                std::string clearLineWithoutTag;
                for (int i = DEFAULT_TAG.size(); i < currentLine.length(); i++) {
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
 * Function opens a file and searches for passwords or tagged entries.
 *
 * @param fileName name of the file to search
 * @param searchedPassword the password or phrase to search for
 * @param startOfLineTag tag marking the start of relevant lines (default "Haslo: ")
 * @param printResults whether to print matching lines (true) or return summary (false)
 * @return summary message if printResults is false, otherwise empty string
 */
std::string search_password(const std::string& fileName, const std::string& searchedPassword, const std::string& startOfLineTag = DEFAULT_TAG, bool printResults = true) {
    if (!does_file_exist(fileName)) {
        std::cout << "Błąd podczas otwierania pliku \"" << fileName << "\", sprawdz podana sciezke lub nazwe pliku." << std::endl;
        return "";
    }

    std::ifstream currentFile(fileName);
    std::vector<std::string> lines;
    std::string currentLine;
    int lineNumber = 1;
    int matchCount = 0;

    const std::string encryptedTag = encrypt_decrypt_input(startOfLineTag);
    const std::string encryptedSearch = encrypt_decrypt_input(searchedPassword);

    while (std::getline(currentFile, currentLine)) {
        lines.push_back(currentLine);

        // Only process lines that begin with the expected tag
        if (currentLine.find(encryptedTag) != std::string::npos) {
            // Decrypt and remove tag
            std::string decryptedLine = encrypt_decrypt_input(currentLine, false);
            std::string clearPart = decryptedLine.substr(startOfLineTag.size());

            // Count or print matches
            if (clearPart == searchedPassword) {
                matchCount++;
            }

            if (printResults) {
                std::cout << lineNumber << ". " << decryptedLine << std::endl;
            }
        }

        lineNumber++;
    }

    currentFile.close();
    write_to_file(fileName, lines);

    // Print the message only if the caller wants it
    if (!printResults) {
        return "Wprowadzono haslo, ktore pojawilo sie w pliku - " 
                + std::to_string(matchCount)
                + " razy.";
    }
  
    return "";
}
