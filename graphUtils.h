#include "Parser.h"
#include <iostream>

string forFile;

string printNode(Tree *tree, int id) {
    string vertexName = "A" + to_string(id);
    forFile += vertexName + "[label=\"" + tree->node + "\"";
    if (tree->isTerm()) {
        forFile += ",color=red";
    }
    forFile += "]\n";

    return vertexName;
}

int printGraph(Tree *tree, int id) {
    string vertexName = printNode(tree, id);
    int nextId = id;
    for (Tree *child : tree->children) {
        nextId++;
        string nextVertexName = "A" + to_string(nextId);
        forFile += vertexName + "->" + nextVertexName + "\n";
        nextId = printGraph(child, nextId);
    }
    return nextId;
}

void visualizeTree(Tree *tree, string name) {
    forFile.clear();
    forFile += "digraph " + name + " {\n";
    printGraph(tree, 0);
    name += ".dot";
    FILE *f = freopen(name.c_str(), "w", stdout);
    forFile += "}\n";
    cout << forFile;
    fclose(f);
}

void makePng(string name) {
    name = "dot -O -Tpng " + name + ".dot";
    system(name.c_str());
}
