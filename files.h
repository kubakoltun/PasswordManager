#pragma once
#include "files.h"
#include "cypher.h"
#include "time_stamp.h"
#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <vector>
#include <chrono>

bool does_file_exist(const std::string& podanyPlik);
std::string read_file_content(const std::string& nazwaPliku, bool usuwanieHasla, bool usuwanieKategorii);
std::string enter_record_into_file(std::string nazwaPliku, const std::string& nazwa, const std::string& haslo, std::string kategoria, const std::string& login, const std::string& strona);
void sort_and_show_passwords_per_input(const std::string& nazwaPliku, const std::string& parametr, const std::string& parametrDrugi, const std::string& wprowadzono, const std::string& wprowadzonoDwa);
void write_to_file(const std::string& fileName, std::vector<std::string> lines, int lineNumber = 0, std::string editedPassword = "", bool isCategoryRemoval = false);
bool validate_whether_the_file_exists(const std::string& fileName);

enum class SearchState {
    Searching,
    FoundFirstMatch,
    FoundAfterTag
};
