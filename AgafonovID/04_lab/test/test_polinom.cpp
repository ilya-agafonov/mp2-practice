#include <gtest.h>
#include "Polinom.h"

TEST(Polinom, can_create_empty_polinom) {
    ASSERT_NO_THROW(Polinom p);
}

TEST(Polinom, can_create_polinom_from_string) {
    ASSERT_NO_THROW(Polinom p("2x^1y^0z^0+3x^0y^1z^0"));
}

TEST(Polinom, can_copy_polinom) {
    Polinom p1("2x^1y^0z^0");
    Polinom p2(p1);
    EXPECT_EQ(true, p1 == p2);
}

TEST(Polinom, assignment_operator_copies_data_correctly) {
    Polinom p1("x^1y^1z^1"), p2;
    p2 = p1;
    EXPECT_EQ(true, p2 == p1);
}

TEST(Polinom, insert_adds_new_monom_to_polinom) {
    Polinom p;
    Monom m(2.0, 111);
    p.insert(m);
    EXPECT_EQ(true, p == Polinom("2x^1y^1z^1"));
}

TEST(Polinom, addition_of_two_polinoms_works) {
    Polinom p1("x^1"), p2("2x^1");
    Polinom sum = p1 + p2;
    EXPECT_EQ(true, sum == Polinom("3x^1"));
}

TEST(Polinom, subtraction_of_two_polinoms_works) {
    Polinom p1("5x^1"), p2("2x^1");
    Polinom diff = p1 - p2;
    EXPECT_EQ(true, diff == Polinom("3x^1"));
}

TEST(Polinom, multiplication_by_scalar_works) {
    Polinom p("x^1+2y^1");
    Polinom result = p * 3;
    EXPECT_EQ(true, result == Polinom("3x^1+6y^1"));
}

TEST(Polinom, multiplication_of_two_polinoms_works) {
    Polinom p1("x^1"), p2("y^1");
    Polinom prod = p1 * p2;
    EXPECT_EQ(true, prod == Polinom("1x^1y^1"));
}

TEST(Polinom, comparison_operator_equal_returns_true_for_equal_polynomials) {
    Polinom p1("2x^1+3y^1"), p2("2x^1+3y^1");
    EXPECT_EQ(true, p1 == p2);
}

TEST(Polinom, comparison_operator_not_equal_returns_true_for_different_polynomials) {
    Polinom p1("x^1"), p2("x^2");
    EXPECT_EQ(true, p1 != p2);
}

TEST(Polinom, can_evaluate_polynomial) {
    Polinom p("2x^1y^1+1z^2");
    double val = p(2, 3, 4); 
    EXPECT_DOUBLE_EQ(28.0, val);
}

TEST(Polinom, output_operator_streams_correct_string) {
    Polinom p("2x^1+3y^2");
    std::ostringstream out;
    out << p;
    EXPECT_EQ("2x+3y^2", out.str());
}

TEST(Polinom, input_operator_parses_string_correctly) {
    std::istringstream in("4x^1y^0z^0 + 2x^0y^1z^0");
    Polinom p;
    in >> p;
    EXPECT_EQ(true, p == Polinom("4x^1+2y^1"));
}
