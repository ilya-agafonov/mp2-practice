#pragma once
#include "HeadList.h"

template<typename T>
class RingList : public HeadList<T> {
public:
    RingList();
    RingList(const RingList<T>& list);
 
    void pushFront(TNode<T>* pNode);
    void pushBack(TNode<T>* pNode);
    void clear();
    const RingList<T>& operator=(const RingList<T>& list);
    // TODO: ???
};

template<typename T>
RingList<T>::RingList() : HeadList<T>() {
    this->pLast = this->pHead;
    this->pHead->pNext = this->pLast;
    this->pStop = this->pHead;
}

template<typename T>
RingList<T>::RingList(const RingList<T>& list) : HeadList<T>() {
    TNode<T>* tmp = list.pHead->pNext;
    while (tmp != list.pHead) {
        pushBack(tmp->data);
        tmp = tmp->pNext;
    }
}

template<typename T>
const RingList<T>& RingList<T>::operator=(const RingList<T>& list) {
    if (this == &list)
        return *this;
    clear();
    TNode<T>* tmp = list.pHead->pNext;
    while (tmp != list.pHead) {
        pushBack(tmp->data); //err
        tmp = tmp->pNext;
    }
    HeadList<T>::operator=(list);
    this->pStop = this->pHead;
    this->pLast->pNext = this->pHead;
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
void RingList<T>::pushFront(TNode<T>* pNode)
{
    HeadList<T>::pushFront(pNode);
    this->pLast->pNext = this->pHead;
}

template<typename T>
void RingList<T>::pushBack(TNode<T>* pNode) {
    HeadList<T>::pushBack(newNode);
    this->pLast->pNext = this->pHead;
}

