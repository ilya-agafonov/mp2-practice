#include <gtest.h>
#include "RingList.h"

TEST(RingList, can_create_empty_ring_list) {
    ASSERT_NO_THROW(RingList<int> l);
}

TEST(RingList, created_ring_list_is_empty) {
    RingList<int> l;
    EXPECT_EQ(true, l.isEmpty());
}

TEST(RingList, pushBack_adds_element_to_ring_list) {
    RingList<int> l;
    l.pushBack(5);
    EXPECT_EQ(5, l.getFirst()->data);
}

TEST(RingList, can_add_multiple_elements_and_keep_order) {
    RingList<int> l;
    l.pushBack(1);
    l.pushBack(2);
    EXPECT_EQ(1, l.getFirst()->data);
}

TEST(RingList, getFirst_returns_correct_node) {
    RingList<int> l;
    l.pushBack(10);
    EXPECT_EQ(10, l.getFirst()->data);
}

TEST(RingList, getHead_returns_header_node) {
    RingList<int> l;
    EXPECT_EQ(l.getFirst(), l.getHead());
}

TEST(RingList, setFirst_changes_first_pointer) {
    RingList<int> l;
    TNode<int>* node = new TNode<int>(99);
    node->pNext = l.getHead();
    l.setFirst(node);
    EXPECT_EQ(99, l.getFirst()->data);
    delete node;
}

TEST(RingList, can_clear_list) {
    RingList<int> l;
    l.pushBack(1);
    l.pushBack(2);
    l.clear();
    EXPECT_EQ(true, l.isEmpty());
}

TEST(RingList, copy_constructor_creates_equal_list) {
    RingList<int> l1;
    l1.pushBack(5);
    RingList<int> l2(l1);
    EXPECT_EQ(5, l2.getFirst()->data);
}

TEST(RingList, operator_assign_creates_equal_list) {
    RingList<int> l1;
    l1.pushBack(42);
    RingList<int> l2;
    l2 = l1;
    EXPECT_EQ(42, l2.getFirst()->data);
}

TEST(RingList, assignment_operator_overwrites_previous_data) {
    RingList<int> l1;
    l1.pushBack(1);
    RingList<int> l2;
    l2.pushBack(2);
    l2 = l1;
    EXPECT_EQ(1, l2.getFirst()->data);
}

TEST(RingList, can_assign_self_without_error) {
    RingList<int> l;
    l.pushBack(77);
    ASSERT_NO_THROW(l = l);
}

TEST(RingList, destructor_does_not_throw) {
    RingList<int>* l = new RingList<int>();
    l->pushBack(123);
    ASSERT_NO_THROW(delete l);
}
