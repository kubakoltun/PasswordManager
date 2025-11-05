#pragma once
#include <string>
#include <vector>

const std::vector<std::string> ALL_TAGS = {
    "Nazwa: ",
    "Kategoria: ",
    "Strona WWW: ",
    "Login: "
};

std::string prompt_line(const std::string& prompt);
int prompt_int(const std::string& prompt);
bool prompt_accept_or_skip(const std::string& prompt);
void password_search_print_helper(std::string inLineName, std::string tagName, std::string mainFile);
void default_choice_message(int from, int to, int userInputMainCommand);
void initializae_sorting_by_params(std::string inLineName, std::string tagName, std::string mainFile);
void print_tags_names(std::string skipTagName = "", bool shouldTrim = false);
std::string choose_secondary_tag(const std::string& tagName);
