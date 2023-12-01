#ifndef BARDCORE_VECTOR3D_H
#define BARDCORE_VECTOR3D_H

#include "dimension3.h"
#include "math.h"

namespace bardcore
{
    class vector3d : public dimension3<vector3d>
    {
    public:
        using dimension3::dimension3; // inherit constructors

        /**
         * \brief reduce the 3D vector from its value to a value between -1 and 1 with length 1
         * \throws zero_exception if length of vector is zero
         * \return normalized vector
         */
        constexpr NODISCARD vector3d normalize() const
        {
            const float l = this->length();

            if (l == 0.f)
                throw zero_exception("vector length must not be zero");
            
            return *this / l;
        }

        /// \brief calculates the cross product of this and another vector
        /// \note formula cross product: a x b = (a_y * b_z - a_z * b_y, a_z * b_x - a_x * b_z, a_x * b_y - a_y * b_x)
        /// \param vector other vector 
        /// \return cross product of this and other vector
        constexpr NODISCARD vector3d cross(const vector3d& vector) const noexcept
        {
            return {
                y * vector.z - z * vector.y,
                z * vector.x - x * vector.z,
                x * vector.y - y * vector.x
            };
        }

        /// \brief calculates the dot product of this and another vector
        /// \note formula dot product: a . b = Σ a_i * b_i
        /// \param vector other vector
        /// \return dot product of this and other vector
        constexpr NODISCARD float dot(const vector3d& vector) const noexcept
        {
            return x * vector.x + y * vector.y + z * vector.z;
        }

        /// \brief calculates the length of the vector
        /// \return length of vector
        constexpr NODISCARD float length() const noexcept
        {
            return math::sqrt(x * x + y * y + z * z);
        }

        /// \brief calculates the angle between this and another vector
        /// \throws zero_exception if length of this or other vector is zero
        /// \note this method is not constexpr because of the std::acos function, perhaps implement own at some point
        /// \param vector other vector
        /// \return angle between this and other vector
        NODISCARD float angle(const vector3d& vector) const
        {
            const float l = length();
            const float vector_l = vector.length();

            if (this == &vector)
                throw std::invalid_argument("vectors mustn't be the same");

            if (l == 0.f || vector_l == 0.f)
                throw zero_exception("vector length must not be zero");

            return math::get_degrees_from_radians(std::acos(dot(vector) / (l * vector_l)));
        }
    };
} // namespace bardcore
#endif //BARDCORE_VECTOR3D_H
