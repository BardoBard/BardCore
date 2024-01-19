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

        // compile time tests
        ASSERT_NEAR(10, result, ROUND_ZERO);
        ASSERT_NEAR(7.2111, result2, ROUND_FOUR_DECIMALS);
        ASSERT_NEAR(3162.28, result3, ROUND_TWO_DECIMALS);

        // runtime tests
        ASSERT_TRUE(math::equals(10, math::sqrt(100))) << math::sqrt(100);
        ASSERT_TRUE(math::equals(7.2111, math::sqrt(52))) << math::sqrt(52);
        ASSERT_TRUE(math::equals(3162.27766, math::sqrt(10000000))) << math::sqrt(10000000);
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

    TEST(math_test, less_than_test)
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

    TEST(math_test, sin_test)
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

    TEST(math_test, cos_test)
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

    TEST(math_test, tan_test)
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

    TEST(math_test, arcsin_test)
    {
        constexpr double compile_time_a = math::arcsin(0);
        constexpr double compile_time_b = math::arcsin(1);
        constexpr double compile_time_c = math::arcsin(-1);
        constexpr double compile_time_d = math::arcsin(0.1);
        constexpr double compile_time_e = math::arcsin(-0.4);
        constexpr double compile_time_f = math::arcsin(math::pi_4); 
        constexpr double compile_time_g = math::arcsin(0.2);
        constexpr double compile_time_h = math::arcsin(0.7);
        constexpr double compile_time_i = math::arcsin(0.9);
        constexpr double compile_time_j = math::arcsin(0.99);
        constexpr double compile_time_k = math::arcsin(-0.99);

        // compile time tests
        ASSERT_TRUE(math::equals(0, compile_time_a));
        ASSERT_TRUE(math::equals(math::pi_2, compile_time_b));
        ASSERT_TRUE(math::equals(-math::pi_2, compile_time_c));
        ASSERT_TRUE(math::equals(0.100165, compile_time_d));
        ASSERT_TRUE(math::equals(-0.41150, compile_time_e));
        ASSERT_TRUE(math::equals(0.90332, compile_time_f)); 
        ASSERT_TRUE(math::equals(0.20136, compile_time_g));
        ASSERT_TRUE(math::equals(0.77539, compile_time_h));
        ASSERT_TRUE(math::equals(1.11973, compile_time_i));
        ASSERT_TRUE(math::equals(1.42738, compile_time_j));
        ASSERT_TRUE(math::equals(-1.42738, compile_time_k));

        ASSERT_TRUE(math::equals(0, math::arcsin(0)));
        ASSERT_TRUE(math::equals(1.5708, math::arcsin(1)));
        ASSERT_TRUE(math::equals(-1.5708, math::arcsin(-1)));
        ASSERT_TRUE(math::equals(0.100165, math::arcsin(0.1)));
        ASSERT_TRUE(math::equals(-0.41152, math::arcsin(-0.4)));
        ASSERT_TRUE(math::equals(0.90334, math::arcsin(math::pi_4)));
        ASSERT_TRUE(math::equals(0.20136, math::arcsin(0.2)));
        ASSERT_TRUE(math::equals(0.77539, math::arcsin(0.7)));
        ASSERT_TRUE(math::equals(1.11977, math::arcsin(0.9)));
        ASSERT_TRUE(math::equals(1.42925, math::arcsin(0.99)));
        ASSERT_TRUE(math::equals(-1.42925, math::arcsin(-0.99)));
    }

    TEST(math_test, arccos_test)
    {
        constexpr double compile_time_a = math::arccos(0);
        constexpr double compile_time_b = math::arccos(1);
        constexpr double compile_time_c = math::arccos(-1);
        constexpr double compile_time_d = math::arccos(0.1);
        constexpr double compile_time_e = math::arccos(-0.4);
        constexpr double compile_time_f = math::arccos(math::pi_4);
        constexpr double compile_time_g = math::arccos(0.2);
        constexpr double compile_time_h = math::arccos(0.7);
        constexpr double compile_time_i = math::arccos(0.9);
        constexpr double compile_time_j = math::arccos(0.99);
        constexpr double compile_time_k = math::arccos(-0.99);

        // compile time tests
        ASSERT_TRUE(math::equals(math::pi_2, compile_time_a));
        ASSERT_TRUE(math::equals(0, compile_time_b));
        ASSERT_TRUE(math::equals(math::pi, compile_time_c));
        ASSERT_TRUE(math::equals(1.47063, compile_time_d));
        ASSERT_TRUE(math::equals(1.98230, compile_time_e));
        ASSERT_TRUE(math::equals(0.66747, compile_time_f));
        ASSERT_TRUE(math::equals(1.36944, compile_time_g));
        ASSERT_TRUE(math::equals(0.79540, compile_time_h));
        ASSERT_TRUE(math::equals(0.45106, compile_time_i));
        ASSERT_TRUE(math::equals(0.14341, compile_time_j));
        ASSERT_TRUE(math::equals(2.99818, compile_time_k));

        ASSERT_TRUE(math::equals(math::pi_2, math::arccos(0)));
        ASSERT_TRUE(math::equals(0, math::arccos(1)));
        ASSERT_TRUE(math::equals(math::pi, math::arccos(-1)));
        ASSERT_TRUE(math::equals(1.47062, math::arccos(0.1)));
        ASSERT_TRUE(math::equals(1.98231, math::arccos(-0.4)));
        ASSERT_TRUE(math::equals(0.66745, math::arccos(math::pi_4)));
        ASSERT_TRUE(math::equals(1.36944, math::arccos(0.2)));
        ASSERT_TRUE(math::equals(0.79539, math::arccos(0.7)));
        ASSERT_TRUE(math::equals(0.45103, math::arccos(0.9)));
        ASSERT_TRUE(math::equals(0.14154, math::arccos(0.99)));
        ASSERT_TRUE(math::equals(3.00005, math::arccos(-0.99)));
    }

    TEST(math_test, arccos_exception_test)
    {
        ASSERT_THROW(math::arccos(1.0001), exception::out_of_range_exception);
        ASSERT_THROW(math::arccos(-1.0001), exception::out_of_range_exception);
        ASSERT_THROW(math::arccos(-20), exception::out_of_range_exception);
        ASSERT_THROW(math::arccos(20), exception::out_of_range_exception);
        ASSERT_THROW(math::arccos(5), exception::out_of_range_exception);
        ASSERT_THROW(math::arccos(-199), exception::out_of_range_exception);
        ASSERT_THROW(math::arccos(-INFINITY), exception::out_of_range_exception);
        ASSERT_THROW(math::arccos(INFINITY), exception::out_of_range_exception);
        ASSERT_THROW(math::arccos(NAN), exception::out_of_range_exception);
        
        ASSERT_NO_THROW(math::arccos(1));
        ASSERT_NO_THROW(math::arccos(-1));
    }

    TEST(math_test, arcsin_exception_test)
    {
        ASSERT_THROW(math::arcsin(1.0001), exception::out_of_range_exception);
        ASSERT_THROW(math::arcsin(-1.0001), exception::out_of_range_exception);
        ASSERT_THROW(math::arcsin(-20), exception::out_of_range_exception);
        ASSERT_THROW(math::arcsin(20), exception::out_of_range_exception);
        ASSERT_THROW(math::arcsin(5), exception::out_of_range_exception);
        ASSERT_THROW(math::arcsin(-199), exception::out_of_range_exception);
        ASSERT_THROW(math::arcsin(-INFINITY), exception::out_of_range_exception);
        ASSERT_THROW(math::arcsin(INFINITY), exception::out_of_range_exception);
        ASSERT_THROW(math::arcsin(NAN), exception::out_of_range_exception);
        
        ASSERT_NO_THROW(math::arcsin(1));
        ASSERT_NO_THROW(math::arcsin(-1));
    }

    TEST(math_test, arctan_test)
    {
        constexpr double compile_time_a = math::arctan(0);
        constexpr double compile_time_b = math::arctan(1);
        constexpr double compile_time_c = math::arctan(-1);
        constexpr double compile_time_d = math::arctan(0.1);
        constexpr double compile_time_e = math::arctan(-0.4);
        constexpr double compile_time_f = math::arctan(math::pi_4);
        constexpr double compile_time_g = math::arctan(0.2);
        constexpr double compile_time_h = math::arctan(0.7);
        constexpr double compile_time_i = math::arctan(0.9);
        constexpr double compile_time_j = math::arctan(0.99);
        constexpr double compile_time_k = math::arctan(-0.99);
        constexpr double compile_time_l = math::arctan(500);

        // compile time tests
        ASSERT_TRUE(math::equals(0, compile_time_a));
        ASSERT_TRUE(math::equals(0.78539, compile_time_b));
        ASSERT_TRUE(math::equals(-0.78539, compile_time_c));
        ASSERT_TRUE(math::equals(0.09967, compile_time_d));
        ASSERT_TRUE(math::equals(-0.38051, compile_time_e));
        ASSERT_TRUE(math::equals(0.66577, compile_time_f));
        ASSERT_TRUE(math::equals(0.19739, compile_time_g));
        ASSERT_TRUE(math::equals(0.61072, compile_time_h));
        ASSERT_TRUE(math::equals(0.73281, compile_time_i));
        ASSERT_TRUE(math::equals(0.78003, compile_time_j));
        ASSERT_TRUE(math::equals(-0.78003, compile_time_k));
        ASSERT_TRUE(math::equals(1.56879, compile_time_l));

        ASSERT_TRUE(math::equals(0, math::arctan(0)));
        ASSERT_TRUE(math::equals(0.78539, math::arctan(1)));
        ASSERT_TRUE(math::equals(-0.78539, math::arctan(-1)));
        ASSERT_TRUE(math::equals(0.09967, math::arctan(0.1)));
        ASSERT_TRUE(math::equals(-0.38051, math::arctan(-0.4)));
        ASSERT_TRUE(math::equals(0.66577, math::arctan(math::pi_4)));
        ASSERT_TRUE(math::equals(0.19739, math::arctan(0.2)));
        ASSERT_TRUE(math::equals(0.61072, math::arctan(0.7)));
        ASSERT_TRUE(math::equals(0.73281, math::arctan(0.9)));
        ASSERT_TRUE(math::equals(0.78037, math::arctan(0.99)));
        ASSERT_TRUE(math::equals(-0.78037, math::arctan(-0.99)));
        ASSERT_TRUE(math::equals(1.56879, math::arctan(500)));

        // infinity and nan tests
        constexpr double compile_time_nan = math::arctan(NAN);
        constexpr double compile_time_inf = math::arctan(INFINITY);
        constexpr double compile_time_ninf = math::arctan(-INFINITY);
        ASSERT_TRUE(std::isnan(compile_time_nan));
        ASSERT_TRUE(math::equals(math::pi_2, compile_time_inf));
        ASSERT_TRUE(math::equals(-math::pi_2, compile_time_ninf));

        ASSERT_TRUE(std::isnan(math::arctan(NAN)));
        ASSERT_TRUE(math::equals(math::arctan(INFINITY),math::pi_2));
        ASSERT_TRUE(math::equals(math::arctan(-INFINITY),-math::pi_2));
    }

    TEST(math_test, factorial)
    {
        constexpr double compile_time_a = math::factorial(0);
        constexpr double compile_time_b = math::factorial(3);
        constexpr double compile_time_c = math::factorial(10);

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
