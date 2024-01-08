#include "search.h"

SearchEngine::SearchEngine()
{
    this->Storage = new SentenceList();
}

SearchEngine::~SearchEngine()
{
    delete this->Storage;
}

void ConvertToLowercase(string &sentence)
{
    for (char &c : sentence)
        if (c <= 'Z' && c >= 'A')
            c = c - ('A' - 'a');
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    ConvertToLowercase(sentence);
    this->Storage->insert(sentence, book_code, page, paragraph, sentence_no);
    return;
}

Node *SearchEngine::search(string pattern, int &n_matches)
{
    ConvertToLowercase(pattern);
    BoyerMoore *SearchMachine = new BoyerMoore(pattern);

    SentenceNode *head = this->Storage->head;
    LinkedList *Occurences = new LinkedList();
    while (head != NULL)
    {
        Occurences = SearchMachine->search(head, Occurences);
        head = head->next;
    }

    n_matches = Occurences->size;
    return Occurences->head;
}
