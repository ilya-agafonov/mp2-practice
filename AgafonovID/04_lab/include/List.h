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
    List(const T& list);
    List(const List<T>&);
    ~List();

    const List& operator=(const List<T>& list);
    bool operator==(const List<T>& list) const;

    TNode<T>* getFirst() const;
    void pushFront(TNode<T>* pNode);
    void pushBack(TNode<T>* pNode);
    void insertAfter(TNode<T>* pNode, int key);
    void insertBefore(TNode<T>* pNode, int key);
    void remove(int key);
    T GetFirst() const { return pFirst->data; };
    T GetCurr() const { return pCurr->data; };
    T reset() const;
    void removefirst();
    bool IsEmpty() const;
    int Size();
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
List<T>::List(const T& list) {
    pFirst = new ListNode<T>(x);

}

template <typename T>
List<T>::List(const List<T>& list) {
    pFirst = nullptr;
    if (list.pFirst != nullptr) {
        TNode<T>* tmp = list.pFirst;
        while (tmp != nullptr) {
            pushBack(new TNode<T>(tmp->data));
            tmp = tmp->pNext;
        }
    }
}

template <typename T>
List<T>::~List() {
    while (pFirst != nullptr) {
        TNode<T>* tmp = pFirst;
        pFirst = pFirst->pNext;
        delete tmp;
    }
}

template <typename T>
const List<T>& List<T>::operator=(const List<T>& list) {
    if (this == &list) {
        return *this;
    }
    while (pFirst != nullptr) {
        TNode<T>* tmp = pFirst;
        pFirst = pFirst->pNext;
        delete tmp;
    }
    if (list.pFirst == nullptr) {
        pFirst = nullptr;
        return *this;
    }
    pFirst = new TNode<T>(list.pFirst->data);
    TNode<T>* curr = pFirst;
    TNode<T>* currList = list.pFirst->pNext;
    while (currList != nullptr) {
        curr->pNext = new TNode<T>(currList->data);
        curr = curr->pNext;
        currList = currList->pNext;
    }
    return *this;
}
template <typename T>
bool List<T>::operator==(const List<T>& list) const {
    TNode<T>* curr1 = pFirst;
    TNode<T>* curr2 = list.pFirst;
    while (curr1 != nullptr && curr2 != nullptr) {
        if (curr1->data != curr2->data) {
            return false;
        }
        curr1 = curr1->pNext;
        curr2 = curr2->pNext;
    }
    return (curr1 == nullptr && curr2 == nullptr);
}

template<typename T>
inline TNode<T>* List<T>::getFirst() const
{
    return pFirst;
}

template <typename T>
void List<T>::pushFront(TNode<T>* pNode) {
    if (pFirst == nullptr) {
        pFirst = pNode;
        return;
    }
    pNode->pNext = pFirst;
    pFirst = pNode;
}

template <typename T>
void List<T>::pushBack(TNode<T>* pNode) {
    if (pFirst == nullptr) {
        pFirst = pNode;
        return;
    }
    TNode<T>* curr = pFirst;
    while (curr->pNext != nullptr) {
        curr = curr->pNext;
    }
    curr->pNext = pNode;
}

template <typename T>
void List<T>::insertAfter(TNode<T>* pNode, int key) {
    TNode<T>* curr = pFirst;
    while ((curr != nullptr) && (curr->data != key)) {
        curr = curr->pNext;
    }
    if (curr == nullptr) {
        throw std::exception("curr nullptr");
    }
    pNode->pNext = curr->pNext;
    curr->pNext = pNode;
}

template <typename T>
void List<T>::insertBefore(TNode<T>* pNode, int key) {
    TNode<T>* prev = nullptr, * curr = pFirst;
    while (curr != nullptr && curr->data != key) {
        prev = curr;
        curr = curr->pNext;
    }
    if (curr == nullptr) {
        throw std::exception("Key not found");
    }
    if (prev == nullptr) {
        pNode->pNext = pFirst;
        pFirst = pNode;
        return;
    }
    pNode->pNext = curr;
    prev->pNext = pNode;
}

template <typename T>
void List<T>::remove(int key) {
    if (pFirst == nullptr) {
        throw std::exception("pFirst nullptr");
    }
    TNode<T>* prev = nullptr, * curr = pFirst;
    while (curr != nullptr && curr->data != key) {
        prev = curr;
        curr = curr->pNext;
    }
    if (curr == nullptr) {
        throw std::exception("Key not found");
    }
    if (prev == nullptr) {
        pFirst = pFirst->pNext;
        delete curr;
        return;
    }
    prev->pNext = curr->pNext;
    delete curr;
}

template <typename T>
T List<T>::reset() const {
    if (pFirst == nullptr) {
        throw "Error";
    }
    return pFirst->data;
}

template <typename T>
bool List<T>::IsEmpty() const {
    return (pFirst == nullptr);
}

template <typename T>
void List<T>::removefirst() {
    TNode<T>* tmp = pFirst;
    if (tmp == nullptr) {
        throw "list empty";
    }
    pFirst = pFirst->pNext;
    delete tmp;
}

template <typename T>
int List<T>::Size() {
    TNode<T>* curr = pFirst;
    int sz = 0;
    while (curr != nullptr) {
        curr = curr->pNext;
        sz++;
    }
    return sz;
}