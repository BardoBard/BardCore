#ifndef BARDCORE_DIMENSION3_H
#define BARDCORE_DIMENSION3_H
#include "../bardcore.h"

namespace bardcore
{
    /**
     * \brief abstract class for 3D
     * \note point3d : public dimension3<point3d>
     * \note this class is also constexpr 
     * \tparam T implementation of the operator
     */
    template <typename T>
    class dimension3
    {
    public:
        float x{}, y{}, z{};
    public:
        NODISCARD constexpr INLINE static T zero() noexcept { return T(0, 0, 0); }
        NODISCARD constexpr INLINE static T one() noexcept { return T(1, 1, 1); }

        NODISCARD constexpr INLINE static T up() noexcept { return T(0, 1, 0); }
        NODISCARD constexpr INLINE static T down() noexcept { return T(0, -1, 0); }
        NODISCARD constexpr INLINE static T left() noexcept { return T(-1, 0, 0); }
        NODISCARD constexpr INLINE static T right() noexcept { return T(1, 0, 0); }
        NODISCARD constexpr INLINE static T forward() noexcept { return T(0, 0, 1); }
        NODISCARD constexpr INLINE static T backward() noexcept { return T(0, 0, -1); }

    public:
        ~dimension3() = default;

        /**
         * \brief copy constructor
         * \param other other dimension3
         */
        constexpr dimension3(const dimension3& other)
            : x{other.x},
              y{other.y},
              z{other.z}
        {
        }

        /**
         * \brief move constructor
         * \param other other dimension3
         */
        constexpr dimension3(dimension3&& other) noexcept
            : x{other.x},
              y{other.y},
              z{other.z}
        {
        }

        /**
         * \brief copy constructor
         * \tparam Derived a derived class of dimension3, e.g. point3d
         * \note this allows to copy a point3d to a vector3d
         * \param other other dimension3
         */
        template <typename Derived, ENABLE_IF_DERIVED(dimension3, Derived)>
        constexpr explicit dimension3(const dimension3<Derived>& other) : dimension3(other.x, other.y, other.z)
        {
        }

        /**
         * \brief default constructor with 0, 0, 0
         */
        constexpr dimension3(): dimension3(0, 0, 0)
        {
        }

        /**
         * \brief constructor with x, y, z in 3D
         * \param x x
         * \param y y
         * \param z z
         */
        constexpr dimension3(const float x, const float y, const float z): x(x), y(y), z(z)
        {
        }

        ///////////////////////////////////////////////////////
        ///                    operators                    ///
        ///////////////////////////////////////////////////////

        /**
         * \brief output operator, prints "(x, y, z)"
         * \param os output stream
         * \param dimension3 dimension3 to output
         * \return output stream "(x, y, z)"
         */
        friend std::ostream& operator<<(std::ostream& os, const dimension3& dimension3)
        {
            return os
                << "("
                << dimension3.x << ", "
                << dimension3.y << ", "
                << dimension3.z
                << ")";
        }

        /**
         * \brief subtracts a dimension3 from another dimension3 and stores the result in a new dimension3
         * \tparam Derived a derived class of dimension3, e.g. point3d
         * \param other other dimension3
        */
        template <typename Derived, ENABLE_IF_DERIVED(dimension3, Derived)>
        NODISCARD constexpr T operator-(const Derived& other) const noexcept
        {
            return {x - other.x, y - other.y, z - other.z};
        }

        /**
         * \brief adds a dimension3 from another dimension3 and stores the result in a new dimension3
         * \tparam Derived a derived class of dimension3, e.g. point3d
         * \param other other dimension3
        */
        template <typename Derived, ENABLE_IF_DERIVED(dimension3, Derived)>
        NODISCARD constexpr T operator+(const Derived& other) const noexcept
        {
            return {x + other.x, y + other.y, z + other.z};
        }

        /**
         * \brief multiplies a dimension3 with n and stores the result in a new dimension3
         * \param n float to multiply with
        */
        NODISCARD constexpr T operator*(const float n) const noexcept
        {
            return {x * n, y * n, z * n};
        }

        /**
         * \brief divides a dimension3 with n and stores the result in a new dimension3
         * \throws std::invalid_argument if n is 0
         * \param n float to divide with
        */
        NODISCARD constexpr T operator/(const float n) const
        {
            if (n == 0.f)
                throw exceptions::zero_exception("division by zero");

            return {x / n, y / n, z / n};
        }

        /**
         * \brief adds a dimension3 to this dimension3
         * \tparam Derived a derived class of dimension3, e.g. point3d
         * \param other other dimension3
        */
        template <typename Derived, ENABLE_IF_DERIVED(dimension3, Derived)>
        void operator+=(const Derived& other) noexcept
        {
            x += other.x;
            y += other.y;
            z += other.z;
        }

        /**
         * \brief subtracts this dimension3 from this dimension3
         * \tparam Derived a derived class of dimension3, e.g. point3d
         * \param other other dimension3
        */
        template <typename Derived, ENABLE_IF_DERIVED(dimension3, Derived)>
        void operator-=(const Derived& other) noexcept
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
        }

        /**
         * \brief multiplies this dimension3 with n
         * \param n float to multiply with
        */
        void operator*=(const float n) noexcept
        {
            x *= n;
            y *= n;
            z *= n;
        }

        /**
         * \brief divides this dimension3 with n
         * \throws zero_exception if n is 0
         * \param n float to divide with
        */
        void operator/=(const float n)
        {
            if (n == 0.f)
                throw exceptions::zero_exception("division by zero");

            x /= n;
            y /= n;
            z /= n;
        }

        /**
         * \brief copy assignment operator
         * \param other other dimension3
         * \return this
         */
        dimension3& operator=(const dimension3& other) noexcept = default;

        /**
         * \brief move assignment operator
         * \param other other dimension3
         * \return this
         */
        dimension3& operator=(dimension3&& other) noexcept = default;

        /**
         * \brief less than operator
         * \param left left dimension3
         * \param right right dimension3
         * \return true if left < right
         */
        NODISCARD constexpr friend bool operator<(const dimension3& left, const dimension3& right) noexcept
        {
            return left.x < right.x
                && left.y < right.y
                && left.z < right.z;
        }

        /**
         * \brief less than or equal operator
         * \param left left dimension3
         * \param right right dimension3
         * \return true if left <= right
         */
        NODISCARD constexpr friend bool operator<=(const dimension3& left, const dimension3& right) noexcept
        {
            return !(right < left);
        }

        /**
         * \brief greater than operator
         * \param left left dimension3
         * \param right right dimension3
         * \return true if left > right
         */
        NODISCARD constexpr friend bool operator>(const dimension3& left, const dimension3& right) noexcept
        {
            return right < left;
        }

        /**
         * \brief greater than or equal operator
         * \param left left dimension3
         * \param right right dimension3
         * \return true if left >= right
         */
        NODISCARD constexpr friend bool operator>=(const dimension3& left, const dimension3& right) noexcept
        {
            return !(left < right);
        }

        /**
         * \brief equal operator
         * \param left left dimension3
         * \param right right dimension3
         * \return true if left == right
         */
        NODISCARD constexpr friend bool operator==(const dimension3& left, const dimension3& right) noexcept
        {
            return left.x == right.x
                && left.y == right.y
                && left.z == right.z;
        }

        /**
         * \brief not equal operator
         * \param left left dimension3
         * \param right right dimension3
         * \return true if left != right
         */
        NODISCARD constexpr friend bool operator!=(const dimension3& left, const dimension3& right) noexcept
        {
            return !(left == right);
        }
    };
} // namespace bardcore
#endif //BARDCORE_DIMENSION3_H
