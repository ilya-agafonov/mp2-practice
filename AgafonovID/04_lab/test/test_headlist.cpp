#include <gtest.h>
#include "HeadList.h"

TEST(HeadList, can_create_list) {
    ASSERT_NO_THROW(HeadList<int> l);
}

TEST(HeadList, can_create_copied_list) {
    HeadList<int> l;
    ASSERT_NO_THROW(HeadList<int> l1(l));
}

TEST(HeadList, correct_create_copied_list)
{
    HeadList<int> l;
    HeadList<int> l1(l);
    EXPECT_TRUE(l == l1);
}

TEST(HeadList, push_front_adds_element) {
    HeadList<int> l;
    TNode<int>* node = new TNode<int>(5);
    l.pushFront(node);
    EXPECT_EQ(5, l.reset());
}

TEST(HeadList, push_back_adds_element_to_end) {
    HeadList<int> l;
    TNode<int>* node = new TNode<int>(10);
    l.pushBack(node);
    EXPECT_EQ(10, l.reset());
}

TEST(HeadList, remove_deletes_node) {
    HeadList<int> l;
    TNode<int>* node = new TNode<int>(5);
    l.pushFront(node);
    l.remove(5);
    EXPECT_TRUE(l.IsEmpty());
}

TEST(HeadList, clear_empties_list) {
    HeadList<int> l;
    TNode<int>* node = new TNode<int>(5);
    l.pushFront(node);
    l.clear();
    EXPECT_TRUE(l.IsEmpty());
}