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
 * Po otworzeniu pliku odczytywana jest jego tresc po kazdej linii
 * Linie pliku sa pushowane na koniec wektora
 * Uzytkownik dostaje liste parametrow, ktore chce usunac
 * Uzytkownik jest proszony o potwierdzenie wyboru nastepnie aby sfinalizowac zmiany wprowadzane sa zmiany do pliku
 * Linie, ktore wybral uzytkownik nie sa wprowadzane do pliku przez co zostaja usuniete
 * Ze wzgledu na wykonywanie operacji na danych do wpliku wprowadzane sa rowniez timestampy
 *
 * @param fileName plik, na ktorym bedzie wykonywana operacja
 * @param isPasswordRemoval informacja dla metody czy usuwane bedzie haslo
 * @param isCategoryRemoval informacja czy nalezy wejsc w siezke usuwania kategorii
 * @return zwracany jest komunikat o pomyslnosci wykonanych operacji
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

    std::ofstream writeToFile(fileName);
    lineNumber--;
    int previousLineNumber = 0;

    if (isCategoryRemoval) {
        previousLineNumber = lineNumber++;
    }

    for (int i = 0; i < lines.size(); i++) {
        if (isCategoryRemoval) {
            if (i != previousLineNumber && i != lineNumber) {
                if (i == 11 || i == 22 || i == 33) {
                    writeToFile << simulate_noise(i) << std::endl;
                }
                writeToFile << lines[i] << std::endl;

            }
        }
        else if (i != lineNumber) {
            if (i == 11 || i == 22 || i == 33) {
                writeToFile << simulate_noise(i) << std::endl;
            }
            writeToFile << lines[i] << std::endl;
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

    return "Dokonano wprowadzonych zmian.";
}

/**
 * Po sprawdzeniu czy plik otworzyl sie poprawnie sprawdzane jest czy, ktorys z parametrow zostal pominiety
 * Do pliku wprowadzane sa wpisane przez uzytkownika biezaco szyfrowane parametry
 * Dana wartosc parametru jest poprzedzona rowniez szyfrowanym kluczem
 * Jako ze sa wykonywane operacje na danych do pliku jest rowniez wprowadzany timestamp
 *
 * @param fileName nazwa pliku, na ktorym beda wykonywane akcje
 * @param name wprowadzona przez uzytkownika nazwa przypisana do hasla
 * @param password zadeklarowane przez uzytkownika haslo
 * @param category kategoria ktora uzytkownik przypisal do hasla
 * @param login login podany przez uzytkownika
 * @param page strona www przypisana do haslo przez uzytkownika
 * @return nazwa pliku, na ktorym zostala wykonana operacja jest zwracana jako czesc komunikatu
 */
std::string enter_record_into_file(std::string fileName, const std::string& name, const std::string& password, std::string category, const std::string& login, const std::string& page) {
    if (!validate_whether_the_file_exists(fileName)) return "";

    std::fstream currentFile(fileName);
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

    // Rewind to start of file for reading
    currentFile.seekg(0);
    std::vector<std::string> lines;
    std::string currentLine;

    while (getline(currentFile, currentLine)) {
        lines.push_back(currentLine);
    }
    currentFile.close();

    write_to_file(fileName, lines);

    return fileName;
}

/**
 * Metoda zapisuje wartosc pliku do wektora, ktory nastepnie jest przeszukiwany w petli
 * W petli poszukiwane sa parametry wprowadzone przez uzytkownika, dla ktorych pokaza sie hasla
 *
 * @param fileName plik, na ktrym bedzie wykonywana operacja
 * @param parametr klucz wartosci parametru podany ze wzgledu na wybor uzytkownika
 * @param parametrDrugi w przypadku sortowania po dwoch parametrach podany przez uzytkownika klucz wartosci parametru
 * @param wprowadzono wartosc parametru wprowadzona przez uzytkownika
 * @param wprowadzonoDwa wartosc drugiego parametru podanego przez uzytkownika
 */
void sort_and_show_passwords_per_input(const std::string& fileName, const std::string& parametr, const std::string& parametrDrugi, const std::string& wprowadzono, const std::string& wprowadzonoDwa) {
    if (!validate_whether_the_file_exists(fileName)) return; // No file so skip the logic - exit early

    std::ifstream currentFile(fileName);
    std::vector<std::string> lines;
    std::string currentLine;
    std::string poszukiwany = parametr + wprowadzono;
    std::string poszukiwanyDrugi = parametrDrugi + wprowadzonoDwa;
    int lineNumber = 0;
    int shownLine = 1;
    std::string przesuniecie;
    bool isFound = false;

    while (std::getline(currentFile, currentLine)) {
        lines.push_back(currentLine);
        shownLine++;
    }

    for (const auto& i : lines) {
        if (i.find(encrypt_decrypt_input(poszukiwany)) != std::string::npos || i.find(encrypt_decrypt_input(poszukiwanyDrugi)) != std::string::npos) {
            przesuniecie = "1";
            isFound = true;
            std::cout << encrypt_decrypt_input(i, false) << std::endl;
        }
        if (currentLine.find(encrypt_decrypt_input(DEFAULT_TAG)) != std::string::npos && przesuniecie == "1" && isFound) {
            przesuniecie = "2";
            std::cout << encrypt_decrypt_input(i, false) << std::endl;
        }
        if ((i.find(encrypt_decrypt_input(parametr)) != std::string::npos || i.find(encrypt_decrypt_input(parametrDrugi)) != std::string::npos) && isFound && przesuniecie == "2") {
            std::cout << i << std::endl;
        }
        if (i.find(encrypt_decrypt_input(DEFAULT_TAG)) != std::string::npos && isFound && przesuniecie == "2") {
            std::cout << i << std::endl;
        }
    }
    currentFile.close();

    write_to_file(fileName, lines);
}

void write_to_file(const std::string& fileName, std::vector<std::string> lines, int lineNumber = 0, std::string editedPassword = "") {
    std::ofstream writeToFile;
    writeToFile.open(fileName);
    lineNumber--;

    // todo what were these magic numbers
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

bool validate_whether_the_file_exists(const std::string& fileName) {
    if (!does_file_exist(fileName)) {
        std::cout << "Błąd podczas otwierania pliku \"" << fileName << "\", sprawdz podana sciezke lub nazwe pliku." << std::endl;
        return false;
    }

    return true;
}
