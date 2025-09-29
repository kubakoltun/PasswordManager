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

            if (obecnaLinia.find(szyfrujWejscie("Haslo: ")) != std::string::npos) {
                std::string usuwanieZbednej;
                for (int i = 7; i < obecnaLinia.length(); i++) {
                    usuwanieZbednej += obecnaLinia[i];
                }
                std::cout << wyswietlonaLinia << ". " << rozszyfrujFraze(usuwanieZbednej) << std::endl;
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
                if (i == 11) {
                    zapisDoPliku << sprawdzCzas("h") << std::endl;
                }
                if (i == 22) {
                    zapisDoPliku << sprawdzCzas("m") << std::endl;
                }
                if (i == 33) {
                    zapisDoPliku << sprawdzCzas("s") << std::endl;
                }
                zapisDoPliku << linie[i] << std::endl;
            }
            else {
                if (i == 11) {
                    zapisDoPliku << sprawdzCzas("h") << std::endl;
                }
                if (i == 22) {
                    zapisDoPliku << sprawdzCzas("m") << std::endl;
                }
                if (i == 33) {
                    zapisDoPliku << sprawdzCzas("s") << std::endl;
                }
                zapisDoPliku << szyfrujWejscie(edytowaneHaslo) << std::endl;
            }
        }

        if (linie.size() < 33) {
            std::string zmie = "v";
            for (int i = linie.size(); i < 35; i++) {
                zmie += 2;
                if (i == 11) {
                    zapisDoPliku << sprawdzCzas("h") << std::endl;
                }
                if (i == 22) {
                    zapisDoPliku << sprawdzCzas("m") << std::endl;
                }
                if (i == 33) {
                    zapisDoPliku << sprawdzCzas("s") << std::endl;
                }
                zapisDoPliku << szyfrujWejscie("1nied3ozla2man4ia5") << szyfrujWejscie(zmie) << std::endl;
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

            if (obecnaLinia.find(szyfrujWejscie(poszukiwany)) != std::string::npos) {
                std::cout << wyswietlonaLinia << ". " << rozszyfrujFraze(obecnaLinia) << std::endl;
                usuwanieZbednej = "";
            }
            if (obecnaLinia.find(szyfrujWejscie("Haslo: ")) != std::string::npos && usuwanieZbednej.empty()) {
                for (int i = 7; i < obecnaLinia.length(); i++) {
                    usuwanieZbednej += obecnaLinia[i];
                }
                std::cout << wyswietlonaLinia << ". " << rozszyfrujFraze(usuwanieZbednej) << std::endl;
            }
            wyswietlonaLinia++;
        }
        obecnyPlik.close();

        std::ofstream zapisDoPliku;
        zapisDoPliku.open(nazwaPliku);
        numerLinii--;

        for (int i = 0; i < linie.size(); i++) {
            if (i != numerLinii) {
                if (i == 11) {
                    zapisDoPliku << sprawdzCzas("h") << std::endl;
                }
                if (i == 22) {
                    zapisDoPliku << sprawdzCzas("m") << std::endl;
                }
                if (i == 33) {
                    zapisDoPliku << sprawdzCzas("s") << std::endl;
                }
                zapisDoPliku << linie[i] << std::endl;
            }
        }

        if (linie.size() < 33) {
            std::string zmie = "e";
            for (int i = linie.size(); i < 35; i++) {
                zmie += 2;
                if (i == 11) {
                    zapisDoPliku << sprawdzCzas("h") << std::endl;
                }
                if (i == 22) {
                    zapisDoPliku << sprawdzCzas("m") << std::endl;
                }
                if (i == 33) {
                    zapisDoPliku << sprawdzCzas("s") << std::endl;
                }
                zapisDoPliku << szyfrujWejscie("1nied3ozla2man4ia5") << szyfrujWejscie(zmie) << std::endl;
            }
        }
        zapisDoPliku.close();
    }
    else {
        std::cout << "Błąd podczas otwierania pliku \"" << nazwaPliku << "\", sprawdz podana sciezke lub nazwe pliku." << std::endl;
    }
}

/**
 * W trakcie tworzenia wektora trzymajacego tresc pliku sprawdzane sa wystapienia hasla podanego przez uzytkownika
 * Prace w obrebie hasla wymagaja zapisania timestampow
 *
 * @param nazwaPliku plik, na ktorym wykonywana jest operacja
 * @param szukaneHaslo haslo podane przez uztykownika, ktorego wartosc jest wyszukiwana w innych liniach pliku
 * @return zwracany jest komunikat o ilosci wystapien podanego hasla w danym pliku
 */
std::string wyszukajWszystkieHasla(const std::string& nazwaPliku, const std::string& szukaneHaslo) {
    std::string komunikat;
    if (does_file_exist(nazwaPliku)) {
        std::ifstream obecnyPlik;
        std::vector<std::string> linie;
        std::string obecnaLinia;
        std::string wyswietlaneHaslo;
        int wyswietlonaLinia = 1;
        int ileRazy = 0;
        obecnyPlik.open(nazwaPliku);
        std::string usuwanieZbednej;

        while (std::getline(obecnyPlik, obecnaLinia)) {
            linie.push_back(obecnaLinia);

            if (obecnaLinia.find(szyfrujWejscie("Haslo: ")) != std::string::npos) {
                for (int i = 7; i < obecnaLinia.length(); i++) {
                    usuwanieZbednej += obecnaLinia[i];
                }
                if (rozszyfrujFraze(usuwanieZbednej) == szukaneHaslo) {
                    ileRazy++;
                }
            }
            wyswietlonaLinia++;
        }

        if (ileRazy == 1) {
            komunikat = "Wprowadzono haslo, ktore jeszcze nie wystepuje w tym pliku.";
        }
        else if (ileRazy == 1) {
            komunikat = "Wprowadzono haslo, ktore pojawilo sie juz raz w pliku.";
        }
        else if (ileRazy > 1) {
            komunikat = &"Wprowadzono haslo, ktore pojawilo sie w pliku - "[ileRazy];
            komunikat += " razy.";
        }
        obecnyPlik.close();

        std::ofstream zapisDoPliku;
        zapisDoPliku.open(nazwaPliku);

        for (int i = 0; i < linie.size(); i++) {
            if (i == 11) {
                zapisDoPliku << sprawdzCzas("h") << std::endl;
            }
            if (i == 22) {
                zapisDoPliku << sprawdzCzas("m") << std::endl;
            }
            if (i == 33) {
                zapisDoPliku << sprawdzCzas("s") << std::endl;
            }
            zapisDoPliku << linie[i] << std::endl;
        }

        if (linie.size() < 33) {
            std::string zmie = "l";
            for (int i = linie.size(); i < 35; i++) {
                zmie += '2';
                if (i == 11) {
                    zapisDoPliku << sprawdzCzas("h") << std::endl;
                }
                if (i == 22) {
                    zapisDoPliku << sprawdzCzas("m") << std::endl;
                }
                if (i == 33) {
                    zapisDoPliku << sprawdzCzas("s") << std::endl;
                }
                zapisDoPliku << szyfrujWejscie("1nied3ozla2man4ia5") << szyfrujWejscie(zmie) << std::endl;
            }
        }
        zapisDoPliku.close();
    }
    else {
        std::cout << "Błąd podczas otwierania pliku \"" << nazwaPliku << "\", sprawdz podana sciezke lub nazwe pliku." << std::endl;

    }
    return komunikat;
}