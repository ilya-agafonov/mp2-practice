#include <gtest.h>
#include "Polinom.h"

TEST(Polinom, can_create_polynom) {
    ASSERT_NO_THROW(Polinom p);
}


TEST(Polinom, parse_invalid_string_throws) {
    ASSERT_ANY_THROW(Polinom("x^y"));  
}


TEST(Polinom, throws_on_too_high_degree) {
    ASSERT_ANY_THROW(Polinom p("x^11"));
}

TEST(Polinom, adds_simple_polinoms) {
    Polinom p1("2x");
    Polinom p2("3x");
    Polinom res = p1 + p2;
    Polinom expected("5x");
    EXPECT_EQ(res, expected);
}

TEST(Polinom, adds_polinoms_with_different_vars) {
    Polinom p1("2x + y");
    Polinom p2("x + 3y");
    Polinom res = p1 + p2;
    Polinom expected("3x + 4y");
    EXPECT_EQ(res, expected);
}

TEST(Polinom, handles_negative_coefficients) {
    Polinom p1("2x - y");
    Polinom p2("-x + 3y");
    Polinom res = p1 + p2;
    Polinom expected("x + 2y");
    EXPECT_EQ(res, expected);
}

TEST(Polinom, subtracts_simple_polinoms) {
    Polinom p1("5x");
    Polinom p2("3x");
    Polinom res = p1 - p2;
    Polinom expected("2x");
    EXPECT_EQ(res, expected);
}

TEST(Polinom, subtracts_polinoms_with_different_vars) {
    Polinom p1("2x + 4y");
    Polinom p2("x + y");
    Polinom res = p1 - p2;
    Polinom expected("x + 3y");
    EXPECT_EQ(res, expected);
}

TEST(Polinom, results_in_zero_polinom) {
    Polinom p1("x + y");
    Polinom p2("x + y");
    Polinom res = p1 - p2;
    Polinom expected("0");
    EXPECT_EQ(res, expected);
}

TEST(Polinom, multiplies_by_scalar) {
    Polinom p("x + 2y");
    Polinom res = p * 3.0;
    Polinom expected("3x + 6y");
    EXPECT_EQ(res, expected);
}

TEST(Polinom, multiplies_two_polinoms) {
    Polinom p1("x + y");
    Polinom p2("x - y");
    Polinom res = p1 * p2;
    Polinom expected("x^2 - y^2");
    EXPECT_EQ(res, expected);
}

TEST(Polinom, multiplies_by_zero) {
    Polinom p("x + y");
    Polinom res = p * 0.0;
    Polinom expected("0");
    EXPECT_EQ(res, expected);
}

TEST(Polinom, evaluates_simple_polinom) {
    Polinom p("2x + 3y - z");
    double res = p.evaluate(1.0, 1.0, 1.0);
    EXPECT_DOUBLE_EQ(4.0, res);
}

TEST(Polinom, evaluates_to_zero) {
    Polinom p("x - x");
    double res = p.evaluate(10.0, 20.0, 30.0);
    EXPECT_DOUBLE_EQ(0.0, res);
}

TEST(Polinom, evaluate_with_zero_vars) {
    Polinom p("5");
    EXPECT_DOUBLE_EQ(5.0, p.evaluate(0.0, 0.0, 0.0));
}

TEST(Polinom, empty_polinom_is_zero) {
    Polinom p;
    EXPECT_TRUE(p == Polinom("0"));
}

TEST(Polinom, polinom_with_zero_coefs_is_zero) {
    Polinom p("0x + 0y - 0z");
    EXPECT_TRUE(p == Polinom("0"));
}

TEST(Polinom, add_zero_polinom_unchanged) {
    Polinom p1("x + y");
    Polinom p2("0");
    Polinom res = p1 + p2;
    EXPECT_EQ(res, p1);
}

TEST(Polinom, multiply_zero_polinom_gives_zero) {
    Polinom p1("0");
    Polinom p2("x + y");
    Polinom res = p1 * p2;
    EXPECT_TRUE(res == Polinom("0"));
}