#pragma once

#include <vector>

class BinTree {

public:
    struct Node {
        int val;
        int cnt;
        Node* left;
        Node* right;
    };

public:
    BinTree();
    ~BinTree();

    void insert(int val);
    void clear();

    std::vector<int> order();

private:
    void clear(Node* node);
    bool insert(Node* node, int val);

private:
    Node* root;
};