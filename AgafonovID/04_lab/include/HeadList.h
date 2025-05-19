#pragma once

#include "List.h"

template<typename T>
class HeadList : public List<T> {
protected:
    TNode<T>* pHead;
public:
    HeadList();
    HeadList(const HeadList<T>& hlist);
    virtual ~HeadList();

    const HeadList& operator=(const HeadList<T>& list);
    void pushFront(TNode<T>* pNode);
    void removefirst();
    virtual void clear();
};

template <typename T>
HeadList<T>::HeadList() : List<T>(){
    pHead = new TNode<T>();
    pHead->pNext = pStop;  
}

template <typename T>
HeadList<T>::HeadList(const HeadList<T>& hlist) : List<T>(hlist) {
    pHead = new TNode<T>();
    pHead->pNext = pFirst;
}

template <typename T>
HeadList<T>::~HeadList() {
    delete pHead;  
}

template <typename T>
const HeadList<T>& HeadList<T>::operator=(const HeadList<T>& list) {
    List<T>::operator=(list);
    pHead->pNext = pFirst;
    return *this;
}

template <typename T>
void HeadList<T>::pushFront(TNode<T>* pNode) {
    List<T>::pushFront(pNode);
    pHead->pNext = pFirst;
}

template <typename T>
void HeadList<T>::removefirst() {
    List<T>::removeFirst();
    pHead->pNext = pFirst;
}

template<typename T>
void HeadList<T>::clear() {
    List<T>::clear();
    pHead->pNext = pStop;
}