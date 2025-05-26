#pragma once

#include <iostream>
#include <string>

template <typename T>
struct TNode {
    T data;
    TNode* pNext;
    TNode() : pNext(nullptr) {};
    TNode(const T& data_) : data(data_), pNext(nullptr) {};
    TNode(const TNode& nd) :data(nd.data), pNext(nd.pNext) {}
    TNode(const TNode* nd) :data(nd.data), pNext(nd.pNext) {}
};

template<typename T>
class List {
protected:
    TNode<T>* pFirst;
    TNode<T>* curr;
    TNode<T>* prev;
    TNode<T>* pStop;
    TNode<T>* pLast;
public:
    List();
    List(const List<T>&);
    virtual ~List();

    const List& operator=(const List<T>& list);
    bool operator==(const List<T>& list) const;

    TNode<T>* getFirst() const;
    TNode<T>* search(T key); // TODO: pPrev and pCurr
    virtual void pushFront(TNode<T>* pNode);
    virtual void pushBack(TNode<T>* pNode);
    void insertAfter(TNode<T>* pNode, int key);
    void insertBefore(TNode<T>* pNode, int key);
    virtual void remove(T key);

    void reset();
    void copy(const List<T>& list);
    void clear();
    virtual void removefirst();
    bool IsEmpty() const;
    bool IsEnd();
    int Size() const;
};

template <typename T>
List<T>::List() {
    pFirst = nullptr;
    curr = nullptr;
    prev = nullptr;
    pStop = nullptr;
    pLast = nullptr;
}


template <typename T>
List<T>::List(const List<T>& list) {
    if (list.pFirst == nullptr) { // TODO: copy()
        pFirst = nullptr;
        return;
    }
    copy(list);
    pStop = nullptr;
}

template <typename T>
List<T>::~List() {
    reset();
    clear();
    pFirst = nullptr;
}

template <typename T>
const List<T>& List<T>::operator=(const List<T>& list) {
    List<T> listcopy(list);
    if (this == &list) {
        return *this;
    }
    if (pFirst != nullptr) { // TODO: clear()
        clear();
    }
    if (list.pFirst == nullptr) { // TODO: copy()
        pFirst = nullptr;
        return *this;
    }
    copy(listcopy);
    return *this;
}
template <typename T>
bool List<T>::operator==(const List<T>& list) const {
    TNode<T>* curr1 = pFirst;
    TNode<T>* curr2 = list.pFirst;
    while (curr1 != pStop && curr2 != list.pStop) {
        if (curr1->data != curr2->data) {
            return false;
        }
        curr1 = curr1->pNext;
        curr2 = curr2->pNext;
    }
    return (curr1 == pStop && curr2 == list.pStop);
}

template<typename T>
inline TNode<T>* List<T>::getFirst() const
{
    return pFirst;
}

template<typename T>
TNode<T>* List<T>::search(T key)
{
    if (IsEmpty()) {
        return nullptr;
    }
    reset();
    while (curr != pStop) {
        if (curr->data == key) {
            return curr;
        }
        prev = curr;
        curr = curr->pNext;
    }
    return nullptr;
}

template <typename T>
void List<T>::pushFront(TNode<T>* pNode) {
    if (pFirst == nullptr) {
        pFirst = pNode;
        pFirst->pNext = pStop;
        pLast = pFirst;
        return;
    }
    pNode->pNext = pFirst;
    pFirst = pNode;
}

template <typename T>
void List<T>::pushBack(TNode<T>* pNode) {
    if (pFirst == nullptr) {
        pushFront(pNode);
        return;
    }
    pLast->pNext = pNode;
    pLast = pNode;
    pLast->pNext = pStop;
}

template <typename T>
void List<T>::insertAfter(TNode<T>* pNode, int key) {
    curr = search(key);
    if (curr == nullptr) {
        throw std::exception("curr nullptr");
    }
    pNode->pNext = curr->pNext;
    curr->pNext = pNode;
}

template <typename T>
void List<T>::insertBefore(TNode<T>* pNode, int key) {
    reset();
    if (curr->data == key)
    {
        pushFront(pNode);
        return;
    }
    curr = search(key);
    
    if (curr == nullptr) {
        throw std::exception("Key not found");
    }

    pNode->pNext = curr;
    prev->pNext = pNode;
}

template <typename T>
void List<T>::remove(T key) {
    reset();
    if (search(key) == nullptr) {
        throw std::exception("key not found");
    }
    if (pFirst->data == key) { // TODO: removeFirst()
        removefirst();
        return;
    }
    curr = search(key);
    if (curr == pLast) {
        prev->pNext = curr->pNext;
        pLast = prev;
        return;
    }
    prev->pNext = curr->pNext;
    delete curr;
}

template <typename T>
void List<T>::reset() {
    curr = pFirst;
    prev = nullptr;
}

template<typename T>
void List<T>::copy(const List<T>& list){
    pFirst = new TNode<T>(list.pFirst->data);
    TNode<T>* curr = pFirst;
    TNode<T>* currList = list.pFirst->pNext;
    while (currList != nullptr) {
        curr->pNext = new TNode<T>(currList->data);
        curr = curr->pNext;
        currList = currList->pNext;
    }
}

template<typename T>
void List<T>::clear()
{
    reset();
    while (curr != pStop) {
        TNode<T>* tmp = curr->pNext;
        delete curr;
        curr = tmp;
    }
}

template <typename T>
bool List<T>::IsEmpty() const {
    return (pFirst == nullptr);
}

template<typename T>
bool List<T>::IsEnd()
{
    return curr == pStop;
}

template <typename T>
void List<T>::removefirst() {
    TNode<T>* tmp = pFirst;
    if (tmp == nullptr) {
        throw "list empty";
    }
    if (pFirst == pLast) {
        pFirst = pLast = nullptr;
    }
    else {
        pFirst = pFirst->pNext;
    }
    delete tmp;
}

template <typename T>
int List<T>::Size() const {
    TNode<T>* curr = pFirst;
    int sz = 0;
    while (curr != nullptr) {
        curr = curr->pNext;
        sz++;
    }
    return sz;
}