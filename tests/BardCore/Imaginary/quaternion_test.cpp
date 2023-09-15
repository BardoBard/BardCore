#include "pch.h"
//
// namespace testing
// {
//     TEST(quaternion_test, multiplication_test)
//     {
//         const quaternion quaternion1 = {1, 2, 3, 4};
//         const quaternion quaternion2 = {5, 6, 7, 8};
//
//         const quaternion result = quaternion1.multiply(quaternion2);
//
//         ASSERT_EQ(-60.f, result.get_real());
//         ASSERT_EQ(12.f, result.get_i());
//         ASSERT_EQ(30.f, result.get_j());
//         ASSERT_EQ(24.f, result.get_k());
//     }
//
//     TEST(quaternion_test, multiplication2_test)
//     {
//         const quaternion quaternion1 = {-56, 0, 2, 1};
//         const quaternion quaternion2 = {9, -3, 0, 9};
//
//         const quaternion result = quaternion1.multiply(quaternion2);
//
//         ASSERT_EQ(-513.f, result.get_real());
//         ASSERT_EQ(186.f, result.get_i());
//         ASSERT_EQ(15.f, result.get_j());
//         ASSERT_EQ(-489.f, result.get_k());
//     }
//
//     TEST(quaternion_test, rotation_point_vector_theta_test)
//     {
//         const vector3d vector = {1, 2, 3};
//         const point3d point = {4, 5, 6};
//         constexpr float theta = 90.f;
//
//         const point3d result = quaternion::rotation(point, vector, theta);
//
//
//         ASSERT_NEAR(3.087f, result.x, ROUND_THREE_DECIMALS);
//         ASSERT_NEAR(2.968f, result.y, ROUND_THREE_DECIMALS);
//         ASSERT_NEAR(7.659f, result.z, ROUND_THREE_DECIMALS);
//     }
//
//     TEST(quaternion_test, rotation_point_vector_theta_test2)
//     {
//         const vector3d vector = {1, 2, 3};
//         const point3d point = {4, 5, 6};
//         constexpr float theta = 180.f;
//
//         const point3d result = quaternion::rotation(point, vector, theta);
//
//         ASSERT_NEAR(0.571f, result.x, ROUND_THREE_DECIMALS);
//         ASSERT_NEAR(4.143f, result.y, ROUND_THREE_DECIMALS);
//         ASSERT_NEAR(7.714f, result.z, ROUND_THREE_DECIMALS);
//     }
//
//     TEST(quaternion_test, rotation_point_vector_zero_theta_test)
//     {
//         const vector3d vector = {1, 2, 3};
//         const point3d point = {4, 5, 6};
//         constexpr float theta = 0;
//
//         const point3d result = quaternion::rotation(point, vector, theta);
//
//
//         ASSERT_NEAR(4, result.x, ROUND_EPSILON);
//         ASSERT_NEAR(5, result.y, ROUND_EPSILON);
//         ASSERT_NEAR(6, result.z, ROUND_EPSILON);
//     }
//
//     TEST(quaternion_test, rotation_vector_vector_theta_test)
//     {
//         const vector3d rotation_vector = {1, 2, 3};
//         const vector3d vector = {4, 5, 6};
//         constexpr float theta = 270.f;
//
//         const vector3d result = quaternion::rotation(vector, rotation_vector, theta);
//
//         ASSERT_NEAR(1.484f, result.x, ROUND_THREE_DECIMALS);
//         ASSERT_NEAR(6.175f, result.y, ROUND_THREE_DECIMALS);
//         ASSERT_NEAR(6.055f, result.z, ROUND_THREE_DECIMALS);
//     }
//
//     TEST(quaternion_test, rotation_vector_vector_theta_test2)
//     {
//         const vector3d rotation_vector = {1, 2, 3};
//         const vector3d vector = {4, 5, 6};
//         constexpr float theta = 360.f;
//
//         const vector3d result = quaternion::rotation(vector, rotation_vector, theta);
//
//         ASSERT_NEAR(4, result.x, ROUND_ONE_DECIMALS);
//         ASSERT_NEAR(5, result.y, ROUND_ONE_DECIMALS);
//         ASSERT_NEAR(6, result.z, ROUND_ONE_DECIMALS);
//     }
//
//     TEST(quaternion_test, rotation_vector_vector_zero_theta_test2)
//     {
//         const vector3d rotation_vector = {1, 2, 3};
//         const vector3d vector = {4, 5, 6};
//         constexpr float theta = 0;
//
//         const vector3d result = quaternion::rotation(vector, rotation_vector, theta);
//
//         ASSERT_NEAR(4, result.x, ROUND_EPSILON);
//         ASSERT_NEAR(5, result.y, ROUND_EPSILON);
//         ASSERT_NEAR(6, result.z, ROUND_EPSILON);
//     }
//
//     //test negative theta
//     TEST(quaternion_test, rotation_vector_vector_negative_theta_test)
//     {
//         const vector3d rotation_vector = {1, 2, 3};
//         const vector3d vector = {4, 5, 6};
//         constexpr float theta = -90.f;
//
//         const vector3d result = quaternion::rotation(vector, rotation_vector, theta);
//
//         ASSERT_NEAR(1.484f, result.x, ROUND_THREE_DECIMALS);
//         ASSERT_NEAR(6.175f, result.y, ROUND_THREE_DECIMALS);
//         ASSERT_NEAR(6.055f, result.z, ROUND_THREE_DECIMALS);
//     }
//
//     //test conjugate
//     TEST(quaternion_test, conjugate_test)
//     {
//         const quaternion quaternion1 = {1, 2, 3, 4};
//
//         const quaternion result = quaternion1.conjugate();
//
//         ASSERT_NEAR(1.f, result.get_real(), ROUND_EPSILON);
//         ASSERT_NEAR(-2.f, result.get_i(), ROUND_EPSILON);
//         ASSERT_NEAR(-3.f, result.get_j(), ROUND_EPSILON);
//         ASSERT_NEAR(-4.f, result.get_k(), ROUND_EPSILON);
//     }
// };
