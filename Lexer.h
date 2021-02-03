#ifndef UNTITLED1_LEXER_H
#define UNTITLED1_LEXER_H
#include <string>
#include <iostream>
#include "Token.h"
using namespace std;


class Lexer {
public:
    Lexer(){}
    string fileString;
    Token firstToken;
    TokenType computedTokenType = DONOTRUN;
    int lineNumber = 1;
    int addedLineNumber = 0;
    unsigned int symbolsRead = 0;
    unsigned int maxSymbolsRead = 0;
    char currentChar;
    bool readNext;
    bool needExtraLine = false;
    string tempTokenValue;
    int totalTokens = 0;


    void setString(string& passedString){
        fileString = passedString;
    }

    void findAllTokens () {
        while (fileString.size() >= 1){
            maxSymbolsRead = 0;
            symbolsRead = 0;
            currentChar = fileString[0];
            tempTokenValue = "";
            lineNumber = lineNumber + addedLineNumber;
            addedLineNumber = 0;
            // WHITESPACE
            if (isspace(currentChar)){
                maxSymbolsRead = 1;
                computedTokenType = DONOTRUN;
            }

            if (currentChar == '\n'){
                lineNumber = lineNumber + 1;
            }

            if (fileString.empty()) {
                computedTokenType = ENDOF;
                lineNumber = lineNumber + 1;
            }

        if (currentChar == ',') {
            symbolsRead = 1;
            if (symbolsRead > maxSymbolsRead) {
                maxSymbolsRead = symbolsRead;
                computedTokenType = COMMA;
            }
            symbolsRead = 0;
            currentChar = fileString[symbolsRead];
        }

        if (currentChar == '.') {
            symbolsRead = 1;
            if (symbolsRead > maxSymbolsRead) {
                maxSymbolsRead = symbolsRead;
                computedTokenType = PERIOD;
            }
            symbolsRead = 0;
            currentChar = fileString[symbolsRead];
        }

        if (currentChar == '?') {
            symbolsRead = 1;
            if (symbolsRead > maxSymbolsRead) {
                maxSymbolsRead = symbolsRead;
                computedTokenType = Q_MARK;
            }
            symbolsRead = 0;
            currentChar = fileString[symbolsRead];
        }

        if (currentChar == '(') {
            symbolsRead = 1;
            if (symbolsRead > maxSymbolsRead) {
                maxSymbolsRead = symbolsRead;
                computedTokenType = LEFT_PAREN;
            }
            symbolsRead = 0;
            currentChar = fileString[symbolsRead];
        }

        if (currentChar == ')') {
            symbolsRead = 1;
            if (symbolsRead > maxSymbolsRead) {
                maxSymbolsRead = symbolsRead;
                computedTokenType = RIGHT_PAREN;
            }
            symbolsRead = 0;
            currentChar = fileString[symbolsRead];
        }

        if (currentChar == ':') {
            symbolsRead = 1;
            if (symbolsRead > maxSymbolsRead) {
                maxSymbolsRead = symbolsRead;
                computedTokenType = COLON;
            }
            symbolsRead = 0;
            currentChar = fileString[symbolsRead];
        }

        if (currentChar == ':') {
            symbolsRead = symbolsRead + 1;
            currentChar = fileString[symbolsRead];
            if (currentChar == '-') {
                symbolsRead = symbolsRead + 1;
            }
            if (symbolsRead > maxSymbolsRead) {
                maxSymbolsRead = symbolsRead;
                computedTokenType = COLON_DASH;
            }
            symbolsRead = 0;
            currentChar = fileString[symbolsRead];
        }

        if (currentChar == '*') {
            symbolsRead = 1;
            if (symbolsRead > maxSymbolsRead) {
                maxSymbolsRead = symbolsRead;
                computedTokenType = MULTIPLY;
            }
            symbolsRead = 0;
            currentChar = fileString[symbolsRead];
        }
        if (currentChar == '+') {
            symbolsRead = 1;
            if (symbolsRead > maxSymbolsRead) {
                maxSymbolsRead = symbolsRead;
                computedTokenType = ADD;
            }
            symbolsRead = 0;
            currentChar = fileString[symbolsRead];
        }
        // STARTING NON SINGLES CHARACTER TOKENS
        // ID
        if (isalpha(currentChar)) {
            symbolsRead = 1;
            currentChar = fileString[symbolsRead];
            while ((isalpha(currentChar)) || isdigit(currentChar)) {
                symbolsRead = symbolsRead + 1;
                if (symbolsRead <=  fileString.size()) {
                    currentChar = fileString[symbolsRead];
                }
                else{
                    currentChar = '.';
                }
            }
            if (symbolsRead > maxSymbolsRead) {
                maxSymbolsRead = symbolsRead;
                computedTokenType = ID;
            }
            symbolsRead = 0;
            currentChar = fileString[symbolsRead];
        }

        //SCHEMES
        if (currentChar == 'S') {
            symbolsRead = symbolsRead + 1;
            currentChar = fileString[symbolsRead];
            if (currentChar == 'c') {
                symbolsRead = symbolsRead + 1;
                currentChar = fileString[symbolsRead];
                if (currentChar == 'h') {
                    symbolsRead = symbolsRead + 1;
                    currentChar = fileString[symbolsRead];
                    if (currentChar == 'e') {
                        symbolsRead = symbolsRead + 1;
                        currentChar = fileString[symbolsRead];
                        if (currentChar == 'm') {
                            symbolsRead = symbolsRead + 1;
                            currentChar = fileString[symbolsRead];
                            if (currentChar == 'e') {
                                symbolsRead = symbolsRead + 1;
                                currentChar = fileString[symbolsRead];
                                if (currentChar == 's') {
                                    symbolsRead = symbolsRead + 1;
                                    currentChar = fileString[symbolsRead];
                                    if (symbolsRead >= maxSymbolsRead) {
                                        maxSymbolsRead = symbolsRead;
                                        computedTokenType = SCHEMES;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            symbolsRead = 0;
            currentChar = fileString[symbolsRead];
        }

        //FACTS
        if (currentChar == 'F') {
            symbolsRead = symbolsRead + 1;
            currentChar = fileString[symbolsRead];
            if (currentChar == 'a') {
                symbolsRead = symbolsRead + 1;
                currentChar = fileString[symbolsRead];
                if (currentChar == 'c') {
                    symbolsRead = symbolsRead + 1;
                    currentChar = fileString[symbolsRead];
                    if (currentChar == 't') {
                        symbolsRead = symbolsRead + 1;
                        currentChar = fileString[symbolsRead];
                        if (currentChar == 's') {
                            symbolsRead = symbolsRead + 1;
                            currentChar = fileString[symbolsRead];
                            if (symbolsRead >= maxSymbolsRead) {
                                maxSymbolsRead = symbolsRead;
                                computedTokenType = FACTS;
                            }
                        }
                    }
                }
            }
            symbolsRead = 0;
            currentChar = fileString[symbolsRead];
        }
        // RULES
        if (currentChar == 'R') {
            symbolsRead = symbolsRead + 1;
            currentChar = fileString[symbolsRead];
            if (currentChar == 'u') {
                symbolsRead = symbolsRead + 1;
                currentChar = fileString[symbolsRead];
                if (currentChar == 'l') {
                    symbolsRead = symbolsRead + 1;
                    currentChar = fileString[symbolsRead];
                    if (currentChar == 'e') {
                        symbolsRead = symbolsRead + 1;
                        currentChar = fileString[symbolsRead];
                        if (currentChar == 's') {
                            symbolsRead = symbolsRead + 1;
                            currentChar = fileString[symbolsRead];
                            if ((symbolsRead >= maxSymbolsRead)) {
                                maxSymbolsRead = symbolsRead;
                                computedTokenType = RULES;
                            }
                        }
                    }
                }
            }

            symbolsRead = 0;
            currentChar = fileString[symbolsRead];
        }
        //QUERIES
        if (currentChar == 'Q') {
            symbolsRead = symbolsRead + 1;
            currentChar = fileString[symbolsRead];
            if (currentChar == 'u') {
                symbolsRead = symbolsRead + 1;
                currentChar = fileString[symbolsRead];
                if (currentChar == 'e') {
                    symbolsRead = symbolsRead + 1;
                    currentChar = fileString[symbolsRead];
                    if (currentChar == 'r') {
                        symbolsRead = symbolsRead + 1;
                        currentChar = fileString[symbolsRead];
                        if (currentChar == 'i') {
                            symbolsRead = symbolsRead + 1;
                            currentChar = fileString[symbolsRead];
                            if (currentChar == 'e') {
                                symbolsRead = symbolsRead + 1;
                                currentChar = fileString[symbolsRead];
                                if (currentChar == 's') {
                                    symbolsRead = symbolsRead + 1;
                                    currentChar = fileString[symbolsRead];
                                    if (symbolsRead >= maxSymbolsRead) {
                                        maxSymbolsRead = symbolsRead;
                                        computedTokenType = QUERIES;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            symbolsRead = 0;
            currentChar = fileString[symbolsRead];
        }

     //Strings
        if (currentChar == '\'') {
            addedLineNumber = 0;
            readNext = true;
            while (readNext) {
                symbolsRead = symbolsRead + 1;
                if (symbolsRead > fileString.size()) {
                    readNext = false;
                    computedTokenType = UNDEFINED;
                }
                currentChar = fileString[symbolsRead];
                if (currentChar == '\n') {
                    addedLineNumber = addedLineNumber + 1;
                }
                if (currentChar == '\'') {
                    symbolsRead = symbolsRead + 1;
                    if (symbolsRead > fileString.size()) {
                        computedTokenType = UNDEFINED;
                        break;
                    }
                    currentChar = fileString[symbolsRead];
                    if (currentChar == '\'') {
                        readNext = true;
                    }
                    else {
                        readNext = false;
                        currentChar = fileString[symbolsRead];
                        if ((symbolsRead >= maxSymbolsRead)) {
                            maxSymbolsRead = symbolsRead;
                            computedTokenType = STRING;
                        }
                    }
                }
            }
            symbolsRead = 0;
            currentChar = fileString[symbolsRead];
        }

        // COMMENT
        if (currentChar == '#') {
            readNext = true;
            symbolsRead = symbolsRead + 1;
            while (readNext) {
                currentChar = fileString[symbolsRead];
                if ((currentChar != EOF) && (currentChar != '\n')) {
                    symbolsRead = symbolsRead + 1;
                    readNext = true;
                } else {
                    readNext = false;
                }
            }
            if (symbolsRead >= maxSymbolsRead) {
                maxSymbolsRead = symbolsRead;
                computedTokenType = COMMENT;
            }
            symbolsRead = 0;
            currentChar = fileString[symbolsRead];
        }

        // +1 line comment
        if (currentChar == '#') {
            symbolsRead = symbolsRead + 1;
            currentChar = fileString[symbolsRead];
            if (currentChar == '|') {
                readNext = true;
                while (readNext) {
                    symbolsRead = symbolsRead + 1;
                    if (symbolsRead > fileString.size()) {
                        readNext = false;
                        computedTokenType = UNDEFINED;
                        break;
                    }
                    currentChar = fileString[symbolsRead];
                    if (currentChar == '\n') {
                        addedLineNumber = addedLineNumber + 1;
                    }
                    if (currentChar == '|') {
                            symbolsRead = symbolsRead + 1;
                            currentChar = fileString[symbolsRead];
                            readNext = true;
                            if (currentChar == '#'){
                                readNext = false;
                                symbolsRead = symbolsRead + 1;
                                if ((computedTokenType == COMMENT) || (symbolsRead >= maxSymbolsRead)) {
                                    maxSymbolsRead = symbolsRead;
                                    computedTokenType = COMMENT;
                                }
                            }
                    }
                    else{
                        readNext = true;
                        if ((symbolsRead >= maxSymbolsRead)){
                            maxSymbolsRead = 100000000;
                        }
                    }
                }
            }
            symbolsRead = 0;
            currentChar = fileString[symbolsRead];
        }

        if ((currentChar != ',') && (currentChar != '.') && (currentChar != '?') &&
            (currentChar != '(') && (currentChar != ')') && (currentChar != ':') &&
            (currentChar != '*') && (currentChar != '+') && (currentChar != 'S') &&
            (currentChar != 'F') && (currentChar != 'R') && (currentChar != 'Q') &&
            (!(isalpha(currentChar))) && (currentChar != '\'') && (currentChar != '#')
            && (!(isspace(currentChar)))) {
            maxSymbolsRead = 1;
            computedTokenType = UNDEFINED;
        }

        if (maxSymbolsRead == 0){
            maxSymbolsRead = fileString.size() - 1;
            addedLineNumber = addedLineNumber - 1;
            needExtraLine = true;
            computedTokenType = UNDEFINED;
        }

        if (maxSymbolsRead == 100000000){
            maxSymbolsRead = fileString.size() - 1;
            needExtraLine = true;
            computedTokenType = UNDEFINED;
        }

        for (unsigned int i = 0; i < maxSymbolsRead; ++i){
            tempTokenValue = tempTokenValue + fileString[i];
        }

        if (needExtraLine == true){
            tempTokenValue = tempTokenValue + '\n';
        }

        if (!(computedTokenType == DONOTRUN)) {
            firstToken.setTokenType(computedTokenType, tempTokenValue, lineNumber);
            firstToken.toString();
            totalTokens = totalTokens + 1;
        }
            fileString.erase(0, maxSymbolsRead);
        }

        computedTokenType = ENDOF;
        firstToken.setTokenType(computedTokenType, tempTokenValue, lineNumber);
        firstToken.toString();
        totalTokens = totalTokens + 1;
        cout << "Total Tokens = " << totalTokens;
    }


    string getToken(){
        firstToken.setTokenType(computedTokenType, tempTokenValue, lineNumber);
        return firstToken.toString();
    }
};

#endif //UNTITLED1_LEXER_H
