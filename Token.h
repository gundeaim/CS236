#ifndef UNTITLED1_TOKEN_H
#define UNTITLED1_TOKEN_H
#include <string>
#include <iostream>
#include <ostream>
using namespace std;

enum TokenType {DONOTRUN, COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, ENDOF};

string tokenTypeToString(TokenType tokenType){
    switch (tokenType) {
        case COMMA: return "COMMA"; break;
        case PERIOD: return "PERIOD"; break;
        case Q_MARK: return "Q_MARK"; break;
        case LEFT_PAREN: return "LEFT_PAREN"; break;
        case RIGHT_PAREN: return "RIGHT_PAREN"; break;
        case COLON: return "COLON"; break;
        case COLON_DASH: return "COLON_DASH"; break;
        case MULTIPLY: return "MULTIPLY"; break;
        case ADD: return "ADD"; break;
        case SCHEMES: return "SCHEMES"; break;
        case FACTS: return "FACTS"; break;
        case RULES: return "RULES"; break;
        case QUERIES: return "QUERIES"; break;
        case ID: return "ID"; break;
        case STRING: return "STRING"; break;
        case COMMENT: return "COMMENT"; break;
        case UNDEFINED: return "UNDEFINED"; break;
        case DONOTRUN: return ""; break;
        case ENDOF: return "EOF";
    }
    return "ERROR";
}

class Token {
public:
    Token(){}
    string fileString;
    string value;
    int lineNumber;
    TokenType currentType;
    string tokenFinalString;
    ostringstream outString;



    void setString(string& passedString){
        fileString = passedString;
    }

    void setTokenType (TokenType computedTokenType, string passedValue, int passedLineNumber){
        currentType = computedTokenType;
        if (currentType == COMMA){
            value = ",";
            lineNumber = passedLineNumber;
        }
        if (currentType == PERIOD){
            value = ".";
            lineNumber = passedLineNumber;
        }
        if (currentType == Q_MARK){
            value = "?";
            lineNumber = passedLineNumber;
        }
        if (currentType == LEFT_PAREN){
            value = "(";
            lineNumber = passedLineNumber;
        }
        if (currentType == RIGHT_PAREN){
            value = ")";
            lineNumber = passedLineNumber;
        }
        if (currentType == COLON){
            value = ":";
            lineNumber = passedLineNumber;
        }
        if (currentType == COLON_DASH){
            value = ":-";
            lineNumber = passedLineNumber;
        }
        if (currentType == MULTIPLY){
            value = "*";
            lineNumber = passedLineNumber;
        }
        if (currentType == ADD){
            value = "+";
            lineNumber = passedLineNumber;
        }
        if (currentType == SCHEMES){
            value = "Schemes";
            lineNumber = passedLineNumber;
        }
        if (currentType == FACTS){
            value = "Facts";
            lineNumber = passedLineNumber;
        }
        if (currentType == RULES){
            value = "Rules";
            lineNumber = passedLineNumber;
        }
        if (currentType == QUERIES){
            value = "Queries";
            lineNumber = passedLineNumber;
        }
        if (currentType == ID){
            value = passedValue;
            lineNumber = passedLineNumber;
        }
        if (currentType == STRING){
            value = passedValue;
            lineNumber = passedLineNumber;
        }
        if (currentType == COMMENT){
            value = passedValue;
            lineNumber = passedLineNumber;
        }
        if (currentType == UNDEFINED){
            value = passedValue;
            lineNumber = passedLineNumber;
        }
        if (currentType == ENDOF) {
            value = "";
            lineNumber = passedLineNumber;
        }
    }

    string toString(){

        tokenFinalString = "(" + tokenTypeToString(currentType) + ",\"" + value + "\"" + "," + "lineNumber FIXME" + ")" + "\n";
        cout << "(" << tokenTypeToString(currentType) << ",\"" << value << "\"" << "," << lineNumber << ")" << endl;
        return tokenFinalString;
    }

};


#endif //UNTITLED1_TOKEN_H
