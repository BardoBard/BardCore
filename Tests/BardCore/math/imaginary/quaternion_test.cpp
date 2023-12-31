#include "pch.h"
#include "BardCore/math/imaginary/quaternion.h"

namespace testing
{
    TEST(quaternion_test, multiplication_test)
    {
        constexpr quaternion quaternion1 = {1, 2, 3, 4};
        constexpr quaternion quaternion2 = {5, 6, 7, 8};

        constexpr quaternion result = quaternion1.multiply(quaternion2);

        ASSERT_EQ(-60.f, result.get_real());
        ASSERT_EQ(12.f, result.get_i());
        ASSERT_EQ(30.f, result.get_j());
        ASSERT_EQ(24.f, result.get_k());
    }

    TEST(quaternion_test, multiplication2_test)
    {
        constexpr quaternion quaternion1 = {-56, 0, 2, 1};
        constexpr quaternion quaternion2 = {9, -3, 0, 9};

        constexpr quaternion result = quaternion1.multiply(quaternion2);

        ASSERT_EQ(-513.f, result.get_real());
        ASSERT_EQ(186.f, result.get_i());
        ASSERT_EQ(15.f, result.get_j());
        ASSERT_EQ(-489.f, result.get_k());
    }

    TEST(quaternion_test, rotation_point_vector_theta_test)
    {
        constexpr vector3d vector = {1, 2, 3};
        constexpr point3d point = {4, 5, 6};
        constexpr float theta = 90.f;

        const point3d result = quaternion::rotate(point, vector, theta);


        ASSERT_NEAR(3.087f, result.x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(2.968f, result.y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(7.659f, result.z, ROUND_THREE_DECIMALS);
    }

    TEST(quaternion_test, rotation_point_vector_theta_test2)
    {
        constexpr vector3d vector = {1, 2, 3};
        constexpr point3d point = {4, 5, 6};
        constexpr float theta = 180.f;

        const point3d result = quaternion::rotate(point, vector, theta);

        ASSERT_NEAR(0.571f, result.x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(4.143f, result.y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(7.714f, result.z, ROUND_THREE_DECIMALS);
    }

    TEST(quaternion_test, rotation_point_vector_zero_theta_test)
    {
        constexpr vector3d vector = {1, 2, 3};
        constexpr point3d point = {4, 5, 6};
        constexpr float theta = 0;

        constexpr point3d result = quaternion::rotate(point, vector, theta);


        ASSERT_NEAR(4, result.x, ROUND_EPSILON);
        ASSERT_NEAR(5, result.y, ROUND_EPSILON);
        ASSERT_NEAR(6, result.z, ROUND_EPSILON);
    }

    TEST(quaternion_test, rotation_vector_theta_test)
    {
        constexpr vector3d rotation_vector = {1, 2, 3};
        constexpr vector3d vector = {4, 5, 6};
        constexpr float theta = 270.f;

        constexpr vector3d result = quaternion::rotate(vector, rotation_vector, theta);

        ASSERT_NEAR(1.484f, result.x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(6.175f, result.y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(6.055f, result.z, ROUND_THREE_DECIMALS);
    }

    TEST(quaternion_test, rotation_vector_theta_test2)
    {
        constexpr vector3d rotation_vector = {1, 2, 3};
        constexpr vector3d vector = {4, 5, 6};
        constexpr float theta = 360.f;

        constexpr vector3d result = quaternion::rotate(vector, rotation_vector, theta);

        ASSERT_NEAR(4, result.x, ROUND_ONE_DECIMALS);
        ASSERT_NEAR(5, result.y, ROUND_ONE_DECIMALS);
        ASSERT_NEAR(6, result.z, ROUND_ONE_DECIMALS);
    }

    //test zero theta
    TEST(quaternion_test, rotation_vector_zero_theta_test2)
    {
        constexpr vector3d rotation_vector = {1, 2, 3};
        constexpr vector3d vector = {4, 5, 6};
        constexpr float theta = 0;

        constexpr vector3d result = quaternion::rotate(vector, rotation_vector, theta);

        ASSERT_NEAR(4, result.x, ROUND_EPSILON);
        ASSERT_NEAR(5, result.y, ROUND_EPSILON);
        ASSERT_NEAR(6, result.z, ROUND_EPSILON);
    }

    //test negative theta
    TEST(quaternion_test, rotation_vector_negative_theta_test)
    {
        constexpr vector3d rotation_vector = {1, 2, 3};
        constexpr vector3d vector = {4, 5, 6};
        constexpr float theta = -90.f;

        constexpr vector3d result = quaternion::rotate(vector, rotation_vector, theta);

        ASSERT_NEAR(1.484f, result.x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(6.175f, result.y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(6.055f, result.z, ROUND_THREE_DECIMALS);
    }

    //test exception
    TEST(quaternion_test, rotation_exception_test)
    {
        constexpr vector3d rotation_vector = {0, 0, 0};
        constexpr vector3d vector = {4, 5, 6};
        constexpr float theta = 90.f;

        ASSERT_THROW(quaternion::rotate(vector, rotation_vector, theta), exception::zero_exception);
    }

    //test exception
    TEST(quaternion_test, rotation_exception_test2)
    {
        constexpr vector3d rotation_vector = {1, 2, 3};
        constexpr vector3d vector = {0, 0, 0};
        constexpr float theta = 90.f;

        ASSERT_THROW(quaternion::rotate(vector, rotation_vector, theta), exception::zero_exception);
    }
    
    //test conjugate
    TEST(quaternion_test, conjugate_test)
    {
        constexpr quaternion quaternion1 = {1, 2, 3, 4};

        constexpr quaternion result = quaternion1.conjugate();

        ASSERT_NEAR(1.f, result.get_real(), ROUND_EPSILON);
        ASSERT_NEAR(-2.f, result.get_i(), ROUND_EPSILON);
        ASSERT_NEAR(-3.f, result.get_j(), ROUND_EPSILON);
        ASSERT_NEAR(-4.f, result.get_k(), ROUND_EPSILON);
    }

    //test conjugate
    TEST(quaternion_test, conjugate_test2)
    {
        constexpr quaternion quaternion1 = {0, 0, 0, 0};

        constexpr quaternion result = quaternion1.conjugate();

        ASSERT_NEAR(0.f, result.get_real(), ROUND_EPSILON);
        ASSERT_NEAR(0.f, result.get_i(), ROUND_EPSILON);
        ASSERT_NEAR(0.f, result.get_j(), ROUND_EPSILON);
        ASSERT_NEAR(0.f, result.get_k(), ROUND_EPSILON);
    }

    //test mirror
    TEST(quaternion_test, mirror_test)
    {
        constexpr vector3d mirror_vector = {1, 2, 3};
        constexpr point3d point = {4, 5, 6};

        constexpr point3d result = quaternion::mirror(point, mirror_vector);

        ASSERT_NEAR(0.57f, result.x, ROUND_TWO_DECIMALS);
        ASSERT_NEAR(4.14f, result.y, ROUND_TWO_DECIMALS);
        ASSERT_NEAR(7.71f, result.z, ROUND_TWO_DECIMALS);
    }

    //test mirror
    TEST(quaternion_test, mirror_test2)
    {
        constexpr vector3d mirror_vector = {0, -2, -1};
        constexpr point3d point = {-9, 8, -7};

        constexpr point3d result = quaternion::mirror(point, mirror_vector);

        ASSERT_NEAR(9.f, result.x, ROUND_EPSILON);
        ASSERT_NEAR(-0.8f, result.y, ROUND_ONE_DECIMALS);
        ASSERT_NEAR(10.6f, result.z, ROUND_ONE_DECIMALS);
    }

    //test mirror zero
    TEST(quaternion_test, mirror_zero_test)
    {
        constexpr vector3d mirror_vector = {0, 0, 0};
        constexpr point3d point = {4, 5, 6};

        ASSERT_THROW(quaternion::mirror(point, mirror_vector), exception::zero_exception);
    }

    //test mirror zero
    TEST(quaternion_test, mirror_zero_test2)
    {
        constexpr vector3d mirror_vector = {1, 2, 3};
        constexpr point3d point = {0, 0, 0};

        ASSERT_THROW(quaternion::mirror(point, mirror_vector), exception::zero_exception);
    }
} // namespace testing
