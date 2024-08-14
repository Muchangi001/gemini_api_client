#ifndef GEMINI_HPP
#define GEMINI_HPP

#include <cpprest/http_client.h>
#include <cpprest/uri.h>
#include <cpprest/json.h>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>
#include <iostream>

std::string& readInput(std::string &prompt,char *argv[], int argc);
std::tm getCurrentTime();

#endif