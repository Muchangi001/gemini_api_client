#include "../include/gemini.hpp"

std::string& readInput(std::string &prompt,char *argv[], int argc){
    for (int i = 1; i != argc;++i) {
        prompt.append(argv[i]);
        if (i != argc - 1) prompt.append(" ");
    }
    return prompt;
}

std::tm getCurrentTime(){
    auto now = std::chrono::system_clock::now();
    std::time_t now_t = std::chrono::system_clock::to_time_t(now);
    return *std::localtime(&now_t); 
}