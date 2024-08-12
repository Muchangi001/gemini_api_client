#include "../include/gemini.hpp"

std::string& readInput(std::string &prompt,char *argv[], int argc){
    for (int i = 1; i != argc;++i) {
        prompt.append(argv[i]);
        if (i != argc - 1) prompt.append(" ");
    }
    return prompt;
}