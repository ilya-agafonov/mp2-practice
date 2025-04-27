#pragma once

#include "List.h"

template<typename T>
class HeadList : public List<T> {
protected:
    TNode<T>* pHead;
public:
    HeadList();
    HeadList(const HeadList<T>& hlist);
    ~HeadList();

    const HeadList& operator=(const HeadList<T>& list);

    void pushFront(TNode<T>* pNode);
    void pushBack(TNode<T>* pNode);
    void insertAfter(TNode<T>* pNode, int key);
    void insertBefore(TNode<T>* pNode, int key);
    void remove(int key);
    void removefirst();
    virtual void clear();
};

template <typename T>
HeadList<T>::HeadList() {
    pHead = new TNode<T>();  
    this->pFirst = nullptr;  
    pHead->pNext = this->pFirst;  
}

template <typename T>
HeadList<T>::HeadList(const HeadList<T>& hlist) {
    pHead = new TNode<T>();  
    this->pFirst = nullptr;  

    TNode<T>* curr = hlist.pHead->pNext; 
    TNode<T>* tail = pHead;

    while (curr != nullptr) {
        TNode<T>* newNode = new TNode<T>(curr->data);
        tail->pNext = newNode;
        tail = newNode;
        curr = curr->pNext;
    }

    this->pFirst = pHead->pNext;  
}

template <typename T>
HeadList<T>::~HeadList() {

    delete pHead;  
}

template <typename T>
const HeadList<T>& HeadList<T>::operator=(const HeadList<T>& list) {
    if (this == &list) {
        return *this;
    }

    while (this->pFirst != nullptr) {
        this->removefirst();
    }    
    TNode<T>* curr = list.pHead->pNext;  
    TNode<T>* tail = pHead;

    while (curr != nullptr) {
        TNode<T>* newNode = new TNode<T>(curr->data);
        tail->pNext = newNode;
        tail = newNode;
        curr = curr->pNext;
    }

    this->pFirst = pHead->pNext;  

    return *this;
}

template <typename T>
void HeadList<T>::pushFront(TNode<T>* pNode) {
    pNode->pNext = pHead->pNext;
    pHead->pNext = pNode;
    this->pFirst = pHead->pNext;  
}

template <typename T>
void HeadList<T>::pushBack(TNode<T>* pNode) {
    TNode<T>* curr = pHead;
    while (curr->pNext != nullptr) {
        curr = curr->pNext;
    }
    curr->pNext = pNode;
    this->pFirst = pHead->pNext;  
}

template <typename T>
void HeadList<T>::insertAfter(TNode<T>* pNode, int key) {
    TNode<T>* curr = pHead->pNext; 
    while ((curr != nullptr) && (curr->data != key)) {
        curr = curr->pNext;
    }
    if (curr == nullptr) {
        throw std::exception("Key not found");
    }
    pNode->pNext = curr->pNext;
    curr->pNext = pNode;
}

template <typename T>
void HeadList<T>::insertBefore(TNode<T>* pNode, int key) {
    TNode<T>* prev = pHead;  
    TNode<T>* curr = pHead->pNext;  

    while (curr != nullptr && curr->data != key) {
        prev = curr;
        curr = curr->pNext;
    }

    if (curr == nullptr) {
        throw std::exception("Key not found");
    }

    pNode->pNext = curr;
    prev->pNext = pNode;
    this->pFirst = pHead->pNext;  
}

template <typename T>
void HeadList<T>::remove(int key) {
    TNode<T>* prev = pHead;  
    TNode<T>* curr = pHead->pNext; 

    while (curr != nullptr && curr->data != key) {
        prev = curr;
        curr = curr->pNext;
    }

    if (curr == nullptr) {
        throw std::exception("Key not found");
    }

    prev->pNext = curr->pNext;
    if (curr == this->pFirst) {
        this->pFirst = pHead->pNext;  
    }
    delete curr;
}

template <typename T>
void HeadList<T>::removefirst() {
    if (pHead->pNext == nullptr) {
        throw "list empty";
    }
    TNode<T>* tmp = pHead->pNext;
    pHead->pNext = tmp->pNext;
    this->pFirst = pHead->pNext;  
    delete tmp;
}

template<typename T>
void HeadList<T>::clear() {
    TNode<T>* curr = pHead->pNext;
    while (curr) {
        TNode<T>* next = curr->pNext;
        delete curr;
        curr = next;
    }
    pHead->pNext = nullptr;
    this->pFirst = nullptr;
}