#include "pch.h"
#include "BardCore/math/math.h"

namespace testing
{
    //test 90 degrees
    TEST(math_test, radians_to_degrees_test)
    {
        constexpr double degrees = math::radians_to_degrees(1.570);

        ASSERT_NEAR(90.0, degrees, ROUND_ONE_DECIMALS);
    }

    //test zero
    TEST(math_test, radians_to_degrees_zero_test)
    {
        constexpr double radians = math::degrees_to_radians(0.0);

        ASSERT_NEAR(0.0, radians, ROUND_ONE_DECIMALS);
    }

    //test negative theta
    TEST(math_test, radians_to_degrees_negative_test)
    {
        constexpr double degrees = math::radians_to_degrees(-1.570);

        ASSERT_NEAR(-90.0, degrees, ROUND_ONE_DECIMALS);
    }

    //test 450 degrees
    TEST(math_test, radians_to_degrees_450_test)
    {
        constexpr double degrees = math::radians_to_degrees(7.854);

        ASSERT_NEAR(450.0, degrees, ROUND_ONE_DECIMALS);
    }

    //test 90 degrees
    TEST(math_test, degrees_to_radians_test)
    {
        constexpr double radians = math::degrees_to_radians(90.0);

        ASSERT_NEAR(1.57, radians, ROUND_TWO_DECIMALS);
    }

    //test zero
    TEST(math_test, degrees_to_radians_zero_test)
    {
        constexpr double radians = math::degrees_to_radians(0.0);

        ASSERT_NEAR(0.0, radians, ROUND_ONE_DECIMALS);
    }

    //test negative theta
    TEST(math_test, degrees_to_radians_negative_test)
    {
        constexpr double radians = math::degrees_to_radians(-90.0);

        ASSERT_NEAR(-1.57, radians, ROUND_TWO_DECIMALS);
    }

    //test 450 degrees
    TEST(math_test, degrees_to_radians_450_test)
    {
        constexpr double radians = math::degrees_to_radians(450.0);

        ASSERT_NEAR(7.85, radians, ROUND_TWO_DECIMALS);
    }

    //test sqrt constexpr
    TEST(math_test, sqrt_test)
    {
        constexpr double result = math::sqrt(100);
        constexpr double result2 = math::sqrt(52);
        constexpr double result3 = math::sqrt(10000000);

        ASSERT_NEAR(10, result, ROUND_ZERO);
        ASSERT_NEAR(7.21, result2, ROUND_TWO_DECIMALS);
        ASSERT_NEAR(3162, result3, ROUND_ONE);
    }

    //test euclidean_gcd constexpr
    TEST(math_test, euclidean_gcd_test)
    {
        constexpr unsigned int result = math::euclidean_gcd(1071, 462);
        constexpr unsigned int result2 = math::euclidean_gcd(564, 34);

        ASSERT_EQ(21, result); // test compile time
        ASSERT_EQ(2, result2); // test compile time

        ASSERT_EQ(21, math::euclidean_gcd(1071, 462)); // test runtime
        ASSERT_EQ(2, math::euclidean_gcd(564, 34)); // test runtime
    }

    //test euclidean_gcd exception
    TEST(math_test, euclidean_gcd_exception_test)
    {
        ASSERT_THROW(math::euclidean_gcd(1, 0), exception::zero_exception);
        ASSERT_THROW(math::euclidean_gcd(0, 1), exception::zero_exception);
        ASSERT_THROW(math::euclidean_gcd(0, 0), exception::zero_exception);
        ASSERT_THROW(math::euclidean_gcd(1, 2), exception::negative_exception);
    }

    TEST(math_test, equals_test)
    {
        ASSERT_TRUE(math::equals(1.0, 1));
        ASSERT_FALSE(math::equals(1.0, 1.001));
        ASSERT_FALSE(math::equals(1.0, 1.0001));
        ASSERT_FALSE(math::equals(1.0, 1.00001));
        ASSERT_TRUE(math::equals(1.0, 1.000001));
        ASSERT_TRUE(math::equals(1.0, 1.000005));
        ASSERT_TRUE(math::equals(100234.0, 100234.0));
        ASSERT_TRUE(math::equals(143256524.0, 143256524.0));

        //infinity and nan tests
        ASSERT_FALSE(math::equals(NAN, NAN));
        ASSERT_FALSE(math::equals(INFINITY, NAN));
        ASSERT_FALSE(math::equals(NAN, INFINITY));
        ASSERT_FALSE(math::equals(INFINITY, INFINITY));
        ASSERT_FALSE(math::equals(-INFINITY, -INFINITY));
        ASSERT_FALSE(math::equals(INFINITY, -INFINITY));
        ASSERT_FALSE(math::equals(214, INFINITY));
        ASSERT_FALSE(math::equals(-214, -INFINITY));
        ASSERT_FALSE(math::equals(INFINITY, 214));
        ASSERT_FALSE(math::equals(-INFINITY, -214));
    }

    TEST(math_test, greater_than_test)
    {
        ASSERT_FALSE(math::greater_than(1.0, 2));
        ASSERT_FALSE(math::greater_than(1.0, 1.0001));
        ASSERT_FALSE(math::greater_than(1.0, 1.000001));
        ASSERT_TRUE(math::greater_than(1.0, -1.1));
        ASSERT_FALSE(math::greater_than(-1.0, 1));
        ASSERT_FALSE(math::greater_than(-25, 0.99999));
        ASSERT_TRUE(math::greater_than(76, 0.9999));
        ASSERT_TRUE(math::greater_than(1, 0.999));
        ASSERT_FALSE(math::greater_than(-1, -0.999));

        //infinity and nan tests
        ASSERT_FALSE(math::greater_than(INFINITY, NAN));
        ASSERT_FALSE(math::greater_than(NAN, INFINITY));
        ASSERT_FALSE(math::greater_than(INFINITY, INFINITY));
        ASSERT_FALSE(math::greater_than(NAN, NAN));

        ASSERT_FALSE(math::greater_than(-INFINITY, INFINITY));
        ASSERT_FALSE(math::greater_than(100, INFINITY));
        ASSERT_FALSE(math::greater_than(-543.53, INFINITY));
        ASSERT_FALSE(math::greater_than(-INFINITY, 100));
    }

    TEST(test_math, less_than_test)
    {
        ASSERT_TRUE(math::less_than(1.0, 2));
        ASSERT_TRUE(math::less_than(1.0, 1.0001));
        ASSERT_FALSE(math::less_than(1.0, 1.000001));
        ASSERT_FALSE(math::less_than(1.0, -1.1));
        ASSERT_TRUE(math::less_than(-1.0, 1));
        ASSERT_TRUE(math::less_than(-25, 0.99999));
        ASSERT_FALSE(math::less_than(76, 0.9999));
        ASSERT_FALSE(math::less_than(1, 0.999));
        ASSERT_TRUE(math::less_than(-1, -0.999));

        //infinity and nan tests
        ASSERT_FALSE(math::less_than(INFINITY, NAN));
        ASSERT_FALSE(math::less_than(NAN, INFINITY));
        ASSERT_FALSE(math::less_than(INFINITY, INFINITY));
        ASSERT_FALSE(math::less_than(NAN, NAN));

        ASSERT_TRUE(math::less_than(-INFINITY, INFINITY));
        ASSERT_TRUE(math::less_than(100, INFINITY));
        ASSERT_TRUE(math::less_than(-543.53, INFINITY));
        ASSERT_TRUE(math::less_than(-INFINITY, 100));
    }

    TEST(math_test, sign_test)
    {
        ASSERT_EQ(1, math::sign(1));
        ASSERT_EQ(0, math::sign(0));
        ASSERT_EQ(-1, math::sign(-1));
        ASSERT_EQ(-1, math::sign(-0.4));
        ASSERT_EQ(1, math::sign(INFINITY));
        ASSERT_EQ(-1, math::sign(-INFINITY));
        ASSERT_EQ(1, math::sign(NAN));
    }

    TEST(math_test, abs_test)
    {
        constexpr double a = 1;
        constexpr double b = 0;
        constexpr double c = -1;
        constexpr double d = -0.4;
        constexpr double e = -1.2;
        constexpr double f = -42;

        ASSERT_TRUE(math::equals(1, math::abs(a)));
        ASSERT_TRUE(math::equals(0, math::abs(b)));
        ASSERT_TRUE(math::equals(1, math::abs(c)));
        ASSERT_TRUE(math::equals(0.4, math::abs(d)));
        ASSERT_TRUE(math::equals(1.2, math::abs(e)));
        ASSERT_TRUE(math::equals(42, math::abs(f)));
    }

    TEST(math_test, mod_test)
    {
        constexpr double compile_time_a = math::mod(5.3, 2);
        constexpr double compile_time_b = math::mod(18.5, 4.2);
        constexpr double compile_time_c = math::mod(0, 1.2);
        constexpr double compile_time_e = math::mod(1.2, 0.1);
        constexpr double compile_time_f = math::mod(1.2, -0.1);
        constexpr double compile_time_g = math::mod(-1.2, 0.1);
        constexpr double compile_time_h = math::mod(0, -0.1);

        ASSERT_TRUE(math::equals(1.3, compile_time_a));
        ASSERT_TRUE(math::equals(1.7, compile_time_b));
        ASSERT_TRUE(math::equals(0, compile_time_c));
        ASSERT_TRUE(math::equals(0, compile_time_e));
        ASSERT_TRUE(math::equals(0, compile_time_f));
        ASSERT_TRUE(math::equals(0, compile_time_g));
        ASSERT_TRUE(math::equals(0, compile_time_h));

        ASSERT_TRUE(math::equals(1.3, math::mod(5.3, 2)));
        ASSERT_TRUE(math::equals(1.7, math::mod(18.5, 4.2)));
        ASSERT_TRUE(math::equals(0, math::mod(0, 1.2)));
        ASSERT_TRUE(math::equals(0, math::mod(1.2, 0.1)));
        ASSERT_TRUE(math::equals(0, math::mod(1.2, -0.1)));
        ASSERT_TRUE(math::equals(0, math::mod(-1.2, 0.1)));
        ASSERT_TRUE(math::equals(0, math::mod(0, -0.1)));

        ASSERT_THROW(math::mod(1, 0), exception::zero_exception);
        ASSERT_THROW(math::mod(6, -0), exception::zero_exception);
        ASSERT_THROW(math::mod(-12, 0), exception::zero_exception);
    }

    TEST(math_test, sin)
    {
        constexpr double compile_time_a = math::sin(0);
        constexpr double compile_time_b = math::sin(1);
        constexpr double compile_time_c = math::sin(-1);
        constexpr double compile_time_d = math::sin(6);
        constexpr double compile_time_e = math::sin(-6);
        constexpr double compile_time_f = math::sin(10.6);
        constexpr double compile_time_g = math::sin(math::pi);
        constexpr double compile_time_h = math::sin(math::pi_2);
        constexpr double compile_time_i = math::sin(INFINITY);
        constexpr double compile_time_j = math::sin(NAN);

        // compile time tests
        ASSERT_TRUE(math::equals(0, compile_time_a));
        ASSERT_TRUE(math::equals(0.84147, compile_time_b));
        ASSERT_TRUE(math::equals(-0.84147, compile_time_c));
        ASSERT_TRUE(math::equals(-0.27942, compile_time_d));
        ASSERT_TRUE(math::equals(0.27942, compile_time_e));
        ASSERT_TRUE(math::equals(-0.92277, compile_time_f));
        ASSERT_TRUE(math::equals(0, compile_time_g));
        ASSERT_TRUE(math::equals(1, compile_time_h));
        ASSERT_TRUE(std::isnan(compile_time_i));
        ASSERT_TRUE(std::isnan(compile_time_j));

        // runtime tests
        ASSERT_TRUE(math::equals(0, math::sin(0)));
        ASSERT_TRUE(math::equals(0.84147, math::sin(1)));
        ASSERT_TRUE(math::equals(-0.84147, math::sin(-1)));
        ASSERT_TRUE(math::equals(-0.27942, math::sin(6)));
        ASSERT_TRUE(math::equals(0.27942, math::sin(-6)));
        ASSERT_TRUE(math::equals(-0.92277, math::sin(10.6)));
        ASSERT_TRUE(math::equals(0, math::sin(math::pi)));
        ASSERT_TRUE(math::equals(1, math::sin(math::pi_2)));
        ASSERT_TRUE(std::isnan(math::sin(INFINITY)));
        ASSERT_TRUE(std::isnan(math::sin(NAN)));
    }

    TEST(math_test, cos)
    {
        constexpr double compile_time_a = math::cos(0);
        constexpr double compile_time_b = math::cos(1);
        constexpr double compile_time_c = math::cos(-1);
        constexpr double compile_time_d = math::cos(6);
        constexpr double compile_time_e = math::cos(-6);
        constexpr double compile_time_f = math::cos(10.6);
        constexpr double compile_time_g = math::cos(math::pi);
        constexpr double compile_time_h = math::cos(math::pi_2);
        constexpr double compile_time_i = math::cos(math::pi_4);

        // compile time tests
        ASSERT_TRUE(math::equals(1, compile_time_a));
        ASSERT_TRUE(math::equals(0.54030, compile_time_b));
        ASSERT_TRUE(math::equals(0.54030, compile_time_c));
        ASSERT_TRUE(math::equals(0.96017, compile_time_d));
        ASSERT_TRUE(math::equals(0.96017, compile_time_e));
        ASSERT_TRUE(math::equals(-0.38534, compile_time_f));
        ASSERT_TRUE(math::equals(-1, compile_time_g));
        ASSERT_TRUE(math::equals(0, compile_time_h));
        ASSERT_TRUE(math::equals(math::sqrt(2) / 2, compile_time_i));

        // runtime tests
        ASSERT_TRUE(math::equals(1, math::cos(0)));
        ASSERT_TRUE(math::equals(0.54030, math::cos(1)));
        ASSERT_TRUE(math::equals(0.54030, math::cos(-1)));
        ASSERT_TRUE(math::equals(0.96017, math::cos(6)));
        ASSERT_TRUE(math::equals(0.96017, math::cos(-6)));
        ASSERT_TRUE(math::equals(-0.38534, math::cos(10.6)));
        ASSERT_TRUE(math::equals(-1, math::cos(math::pi)));
        ASSERT_TRUE(math::equals(0, math::cos(math::pi_2)));
        ASSERT_TRUE(math::equals(math::sqrt(2) / 2, math::cos(math::pi_4)));

        // infinity and nan tests
        constexpr double compile_time_nan = math::cos(NAN);
        constexpr double compile_time_inf = math::cos(INFINITY);
        constexpr double compile_time_ninf = math::cos(-INFINITY);
        ASSERT_TRUE(std::isnan(math::cos(NAN)));
        ASSERT_TRUE(std::isnan(math::cos(INFINITY)));
        ASSERT_TRUE(std::isnan(math::cos(-INFINITY)));

        ASSERT_TRUE(std::isnan(compile_time_nan));
        ASSERT_TRUE(std::isnan(compile_time_inf));
        ASSERT_TRUE(std::isnan(compile_time_ninf));
    }

    TEST(math_test, tan)
    {
        constexpr double compile_time_a = math::tan(0);
        constexpr double compile_time_b = math::tan(1);
        constexpr double compile_time_c = math::tan(-1);
        constexpr double compile_time_d = math::tan(6);
        constexpr double compile_time_e = math::tan(-6);
        constexpr double compile_time_f = math::tan(10.6);
        constexpr double compile_time_g = math::tan(math::pi);
        constexpr double compile_time_h = math::tan(math::pi_2);
        constexpr double compile_time_i = math::tan(math::pi_4);
        constexpr double compile_time_j = math::tan(math::pi_2 + 3 * math::pi - 0.05);
        constexpr double compile_time_k = math::tan(9000.0);
        constexpr double compile_time_l = math::tan(-5345.0);

        // compile time tests
        ASSERT_TRUE(math::equals(0, compile_time_a));
        ASSERT_TRUE(math::equals(1.5574, compile_time_b));
        ASSERT_TRUE(math::equals(-1.5574, compile_time_c));
        ASSERT_TRUE(math::equals(-0.29101, compile_time_d));
        ASSERT_TRUE(math::equals(0.29101, compile_time_e));
        ASSERT_TRUE(math::equals(2.39468, compile_time_f));
        ASSERT_TRUE(math::equals(0, compile_time_g));
        ASSERT_TRUE(std::isnan(compile_time_h));
        ASSERT_TRUE(math::equals(1, compile_time_i));
        ASSERT_NEAR(20, compile_time_j, 0.1);
        ASSERT_TRUE(math::equals(-0.78085, compile_time_k));
        ASSERT_TRUE(math::equals(-2.239845, compile_time_l));

        ASSERT_TRUE(math::equals(0, math::tan(0)));
        ASSERT_TRUE(math::equals(1.5574, math::tan(1)));
        ASSERT_TRUE(math::equals(-1.5574, math::tan(-1)));
        ASSERT_TRUE(math::equals(-0.29101, math::tan(6)));
        ASSERT_TRUE(math::equals(0.29101, math::tan(-6)));
        ASSERT_TRUE(math::equals(2.39472, math::tan(10.6)));
        ASSERT_TRUE(math::equals(0, math::tan(math::pi)));
        ASSERT_TRUE(std::isnan(math::tan(math::pi_2)));
        ASSERT_TRUE(math::equals(1, math::tan(math::pi_4)));
        ASSERT_NEAR(20, math::tan(math::pi_2 + 3 * math::pi - 0.05), 0.1);
        ASSERT_TRUE(math::equals(-0.78085, math::tan(9000)));
        ASSERT_TRUE(math::equals(-2.239878, math::tan(-5345)));

        // infinity and nan tests
        constexpr double compile_time_nan = math::tan(NAN);
        constexpr double compile_time_inf = math::tan(INFINITY);
        constexpr double compile_time_ninf = math::tan(-INFINITY);
        ASSERT_TRUE(std::isnan(math::tan(NAN)));
        ASSERT_TRUE(std::isnan(math::tan(INFINITY)));
        ASSERT_TRUE(std::isnan(math::tan(-INFINITY)));

        ASSERT_TRUE(std::isnan(compile_time_nan));
        ASSERT_TRUE(std::isnan(compile_time_inf));
        ASSERT_TRUE(std::isnan(compile_time_ninf));
    }

    TEST(math_test, factorial)
    {
        constexpr unsigned int compile_time_a = math::factorial(0);
        constexpr unsigned int compile_time_b = math::factorial(3);
        constexpr unsigned int compile_time_c = math::factorial(10);

        // compile time tests
        ASSERT_TRUE(math::equals(1, compile_time_a));
        ASSERT_TRUE(math::equals(6, compile_time_b));
        ASSERT_TRUE(math::equals(3628800, compile_time_c));

        // runtime tests
        ASSERT_TRUE(math::equals(1, math::factorial(0)));
        ASSERT_TRUE(math::equals(6, math::factorial(3)));
        ASSERT_TRUE(math::equals(3628800, math::factorial(10)));
    }

} // namespace testing
