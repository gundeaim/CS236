#ifndef UNTITLED1_PARSER_H
#define UNTITLED1_PARSER_H
#include <iostream>
#include <vector>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <iterator>
#include <set>
#include "Lexer.h"

using namespace std;

class Parser{
public:
    TokenType currentTokenType = SCHEMES;
    vector<Token*> inputVector;
    int currentIndex = 0;
    string exceptionMessage;
    int numOfSchemes = 0;
    int numOfQueries = 0;
    int numOfRules = 0;
    int numOfFacts = 0;
    bool alreadyPrinted = false;
    stringstream successString;
    string tempString = "";
    set <string> domains;


    void setTokenVector(vector<Token*> tokenVector){
        for (unsigned int i = 0; i < tokenVector.size(); i++){
            inputVector.push_back(tokenVector[i]);
        }
    }

    void makeSuccessString(){
        successString << tempString << endl;
        tempString = "";
    }

    void makeTempString(){
        if (inputVector[currentIndex]->currentType != COLON_DASH) {
            tempString = tempString + inputVector[currentIndex]->getTokenValue();
        }
        else {
            tempString = tempString + " " + inputVector[currentIndex]->getTokenValue() + " ";
        }
    }

    void moveToNextToken(){
        if (alreadyPrinted == false && currentTokenType != COLON){
            makeTempString();
        }
        alreadyPrinted = false;
        currentIndex++;
        currentTokenType = inputVector[currentIndex]->getTokenType();
    }

    void moveToLastToken(){
        alreadyPrinted = true;
        currentIndex--;
        currentTokenType = inputVector[currentIndex]->getTokenType();
    }

    void throwException(){
        stringstream os;
        os << "Failure!" << endl;
        os << "\t(" << inputVector[currentIndex]->getTokenTypeAsString() << ",\"" + inputVector[currentIndex]->getTokenValue() << "\"," << inputVector[currentIndex]->getTokenLine() << ")";
        exceptionMessage = os.str();
        throw exceptionMessage;
    }

    void parseIDList(){
        moveToNextToken();
        if (currentTokenType == COMMA){
            moveToNextToken();
            if (currentTokenType == ID){
                parseIDList();
            }
            else{
                throwException();
            }
        }
        else {
            if (currentTokenType == RIGHT_PAREN){
                moveToLastToken();
            } //should return to function that called it once done
            else{
                throwException();
            }
        }
    }

    void parseScheme(){
        numOfSchemes++;
        tempString = tempString + "\n" + "\t";
        alreadyPrinted = true;
        moveToNextToken();
        if (currentTokenType == ID){
            moveToNextToken();
            if (currentTokenType == LEFT_PAREN){
                moveToNextToken();
                if (currentTokenType == ID){
                    moveToNextToken();
                    if (currentTokenType == COMMA) {
                        moveToLastToken();
                        parseIDList();
                        moveToNextToken();
                    }
                    if (currentTokenType == RIGHT_PAREN){}//once done should return to function that called it
                    else{
                        throwException();
                    }
                }
                else{
                    throwException();
                }
            }
        }
        else {
            throwException();
        }
    }

    void parseSchemeList(){
        moveToNextToken();
        if (currentTokenType == ID){
            moveToLastToken();
            parseScheme();
            parseSchemeList();
        }
        else if (currentTokenType == FACTS){
            moveToLastToken();
        }
        else {
            throwException();
        }
    }

    void parseStringList(){
        moveToNextToken();
        if (currentTokenType == COMMA){
            moveToNextToken();
            if (currentTokenType == STRING){
                domains.insert(inputVector[currentIndex]->getTokenValue());
                parseStringList();
            }
            else{
                throwException();
            }
        }
        else {
            if (currentTokenType == RIGHT_PAREN){
                moveToLastToken();
            } //should return to function that called it once done
            else{
                throwException();
            }
        }
    }

    void parseFact(){
        numOfFacts++;
        tempString = tempString + "\n" + "\t";
        moveToNextToken();
        if (currentTokenType == ID){
            moveToNextToken();
            if (currentTokenType == LEFT_PAREN){
                moveToNextToken();
                if (currentTokenType == STRING){
                    domains.insert(inputVector[currentIndex]->getTokenValue());
                    parseStringList();
                    moveToNextToken();
                    if (currentTokenType == RIGHT_PAREN){
                        moveToNextToken();
                        if (currentTokenType == PERIOD){}
                        else {
                            throwException();
                        }
                    }//once done should return to function that called it
                }
            }
        }
    }

    void parseFactList(){
        moveToNextToken();
        if (currentTokenType == ID){
            moveToLastToken();
            parseFact();
            parseFactList();
        }
        else if (currentTokenType == RULES){
            moveToLastToken();
        }
        else {
            throwException();
        }
    }

    void parseOperator(){
        moveToNextToken();
        if (currentTokenType == ADD || currentTokenType == MULTIPLY){}
    }

    void parseParameter2(){
        moveToNextToken();
        if (currentTokenType == STRING || currentTokenType == ID){}
        else if (currentTokenType == LEFT_PAREN){
            moveToLastToken();
            parseExpression();
        }
        else{
            moveToLastToken();
            throwException();
        }
    }

    void parseExpression(){
        moveToNextToken();
        if (currentTokenType == LEFT_PAREN) {
            moveToNextToken();
            if (currentTokenType == STRING || currentTokenType == ID || currentTokenType == LEFT_PAREN) {
                moveToLastToken();
                parseParameter2();
                parseOperator();
                parseParameter2();
                moveToNextToken();
                if (currentTokenType == RIGHT_PAREN) {}
            }
            else {
                throwException();
            }
        }
    }


    void parseParameter(){
        moveToNextToken();
        if (currentTokenType == STRING || currentTokenType == ID){}
        else if (currentTokenType == LEFT_PAREN){
            moveToLastToken();
            parseExpression();
        }
        else{
            throwException();
        }
    }

    void parseParameterList(){
        moveToNextToken();
        if (currentTokenType == COMMA){
            moveToNextToken();
            if (currentTokenType == STRING || currentTokenType == ID || currentTokenType == LEFT_PAREN){
                moveToLastToken();
                parseParameter();
                parseParameterList();
            }
        }
        else if (currentTokenType == RIGHT_PAREN){
            moveToLastToken();
        }
    }

    void parsePredicate(){
        moveToNextToken();
        if (currentTokenType == ID){
            moveToNextToken();
            if (currentTokenType == LEFT_PAREN){
                moveToNextToken();
                if (currentTokenType == STRING || currentTokenType == ID || currentTokenType == LEFT_PAREN){
                    moveToLastToken();
                    parseParameter();
                    parseParameterList();
                    moveToNextToken();
                    if (currentTokenType == RIGHT_PAREN){}
                }
            }
        }
    }

    void parsePredicateList(){
        moveToNextToken();
        if (currentTokenType == COMMA){
            moveToNextToken();
            if (currentTokenType == STRING || currentTokenType == ID || currentTokenType == LEFT_PAREN){
                moveToLastToken();
                parsePredicate();
                parsePredicateList();
            }
        }
        else if (currentTokenType == PERIOD){
            moveToLastToken();
        }
    }

    void parseRule(){
        numOfRules++;
        moveToNextToken();
        if (currentTokenType == ID){
            moveToLastToken();
            parseScheme(); //same production as headPredicate
            moveToNextToken();
            if (currentTokenType == COLON_DASH){
                moveToNextToken();
                if (currentTokenType == ID){
                    moveToLastToken();
                    parsePredicate();
                    parsePredicateList();
                    moveToNextToken();
                    if (currentTokenType == PERIOD){}
                    else {
                        moveToLastToken();
                        throwException();
                    }
                }
            }
        }
    }

    void parseRuleList(){
        moveToNextToken();
        if (currentTokenType == ID){
            moveToLastToken();
            parseRule();
            parseRuleList();
        }
        else if (currentTokenType == QUERIES){
            moveToLastToken();
        }
        else {
            throwException();
        }
    }

    void parseQuery(){
        numOfQueries++;
        tempString = tempString + "\n" + "\t";
        moveToNextToken();
        if (currentTokenType == ID){
            moveToLastToken();
            parsePredicate();
            moveToNextToken();
            if (currentTokenType == Q_MARK){

            }
            else {
                throwException();
            }
        }
        else {
            moveToLastToken();
            throwException();
        }
    }

    void parseQueryList(){
        moveToNextToken();
        if (currentTokenType == ID){
            moveToLastToken();
            parseQuery();
            parseQueryList();
        }
        else if (currentTokenType == ENDOF){
            moveToLastToken();
        }
        else {
            throwException();
        }
    }

    void MakeDomainString(){
        set<string> :: iterator itr;
        unsigned int timesRan = 0;
        for (itr = domains.begin(); itr != domains.end(); itr++){
            timesRan++;
            if (timesRan != domains.size()) {
                successString << "\t" << *itr << endl;
            }
            else {
                successString << "\t" << *itr;
            }
        }
    }

    void datalogProgram(){
        //currentTokenType = inputVector[currentIndex]->currentType;
        if (currentTokenType == SCHEMES){
            alreadyPrinted = true;
            moveToNextToken();
            if (currentTokenType == COLON){
                parseScheme();
                parseSchemeList();
                successString << "Schemes(" << numOfSchemes << "):";
                makeSuccessString();
                moveToNextToken();
                if (currentTokenType == FACTS){
                    alreadyPrinted = true;
                    moveToNextToken();
                    if (currentTokenType == COLON){
                        parseFactList();
                        successString << "Facts(" << numOfFacts << "):";
                        makeSuccessString();
                        moveToNextToken();
                        if (currentTokenType == RULES){
                            alreadyPrinted = true;
                            moveToNextToken();
                            if (currentTokenType == COLON){
                                parseRuleList();
                                successString << "Rules(" << numOfRules << "):";
                                makeSuccessString();
                                moveToNextToken();
                                if (currentTokenType == QUERIES){
                                    alreadyPrinted = true;
                                    moveToNextToken();
                                    if (currentTokenType == COLON){
                                        parseQuery();
                                        parseQueryList();
                                        successString << "Queries(" << numOfQueries << "):";
                                        makeSuccessString();
                                        moveToNextToken();
                                        successString << "Domain(" << domains.size() << "):" << endl;
                                        MakeDomainString();
                                        if (currentTokenType == ENDOF){
                                            cout << "Success!" << endl;
                                            cout << successString.str();
                                        }
                                    }
                                    else{
                                        throwException();
                                    }
                                }
                                else{
                                    throwException();
                                }
                            }
                            else{
                                throwException();
                            }
                        }
                        else{
                            throwException();
                        }
                    }
                    else{
                        throwException();
                    }
                }
                else{
                    throwException();
                }
            }
            else{
                throwException();
            }
        }
        else{
            throwException();
        }
    }
};

#endif //UNTITLED1_PARSER_H
