
// #pragma once
// #include <iostream>
// #include <fstream>
// #include "Node.h"
// #include "dict.h"
// #include "search.h"

// using namespace std;

// class LL
// {
// private:
// public:
//     Node *head;
//     Node *tail;
//     int size;
//     LL()
//     {
//         this->head = new Node(-1, -1, -1, -1, -1);
//         this->tail = new Node(-1, -1, -1, -1, -1);
//         this->head->left = this->head->right = NULL;
//         this->tail->left = this->tail->right = NULL;
//         this->size = 0;
//     };

//     ~LL()
//     {
//         while (this->head != NULL)
//         {
//             Node *temp = this->head;
//             this->head = this->head->right;
//             delete temp;
//         }
//         this->size = 0;
//     };

//     void insert(int book_code, int page, int paragraph, int sentence_no, int offset)
//     {
//         Node *node = new Node(book_code, page, paragraph, sentence_no, offset);
//         node->left = node->right = NULL;
//         if (size == 0)
//             this->head = this->tail = node;
//         else
//         {
//             this->tail->right = node;
//             node->left = this->tail;
//             this->tail = node;
//         }
//         this->size++;
//     };
// };

// class MaxHeap
// {
// private:
//     void HeapifyUp(int index)
//     {
//         int parentindex = (index - 1) / 2;
//         if (parentindex < 0)
//             return;
//         if (Heap[parentindex].second >= Heap[index].second)
//             return;
//         swap(Heap[parentindex], Heap[index]);
//         HeapifyUp(parentindex);
//     }

//     void HeapifyDown(int index)
//     {
//         int leftindex = 2 * index + 1;
//         int rightindex = 2 * index + 2;
//         int minimumindex = index;

//         if (leftindex < size && Heap[leftindex].second > Heap[minimumindex].second)
//             minimumindex = leftindex;
//         if (rightindex < size && Heap[rightindex].second > Heap[minimumindex].second)
//             minimumindex = rightindex;

//         if (minimumindex == index)
//             return;

//         swap(Heap[minimumindex], Heap[index]);
//         HeapifyDown(minimumindex);
//     }

// public:
//     vector<pair<Node *, long double>> Heap;
//     int size;

//     MaxHeap()
//     {
//         size = 0;
//     }

//     ~MaxHeap()
//     {
//         Heap.clear();
//         size = 0;
//     }

//     void push(pair<Node *, long double> data)
//     {
//         Heap.push_back(data);
//         size++;
//         HeapifyUp(size - 1);
//     }

//     void pop()
//     {
//         if (size == 0)
//             return;
//         swap(Heap[0], Heap[size - 1]);
//         Heap.pop_back();
//         size--;
//         HeapifyDown(0);
//     }

//     Node *top()
//     {
//         if (size == 0)
//             return NULL;
//         return Heap[0].first;
//     }

//     bool empty()
//     {
//         return (size == 0);
//     }
// };

// class QNA_tool
// {
// private:
//     void query_llm(string filename, Node *root, int k, string API_KEY, string question);
//     // filename is the python file which will call ChatGPT API
//     // root is the head of the linked list of paragraphs
//     // k is the number of paragraphs (or the number of nodes in linked list)
//     // API_KEY is the API key for ChatGPT
//     // question is the question asked by the user

//     // You can add attributes/helper functions here

// public:
//     QNA_tool();
//     ~QNA_tool();

//     void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);
//     // This function is similar to the functions in dict and search
//     // The corpus will be provided to you via this function
//     // It will be called for each sentence in the corpus

//     Node *get_top_k_para(string question, int k);
//     // This function takes in a question, preprocess it
//     // And returns a list of paragraphs which contain the question
//     // In each Node, you must set: book_code, page, paragraph (other parameters won't be checked)

    // std::string get_paragraph(int book_code, int page, int paragraph);
    // // Given the book_code, page number, and the paragraph number, returns the string paragraph.
    // // Searches through the corpus.

//     void query(string question, string filename);
//     // This function takes in a question and a filename.
//     // It should write the final answer to the specified filename.

//     Dict *TotalUniv;
//     Dict *TotalCorpus;
//     vector<pair<vector<int>, Dict *>> ParagraphWords;
// };
#pragma once
#include <iostream>
#include <fstream>
#include "search.h"
//#include "dict.h"
#include "Node.h"

using namespace std;

struct match{
    Node* matches;
    int frequency;
};

class new_node{
    public:
    new_node* next;
    int book_no;
    int page_no;
    int para_no;
    double word_count;
    int diff_words;

    new_node(int b_code, int pg, int para){
        book_no = b_code;
        page_no = pg;
        para_no = para;
        word_count = 1;
        diff_words = 0;
    }
};

class QNA_tool {

private:

    // You are free to change the implementation of this function
    void query_llm(string filename, Node* root, int k, string API_KEY);
    // You can add attributes/helper functions here

public:
    //Dict dict;
    SearchEngine search;
    
    size_t size;//number of elements in word_matches;
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    
    QNA_tool(); // Constructor
    ~QNA_tool(); // Destructor

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);
    // This function is similar to the functions in dict and search 
    // The corpus will be provided to you via this function
    // It will be called for each sentence in the corpus

    Node* get_top_k_para(string question, int k);
    // This function takes in a question, preprocess it
    // And returns a list of paragraphs which contain the question
    // In each Node, you must set: book_code, page, paragraph (other parameters won't be checked)

    std::string get_paragraph(int book_code, int page, int paragrpah);

    void query(string question, string filename);

    bool separator(char c);

    long long gen_freq(string wordFreq);

    bool in_para_score(vector<new_node*> vec, new_node* Word);

    void sortpara(vector<new_node*> vec, int k);

    // This function takes in a question and a filename.
    // It should write the final answer to the specified filename.

    /* -----------------------------------------*/
    /* Please do not touch the code above this line */

    // You can add attributes/helper functions here
};