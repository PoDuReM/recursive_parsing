#pragma once

#include "LexicalAnalyzer.h"
#include "Tree.h"

class Parser {

private:
    LexicalAnalyzer *lex;

    int error() {
        cerr << "unexpected char : \'" << lex->getCurChar() << "\' at " << lex->getCurPos();
        exit(1);
    }

public:

    Tree *parse(const string &s) {
        lex = new LexicalAnalyzer(s);
        Tree *vertex = E();
        if (lex->getCurToken() != END) {
            cerr << "unexpected characters at index : " << lex->getCurPos();
        }
        return vertex;
    }

private:
    Tree *E() {
        Tree *vertex = new Tree("E");
        Token t = lex->getCurToken();
        if (t == NOT || t == VAR || t == LPAREN) {
            vertex->children.push_back(X());
            vertex->children.push_back(EPrime());
        } else {
            error();
        }
        return vertex;
    }

    Tree *X() {
        Tree *vertex = new Tree("X");
        Token t = lex->getCurToken();
        if (t == NOT || t == VAR || t == LPAREN) {
            vertex->children.push_back(C());
            vertex->children.push_back(XPrime());
        } else {
            error();
        }
        return vertex;
    }

    Tree *C() {
        Tree *vertex = new Tree("C");
        Token t = lex->getCurToken();
        if (t == NOT || t == VAR || t == LPAREN) {
            vertex->children.push_back(V());
            vertex->children.push_back(CPrime());
        } else {
            error();
        }
        return vertex;
    }

    Tree *V() {
        Tree *vertex = new Tree("V");
        switch (lex->getCurToken()) {
            case NOT:
                vertex->children.push_back(new Tree("!"));
                lex->nextToken();
                vertex->children.push_back(V());
                break;
            case LPAREN:
                vertex->children.push_back(new Tree("("));
                lex->nextToken();
                vertex->children.push_back(E());
                if (lex->getCurToken() != RPAREN) {
                    cerr << "expected : )" << endl;
                    error();
                }
                vertex->children.push_back(new Tree(")"));
                lex->nextToken();
                break;
            case VAR:
                vertex->children.push_back(new Tree(lex->getCurChar()));
                lex->nextToken();
                break;
            default:
                error();
        }
        return vertex;
    }

    Tree *EPrime() {
        Tree *vertex = new Tree("E'");
        Token t = lex->getCurToken();
        if (t == OR) {
            vertex->children.push_back(new Tree("|"));
            lex->nextToken();
            vertex->children.push_back(X());
            vertex->children.push_back(EPrime());
        } else if (t != RPAREN && t != END) {
            error();
        }

        return vertex;
    }

    Tree *XPrime() {
        Tree *vertex = new Tree("X'");
        Token t = lex->getCurToken();
        if (t == XOR) {
            vertex->children.push_back(new Tree("^"));
            lex->nextToken();
            vertex->children.push_back(C());
            vertex->children.push_back(XPrime());
        } else if (t != RPAREN && t != OR && t != END)
            error();
        return vertex;
    }

    Tree *CPrime() {
        Tree *vertex = new Tree("C'");
        Token t = lex->getCurToken();
        if (t == AND) {
            vertex->children.push_back(new Tree("&"));
            lex->nextToken();
            vertex->children.push_back(V());
            vertex->children.push_back(CPrime());
        } else if (t != RPAREN && t != OR && t != XOR && t != END)
            error();
        return vertex;
    }
};