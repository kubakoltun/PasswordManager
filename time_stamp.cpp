#include <chrono>
#include <ctime>
#include "time_stamp.h"

/**
 * The function creates simulated noise so that other entries are not that visiable
 *
 * @param timePartIndicator part of the time that will be chosen: 11 = h, 22 = m, 33 = s
 * @return string containing part of the timestamp covered by a random string
 */
std::string simulate_noise(int timePartIndicator) {
    auto start = std::chrono::system_clock::now();
    auto legacyStart = std::chrono::system_clock::to_time_t(start);
    char tmBuff[30];
    ctime_s(tmBuff, sizeof(tmBuff), &legacyStart);

    std::string randomString = generate_random_string(rand() % 25);

    std::string time = tmBuff;
    std::string noise;

    if (timePartIndicator == 11) {
        noise += time[11];
        noise += randomString;
        noise += time[12];

        return noise;
    }

    if (timePartIndicator == 22) {
        noise += time[14];
        noise += randomString;
        noise += time[15];

        return noise;
    }

    if (timePartIndicator == 33) {
        noise += time[17];
        noise += randomString; 
        noise += time[18];

        return noise;
    }

    return "";
}

/**
 * Generating random string with length regulated by a parameter
 * 
 * @param len number of characters that the string should have 
 * @return random string
 */
std::string generate_random_string(const int len) {
    static const char alphaNum[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; i++) {
        tmp_s += alphaNum[rand() % (sizeof(alphaNum) - 1)];
    }

    return tmp_s;
}
