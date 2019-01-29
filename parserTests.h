#pragma once

#include "Parser.h"
#include "graphUtils.h"

void testWithVisualization() {
    cout << "visualization test: ";
    Parser *parser = new Parser();
    Tree *tree;
    try {
        tree = parser->parse("!(!0|b&(c|d))^e|!f^0");
        visualizeTree(tree, "example");
        makePng("example");
    } catch (exception e) {
        cerr << e.what();
        return;
    }
    cerr << "OK" << endl;

}

void lexerTest() {
    cout << "lexer test: ";
    string s = "|^&!()";
    for (char c = 'a'; c <= 'z'; c++) {
        s.push_back(c);
    }
    LexicalAnalyzer *la = new LexicalAnalyzer(s);
    while (la->getCurToken() != END) {
        la->nextToken();
    }
    cout << "OK" << endl;
}

string deleteWhitespace(string str) {
    string new_str;
    for (char i : str) {
        if (!isspace(i) && i != '\t' && i != '\n' && i != '\r') {
            new_str.push_back(i);
        }
    }
    return new_str;
}

int idTest = 1;

void test(const string &expression, bool fail) {
    cout << "test #" << idTest << " ";
    idTest++;
    string result;
    Parser *parser = new Parser();
    try {
        result = parser->parse(expression)->toString();
    } catch (...) {
        if (fail)
            cout << "OK" << endl;
        else
            cerr << "fail " << endl;
        delete parser;
        return;
    }
    if (!fail && deleteWhitespace(expression) == result) {
        cout << "OK" << endl;
    } else {
        cout << "fail at expression: " << expression <<" " << result << endl;
    }
    delete parser;
}

void testVariable() {
    test("a", false);
    test("d", false);
    test("(((x)))", false);
}

void testNegation() {
    test("!a", false);
    test("!!!!a", false);
    test("!((!!(!a)))", false);
}

void testConjunction() {
    test("a&a", false);
    test("a&b&c&d", false);
    test("(a&b)&(c&(d&e))", false);
}

void testXor() {
    test("a^a", false);
    test("a^b^c^d", false);
    test("a^b&c^d&e", false);
    test("a^b&(c^d)&e", false);
}

void testDisjunction() {
    test("a|a", false);
    test("a|b|c|d", false);
    test("a|b&c|d&e", false);
    test("a|b&(c|d)^e|f^a", false);
}

void test01() {
    test("1|b&(0|d)^1|0^a", false);
    test("(a&b)&(c&(d&1))", false);
    test("!!!0", false);
    test("(0^1)", false);
}


void testWithSpaces() {
    test("a | b", false);
    test("    a", false);
    test("b   ", false);
    test("   a   ^  ! b   ", false);
}

void testIncorrectInput() {
//    test("a || b & c", true);
//    test("!!x & a | (b & c", true);
//    test("b)))", true);
//    test("!!x & a | b)))", true);
//    test("!!x & () | b", true);
//    test("x !& a", true);
//    test("x ! a", true);
//    test("x () c", true);
//    test("x &", true);
//    test("x |", true);
//    test("x ^", true);
//    test("& x", true);
//    test("|a", true);
//    test("d | (d) | (e & a ^ a | (c) ^ (!a) | c) | b) | (!e) ^ (!a ^ (c))", true);
}
