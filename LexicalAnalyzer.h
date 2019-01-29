#pragma once

#include <iostream>
#include <exception>

using namespace std;

enum Token {
    LPAREN, RPAREN, AND, OR, XOR, NOT, VAR, END
};

class LexicalAnalyzer {

private:
    string curString;
    Token curToken;
    int curChar{};
    int curPos;

public:
    explicit LexicalAnalyzer(string const &s) {
        curString = s;
        curPos = 0;
        nextToken();
    }

    void nextToken() {
        nextChar();
        while (isBlank(curChar)) {
            nextChar();
        }
        switch (curChar) {
            case '(' :
                curToken = LPAREN;
                break;
            case ')' :
                curToken = RPAREN;
                break;
            case '&':
                curToken = AND;
                break;
            case '|' :
                curToken = OR;
                break;
            case '^':
                curToken = XOR;
                break;
            case '!':
                curToken = NOT;
                break;
            case -1:
                curToken = END;
                break;
            default:
                if (curChar == '0' || curChar == '1' || islower(curChar)) {
                    curToken = VAR;
                } else {
                    cerr << "Illegal character : " << (char) curChar << " on " << curPos;
                    exit(1);
                }
        }
    }

private:


    void nextChar() {
        curPos++;
        try {
            if (curPos - 1 == curString.length())
                curChar = -1;
            else
                curChar = curString[curPos - 1];
        } catch (exception e) {
            cerr << e.what() << " at " << curPos;
            exit(1);
        }
    }

    bool isBlank(int c) {
        return c == ' ' || c == '\r' || c == '\n' || c == '\t';
    }

public:
    Token getCurToken() {
        return curToken;
    }

    int getCurPos() {
        return curPos;
    }

    char getCurChar() {
        return (char) curChar;
    }
};