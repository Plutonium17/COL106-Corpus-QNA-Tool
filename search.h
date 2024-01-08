
#include <string>
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

class LinkedList
{
private:
public:
    Node *head;
    Node *tail;
    int size;
    LinkedList()
    {
        this->head = NULL;
        this->tail = NULL;
        this->size = 0;
    };

    ~LinkedList()
    {
        while (this->head != NULL)
        {
            Node *temp = this->head;
            this->head = this->head->right;
            delete temp;
        }
        this->size = 0;
    };

    void insert(int book_code, int page, int paragraph, int sentence_no, int offset)
    {
        Node *node = new Node(book_code, page, paragraph, sentence_no, offset);
        if (this->head == NULL)
        {
            this->head = node;
            this->tail = node;
        }
        else
        {
            this->tail->right = node;
            node->left = this->tail;
            this->tail = node;
        }
        this->size++;
    };
};

class SentenceNode
{
private:
public:
    string sentence;
    int book_code;
    int page;
    int paragraph;
    int sentence_no;
    SentenceNode *prev;
    SentenceNode *next;
    SentenceNode()
    {
        this->sentence = "";
        this->book_code = -1;
        this->page = -1;
        this->paragraph = -1;
        this->sentence_no = 0;
        this->prev = NULL;
        this->next = NULL;
    };

    SentenceNode(string sentence, int book_code, int page, int paragraph, int sentence_no)
    {
        this->sentence = sentence;
        this->book_code = book_code;
        this->page = page;
        this->paragraph = paragraph;
        this->sentence_no = sentence_no;
        this->prev = NULL;
        this->next = NULL;
    };

    ~SentenceNode()
    {
        this->sentence = "";
        this->book_code = -1;
        this->page = -1;
        this->paragraph = -1;
        this->sentence_no = 0;
        this->prev = NULL;
        this->next = NULL;
    };
};

class SentenceList
{
private:
public:
    int numberOFsentences;
    SentenceNode *head;
    SentenceNode *tail;
    SentenceList()
    {
        this->numberOFsentences = 0;
        this->head = NULL;
        this->tail = NULL;
    };

    ~SentenceList()
    {
        while (this->head != NULL)
        {
            SentenceNode *temp = this->head;
            this->head = this->head->next;
            delete temp;
        }
        this->numberOFsentences = 0;
    };

    void insert(string sentence, int book_code, int page, int paragraph, int sentence_no)
    {
        SentenceNode *node = new SentenceNode(sentence, book_code, page, paragraph, sentence_no);
        if (this->head == NULL)
        {
            this->head = node;
            this->tail = node;
        }
        else
        {
            node->prev = this->tail;
            this->tail->next = node;
            this->tail = node;
        }
        this->numberOFsentences++;
    };
};

class BoyerMoore
{
private:
    string pattern;
    vector<int> BadCharacter;
    vector<int> GoodSuffix;

public:
    BoyerMoore(string pattern)
    {
        this->pattern = pattern;
        DoBadCharacter();
        DoGoodSuffix();
    };

    ~BoyerMoore()
    {
        this->pattern = "";
        this->BadCharacter.clear();
        this->GoodSuffix.clear();
    };

    void DoBadCharacter()
    {
        for (int i = 0; i < 256; i++)
            this->BadCharacter.emplace_back(-1);

        int pattern_size = this->pattern.size();
        for (int i = 0; i < pattern_size; i++)
            this->BadCharacter[pattern[i]] = i;
    };

    void DoGoodSuffix()
    {
        int pattern_size = this->pattern.size();
        for (int i = 0; i < pattern_size + 1; i++)
            this->GoodSuffix.emplace_back(pattern_size);

        int counter = pattern_size;
        for (int i = pattern_size - 1; i >= 0; i--)
        {
            if (counter < 0 && this->pattern[i] == this->pattern[counter])
                counter = i;
            this->GoodSuffix[i] = counter;
            counter--;
        }

        counter = GoodSuffix[0];
        for (int i = 0; i < pattern_size; i++)
        {
            if (this->GoodSuffix[i] == pattern_size)
                this->GoodSuffix[i] = counter;
            if (i == counter)
                counter = this->GoodSuffix[counter];
        }
    };

    LinkedList *search(SentenceNode *node, LinkedList *Occurences)
    {
        string sentence = node->sentence;
        int pattern_size = this->pattern.size();
        int sentence_size = sentence.size();
        int position = 0;

        while (position <= sentence_size - pattern_size)
        {
            int index = pattern_size - 1;
            while (index >= 0 && this->pattern[index] == sentence[position + index])
                index--;

            if (index < 0)
            {
                int offset = position;
                Occurences->insert(node->book_code, node->page, node->paragraph, node->sentence_no, offset);
                if (position < sentence_size - pattern_size)
                    position += (pattern_size - this->BadCharacter[sentence[position + pattern_size]]);
                else
                    position++;
            }
            else
                position += max(1, index - this->BadCharacter[sentence[position + index]]);
        }
        return Occurences;
    };
};

class SearchEngine
{
private:
    SentenceList *Storage;

public:
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node *search(string pattern, int &n_matches);
};