#include "../include/gemini.hpp"

int main(int argc, char *argv[]) {

    const std::string logsDir = std::filesystem::current_path().string() + "/gemini_logs";
    const std::string logFilePath = logsDir + "/gemini_logs.md";
    const std::string uri = "https://generativelanguage.googleapis.com";
    std::string apiKey = ""; //replace with your actual api key

    //checking if the log file exists
    if (!std::filesystem::exists(logsDir)) {
        std::cout << "creating new '" << logsDir << "' directory" << std::endl;
        std::filesystem::create_directory(logsDir);
        std::cout << "creating new '" << logFilePath << "' file" << std::endl;
    }

    std::cout << "writing to '" << logFilePath << "'" << std::endl << std::endl;

    //storing the existing log contents in a stringstream
    std::ifstream existingFile(logFilePath);
    std::stringstream buffer;
    buffer << existingFile.rdbuf();
    existingFile.close();

    //opening the log file in truncate mode to overrite content
    std::ofstream logFile;
    logFile.open(logFilePath, std::ios::trunc);

    //checking if the log file is open
    if (!logFile) {
        std::cerr << "Error : Could not open the file for writing" << std::endl;
        return 1;
    }

    //storing input
    std::string prompt;
    prompt = readInput(prompt, argv, argc);

    //creating http client
    web::http::client::http_client client (U(uri));

    //setting up json payload for the post request
    web::json::value postData = web::json::value::object({{
        U("contents"), web::json::value::array({
            web::json::value::object({{
                U("parts"), web::json::value::array({
                    web::json::value::object({{
                        U("text"), web::json::value::string(U(prompt))
                    }})
                })
            }})
        })
    }});

    //create and configure http post request
    web::http::http_request request(web::http::methods::POST);
    request.set_request_uri(U("/v1beta/models/gemini-1.5-flash-latest:generateContent?key=") + U(apiKey));
    request.headers().set_content_type(U("application/json"));
    request.set_body(postData);

    //send request and process response
    client.request(request).then([&](web::http::http_response response){
        if (response.status_code() == web::http::status_codes::OK) {
            auto body = response.extract_json().get();
            auto text = body[U("candidates")][0][U("content")][U("parts")][0][U("text")].as_string();

            //get the current time and format it
            std::tm currentTime = getCurrentTime();

            //write the response to the log file
            logFile << "**TIME :**"<< " *" << std::put_time(&currentTime, "%d-%m-%Y %H:%M:%S") << "*" << "<br>" << std::endl;
            logFile << "**PROMPT =>** " << prompt << "<br>" << std::endl;
            logFile << "**RESPONSE ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓**" << "<br>" <<std::endl;
            logFile << text << std::endl;
            logFile << "---" << std::endl;

            //append old logs content
            logFile << buffer.str();

            //write response to stdout
            std::cout << "RESPONSE ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓" <<std::endl;
            std::cout << text <<std::endl;
        } else {
            std::cerr << "Request failed with status code: " << response.status_code() << std::endl;
        }
    }).wait();

    //closing the log file
    logFile.close();

    return 0;
}
