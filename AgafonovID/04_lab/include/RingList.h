#pragma once
#include "HeadList.h"

template<typename T>
class RingList : public HeadList<T> {
public:
    RingList();
    RingList(const RingList<T>& list);
    ~RingList();

    RingList<T>& operator=(const RingList<T>& list);
    void pushBack(T data); 
    void clear();         
    
};

template<typename T>
RingList<T>::RingList() {
    this->pHead = new TNode<T>;
    this->pHead->pNext = this->pHead;
    this->pFirst = this->pHead;
}

template<typename T>
RingList<T>::RingList(const RingList<T>& list) : RingList<T>() {
    TNode<T>* tmp = list.pHead->pNext;
    while (tmp != list.pHead) {
        pushBack(tmp->data);
        tmp = tmp->pNext;
    }
}

template<typename T>
RingList<T>::~RingList() {
    clear();
    delete this->pHead;
    this->pHead = nullptr;
}

template<typename T>
RingList<T>& RingList<T>::operator=(const RingList<T>& list) {
    if (this == &list)
        return *this;

    clear();
    TNode<T>* tmp = list.pHead->pNext;
    while (tmp != list.pHead) {
        pushBack(tmp->data);
        tmp = tmp->pNext;
    }
    return *this;
}


template<typename T>
void RingList<T>::clear() {
    TNode<T>* current = this->pHead->pNext;
    while (current != this->pHead) {
        TNode<T>* next = current->pNext;
        delete current;
        current = next;
    }
    this->pHead->pNext = this->pHead;  
    this->pFirst = this->pHead;
}

template<typename T>
void RingList<T>::pushBack(T data) {
    TNode<T>* newNode = new TNode<T>(data);

    if (this->pHead->pNext == this->pHead) { 
        this->pHead->pNext = newNode;
        newNode->pNext = this->pHead;
        this->pFirst = newNode;
    }
    else {
        TNode<T>* last = this->pHead->pNext;
        while (last->pNext != this->pHead) {
            last = last->pNext;
        }
        last->pNext = newNode;
        newNode->pNext = this->pHead;
    }
}
