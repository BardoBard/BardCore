#include "pch.h"
#include "BardCore/math/math.h"

namespace testing
{
    //test 90 degrees
    TEST(math_test, radians_to_degrees_test)
    {
        constexpr float degrees = math::radians_to_degrees(1.570f);

        ASSERT_NEAR(90.f, degrees, ROUND_ONE_DECIMALS);
    }

    //test zero
    TEST(math_test, radians_to_degrees_zero_test)
    {
        constexpr float radians = math::degrees_to_radians(0.f);

        ASSERT_NEAR(0.0f, radians, ROUND_ONE_DECIMALS);
    }

    //test negative theta
    TEST(math_test, radians_to_degrees_negative_test)
    {
        constexpr float degrees = math::radians_to_degrees(-1.570f);

        ASSERT_NEAR(-90.0f, degrees, ROUND_ONE_DECIMALS);
    }

    //test 450 degrees
    TEST(math_test, radians_to_degrees_450_test)
    {
        constexpr float degrees = math::radians_to_degrees(7.854f);

        ASSERT_NEAR(450.0f, degrees, ROUND_ONE_DECIMALS);
    }

    //test 90 degrees
    TEST(math_test, degrees_to_radians_test)
    {
        constexpr float radians = math::degrees_to_radians(90.f);

        ASSERT_NEAR(1.57f, radians, ROUND_TWO_DECIMALS);
    }

    //test zero
    TEST(math_test, degrees_to_radians_zero_test)
    {
        constexpr float radians = math::degrees_to_radians(0.f);

        ASSERT_NEAR(0.0f, radians, ROUND_ONE_DECIMALS);
    }

    //test negative theta
    TEST(math_test, degrees_to_radians_negative_test)
    {
        constexpr float radians = math::degrees_to_radians(-90.f);

        ASSERT_NEAR(-1.57f, radians, ROUND_TWO_DECIMALS);
    }

    //test 450 degrees
    TEST(math_test, degrees_to_radians_450_test)
    {
        constexpr float radians = math::degrees_to_radians(450.f);

        ASSERT_NEAR(7.85f, radians, ROUND_TWO_DECIMALS);
    }

    //test sqrt constexpr
    TEST(math_test, sqrt_test)
    {
        constexpr float result = math::sqrt(100);
        constexpr float result2 = math::sqrt(52);
        constexpr float result3 = math::sqrt(10000000);

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

    TEST(math_test, fequals_test)
    {
        ASSERT_TRUE(math::fequals(1.f, 1));
        ASSERT_FALSE(math::fequals(1.f, 1.001f));
        ASSERT_FALSE(math::fequals(1.f, 1.0001f));
        ASSERT_TRUE(math::fequals(1.f, 1.00001f));
        ASSERT_TRUE(math::fequals(100234.f, 100234.f));
        ASSERT_TRUE(math::fequals(143256524.f, 143256524.f));

        //infinity and nan tests
        ASSERT_FALSE(math::fequals(NAN, NAN));
        ASSERT_FALSE(math::fequals(INFINITY, NAN));
        ASSERT_FALSE(math::fequals(NAN, INFINITY));
        ASSERT_FALSE(math::fequals(INFINITY, INFINITY));
        ASSERT_FALSE(math::fequals(-INFINITY, -INFINITY));
        ASSERT_FALSE(math::fequals(INFINITY, -INFINITY));
        ASSERT_FALSE(math::fequals(214, INFINITY));
        ASSERT_FALSE(math::fequals(-214, -INFINITY));
        ASSERT_FALSE(math::fequals(INFINITY, 214));
        ASSERT_FALSE(math::fequals(-INFINITY, -214));
    }

    TEST(math_test, fgreater_than_test)
    {
        ASSERT_FALSE(math::fgreater_than(1.f, 2));
        ASSERT_FALSE(math::fgreater_than(1.f, 1.0001f));
        ASSERT_FALSE(math::fgreater_than(1.f, 1.000001f));
        ASSERT_TRUE(math::fgreater_than(1.f, -1.1f));
        ASSERT_FALSE(math::fgreater_than(-1.f, 1));
        ASSERT_FALSE(math::fgreater_than(-25, 0.99999f));
        ASSERT_TRUE(math::fgreater_than(76, 0.9999f));
        ASSERT_TRUE(math::fgreater_than(1, 0.999f));
        ASSERT_FALSE(math::fgreater_than(-1, -0.999f));

        //infinity and nan tests
        ASSERT_FALSE(math::fgreater_than(INFINITY, NAN));
        ASSERT_FALSE(math::fgreater_than(NAN, INFINITY));
        ASSERT_FALSE(math::fgreater_than(INFINITY, INFINITY));
        ASSERT_FALSE(math::fgreater_than(NAN, NAN));

        ASSERT_FALSE(math::fgreater_than(-INFINITY, INFINITY));
        ASSERT_FALSE(math::fgreater_than(100, INFINITY));
        ASSERT_FALSE(math::fgreater_than(-543.53f, INFINITY));
        ASSERT_FALSE(math::fgreater_than(-INFINITY, 100));
    }

    TEST(test_math, fless_than_test)
    {
        ASSERT_TRUE(math::fless_than(1.f, 2));
        ASSERT_TRUE(math::fless_than(1.f, 1.0001f));
        ASSERT_FALSE(math::fless_than(1.f, 1.000001f));
        ASSERT_FALSE(math::fless_than(1.f, -1.1f));
        ASSERT_TRUE(math::fless_than(-1.f, 1));
        ASSERT_TRUE(math::fless_than(-25, 0.99999f));
        ASSERT_FALSE(math::fless_than(76, 0.9999f));
        ASSERT_FALSE(math::fless_than(1, 0.999f));
        ASSERT_TRUE(math::fless_than(-1, -0.999f));

        //infinity and nan tests
        ASSERT_FALSE(math::fless_than(INFINITY, NAN));
        ASSERT_FALSE(math::fless_than(NAN, INFINITY));
        ASSERT_FALSE(math::fless_than(INFINITY, INFINITY));
        ASSERT_FALSE(math::fless_than(NAN, NAN));

        ASSERT_TRUE(math::fless_than(-INFINITY, INFINITY));
        ASSERT_TRUE(math::fless_than(100, INFINITY));
        ASSERT_TRUE(math::fless_than(-543.53f, INFINITY));
        ASSERT_TRUE(math::fless_than(-INFINITY, 100));
    }

    TEST(math_test, sign_test)
    {
        ASSERT_EQ(1, math::fsign(1));
        ASSERT_EQ(0, math::fsign(0));
        ASSERT_EQ(-1, math::fsign(-1));
        ASSERT_EQ(-1, math::fsign(-0.4f));
        ASSERT_EQ(1, math::fsign(INFINITY));
        ASSERT_EQ(-1, math::fsign(-INFINITY));
        ASSERT_EQ(1, math::fsign(NAN));
    }

    TEST(math_test, abs_test)
    {
        constexpr float a = 1;
        constexpr float b = 0;
        constexpr float c = -1;
        constexpr float d = -0.4f;
        constexpr float e = -1.2f;
        constexpr float f = -42;

        ASSERT_TRUE(math::fequals(1, math::fabs(a)));
        ASSERT_TRUE(math::fequals(0, math::fabs(b)));
        ASSERT_TRUE(math::fequals(1, math::fabs(c)));
        ASSERT_TRUE(math::fequals(0.4f, math::fabs(d)));
        ASSERT_TRUE(math::fequals(1.2f, math::fabs(e)));
        ASSERT_TRUE(math::fequals(42, math::fabs(f)));
    }

    TEST(math_test, fmod_test)
    {
        constexpr float compile_time_a = math::fmod(5.3f, 2);
        constexpr float compile_time_b = math::fmod(18.5f, 4.2f);
        constexpr float compile_time_c = math::fmod(0, 1.2f);
        constexpr float compile_time_e = math::fmod(1.2f, 0.1f);
        constexpr float compile_time_f = math::fmod(1.2f, -0.1f);
        constexpr float compile_time_g = math::fmod(-1.2f, 0.1f);

        ASSERT_TRUE(math::fequals(1.3f, compile_time_a));
        ASSERT_TRUE(math::fequals(1.7f, compile_time_b));
        ASSERT_TRUE(math::fequals(0, compile_time_c));
        ASSERT_TRUE(math::fequals(0, compile_time_e));
        ASSERT_TRUE(math::fequals(0, compile_time_f));
        ASSERT_TRUE(math::fequals(0, compile_time_g));

        ASSERT_THROW(math::fmod(1, 0), exception::zero_exception);
        ASSERT_THROW(math::fmod(6, -0), exception::zero_exception);
        ASSERT_THROW(math::fmod(-12, 0), exception::zero_exception);
    }

    TEST(math_test, fexp_test)
    {
        constexpr float compile_time_a = math::fexp(0);
        constexpr float compile_time_b = math::fexp(1);
        constexpr float compile_time_c = math::fexp(-1);
        constexpr float compile_time_d = math::fexp(6);
        constexpr float compile_time_e = math::fexp(-6);
        constexpr float compile_time_f = math::fexp(10.6f);

        // compile time tests
        ASSERT_TRUE(math::fequals(1, compile_time_a));
        ASSERT_TRUE(math::fequals(2.71828f, compile_time_b));
        ASSERT_TRUE(math::fequals(0.36788f, compile_time_c));
        ASSERT_TRUE(math::fequals(403.42868f, compile_time_d));
        ASSERT_TRUE(math::fequals(0.00247f, compile_time_e));
        ASSERT_TRUE(math::fequals(40134.8555f, compile_time_f));

        // runtime tests
        ASSERT_TRUE(math::fequals(1, math::fexp(0)));
        ASSERT_TRUE(math::fequals(2.71828f, math::fexp(1)));
        ASSERT_TRUE(math::fequals(0.36788f, math::fexp(-1)));
        ASSERT_TRUE(math::fequals(403.42879f, math::fexp(6)));
        ASSERT_TRUE(math::fequals(0.00247f, math::fexp(-6)));
        ASSERT_TRUE(math::fequals(40134.8516f, math::fexp(10.6)));
    }

    TEST(math_test, fsin)
    {
        constexpr float compile_time_a = math::fsin(0);
        constexpr float compile_time_b = math::fsin(1);
        constexpr float compile_time_c = math::fsin(-1);
        constexpr float compile_time_d = math::fsin(6);
        constexpr float compile_time_e = math::fsin(-6);
        constexpr float compile_time_f = math::fsin(10.6f);

        // compile time tests
        ASSERT_TRUE(math::fequals(0, compile_time_a));
        ASSERT_TRUE(math::fequals(0.84147f, compile_time_b));
        ASSERT_TRUE(math::fequals(-0.84147f, compile_time_c));
        ASSERT_TRUE(math::fequals(-0.27942f, compile_time_d));
        ASSERT_TRUE(math::fequals(0.27942f, compile_time_e));
        ASSERT_TRUE(math::fequals(-0.92277f, compile_time_f));

        // runtime tests
        ASSERT_TRUE(math::fequals(0, math::fsin(0)));
        ASSERT_TRUE(math::fequals(0.84147f, math::fsin(1)));
        ASSERT_TRUE(math::fequals(-0.84147f, math::fsin(-1)));
        ASSERT_TRUE(math::fequals(-0.27942f, math::fsin(6)));
        ASSERT_TRUE(math::fequals(0.27942f, math::fsin(-6)));
        ASSERT_TRUE(math::fequals(-0.92277f, math::fsin(10.6f)));
    }

    TEST(math_test, fcos)
    {
        constexpr float compile_time_a = math::fcos(0);
        constexpr float compile_time_b = math::fcos(1);
        constexpr float compile_time_c = math::fcos(-1);
        constexpr float compile_time_d = math::fcos(6);
        constexpr float compile_time_e = math::fcos(-6);
        constexpr float compile_time_f = math::fcos(10.6f);

        // compile time tests
        ASSERT_TRUE(math::fequals(1, compile_time_a));
        ASSERT_TRUE(math::fequals(0.54030f, compile_time_b));
        ASSERT_TRUE(math::fequals(0.54030f, compile_time_c));
        ASSERT_TRUE(math::fequals(0.96017f, compile_time_d));
        ASSERT_TRUE(math::fequals(0.96017f, compile_time_e));
        ASSERT_TRUE(math::fequals(-0.3852f, compile_time_f));

        // runtime tests
        ASSERT_TRUE(math::fequals(1, math::fcos(0)));
        ASSERT_TRUE(math::fequals(0.54030f, math::fcos(1)));
        ASSERT_TRUE(math::fequals(0.54030f, math::fcos(-1)));
        ASSERT_TRUE(math::fequals(0.96017f, math::fcos(6)));
        ASSERT_TRUE(math::fequals(0.96017f, math::fcos(-6)));
        ASSERT_TRUE(math::fequals(-0.38534f, math::fcos(10.6f)));

        // infinity and nan tests
        constexpr float compile_time_nan = math::fcos(NAN);
        constexpr float compile_time_inf = math::fcos(INFINITY);
        constexpr float compile_time_ninf = math::fcos(-INFINITY);
        ASSERT_TRUE(std::isnan(math::fcos(NAN)));
        ASSERT_TRUE(std::isnan(math::fcos(INFINITY)));
        ASSERT_TRUE(std::isnan(math::fcos(-INFINITY)));

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
        ASSERT_TRUE(math::fequals(1, compile_time_a));
        ASSERT_TRUE(math::fequals(6, compile_time_b));
        ASSERT_TRUE(math::fequals(3628800, compile_time_c));

        // runtime tests
        ASSERT_TRUE(math::fequals(1, math::factorial(0)));
        ASSERT_TRUE(math::fequals(6, math::factorial(3)));
        ASSERT_TRUE(math::fequals(3628800, math::factorial(10)));
    }
} // namespace testing
