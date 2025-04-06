#include "HeadList.h"

template<typename T>
HeadList<T>::HeadList() : List<T>() {
    pHead = new TNode<T>(T(), -1);
    pHead->pNext = pFirst;
    prev = pHead;
    pStop = nullptr;
}

template<typename T>
HeadList<T>::HeadList(const HeadList<T>& hlist) {

}

template<typename T>
HeadList<T>::~HeadList() {

}