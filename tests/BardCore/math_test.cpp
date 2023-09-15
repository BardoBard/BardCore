#include "pch.h"

namespace testing
{
    //test 90 degrees
    TEST(math_test, get_degrees_from_radians_test)
    {
        const float degrees = math::get_degrees_from_radians(1.570f);

        ASSERT_NEAR(90.f, degrees, ROUND_ONE_DECIMALS);
    }

    //test zero
    TEST(math_test, get_degrees_from_radians_zero_test)
    {
        const float radians = math::get_radians_from_degrees(0.f);

        ASSERT_NEAR(0.0f, radians, ROUND_ONE_DECIMALS);
    }

    //test negative theta
    TEST(math_test, get_degrees_from_radians_negative_test)
    {
        const float degrees = math::get_degrees_from_radians(-1.570f);

        ASSERT_NEAR(-90.0f, degrees, ROUND_ONE_DECIMALS);
    }

    //test 450 degrees
    TEST(math_test, get_degrees_from_radians_450_test)
    {
        const float degrees = math::get_degrees_from_radians(7.854f);

        ASSERT_NEAR(450.0f, degrees, ROUND_ONE_DECIMALS);
    }

    //test 90 degrees
    TEST(math_test, get_radians_from_degrees_test)
    {
        const float radians = math::get_radians_from_degrees(90.f);

        ASSERT_NEAR(1.57f, radians, ROUND_TWO_DECIMALS);
    }

    //test zero
    TEST(math_test, get_radians_from_degrees_zero_test)
    {
        const float radians = math::get_radians_from_degrees(0.f);

        ASSERT_NEAR(0.0f, radians, ROUND_ONE_DECIMALS);
    }

    //test negative theta
    TEST(math_test, get_radians_from_degrees_negative_test)
    {
        const float radians = math::get_radians_from_degrees(-90.f);

        ASSERT_NEAR(-1.57f, radians, ROUND_TWO_DECIMALS);
    }

    //test 450 degrees
    TEST(math_test, get_radians_from_degrees_450_test)
    {
        const float radians = math::get_radians_from_degrees(450.f);

        ASSERT_NEAR(7.85f, radians, ROUND_TWO_DECIMALS);
    }
};
