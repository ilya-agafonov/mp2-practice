#include <gtest.h>
#include "Monom.h"

TEST(MonomTest, can_create_monom)
{
    ASSERT_NO_THROW(Monom m);
}

TEST(MonomTest, ConstructorSetsCorrectValues) {
    Monom m(2.5, 123);
    EXPECT_DOUBLE_EQ(m.getCoef(), 2.5);
}

TEST(MonomTest, can_copy_constructor_copies_values) {
    Monom m1(3.0, 111);
    Monom m2(m1);
    EXPECT_EQ(m2.getDegree(), 111);
}

TEST(MonomTest, SetAndGetDegree) {
    Monom m;
    m.setDegree(321);
    EXPECT_EQ(m.getDegree(), 321);
}

TEST(MonomTest, EqualOperatorTrueForSameDegree) {
    Monom m1(2, 123), m2(3, 123);
    EXPECT_TRUE(m1 == m2);
}

TEST(MonomTest, NotEqualOperatorTrueForDifferentDegree) {
    Monom m1(2, 123), m2(2, 124);
    EXPECT_TRUE(m1 != m2);
}

TEST(MonomTest, LessOperatorTrueIfDegreeLess) {
    Monom m1(2, 122), m2(2, 123);
    EXPECT_TRUE(m1 < m2);
}

TEST(MonomTest, GreaterOperatorTrueIfDegreeGreater) {
    Monom m1(2, 124), m2(2, 123);
    EXPECT_TRUE(m1 > m2);
}

TEST(MonomTest, ValueIsEvaluatedCorrectly) {
    Monom m(2, 321);
    EXPECT_DOUBLE_EQ(m(2.0, 2.0, 2.0), 2 * pow(2, 3) * pow(2, 2) * 2);
}

TEST(MonomTest, AddWithSameDegree) {
    Monom m1(1, 321), m2(2, 321);
    Monom sum = m1 + m2;
    EXPECT_DOUBLE_EQ(sum.getCoef(), 3.0);
}

TEST(MonomTest, SubtractWithSameDegree) {
    Monom m1(3, 321), m2(1, 321);
    Monom diff = m1 - m2;
    EXPECT_DOUBLE_EQ(diff.getCoef(), 2.0);
}

TEST(MonomTest, MultiplyTwoMonomsValidDegree) {
    Monom m1(2, 111), m2(3, 111);
    Monom res = m1 * m2;
    EXPECT_DOUBLE_EQ(res.getCoef(), 6.0);
}

TEST(MonomTest, MultiplyTwoMonomsThrowsIfDegreeTooBig) {
    Monom m1(2, 999), m2(1, 1);
    EXPECT_THROW(m1 * m2, std::exception);
}

TEST(MonomTest, MultiplyByScalar) {
    Monom m(2, 123);
    Monom res = m * 3;
    EXPECT_DOUBLE_EQ(res.getCoef(), 6.0);
}

