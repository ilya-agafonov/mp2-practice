#pragma once
#include "HeadList.h"

template<typename T>
class RingList : public HeadList<T> {
public:
    RingList();
    RingList(const RingList<T>& other);
    ~RingList();

    void pushBack(T data); 
    void clear();         
    void print() const;
};

template<typename T>
RingList<T>::RingList() {
    this->pHead = new TNode<T>;
    this->pHead->pNext = this->pHead;
    this->pFirst = this->pHead;
}

template<typename T>
RingList<T>::RingList(const RingList<T>& other) : RingList<T>() {
    TNode<T>* tmp = other.pHead->pNext;
    while (tmp != other.pHead) {
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
    TNode<T>* last = this->pHead;

    while (last->pNext != this->pHead) {
        last = last->pNext;
    }

    last->pNext = newNode;
    newNode->pNext = this->pHead;

    if (this->pFirst == this->pHead) {
        this->pFirst = newNode;
    }
}

template<typename T>
void RingList<T>::print() const {
    TNode<T>* tmp = pHead->pNext;
    while (tmp != pHead) {
        cout << tmp->data << " ";
        tmp = tmp->pNext;
    }
    cout << endl;
}