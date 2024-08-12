#include "../include/gemini.hpp"

int main(int argc, char *argv[]) {

    const std::string uri = "https://generativelanguage.googleapis.com";
    std::string apiKey = "AIzaSyCFDYHepi-dXQ-n2YZpR_sx6OlAgVDbgOs";

    //storing input
    std::string prompt;
    prompt = readInput(prompt, argv, argc);

    //http client
    web::http::client::http_client client (U(uri));

    //json payload
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

    //http request
    web::http::http_request request(web::http::methods::POST);
    request.set_request_uri(U("/v1beta/models/gemini-1.5-flash-latest:generateContent?key=") + U(apiKey));
    request.headers().set_content_type(U("application/json"));
    request.set_body(postData);

    //send request
    client.request(request).then([](web::http::http_response response){
        if (response.status_code() == web::http::status_codes::OK) {
            auto body = response.extract_json().get();
            auto text = body[U("candidates")][0][U("content")][U("parts")][0][U("text")].as_string();
            std::cout << text <<std::endl;
        }else std::cerr << "Request failed with status code: " << response.status_code() << std::endl;
    }).wait();

    return 0;
}