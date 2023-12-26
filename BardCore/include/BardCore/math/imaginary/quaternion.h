#ifndef BARDCORE_QUATERNION_H
#define BARDCORE_QUATERNION_H

#include "BardCore/interfaces/dimension4.h"
#include "BardCore/math/math.h"
#include "BardCore/math/point3d.h"

namespace bardcore
{
    /**
     * \brief quaternion is a 4D object, this quaternion class is pretty basic in the sense that it only supports the basic operations
     *
     *  perhaps later there will be things like ring theory, matrix representation
     */
    class quaternion : public dimension4<quaternion>
    {
    private:
    public:
        using dimension4::dimension4; // inherit constructors

        NODISCARD constexpr float get_real() const noexcept { return x; }
        NODISCARD constexpr float get_i() const noexcept { return y; }
        NODISCARD constexpr float get_j() const noexcept { return z; }
        NODISCARD constexpr float get_k() const noexcept { return w; }

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
        constexpr quaternion(const float real, const float i, const float j, const float k)
        {
            x = real;
            y = i;
            z = j;
            w = k;
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
        NODISCARD static T rotate(const T& to_be_rotated_3d, const vector3d& rotation_vector, float theta)
        {
            if (to_be_rotated_3d == dimension3<T>::zero())
                throw exception::zero_exception("to_be_mirrored_3d must not be (0,0,0)");

            //theta from degrees to rad
            theta = math::degrees_to_radians(theta / 2);

            //get cos and sin
            const float cos = std::cos(theta);
            const float sin = std::sin(theta);

            //get unitvector (aka normalized vector mult sin)
            const vector3d unit_vector = rotation_vector.normalize() * sin; //throws zero_exception

            //quaternion
            const quaternion q = quaternion(cos, unit_vector.x, unit_vector.y, unit_vector.z);

            //conjugated quaternion of Q
            const quaternion con_q = q.conjugate();

            //quaternion from given point
            const quaternion p = quaternion(0, to_be_rotated_3d.x, to_be_rotated_3d.y, to_be_rotated_3d.z);

            const quaternion result = con_q * p * q;

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

            const quaternion result = con_q * p * q;

            return {result.y, result.z, result.w};
        }

        /**
         * \brief multiplies two quaternions, this is not a standard multiplication
         * \note for any two quaternions a and b, the order of multiplication is important, i.e. a * b != b * a
         * \note please read https://en.wikipedia.org/wiki/Quaternion#Hamilton_product for more information
         * \param quaternion other quaternion
         * \return multiplied quaternion
         */
        NODISCARD constexpr quaternion operator*(const quaternion& quaternion) const noexcept
        {
            const float real = (x * quaternion.x - y * quaternion.y - z * quaternion.z - w * quaternion.w);
            const float i = (x * quaternion.y + y * quaternion.x + z * quaternion.w - w * quaternion.z);
            const float j = (x * quaternion.z - y * quaternion.w + z * quaternion.x + w * quaternion.y);
            const float k = (x * quaternion.w + y * quaternion.z - z * quaternion.y + w * quaternion.x);
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
        NODISCARD constexpr float length() const noexcept
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
            const float l = length();

            if (l == 0.f)
                throw exception::zero_exception("quaternion length must not be zero");

            return *this / l;
        }
    };
} // namespace bardcore
#endif //BARDCORE_QUATERNION_H
