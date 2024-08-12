# LIBRARY USED
**C++ REST SDK (Casablanca)** for sending post request.


# INSTALLING THE LIBRARY
**1. Debian based distros** -> sudo apt-get install libcpprest-dev<br>
**2. Fedora** -> sudo dnf install cpprest 

# TO RUN THE PROGRAM
Make sure to install C++ REST SDK library in your system.<br>
You also have to replace the value of the **apiKey** variable inside the main function with your actual **api key**.<br>
Run the **"gemini"** executable in the bin folder along with your prompt **(Only for linux users)**.<br>
**i.e, ./gemini Hello there,can you explain how AI works? or ./gemini "Hello there,can you explain how AI works?".I prefer to use the latter one because certain symbols have special meaning to the shell e.g. '?'**.
Windows and Mac users will have to compile the code themselves.

# COMPILING THE CODE
For G++ compiler run -> **g++ src/gemini.cpp src/main.cpp -o bin/gemini -lcpprest -lssl -lcrypto -lboost_system**
