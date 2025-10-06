#pragma once
#include "password.cpp"
#include "cypher.h"
#include "files.h"
#include "time_stamp.h"
#include <string>

std::string generate_password(const int ilosc_znakow, const bool wielkie, const bool specjalne, const std::string& nazwa);
std::string password_strength_verifier(std::string haslo);
std::string password_edition(const std::string& nazwaPliku);
void search_password(const std::string& nazwaPliku, const std::string& szukaneHaslo, const std::string& parametr);
std::string search_all_passwords(const std::string& fileName, const std::string& searchedPassword);
