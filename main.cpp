#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "Lexer.h"
#include "Parser.h"


using namespace std;

int main(int argc, char* argv[]) {
    ifstream file;
    string tempString;
    string fileContents;
    file.open(argv[1]);

    if (!file.is_open()) {
        cout << "error while opening the file.";
    }
    else {
        while (file.peek() != EOF){
            getline(file, tempString);
            fileContents = fileContents + tempString + "\n";
        }
    }

    Lexer object1;
    object1.setString(fileContents);
    object1.findAllTokens();

    Parser parserObject;
    parserObject.setTokenVector(object1.getTokenVector());
    try {
        parserObject.datalogProgram();
    }
    catch (string message){
        cout << message;
    }


    //Lexer testObject;
    //testObject.setString(testString);
    //testObject.findAllTokens();
    //cout << testObject.getToken();

    return 0;
}
