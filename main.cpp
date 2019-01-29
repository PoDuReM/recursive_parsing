#include <bits/stdc++.h>
#include "Parser.h"
#include "parserTests.h"

using namespace std;


void tests() {
    lexerTest();
    testVariable();
    testConjunction();
    testDisjunction();
    testNegation();
    testXor();
    testWithSpaces();
    test01();
    testWithVisualization();
}

void inccorrectTest() {
//    test("!!x & a | (b & c", true);
//    test("b)))", true);
//    test("x ^", true);
//    test("& x", true);
//    test("|a", true);
    test("d | (d) | (e & a ^ a | (c) ^ (!a) | c) | b) | (!e) ^ (!a ^ (c))", true);
}

int main() {
//    tests();
    inccorrectTest();
}