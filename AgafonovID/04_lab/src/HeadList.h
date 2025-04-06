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



};