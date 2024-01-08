#include "dict.h"

Dict::Dict()
{
    Storage = new AVLTree();
}

Dict::~Dict()
{
    delete Storage;
}

void Lowercase(string &word)
{
    for (char &c : word)
        if (c <= 'Z' && c >= 'A')
            c = c - ('A' - 'a');
}

bool CheckPunctuation(char c)
{
    switch (c)
    {
    case ' ':
    case '.':
    case ',':
    case '-':
    case ':':
    case '!':
    case '\"':
    case '\'':
    case '(':
    case ')':
    case '?':
    case '[':
    case ']':
    case ';':
    case '@':
        return true;
    default:
        return false;
    }
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    string word = "";
    for (char c : sentence)
    {
        if (CheckPunctuation(c) == true && word != "")
        {
            Lowercase(word);
            Storage->root = Storage->insert(Storage->root, word);
            word = "";
        }
        else if (CheckPunctuation(c) == false)
            word = word + c;
    }
    if (word != "")
    {
        Lowercase(word);
        Storage->root = Storage->insert(Storage->root, word);
        word = "";
    }
    return;
}

long long Dict::get_word_count(string word)
{
    Lowercase(word);
    AVLNode *WordNode = Storage->search(Storage->root, word);
    return WordNode->get_weight();
}

void InOrder(AVLNode *root, vector<string> &InOrderStorage)
{
    if (root == NULL)
        return;
    InOrder(root->left, InOrderStorage);

    string element = string(root->id) + ", " + to_string(root->weight);
    InOrderStorage.emplace_back(element);

    InOrder(root->right, InOrderStorage);
}

void Dict::dump_dictionary(string filename)
{
    ofstream file;
    file.open(filename, ios::app);

    vector<string> InOrderStorage;
    InOrder(Storage->root, InOrderStorage);

    for (string element : InOrderStorage)
        file << element << endl;
    file.close();

    return;
}