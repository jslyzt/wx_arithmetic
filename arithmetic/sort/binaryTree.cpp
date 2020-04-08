#include "binaryTree.h"
#include <stack>

BinTree::BinTree()
    : root(nullptr)
{
}

BinTree::~BinTree()
{
    clear();
}

void BinTree::insert(int val)
{
    if (root == nullptr)
    {
        root = new Node{ val, 1, nullptr, nullptr };
    }
    else
    {
        insert(root, val);
    }
}

void BinTree::clear()
{
    if (root != nullptr)
    {
        clear(root);
        root = nullptr;
    }
}

void BinTree::clear(Node* node)
{
    if (node == nullptr)
    {
        return;
    }
    if (node->left != nullptr)
    {
        clear(node->left);
        node->left = nullptr;
    }
    if (node->right != nullptr)
    {
        clear(node->right);
        node->right = nullptr;
    }
    delete node;
}

bool BinTree::insert(Node* node, int val)
{
    if (node == nullptr)
    {
        return false;
    }
    if (val == node->val)
    {
        node->cnt++;
        return true;
    }
    else if (val > node->val)
    {
        if (node->right == nullptr)
        {
            node->right = new Node{ val, 1, nullptr, nullptr };
        }
        else
        {
            insert(node->right, val);
        }
    }
    else
    {
        if (node->left == nullptr)
        {
            node->left = new Node{ val, 1, nullptr, nullptr };
        }
        else
        {
            insert(node->left, val);
        }
    }
    return true;
}

std::vector<int> BinTree::order()
{
    auto vals = std::vector<int>();
    if (root != nullptr)
    {
        std::stack<Node*> stack;
        Node* node = root;

        while (node != nullptr || stack.empty() == false)
        {
            if (node != nullptr)
            {
                stack.push(node);
                node = node->left;
            }
            else
            {
                node = stack.top();
                stack.pop();
                for (int i = 0; i < node->cnt; i++) {
                    vals.push_back(node->val);
                }
                node = node->right;
            }
        }
    }
    return vals;
}