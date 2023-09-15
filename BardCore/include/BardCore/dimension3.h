#ifndef BARDCORE_BARDDIMENSION3_H
#define BARDCORE_BARDDIMENSION3_H
#include "BardCore.h"

namespace bardcore
{
    /**
     * \brief abstract class for 3D
     * usage: point3d : public dimension3<point3d>
     * \tparam T implementation of the operator
     */
    template <typename T>
    class dimension3
    {
    public:
        float x, y, z;

    public:
        ~dimension3() = default;

        dimension3(const dimension3& other)
            : x{other.x},
              y{other.y},
              z{other.z}
        {
        }

        dimension3(dimension3&& other) noexcept
            : x{other.x},
              y{other.y},
              z{other.z}
        {
        }

        template <typename Derived>
        explicit dimension3(const dimension3<Derived>& other) : dimension3(other.x, other.y, other.z)
        {
        }

        dimension3(): dimension3(0, 0, 0)
        {
        }

        dimension3(const float x, const float y, const float z): x(x), y(y), z(z)
        {
        }

        ///////////////////////////////////////////////////////
        ///                    operators                    ///
        ///////////////////////////////////////////////////////

        /**
         * \brief subtracts a dimension3 from another dimension3 and stores the result in a new dimension3
         *
         * \param other other dimension3
        */
        NODISCARD inline T operator-(const T& other) const
        {
            return {x - other.x, y - other.y, z - other.z};
        }

        /**
         * \brief adds a dimension3 from another dimension3 and stores the result in a new dimension3
         *
         * \param other other dimension3
        */
        NODISCARD inline T operator+(const T& other) const
        {
            return {x + other.x, y + other.y, z + other.z};
        }

        /**
         * \brief multiplies a dimension3 with n and stores the result in a new dimension3
         *
         * \param n float to multiply with
        */
        NODISCARD inline T operator*(const float n) const
        {
            return {x * n, y * n, z * n};
        }

        /**
         * \brief divides a dimension3 with n and stores the result in a new dimension3
         *
         * \param n float to divide with
        */
        NODISCARD inline T operator/(const float n) const
        {
            return (n == 0) ? T{0, 0, 0} : T{x / n, y / n, z / n};
        }

        /**
         * \brief adds a dimension3 to this dimension3
         *
         * \param other other dimension3
        */
        inline void operator+=(const T& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
        }

        /**
         * \brief subtracts this dimension3 from this dimension3
         *
         * \param other other dimension3
        */
        inline void operator-=(const T& other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
        }

        /**
         * \brief multiplies this dimension3 with n
         *
         * \param n float to multiply with
        */
        inline void operator*=(const float n)
        {
            x *= n;
            y *= n;
            z *= n;
        }

        /**
         * \brief divides this dimension3 with n
         *
         * \param n float to divide with
        */
        inline void operator/=(const float n)
        {
            x /= n;
            y /= n;
            z /= n;
        }

        dimension3& operator=(const dimension3& other)
        {
            x = other.x;
            y = other.y;
            z = other.z;

            return *this;
        }

        dimension3& operator=(dimension3&& other) noexcept
        {
            x = other.x;
            y = other.y;
            z = other.z;

            return *this;
        }

        friend bool operator<(const dimension3& left, const dimension3& right)
        {
            if (left.x < right.x)
                return true;
            if (right.x < left.x)
                return false;
            if (left.y < right.y)
                return true;
            if (right.y < left.y)
                return false;
            return left.z < right.z;
        }

        friend bool operator<=(const dimension3& left, const dimension3& right)
        {
            return !(right < left);
        }

        friend bool operator>(const dimension3& left, const dimension3& right)
        {
            return right < left;
        }

        friend bool operator>=(const dimension3& left, const dimension3& right)
        {
            return !(left < right);
        }

        friend std::ostream& operator<<(std::ostream& os, const dimension3& dimension3)
        {
            return os
                << "x: " << dimension3.x
                << " y: " << dimension3.y
                << " z: " << dimension3.z;
        }

        friend bool operator==(const dimension3& left, const dimension3& right)
        {
            return left.x == right.x
                && left.y == right.y
                && left.z == right.z;
        }

        friend bool operator!=(const dimension3& left, const dimension3& right)
        {
            return !(left == right);
        }
    };
}
#endif //BARDCORE_BARDDIMENSION3_H
