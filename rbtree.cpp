#include "rbtree.h"

RBtree::Node::Node(const ValueType &value, Node *next_left, Node *next_right, Node *parent, Color color, KeyType key)
{
    this->value = value;
    this->next_left = next_left;
    this->next_right = next_right;
    this->parent = parent;
    this->color = color;
    this->key = key;
}

RBtree::Node::~Node()
{
    //ничего не удаляем
}



RBtree::RBtree()
    :_root()
{
//    std::cout << "creat" << std::endl;
//    _root = nullptr;
//    std::cout << "creat1" << std::endl;
}

RBtree::~RBtree()
{

}

RBtree::RBtree(const RBtree &copyTree)
{
//    this->_root = new Node(copyTree._root->value, nullptr, nullptr, nullptr, Color::black, copyTree._root->key);
//    if (!isEmpty(copyTree))
//    {

//    }
}

RBtree::RBtree(RBtree &&copyTree) noexcept
{

}

RBtree& RBtree::operator=(const RBtree &copyTree)
{

}

RBtree& RBtree::operator=(RBtree &&copyTree) noexcept
{

}

RBtree::Node* RBtree::uncle(Node *node)
{
    if (!grandpa(node))
        return nullptr;
    if (node->parent == grandpa(node)->next_right)
        return grandpa(node)->next_left;
    else
        return grandpa(node)->next_right;
}

RBtree::Node* RBtree::grandpa(Node *node)
{
    if (node == nullptr || node->parent == nullptr)
        return nullptr;
    return node->parent->parent;

}

void RBtree::addNode(KeyType key, ValueType value)
{
    if (this->isEmpty() == true)
    {
        //std::cout << "norm" << std::endl;
        _root = new Node(value, 0, 0, 0, Color::black, key);
        //std::cout << _root->value << " first " << std::endl;
        return;
    }

    Node *node = _root;
   // std::cout << "step 2 " << node->key << " " << key << std::endl;

    if (node->key > key)
    {
        //std::cout << "left br" << std::endl;
        if (node->next_left != nullptr)
        {
            //std::cout << "go to lft rec" << std::endl;
            addNode(key, value, node->next_left);

        }
        else
        {
            //std::cout << "step 2 " << key << std::endl;
            Node *newNode = new Node(value, nullptr, nullptr, node, Color::red, key);
            node->next_left = newNode;
            //std::cout << newNode->value << std::endl;
            balance(newNode);
        }
    }
    else
    {
        std::cout << "right br" << std::endl;
        if (node->next_right != nullptr)
        {
            addNode(key, value, node->next_right);
        }
        else
        {
            Node *newNode = new Node(value, nullptr, nullptr, node, Color::red, key);
            node->next_right = newNode;
            balance(newNode);
        }
    }
}

void RBtree::addNode(KeyType key, ValueType value, Node* node)
{
    //std::cout << node->key << " - " << key << std::endl;
    if (node->key > key)
    {
        std::cout << "left add" << std::endl;
        if (node->next_left != nullptr)
        {
            addNode(key, value, node->next_left);
        }
        else
        {
            Node *newNode = new Node(value, nullptr, nullptr, node, Color::red, key);
            node->next_left = newNode;
            std::cout << node->next_left->key << std::endl;

            balance(newNode);
        }
    }
    else
    {
        std::cout << "right add" << std::endl;
        if (node->next_right != nullptr)
        {
            addNode(key, value, node->next_right);
        }
        else
        {
            Node *newNode = new Node(value, nullptr, nullptr, node, Color::red, key);
            node->next_right = newNode;
            balance(newNode);
        }
    }
}

void RBtree::balance_1(Node *node)
{
    if (node->parent == nullptr)
    {
        node->color = Color::black;
    }
    else
    {
        balance_2(node);
    }
}

void RBtree::balance_2(Node *node)
{
    if (node->parent->color == Color::red)
        balance_3(node);
    else
        return;
}

void RBtree::balance_3(Node *node)
{
    Node *unc = uncle(node);
    if ((unc != nullptr)&&(unc->color == Color::red))
    {       
        node->parent->color = Color::black;
        uncle(node)->color = Color::black;
        grandpa(node)->color = Color::red;
        if (grandpa(node) == _root)
            grandpa(node)->color = Color::black;
    }
    else
        balance_4(node);
}

void RBtree::balance_4(Node *node)
{
    Node *gr = grandpa(node);
    if ((node == node->parent->next_right) && (node->parent == gr->next_left))
    {
        std::cout << "left rotate_4" << std::endl;
        leftRotate(node->parent);
        node = node->next_left;
    }
    else if (node == node->parent->next_left && node->parent == gr->next_right)
    {
        std::cout << "right rotate_4" << std::endl;
        rightRotate(node->parent);
        node = node->next_right;
    }
    balance_5(node);
}

void RBtree::balance_5(Node *node)
{
    Node *gr = grandpa(node);
    node->parent->color = Color::black;
    gr->color = Color::red;
    //std::cout << _root->key << " " <<_root->next_left << std::endl;
    if (node == node->parent->next_left && node->parent == gr->next_left)
    {
        std::cout << "right rotate_5" << std::endl;
        rightRotate(gr);
    }
    else
    {
        std::cout << "left rotate_5" << std::endl;
        leftRotate(gr);
    }
}

void RBtree::balance(Node *node)
{
    fixBalance(node);
    if (node->parent->color == Color::red)
        std::cout << "wtf" << std::endl;
}

void RBtree::leftRotate(Node *node)
{
    std::cout << "lrot" << std::endl;
    Node *right = node->next_right;
    if (node->parent == nullptr)
        _root = right;
    right->parent = node->parent; //теперь тут ссылка на деда правого потомка господи как сложно
    //std::cout << right->key << std::endl;
    if (grandpa(right))
    {
        if (grandpa(right)->next_left == node)
            grandpa(right)->next_left = right;
        else
            grandpa(right)->next_right = right;
    }

    node->next_right = right->next_left;
    if (right->next_left)
        right->next_left->parent = node;

    node->parent = right;
    right->next_left = node;
//    std::cout << node->parent->value << " " << node->value << " " << node->parent->next_right->key << std::endl;
//    std::cout << node->key << " " << node->next_left->key << " " << node->next_right->key << std::endl;
//    std::cout << _root->key << std::endl;

//    Node *pin = node->next_right;
//    node->next_right = pin->next_left;
//    if (pin->next_left != nullptr)
//        pin->next_left->parent = node;
//    pin->parent = node->parent;
//    if (node->parent == nullptr)
//        _root = pin;
//    else
//    {
//        if (node == (node->parent->next_left))
//            node->parent->next_left = pin;
//        else
//            node->parent->next_right = pin;
//    }
//    pin->next_left = node;
//    node->parent = pin;
}

void RBtree::rightRotate(Node *node)
{
    std::cout << "rrot" << std::endl;
   //std::cout << node->key << std::endl;

//    Node *left = node->next_left;
//    if (node->parent == nullptr) // открытие Даши
//        _root = left;
//    left->parent = grandpa(left);
//    if (grandpa(left))
//    {
//        if (grandpa(left)->next_right == node)
//            grandpa(left)->next_right = left;
//        else
//            grandpa(left)->next_left = left;
//    }

//    node->next_left = left->next_right;
//    if (left->next_right)
//        left->next_right->parent = node;

//    node->parent = left;
//    left->next_right = node;
    //std::cout << node->key << std::endl;

    Node *pin = node->next_left;
    node->next_left = pin->next_right;
    if (pin->next_right != nullptr)
        pin->next_right->parent = node;
    pin->parent = node->parent;
    if (node->parent == nullptr)
        _root = pin;
    else
    {
        if (node == (node->parent->next_right))
            node->parent->next_right = pin;
        else
            node->parent->next_left = pin;
    }
    pin->next_right = node;
    node->parent = pin;
}

void RBtree::fixBalance(Node *node)
{
    if (node == _root)
    {
        node->color = Color::black;
        return;
    }
    std::cout << "POL" << std::endl;
    while (node->parent->color == Color::red)
    {
        if (grandpa(node)->next_right == node->parent)
        {
            if (uncle(node) != nullptr)
            {
                if (uncle(node)->color == Color::red)
                {
                    node->parent->color = Color::black;
                    uncle(node)->color = Color::black;
                    grandpa(node)->color = Color::red;
                    node = grandpa(node);
                }
            }
            else
            {
                if (node == node->parent->next_left)
                {
                    //node = node->parent;
                    rightRotate(node->parent);
                }
                node->parent->color = Color::black;
                grandpa(node)->color = Color::red;
                leftRotate(grandpa(node));
            }
            _root->color = Color::black;
        }
        else
        {
            if (uncle(node) != nullptr)
            {
                if (uncle(node)->color == Color::red)
                {
                    node->parent->color = Color::black;
                    uncle(node)->color = Color::black;
                    grandpa(node)->color = Color::red;
                    node = grandpa(node);
                }
            }
            else
            {
                if (node == node->parent->next_right)
                {
                    //node = node->parent;
                    leftRotate(node->parent);
                }
                node->parent->color = Color::black;
                grandpa(node)->color = Color::red;
                rightRotate(grandpa(node));
            }
            _root->color = Color::black;
        }
    }

}

void RBtree::removeNode(KeyType key)
{

}

bool RBtree::isEmpty()
{
    if (_root != nullptr)
        return false;
    return true;
}

void RBtree::printTree()
{
    std::cout << _root->value << std::endl;
//    std::cout << _root->next_left->value << std::endl;
    std::cout << _root->next_right->next_right->next_right->value << std::endl;
//    if (_root->next_right->next_right->color == Color::black)
//        std::cout << "black" << std::endl;
}


