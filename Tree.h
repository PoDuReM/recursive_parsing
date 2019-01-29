#pragma once

#include <utility>
#include <iostream>
#include <vector>

using namespace std;

class Tree {

private:

public:

    string node;
    vector<Tree *> children;

public:

    explicit Tree(string node) {
        this->node = std::move(node);
    }

    explicit Tree(char ch) {
        node.push_back(ch);
    }

    ~Tree() {
        for (auto &i : children) {
            delete i;
        }
    }

    string toString() {
        if (isTerm()) {
            return node;
        }
        string res;
        for (Tree *child : children) {
            res.append(child->toString());
        }
        return res;

    }

    bool isTerm() {
        return node == "^" || node == "&" || node == "|" || node == "!" || node == "(" || node == ")" ||
               (bool) islower(node[0]) || node == "0" || node == "1";
    }

};