#include "cypher.cpp"
#include "files.h"
#include "files.cpp"
#include "time_stamp.h"
#include "time_stamp.cpp"
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <cctype>

/**
 * Generates a random password according to user defined rules (arguments).
 *
 * @param length - lenght of the password decaler by the user
 * @param use_uppercase - tells whether the password should contain capital letters
 * @param use_special - tells whether  the password should contain special characters
 * @param name - name of the password
 * @return a generated password is returned
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

    // Shuffle so guarantees aren’t at the front
    std::shuffle(password.begin(), password.end(), gen);

    return password;
}

/**
 * Veryfing the password strenght based on some general criteria
 *
 * @param password - password that is beign verified
 * @return quality of the password in a string 
 */
std::string password_strength_verifier(std::string password) {
    int lowercaseCount = 0;
    int uppercaseCount = 0;
    int digitCount     = 0;
    int specialCount   = 0;

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

    if (password_length >= 12 && lowercaseCount > 3 && uppercaseCount > 3 && digitCount > 2 && specialCount >= 2) {
        return "Excelent";
    }
    if (password_length >= 9 && lowercaseCount > 2 && uppercaseCount > 2 && digitCount >= 2) {
        return "Good";
    }
    if (password_length >= 8 && lowercaseCount >= 1 && uppercaseCount >= 1 && digitCount >= 1) {
        return "Bad";
    }
    if (password_length > 4 && password_length < 8) {
        return "Terrible";
    }

    return "Dangerous";
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
std::string password_edition(const std::string& nazwaPliku) {

    if (does_file_exist(nazwaPliku)) {
        std::ifstream obecnyPlik;
        std::vector<std::string> linie;
        std::string obecnaLinia;
        std::string edytowaneHaslo;
        int numerLinii = 0;
        obecnyPlik.open(nazwaPliku);
        int wyswietlonaLinia = 1;

        while (getline(obecnyPlik, obecnaLinia)) {
            linie.push_back(obecnaLinia);

            if (obecnaLinia.find(encrypt_decrypt_input("Haslo: ")) != std::string::npos) {
                std::string usuwanieZbednej;
                for (int i = 7; i < obecnaLinia.length(); i++) {
                    usuwanieZbednej += obecnaLinia[i];
                }
                std::cout << wyswietlonaLinia << ". " << encrypt_decrypt_input(usuwanieZbednej, false) << std::endl;
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
                if (i == 11 || i == 22 || i == 33) {
                    zapisDoPliku << simulate_noise(i) << std::endl;
                }
                zapisDoPliku << linie[i] << std::endl;
            }
            else {
                if (i == 11 || i == 22 || i == 33) {
                    zapisDoPliku << simulate_noise(i) << std::endl;
                }
                zapisDoPliku << encrypt_decrypt_input(edytowaneHaslo) << std::endl;
            }
        }

        if (linie.size() < 33) {
            std::string zmie = "v";
            for (int i = linie.size(); i < 35; i++) {
                zmie += 2;
                if (i == 11 || i == 22 || i == 33) {
                    zapisDoPliku << simulate_noise(i) << std::endl;
                }
                zapisDoPliku << encrypt_decrypt_input("1nied3ozla2man4ia5") << encrypt_decrypt_input(zmie) << std::endl;
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
    if (does_file_exist(nazwaPliku)) {
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

            if (obecnaLinia.find(encrypt_decrypt_input(poszukiwany)) != std::string::npos) {
                std::cout << wyswietlonaLinia << ". " << encrypt_decrypt_input(obecnaLinia, false) << std::endl;
                usuwanieZbednej = "";
            }
            if (obecnaLinia.find(encrypt_decrypt_input("Haslo: ")) != std::string::npos && usuwanieZbednej.empty()) {
                for (int i = 7; i < obecnaLinia.length(); i++) {
                    usuwanieZbednej += obecnaLinia[i];
                }
                std::cout << wyswietlonaLinia << ". " << encrypt_decrypt_input(usuwanieZbednej, false) << std::endl;
            }
            wyswietlonaLinia++;
        }
        obecnyPlik.close();

        std::ofstream zapisDoPliku;
        zapisDoPliku.open(nazwaPliku);
        numerLinii--;

        for (int i = 0; i < linie.size(); i++) {
            if (i != numerLinii) {
                if (i == 11 || i == 22 || i == 33) {
                    zapisDoPliku << simulate_noise(i) << std::endl;
                }
                zapisDoPliku << linie[i] << std::endl;
            }
        }

        if (linie.size() < 33) {
            std::string zmie = "e";
            for (int i = linie.size(); i < 35; i++) {
                zmie += 2;
                if (i == 11 || i == 22 || i == 33) {
                    zapisDoPliku << simulate_noise(i) << std::endl;
                }
                zapisDoPliku << encrypt_decrypt_input("1nied3ozla2man4ia5") << encrypt_decrypt_input(zmie) << std::endl;
            }
        }
        zapisDoPliku.close();
    }
    else {
        std::cout << "Błąd podczas otwierania pliku \"" << nazwaPliku << "\", sprawdz podana sciezke lub nazwe pliku." << std::endl;
    }
}

/**
 * Function opens a file and looks through it line by line in serach of a password passed in parameters
 *
 * @param fileName name of the file that will be searched
 * @param searchedPassword password that will be searched for
 * @return message stating how many times was the password found in the file
 */
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
        endMessage = &"Wprowadzono haslo, ktore pojawilo sie w pliku - "[howManyTimesWasThePasswordFound];
        endMessage += " razy.";
        currentFile.close();

        std::ofstream writeToFile;
        writeToFile.open(fileName);
        for (int i = 0; i < lines.size(); i++) {
            if (i == 11 || i == 22 || i == 33) {
                writeToFile << simulate_noise(i) << std::endl;
            }
            writeToFile << lines[i] << std::endl;
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
    else {
        std::cout << "Błąd podczas otwierania pliku \"" << fileName << "\", sprawdz podana sciezke lub nazwe pliku." << std::endl;
    }

    return endMessage;
}
