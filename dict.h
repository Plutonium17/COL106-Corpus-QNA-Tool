#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class AVLNode
{
private:
public:
    string id;
    long long weight;
    int height;
    AVLNode *parent = NULL;
    AVLNode *left = NULL;
    AVLNode *right = NULL;

    AVLNode()
    {
        id = "";
        weight = 1;
        height = 0;
    };

    AVLNode(string key)
    {
        id = key;
        weight = 1;
        height = 0;
    };

    ~AVLNode()
    {
        parent = NULL;
        left = NULL;
        right = NULL;
        id = "";
        weight = 0;
        height = -1;
    }

    int get_height()
    {
        if (this == NULL)
            return -1;
        return height;
    };

    long long get_weight()
    {
        if (this == NULL)
            return 0LL;
        return weight;
    };

    int balance_factor()
    {
        if (this == NULL)
            return 0;
        return (left->get_height() - right->get_height());
    };

    void update_height()
    {
        if (this == NULL)
            return;
        this->height = 1 + max(this->left->get_height(), this->right->get_height());
    }
};

class AVLTree
{
private:
public:
    int size;
    AVLNode *root;
    AVLTree()
    {
        size = 0;
        root = NULL;
    };

    void deleteTree(AVLNode *root)
    {
        if (root == NULL)
            return;
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    };

    ~AVLTree()
    {
        deleteTree(root);
        size = 0;
    };

    AVLNode *LeftLeftRotation(AVLNode *node)
    {
        AVLNode *node1 = node->right;
        AVLNode *node2 = node1->left;

        node1->left = node;
        node->right = node2;

        node1->parent = node->parent;
        node->parent = node1;

        if (node2 != NULL)
            node2->parent = node;

        node->update_height();
        node1->update_height();

        if (node == root)
            root = node1;

        return node1;
    };

    AVLNode *RightRightRotation(AVLNode *node)
    {
        AVLNode *node1 = node->left;
        AVLNode *node2 = node1->right;

        node1->right = node;
        node->left = node2;

        node1->parent = node->parent;
        node->parent = node1;

        if (node2 != NULL)
            node2->parent = node;

        node->update_height();
        node1->update_height();

        if (node == root)
            root = node1;

        return node1;
    };

    AVLNode *search(AVLNode *root, string key)
    {
        if (root == NULL)
            return NULL;
        else if (root->id == key)
            return root;
        else if (root->id < key)
            return search(root->right, key);
        else if (root->id > key)
            return search(root->left, key);
        return NULL;
    };

    AVLNode *insert(AVLNode *root, string key)
    {

        if (root == NULL)
        {
            root = new AVLNode(key);
            size++;
            return root;
        }
        else if (root->id < key)
        {
            root->right = insert(root->right, key);
            root->right->parent = root;
        }
        else if (root->id > key)
        {
            root->left = insert(root->left, key);
            root->left->parent = root;
        }
        else
        {
            root->weight++;
            return root;
        }

        root->update_height();
        int balance = root->balance_factor();

        if (balance > 1 && key < root->left->id)
            return RightRightRotation(root);
        else if (balance < -1 && key > root->right->id)
            return LeftLeftRotation(root);
        else if (balance > 1 && key > root->left->id)
        {
            root->left = LeftLeftRotation(root->left);
            return RightRightRotation(root);
        }
        else if (balance < -1 && key < root->right->id)
        {
            root->right = RightRightRotation(root->right);
            return LeftLeftRotation(root);
        }
        return root;
    };

    int get_size()
    {
        return size;
    };
};

class Dict
{
private:
public:
    AVLTree *Storage;

    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    long long get_word_count(string word);

    void dump_dictionary(string filename);
};