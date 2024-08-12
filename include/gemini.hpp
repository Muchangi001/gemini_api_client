#ifndef GEMINI_HPP
#define GEMINI_HPP

#include <cpprest/http_client.h>
#include <cpprest/uri.h>
#include <cpprest/json.h>
#include <string>
#include <iostream>

std::string& readInput(std::string &prompt,char *argv[], int argc);

#endif