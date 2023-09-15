#include "pch.h"

namespace testing
{
    //test angle
    TEST(vector3d_test, angle_test)
    {
        const vector3d vector1 = {1, 2, 3};
        const vector3d vector2 = {4, 5, 6};

        const float result = vector1.angle(vector2);

        ASSERT_NEAR(12.94f, result, ROUND_TWO_DECIMALS);
    }

    //test angle with zero
    TEST(vector3d_test, angle_zero_test)
    {
        const vector3d vector1 = {1, 2, 3};
        const vector3d vector2 = {0, 0, 0};

        ASSERT_ANY_THROW(vector1.angle(vector2));
    }

    //test angle with same vector
    TEST(vector3d_test, angle_same_vector_test)
    {
        const vector3d vector1 = {1, 2, 3};
        const vector3d vector2 = {1, 2, 3};
        ASSERT_NO_THROW(vector1.angle(vector2));
    }

    //test angle with same object
    TEST(vector3d_test, angle_same_object_test)
    {
        const vector3d vector1 = {1, 2, 3};
        ASSERT_ANY_THROW(vector1.angle(vector1));
    }

    //test dot
    TEST(vector3d_test, dot_test)
    {
        const vector3d vector1 = {1, 2, 3};
        const vector3d vector2 = {4, 5, 6};

        const float result = vector1.dot(vector2);

        ASSERT_EQ(32.f, result);
    }

    //test dot with negative result
    TEST(vector3d_test, dot_negative_test)
    {
        const vector3d vector1 = {1, 2, 3};
        const vector3d vector2 = {-4, -5, -6};

        const float result = vector2.dot(vector1);

        ASSERT_EQ(-32.f, result);
    }

    //test dot with zero
    TEST(vector3d_test, dot_zero_test)
    {
        const vector3d vector1 = {1, 2, 3};
        const vector3d vector2 = {0, 0, 0};

        const float result = vector1.dot(vector2);

        ASSERT_EQ(0.f, result);
    }

    //lenght test
    TEST(vector3d_test, length_test)
    {
        const vector3d vector1 = {1, 2, 3};

        const float result = vector1.length();

        ASSERT_NEAR(3.742f, result, ROUND_THREE_DECIMALS);
    }

    //test length with negative input
    TEST(vector3d_test, length_negative_test)
    {
        const vector3d vector1 = {-1, -2, -3};

        const float result = vector1.length();

        ASSERT_NEAR(3.742f, result, ROUND_THREE_DECIMALS);
    }

    //test length with zero
    TEST(vector3d_test, length_zero_test)
    {
        const vector3d vector1 = {0, 0, 0};

        const float result = vector1.length();

        ASSERT_EQ(0.f, result);
    }


    //normalize test 1
    TEST(vector3d_test, normalize_test)
    {
        const vector3d vector1 = {3, 2, -1};

        const vector3d result = vector1.normalize();

        ASSERT_NEAR(0.802f, result.x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.535f, result.y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(-0.267f, result.z, ROUND_THREE_DECIMALS);
    }

    //normalize test with negative input
    TEST(vector3d_test, normalize_negative_test)
    {
        const vector3d vector1 = {-3, -2, 1};

        const vector3d result = vector1.normalize();

        ASSERT_NEAR(-0.802f, result.x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(-0.535f, result.y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.267f, result.z, ROUND_THREE_DECIMALS);
    }

    //normalize test 2
    TEST(vector3d_test, normalize2_test)
    {
        const vector3d vector1 = {-0.834f, -0.653f, -0.127f};

        const vector3d result = vector1.normalize();

        ASSERT_NEAR(-0.782f, result.x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(-0.612f, result.y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(-0.119f, result.z, ROUND_THREE_DECIMALS);
    }

    //normalize test with zero
    TEST(vector3d_test, normalize_zero_test)
    {
        const vector3d vector1 = {0, 0, 0};
        const auto result = vector1.normalize();

        ASSERT_EQ(0.f, result.x);
        ASSERT_EQ(0.f, result.y);
        ASSERT_EQ(0.f, result.z);
    }

    //all tests
    TEST(vector3d_test, all_test)
    {
        const vector3d vector1 = {45, 32, 78}; //original vector 
        const vector3d vector2 = {14, 26, 52}; //used for angle calculations
        const vector3d vector3 = {12, 76, 51}; //used for dot product
        const vector3d vector4 = {11, 96, 47}; //used for normalization

        //angle
        float result = vector1.angle(vector2);
        ASSERT_NEAR(15.09f, result, ROUND_TWO_DECIMALS);

        //dot
        result = vector1.dot(vector3);
        ASSERT_EQ(6950.f, result);

        //length
        result = vector1.length();
        ASSERT_NEAR(95.567f, result, ROUND_THREE_DECIMALS);

        //length
        result = vector3.length();
        ASSERT_NEAR(92.309f, result, ROUND_THREE_DECIMALS);

        //normalize
        const vector3d result_normalize = vector1.normalize();

        ASSERT_NEAR(0.471f, result_normalize.x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.335f, result_normalize.y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.816f, result_normalize.z, ROUND_THREE_DECIMALS);
    }
}
