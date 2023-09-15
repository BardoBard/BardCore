#ifndef BARDCORE_VECTOR3D_H
#define BARDCORE_VECTOR3D_H

#include "BardCore/dimension3.h"
#include "BardCore/math.h"

namespace bardcore
{
    class vector3d : public dimension3<vector3d>
    {
    public:
        explicit vector3d(const dimension3& other): dimension3(other)
        {
        }

        explicit vector3d(dimension3&& other): dimension3(other)
        {
        }

        vector3d(const float x, const float y, const float z): dimension3(x, y, z)
        {
        }

        template <typename Derived>
        explicit vector3d(const dimension3<Derived>& other) : dimension3(other)
        {
        }


        /**
        * reduce the 3D vector from its value to a value between -1 and 1 with length 1
        */
        NODISCARD vector3d normalize() const
        {
            const float l = this->length();


            return *this / l;
        }

        /**
         * calculates cross product from this vector and another one
         *
         * @param vector1 x
         */
        NODISCARD vector3d cross(const vector3d& vector1) const
        {
            return {
                y * vector1.z - z * vector1.y,
                z * vector1.x - x * vector1.z,
                x * vector1.y - y * vector1.x
            };
        }

        /**
        * calculates dot product from this and another 3D vector
        *
        * @param vector other vector to perform the dot product with
        * @return dot product of this and second vector
        */
        NODISCARD float dot(const vector3d& vector) const
        {
            return {x * vector.x + y * vector.y + z * vector.z};
        }

        /**
         * calculates length of current vector
         *
         * @return length
         */
        NODISCARD float length() const
        {
            return {std::sqrt(x * x + y * y + z * z)};
        }

        /**
         * returns angle in degrees
         *
         * @param vector other vector to perform the angle with
         * @return angle of vector (in degrees)
         */
        NODISCARD float angle(const vector3d& vector) const
        {
            const float l = length();
            const float vector_l = vector.length();

            if (this == &vector)
                throw std::invalid_argument("vectors mustn't be the same");

            if (l == 0 || vector_l == 0)
                throw std::invalid_argument("vector length must not be zero");

            return math::get_degrees_from_radians(std::acos(dot(vector) / (l * vector_l)));
        }
    };
}
#endif //BARDCORE_VECTOR3D_H
