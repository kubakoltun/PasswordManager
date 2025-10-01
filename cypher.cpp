#include "cypher.h"
#include <string>

/**
 * String passed in the parameter gets its ASCII characters moved to either encrypt or decrypt its value
 * Shifting the char to the next value (+1) is considered a encryption
 * Shifting the chat to the previous value (-1) is considered a decryption
 *
 * @param inputString parameter that will be encrypted
 * @param isEncription decides whether its a encryption or decryption, default true = encryption
 * @return encrypted argument
 */
std::string encrypt_decrypt_input(std::string inputString, bool isEncription = true) {
    size_t stringLength = inputString.length();
    std::string encryptedString;
    char tmpCharShift = ' ';

    for (size_t i = 0; i < stringLength; i++) {
        tmpCharShift = inputString[i];
        tmpCharShift = isEncription ? tmpCharShift+1 : tmpCharShift-1;
        encryptedString += tmpCharShift;
    }

    return encryptedString;
}
