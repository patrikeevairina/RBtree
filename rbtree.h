#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>

using ValueType = int;
using KeyType = int;

enum class Color
{
    black,
    red
};


class RBtree
{
protected:
    struct Node
    {
        Node(Node* next_left = nullptr, Node* next_right = nullptr, Node* parent = nullptr);
        Node(const ValueType &value, Node *next_left = nullptr, Node *next_right = nullptr, Node *parent = nullptr, Color color = Color::black, KeyType key = 0);
        ~Node();

        ValueType value;
        Node *next_left;
        Node *next_right;
        Node *parent;
        Color color;
        KeyType key;
    };
private:
    Node *_root;
public:
    RBtree();
    ~RBtree();
    RBtree(const RBtree &copyTree);
    RBtree(RBtree &&copyTree) noexcept;

    RBtree& operator=(const RBtree &copyTree);
    RBtree& operator=(RBtree &&copyTree) noexcept;

    void addNode(KeyType key, ValueType value, Node* node);
    void addNode(KeyType key, ValueType value);
    void balance(Node *node);
    void balance_1(Node *node);
    void balance_2(Node *node);
    void balance_3(Node *node);
    void balance_4(Node *node);
    void balance_5(Node *node);

    void fixBalance(Node *node);//попытка написать альтернативу 5-ти балансам

    void leftRotate(Node *node);
    void rightRotate(Node *node);

    void removeNode(KeyType key);

    Node *uncle(Node *node);
    Node *grandpa(Node *node);

    Node* findByKey(KeyType key);
    Node* findMaxKey();
    Node* findMinKey();
    size_t sizeTree();
    bool isEmpty();

    void printTree();

};

#endif // RBTREE_H
