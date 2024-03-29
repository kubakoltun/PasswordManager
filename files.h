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

bool czyPlikIstnieje(const std::string& podanyPlik);
std::string odczytanieZawartosciPliku(const std::string& nazwaPliku, bool usuwanieHasla, bool usuwanieKategorii);
std::string wpisanieDoPliku(std::string nazwaPliku, const std::string& nazwa, const std::string& haslo, std::string kategoria, const std::string& login, const std::string& strona);
void sortowaniePoParametrach(const std::string& nazwaPliku, const std::string& parametr, const std::string& parametrDrugi, const std::string& wprowadzono, const std::string& wprowadzonoDwa);
