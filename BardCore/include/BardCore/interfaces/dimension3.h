#pragma once

#include "BardCore/bardcore.h"
#include "BardCore/math/math.h"

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
        double x{}, y{}, z{};

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
        constexpr dimension3(const double x, const double y, const double z): x(x), y(y), z(z)
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
         * \return new dimension3
        */
        template <typename Derived, ENABLE_IF_DERIVED(dimension3, Derived)>
        NODISCARD constexpr T operator-(const Derived& other) const noexcept
        {
            return {x - other.x, y - other.y, z - other.z};
        }

        /**
         * \brief subtracts a double from a dimension3 and stores the result in a new dimension3
         * \param n double to subtract with
         * \return new dimension3
         */
        NODISCARD constexpr T operator-(const double n) const noexcept
        {
            return {x - n, y - n, z - n};
        }

        /**
         * \brief adds a dimension3 from another dimension3 and stores the result in a new dimension3
         * \tparam Derived a derived class of dimension3, e.g. point3d
         * \param other other dimension3
         * \return new dimension3
        */
        template <typename Derived, ENABLE_IF_DERIVED(dimension3, Derived)>
        NODISCARD constexpr T operator+(const Derived& other) const noexcept
        {
            return {x + other.x, y + other.y, z + other.z};
        }

        /**
         * \brief adds a double from a dimension3 and stores the result in a new dimension3
         * \param n double to add with
         * \return new dimension3
         */
        NODISCARD constexpr T operator+(const double n) const noexcept
        {
            return {x + n, y + n, z + n};
        }

        /**
         * \brief multiplies a dimension3 with n and stores the result in a new dimension3
         * \param n double to multiply with
         * \return new dimension3
        */
        NODISCARD constexpr T operator*(const double n) const noexcept
        {
            return {x * n, y * n, z * n};
        }

        /**
         * \brief divides a dimension3 with n and stores the result in a new dimension3
         * \throws std::invalid_argument if n is 0
         * \param n double to divide with
         * \return new dimension3
        */
        NODISCARD constexpr T operator/(const double n) const
        {
            if (n == 0)
                throw exception::zero_exception("division by zero");

            return {x / n, y / n, z / n};
        }

        /**
         * \brief adds a dimension3 to this dimension3
         * \tparam Derived a derived class of dimension3, e.g. point3d
         * \param other other dimension3
         * \return this
        */
        template <typename Derived, ENABLE_IF_DERIVED(dimension3, Derived)>
        constexpr dimension3& operator+=(const Derived& other) noexcept
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        /**
         * \brief adds a double to this dimension3
         * \param n double to add with
         * \return this
         */
        constexpr dimension3& operator+=(const double n) noexcept
        {
            x += n;
            y += n;
            z += n;
            return *this;
        }

        /**
         * \brief subtracts this dimension3 from this dimension3
         * \tparam Derived a derived class of dimension3, e.g. point3d
         * \param other other dimension3
         * \return this
        */
        template <typename Derived, ENABLE_IF_DERIVED(dimension3, Derived)>
        constexpr dimension3& operator-=(const Derived& other) noexcept
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        /**
         * \brief subtracts a double from this dimension3
         * \param n double to subtract with
         * \return this
         */
        constexpr dimension3& operator-=(const double n) noexcept
        {
            x -= n;
            y -= n;
            z -= n;
            return *this;
        }

        /**
         * \brief multiplies this dimension3 with n
         * \param n double to multiply with
         * \return this
        */
        constexpr dimension3& operator*=(const double n) noexcept
        {
            x *= n;
            y *= n;
            z *= n;
            return *this;
        }

        /**
         * \brief divides this dimension3 with n
         * \throws zero_exception if n is 0
         * \param n double to divide with
         * \return this
        */
        constexpr dimension3& operator/=(const double n)
        {
            if (n == 0)
                throw exception::zero_exception("division by zero");

            x /= n;
            y /= n;
            z /= n;
            return *this;
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
         * \brief makes this dimension3 negative
         * \return this
        */
        constexpr dimension3& operator-() noexcept
        {
            x = -x;
            y = -y;
            z = -z;
            return *this;
        }

        /**
         * \brief makes this dimension3 positive
         * \return this
         */
        constexpr dimension3& abs() noexcept
        {
            x = math::abs(x);
            y = math::abs(y);
            z = math::abs(z);
            return *this;
        }

        /**
         * \brief less than operator
         * \param left left dimension3
         * \param right right dimension3
         * \return true if left < right
         */
        NODISCARD constexpr friend bool operator<(const dimension3& left, const dimension3& right) noexcept
        {
            return math::less_than(left.x, right.x)
                && math::less_than(left.y, right.y)
                && math::less_than(left.z, right.z);
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
            return math::equals(left.x, right.x)
                && math::equals(left.y, right.y)
                && math::equals(left.z, right.z);
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

    /**
     * \brief subtracts n from another dimension3 and stores the result in a new dimension3
     * \param n double to subtract with
     * \param other other dimension3
     * \return new dimension3
     */
    template <typename Derived, ENABLE_IF_DERIVED(dimension3, Derived)>
    NODISCARD constexpr dimension3<Derived> operator-(const double n, const dimension3<Derived>& other) noexcept
    {
        return {n - other.x, n - other.y, n - other.z};
    }

    /**
     * \brief adds n to another dimension3 and stores the result in a new dimension3
     * \param n double to add with
     * \param other other dimension3
     * \return new dimension3
     */
    template <typename Derived, ENABLE_IF_DERIVED(dimension3, Derived)>
    NODISCARD constexpr dimension3<Derived> operator+(const double n, const dimension3<Derived>& other) noexcept
    {
        return other + n;
    }

    /**
     * \brief multiplies n with another dimension3 and stores the result in a new dimension3
     * \param n double to multiply with
     * \param other other dimension3
     * \return new dimension3
     */
    template <typename Derived, ENABLE_IF_DERIVED(dimension3, Derived)>
    NODISCARD constexpr dimension3<Derived> operator*(const double n, const dimension3<Derived>& other) noexcept
    {
        return other * n;
    }

    /**
     * \brief divides n with another dimension3 and stores the result in a new dimension3
     * \throws zero_exception if x, y or z is 0
     * \param n double to divide with
     * \param other other dimension3
     * \return new dimension3
     */
    template <typename Derived, ENABLE_IF_DERIVED(dimension3, Derived)>
    NODISCARD constexpr dimension3<Derived> operator/(const double n, const dimension3<Derived>& other)
    {
        if (math::equals(other.x, 0.) || math::equals(other.y, 0.) || math::equals(other.z, 0.))
            throw exception::zero_exception("division by zero");

        return {n / other.x, n / other.y, n / other.z};
    }
} // namespace bardcore