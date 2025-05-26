#include <gtest.h>
#include "HeadList.h"

TEST(HeadList, can_create_empty_list) {
    ASSERT_NO_THROW(HeadList<int> l);
}

TEST(HeadList, created_list_is_empty) {
    HeadList<int> l;
    EXPECT_EQ(true, l.IsEmpty());
}


TEST(HeadList, size_returns_correct_value) {
    HeadList<int> list;
    list.pushBack(new TNode<int>(1));
    list.pushBack(new TNode<int>(2));
    EXPECT_EQ(2, list.Size());
}

TEST(HeadList, can_insert_after_node) {
    HeadList<int> l;
    TNode<int>* node1 = new TNode<int>(5);
    TNode<int>* node2 = new TNode<int>(10);
    TNode<int>* node3 = new TNode<int>(15);
    l.pushFront(node1);
    l.pushBack(node2);
    ASSERT_NO_THROW(l.insertAfter(node3, 5));
}

TEST(HeadList, can_insert_before_node) {
    HeadList<int> l;
    TNode<int>* node1 = new TNode<int>(10);
    TNode<int>* node2 = new TNode<int>(20);
    TNode<int>* node3 = new TNode<int>(15);
    l.pushFront(node1);
    l.pushBack(node2);
    ASSERT_NO_THROW(l.insertBefore(node3, 20));
}

TEST(HeadList, can_remove_node_by_key) {
    HeadList<int> l;
    TNode<int>* node1 = new TNode<int>(10);
    TNode<int>* node2 = new TNode<int>(20);
    l.pushFront(node1);
    l.pushBack(node2);
    ASSERT_NO_THROW(l.remove(10));
}

TEST(HeadList, remove_throws_if_not_found) {
    HeadList<int> list;
    list.pushBack(new TNode<int>(1));
    ASSERT_ANY_THROW(list.remove(2));
}

TEST(HeadList, can_remove_first_element) {
    HeadList<int> l;
    TNode<int>* node1 = new TNode<int>(5);
    TNode<int>* node2 = new TNode<int>(10);
    l.pushFront(node1);
    l.pushBack(node2);
    ASSERT_NO_THROW(l.removefirst());
}



TEST(HeadList, can_copy_list) {
    HeadList<int> l1;
    TNode<int>* node = new TNode<int>(5);
    l1.pushFront(node);
    ASSERT_NO_THROW(HeadList<int> l2(l1));
}

TEST(HeadList, copied_list_is_equal_to_original) {
    HeadList<int> l1;
    TNode<int>* node = new TNode<int>(5);
    l1.pushFront(node);
    HeadList<int> l2 = l1;
    EXPECT_EQ(true, l1 == l2);
}

TEST(HeadList, can_assign_list) {
    HeadList<int> l1;
    TNode<int>* node = new TNode<int>(5);
    l1.pushFront(node);
    HeadList<int> l2;
    ASSERT_NO_THROW(l2 = l1);
}

TEST(HeadList, assigned_list_is_equal_to_original) {
    HeadList<int> l1;
    TNode<int>* node = new TNode<int>(5);
    l1.pushFront(node);
    HeadList<int> l2;
    l2 = l1;
    EXPECT_EQ(true, l1 == l2);
}

TEST(HeadList, can_check_if_list_is_empty) {
    HeadList<int> l;
    ASSERT_NO_THROW(l.IsEmpty());
}

TEST(HeadList, assignment_operator_works_correctly) {
    HeadList<int> list;
    list.pushBack(new TNode<int>(3));
    HeadList<int> list2;
    list2 = list;
    EXPECT_EQ(true, list2 == list);
}

TEST(HeadList, returns_false_if_different) {
    HeadList<int> list1;
    list1.pushBack(new TNode<int>(1));
    HeadList<int> list2;
    list2.pushBack(new TNode<int>(2));
    EXPECT_EQ(false, list1 == list2);
}

TEST(HeadList, can_get_first) {
    HeadList<int> list;
    list.pushBack(new TNode<int>(42));
    EXPECT_EQ(42, list.getFirst()->data);
}
