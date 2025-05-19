#include <gtest.h>
#include "Monom.h"

TEST(Monom, can_create_default_monom) {
    ASSERT_NO_THROW(Monom m);
}

TEST(Monom, default_monom_has_zero_coef_and_degree) {
    Monom m;
    EXPECT_EQ(0, m.getCoef());
}

TEST(Monom, can_create_monom_with_parameters) {
    Monom m(2.5, 321);
    EXPECT_EQ(2.5, m.getCoef());
}

TEST(Monom, can_copy_monom) {
    Monom m1(1.1, 123);
    Monom m2(m1);
    EXPECT_EQ(1.1, m2.getCoef());
}

TEST(Monom, getDegree_returns_correct_value) {
    Monom m(3.0, 456);
    EXPECT_EQ(456, m.getDegree());
}

TEST(Monom, can_setCoef) {
    Monom m;
    m.setCoef(9.99);
    EXPECT_EQ(9.99, m.getCoef());
}

TEST(Monom, can_setDegree) {
    Monom m;
    m.setDegree(321);
    EXPECT_EQ(321, m.getDegree());
}

TEST(Monom, equal_operator_returns_true_for_equal_monomials) {
    Monom m1(1.0, 123), m2(1.0, 123);
    EXPECT_EQ(true, m1 == m2);
}

TEST(Monom, less_operator_works_correctly) {
    Monom m1(1.0, 123), m2(1.0, 124);
    EXPECT_EQ(true, m1 < m2);
}

TEST(Monom, greater_operator_works_correctly) {
    Monom m1(1.0, 999), m2(1.0, 123);
    EXPECT_EQ(true, m1 > m2);
}

TEST(Monom, greater_equal_operator_true_when_equal) {
    Monom m1(1.0, 321), m2(1.0, 321);
    EXPECT_EQ(true, m1 >= m2);
}

TEST(Monom, less_equal_operator_true_when_equal) {
    Monom m1(1.0, 654), m2(1.0, 654);
    EXPECT_EQ(true, m1 <= m2);
}

TEST(Monom, Monom_tostr_returns_expected_string) {
    Monom m(2.5, 123); 
    EXPECT_EQ("2.5xy^2z^3", m.Monom_tostr());
}

TEST(Monom, monom_evaluation_works) {
    Monom m(2.0, 111); 
    EXPECT_DOUBLE_EQ(2.0 * 2 * 3 * 4, m(2, 3, 4));
}

TEST(Monom, can_add_monomials_with_same_degree) {
    Monom m1(2.0, 321), m2(3.0, 321);
    EXPECT_EQ(5.0, (m1 + m2).getCoef());
}

TEST(Monom, subtracting_monomials_with_same_degree_works) {
    Monom m1(5.0, 321), m2(2.0, 321);
    EXPECT_EQ(3.0, (m1 - m2).getCoef());
}

TEST(Monom, multiplying_two_monomials_combines_coeff_and_adds_degrees) {
    Monom m1(2.0, 123), m2(3.0, 234); 
    EXPECT_EQ(6.0, (m1 * m2).getCoef());
}

TEST(Monom, multiplying_by_scalar_works) {
    Monom m(4.0, 321);
    EXPECT_EQ(20.0, (m * 5.0).getCoef());
}

TEST(Monom, assignment_operator_copies_data_correctly) {
    Monom m1(1.5, 111), m2;
    m2 = m1;
    EXPECT_EQ(1.5, m2.getCoef());
}
