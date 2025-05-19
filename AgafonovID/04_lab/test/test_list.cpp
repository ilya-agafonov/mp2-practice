#include <gtest.h>
#include "List.h"

TEST(List, can_create_empty_list) {
    ASSERT_NO_THROW(List<int> l);
}

TEST(List, created_list_is_empty) {
    List<int> l;
    EXPECT_EQ(true, l.IsEmpty());
}

TEST(List, can_push_front_to_list) {
    List<int> l;
    TNode<int>* node = new TNode<int>(5);
    l.pushFront(node);
    EXPECT_EQ(5, l.reset());
}

TEST(List, can_push_back_to_list) {
    List<int> l;
    TNode<int>* node1 = new TNode<int>(5);
    l.pushFront(node1);
    EXPECT_EQ(5, l.reset());
}

TEST(List, size_returns_correct_value) {
    List<int> list;
    list.pushBack(new TNode<int>(1));
    list.pushBack(new TNode<int>(2));
    EXPECT_EQ(list.Size(), 2);
}

TEST(List, can_insert_after_node) {
    List<int> l;
    TNode<int>* node1 = new TNode<int>(5);
    TNode<int>* node2 = new TNode<int>(10);
    TNode<int>* node3 = new TNode<int>(15);
    l.pushFront(node1);
    l.pushBack(node2);
    ASSERT_NO_THROW(l.insertAfter(node3, 5));
}

TEST(List, can_insert_before_node) {
    List<int> l;
    TNode<int>* node1 = new TNode<int>(10);
    TNode<int>* node2 = new TNode<int>(20);
    TNode<int>* node3 = new TNode<int>(15);
    l.pushFront(node1);
    l.pushBack(node2);
    ASSERT_NO_THROW(l.insertBefore(node3, 20));
}

TEST(List, can_remove_node_by_key) {
    List<int> l;
    TNode<int>* node1 = new TNode<int>(10);
    TNode<int>* node2 = new TNode<int>(20);
    l.pushFront(node1);
    l.pushBack(node2);
    ASSERT_NO_THROW(l.remove(10));
}

TEST(List, RemoveThrowsIfNotFound) {
    List<int> list;
    list.pushBack(new TNode<int>(1));
    ASSERT_ANY_THROW(list.remove(2));
}

TEST(List, removed_node_changes_list) {
    List<int> l;
    TNode<int>* node1 = new TNode<int>(10);
    TNode<int>* node2 = new TNode<int>(20);
    l.pushFront(node1);
    l.pushBack(node2);
    l.remove(10);
    EXPECT_EQ(20, l.reset());
}

TEST(List, can_reset_to_first_element) {
    List<int> l;
    TNode<int>* node = new TNode<int>(5);
    l.pushFront(node);
    EXPECT_EQ(5, l.reset());
}

TEST(List, can_remove_first_element) {
    List<int> l;
    TNode<int>* node1 = new TNode<int>(5);
    TNode<int>* node2 = new TNode<int>(10);
    l.pushFront(node1);
    l.pushBack(node2);
    ASSERT_NO_THROW(l.removefirst());
}

TEST(List, reset_after_removing_first_element) {
    List<int> l;
    TNode<int>* node1 = new TNode<int>(5);
    TNode<int>* node2 = new TNode<int>(10);
    l.pushFront(node1);
    l.pushBack(node2);
    l.removefirst();
    EXPECT_EQ(10, l.reset());
}

TEST(List, can_copy_list) {
    List<int> l1;
    TNode<int>* node = new TNode<int>(5);
    l1.pushFront(node);
    ASSERT_NO_THROW(List<int> l2(l1));
}

TEST(List, copied_list_is_equal_to_original) {
    List<int> l1;
    TNode<int>* node = new TNode<int>(5);
    l1.pushFront(node);
    List<int> l2 = l1;
    EXPECT_EQ(true, l1 == l2);
}

TEST(List, can_assign_list) {
    List<int> l1;
    TNode<int>* node = new TNode<int>(5);
    l1.pushFront(node);
    List<int> l2;
    ASSERT_NO_THROW(l2 = l1);
}

TEST(List, assigned_list_is_equal_to_original) {
    List<int> l1;
    TNode<int>* node = new TNode<int>(5);
    l1.pushFront(node);
    List<int> l2;
    l2 = l1;
    EXPECT_EQ(true, l1 == l2);
}

TEST(List, can_check_if_list_is_empty) {
    List<int> l;
    ASSERT_NO_THROW(l.IsEmpty());
}

TEST(ListTest, AssignmentOperatorWorksCorrectly) {
    List<int> list;
    list.pushBack(new TNode<int>(3));
    List<int> list2;
    list2 = list;
    EXPECT_EQ(true, list2 == list);
}

TEST(List, returns_false_if_different) {
    List<int> list1;
    list1.pushBack(new TNode<int>(1));
    List<int> list2;
    list2.pushBack(new TNode<int>(2));
    EXPECT_EQ(false, list1 == list2);
}

TEST(List, can_getFirst) {
    List<int> list;
    list.pushBack(new TNode<int>(42));
    EXPECT_EQ(list.getFirst()->data, 42);
}