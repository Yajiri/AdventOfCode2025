#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;

struct Node {
    string name;
    Node* parent;
    vector<Node*> children;

    Node(const string& name, Node* parent)
        : name(name), parent(parent) {}
};

bool existInParents(Node* current, const string& target) {
    while (current != nullptr) {
        if (current->name == target) {   //-> is used instead of . because it's a pointer.
            return true;
        }
        current = current-> parent;
    }
    return false;
}

void search(Node* current, unordered_map<string, vector<string>>& graph) {
        auto it = graph.find(current->name);
        if (it == graph.end()) {
            return;
        }

        const vector<string>& moves = it->second;
        for (const string& move : moves) {
            if(existInParents(current, move)) {
                continue;
            }
            Node* child = new Node(move, current);
            current->children.push_back(child);
            search(child, graph);
        }
}

void printTree(Node* node, int depth) {
    for (int i = 0; i < depth; i++) {
        cout <<" ";
    }
    cout << node->name << '\n';

    for (Node* child : node->children) {
        printTree(child, depth + 1);
    }
}

int countPaths(Node* node) {
    if (node->name == "out") {
        return 1;
    }
    int paths = 0;
    for (Node* child : node->children) {
        paths += countPaths(child);
    }
    return paths;
}

int main() {
    vector<string> grid;

    ifstream file("input.txt");
        if(!file) {
            cout << "This file can't be found";
            return 1;
        } 
        string line;
        while (getline(file, line)) {
            grid.push_back(line);
        }
    
    string startPoint = "you";
    Node* root = new Node(startPoint, nullptr);
    unordered_map<string, vector<string>> graph;

    for (const string& line :grid) {
        size_t colon = line.find(": ");

        if(colon == string::npos) {
            cerr << "Invalid Line: " << line << '\n';
            continue;
        }

        string from = line.substr(0, colon);
        string rest = line.substr(colon + 2); //+ 2 is just to avoid the : and the " ".

        vector<string> moves;

        istringstream iss(rest);
        string move;
        while (iss >> move) {
            moves.push_back(move);
        }

        graph[from] = moves;

        size_t start = 0;
        size_t end;

    }
    search(root, graph);
    printTree(root, 0);

    cout << "\nPaths to out: "
         << countPaths(root)
         << '\n';
    return 0;
}
