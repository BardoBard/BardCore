#ifndef BARDCORE_VECTOR3D_H
#define BARDCORE_VECTOR3D_H

#include "BardCore/interfaces/dimension3.h"
#include "BardCore/math/math.h"

namespace bardcore
{
    /**
     * \brief 3D vector, not the traditional kind, that'd be a ray, this is a vector from the origin to a point
     * \note inherits from dimension3
     * \note this class is also constexpr
     */
    class vector3d : public dimension3<vector3d>
    {
    public:
        using dimension3::dimension3; // inherit constructors

        /**
         * \brief reduce the 3D vector from its value to a value between -1 and 1 with length 1
         * \throws zero_exception if length of vector is zero
         * \return normalized vector
         */
        NODISCARD constexpr vector3d normalize() const
        {
            const float l = this->length();

            if (l == 0.f)
                throw exception::zero_exception("vector length must not be zero");

            return *this / l;
        }

        /**
         * \brief calculates the cross product of this and another vector
         * \note formula cross product: a x b = (a_y * b_z - a_z * b_y, a_z * b_x - a_x * b_z, a_x * b_y - a_y * b_x)
         * \param vector other vector 
         * \return cross product of this and other vector
         */
        NODISCARD constexpr vector3d cross(const vector3d& vector) const noexcept
        {
            return {
                y * vector.z - z * vector.y,
                z * vector.x - x * vector.z,
                x * vector.y - y * vector.x
            };
        }
        
        /**
         * \brief calculates the dot product of this and another vector
         * \note formula dot product: a . b = Σ a_i * b_i
         * \param vector other vector
         * \return dot product of this and other vector
         */
        NODISCARD constexpr float dot(const vector3d& vector) const noexcept
        {
            return x * vector.x + y * vector.y + z * vector.z;
        }
        
        /**
         * \brief calculates the length of the vector
         * \return length of vector
         */
        NODISCARD constexpr float length() const noexcept
        {
            return math::sqrt(length_squared());
        }
        
        /**
         * \brief calculates the length squared of the vector
         * \return length squared of vector
         */
        NODISCARD constexpr float length_squared() const noexcept
        {
            return x * x + y * y + z * z;
        }
        
        /**
         * \brief calculates the angle from -1 to 1 between this and another vector
         * \note -1 means the vectors are opposite, 1 means the vectors are the same
         * \note this method is way faster than calculating the degrees/radians
         * \throws same_object_exception if this and other vector are the same
         * \throws zero_exception if length of this or other vector is zero
         * \param vector other vector
         * \return -1 to 1 angle between this and other vector
         */
        NODISCARD constexpr float angle_dot(const vector3d& vector) const
        {
            if (this == &vector)
                throw exception::same_object_exception("vectors mustn't be the same");

            return this->normalize().dot(vector.normalize());
        }
                
        /**
         * \brief calculates the angle in radians between this and another vector
         * \note this method is not constexpr because of the std::acos function, perhaps implement own at some point
         * \throws same_object_exception if this and other vector are the same
         * \throws zero_exception if length of this or other vector is zero
         * \param vector other vector
         * \return angle in radians between this and other vector
         */
        NODISCARD float angle_radians(const vector3d& vector) const
        {
            return std::acos(angle_dot(vector));
        }
        
        /**
         * \brief calculates the angle in degrees between this and another vector
         * \note this method is not constexpr because of the std::acos function, perhaps implement own at some point
         * \throws same_object_exception if this and other vector are the same
         * \throws zero_exception if length of this or other vector is zero
         * \param vector other vector
         * \return angle in degrees between this and other vector
         */
        NODISCARD float angle_degrees(const vector3d& vector) const
        {
            return math::radians_to_degrees(angle_radians(vector));
        }
    };
} // namespace bardcore
#endif //BARDCORE_VECTOR3D_H
