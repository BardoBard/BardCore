#pragma once

#include "BardCore/interfaces/dimension4.h"
#include "BardCore/math/math.h"
#include "BardCore/math/vector3d.h"

namespace bardcore
{
    /**
     * \brief quaternion is a 4D object, this quaternion class is pretty basic in the sense that it only supports the basic operations
     */
    class quaternion : public dimension4<quaternion>
    {
    private:
    public:
        using dimension4::dimension4; // inherit constructors

        NODISCARD constexpr double get_real() const noexcept { return x; }
        NODISCARD constexpr double get_i() const noexcept { return y; }
        NODISCARD constexpr double get_j() const noexcept { return z; }
        NODISCARD constexpr double get_k() const noexcept { return w; }

        /**
         * \brief default constructor with 0, 0, 0, 0
         */
        constexpr quaternion() : quaternion(0, 0, 0, 0)
        {
        }

        /**
         * \brief constructor for quaternion
         * \param real real
         * \param i i
         * \param j j
         * \param k k
         */
        constexpr quaternion(const double real, const double i, const double j, const double k)
        {
            x = real;
            y = i;
            z = j;
            w = k;
        }

        /**
         * \brief deprecated, use rotate_degrees/rotate_radians instead
         */
        template <typename T, ENABLE_IF_DERIVED(dimension3, T)>
        DEPRECATED("Use rotate_degrees/rotate_radians instead of this function.") NODISCARD constexpr static T rotate(
            const T& to_be_rotated_3d, const vector3d& rotation_vector, const double theta)
        {
            return rotate_radians(to_be_rotated_3d, rotation_vector, math::degrees_to_radians(theta));
        }

        /**
         * \brief calculates the rotation of a 3D object (to_be_rotated3d) around a given axis (rotation_vector) with a given angle (theta)
         * \throws zero_exception if length of to_be_rotated_3d is zero
         * \throws zero_exception if length of rotation_vector is zero
         * \tparam T an inherited class of dimension3, e.g. point3d, vector3d, ...
         * \param to_be_rotated_3d the 3D object that should be rotated
         * \param rotation_vector the axis around which the object should be rotated
         * \param theta the angle in degrees
         * \return rotated 3D object
         */
        template <typename T, ENABLE_IF_DERIVED(dimension3, T)>
        NODISCARD constexpr static T rotate_degrees(const T& to_be_rotated_3d, const vector3d& rotation_vector,
                                                    const double theta)
        {
            return rotate_radians(to_be_rotated_3d, rotation_vector, math::degrees_to_radians(theta));
        }

        /**
         * \brief calculates the rotation of a 3D object (to_be_rotated3d) around a given axis (rotation_vector) with a given angle (theta)
         * \throws zero_exception if length of to_be_rotated_3d is zero
         * \throws zero_exception if length of rotation_vector is zero
         * \tparam T an inherited class of dimension3, e.g. point3d, vector3d, ...
         * \param to_be_rotated_3d the 3D object that should be rotated
         * \param rotation_vector the axis around which the object should be rotated
         * \param theta the angle in radians
         * \return rotated 3D object
         */
        template <typename T, ENABLE_IF_DERIVED(dimension3, T)>
        NODISCARD constexpr static T rotate_radians(const T& to_be_rotated_3d, const vector3d& rotation_vector,
                                                    double theta)
        {
            if (to_be_rotated_3d == dimension3<T>::zero())
                throw exception::zero_exception("to_be_rotated_3d must not be (0,0,0)");

            theta /= 2;

            //get cos and sin
            const double cos = math::cos(theta);
            const double sin = math::sin(theta);

            //get unitvector (aka normalized vector mult sin)
            const vector3d unit_vector = rotation_vector.normalize() * sin; //throws zero_exception

            //quaternion
            const quaternion q = quaternion(cos, unit_vector.x, unit_vector.y, unit_vector.z);

            //conjugated quaternion of Q
            const quaternion con_q = q.conjugate();

            //quaternion from given point
            const quaternion p = quaternion(0, to_be_rotated_3d.x, to_be_rotated_3d.y, to_be_rotated_3d.z);

            const quaternion result = con_q.multiply(p).multiply(q);

            return {result.y, result.z, result.w};
        }

        /**
         * \brief calculates the mirror of a 3D object (mirror3d) around a given axis (mirror_vector)
         * \throws zero_exception if length of to_be_mirrored_3d is zero
         * \throws zero_exception if length of mirror_vector is zero
         * \tparam T an inherited class of dimension3, e.g. point3d, vector3d, ...
         * \param to_be_mirrored_3d the 3D object that should be mirrored
         * \param mirror_vector the axis around which the object should be mirrored
         * \return mirrored 3D object
         */
        template <typename T, ENABLE_IF_DERIVED(dimension3, T)>
        NODISCARD constexpr static T mirror(const T& to_be_mirrored_3d, const vector3d& mirror_vector)
        {
            if (to_be_mirrored_3d == dimension3<T>::zero())
                throw exception::zero_exception("to_be_mirrored_3d must not be (0,0,0)");

            //get unitvector (aka normalized vector)
            const vector3d unit_vector = mirror_vector.normalize(); //throws zero_exception

            //quaternion
            const quaternion q = quaternion(0, unit_vector.x, unit_vector.y, unit_vector.z);

            //conjugated quaternion of Q
            const quaternion con_q = q.conjugate();

            //quaternion from given point
            const quaternion p = quaternion(0, to_be_mirrored_3d.x, to_be_mirrored_3d.y, to_be_mirrored_3d.z);

            const quaternion result = con_q.multiply(p.multiply(q));

            return {result.y, result.z, result.w};
        }

        /**
         * \brief multiplies two quaternions, this is not a standard multiplication
         * \note for any two quaternions a and b, the order of multiplication is important, i.e. a * b != b * a
         * \note please read https://en.wikipedia.org/wiki/Quaternion#Hamilton_product for more information
         * \param quaternion other quaternion
         * \return multiplied quaternion
         */
        NODISCARD constexpr quaternion multiply(const quaternion& quaternion) const noexcept
        {
            const double real = (x * quaternion.x - y * quaternion.y - z * quaternion.z - w * quaternion.w);
            const double i = (x * quaternion.y + y * quaternion.x + z * quaternion.w - w * quaternion.z);
            const double j = (x * quaternion.z - y * quaternion.w + z * quaternion.x + w * quaternion.y);
            const double k = (x * quaternion.w + y * quaternion.z - z * quaternion.y + w * quaternion.x);
            return {real, i, j, k};
        }

        /**
         * \brief calculates the conjugated quaternion
         * \return conjugated quaternion (x, -y, -z, -w) (real, -i, -j, -k)
         */
        NODISCARD constexpr quaternion conjugate() const noexcept
        {
            return {x, -y, -z, -w};
        }

        /**
         * \brief calculates the length of the quaternion
         * \return length of the quaternion
         */
        NODISCARD constexpr double length() const noexcept
        {
            return math::sqrt(x * x + y * y + z * z + w * w);
        }

        /**
         * \brief calculates the normalized quaternion (length = 1) (aka unit quaternion)
         * \note read https://en.wikipedia.org/wiki/Quaternion#Unit_quaternion for more information
         * \throws zero_exception if length is 0
         * \return normalized quaternion
         */
        NODISCARD constexpr quaternion normalize() const
        {
            const double l = length();

            if (l == 0)
                throw exception::zero_exception("quaternion length must not be zero");

            return *this / l;
        }
    };
} // namespace bardcore