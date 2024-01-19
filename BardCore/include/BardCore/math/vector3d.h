#pragma once

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
            const double l = this->length();

            if (l == 0)
                throw exception::zero_exception("vector length must not be zero");

            //branchless normalization
            return l == 1.
                       ? *this
                       : *this / l;
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
        NODISCARD constexpr double dot(const vector3d& vector) const noexcept
        {
            return x * vector.x + y * vector.y + z * vector.z;
        }

        /**
         * \brief calculates the length of the vector
         * \return length of vector
         */
        NODISCARD constexpr double length() const noexcept
        {
            return math::sqrt(length_squared());
        }

        /**
         * \brief calculates the length squared of the vector
         * \return length squared of vector
         */
        NODISCARD constexpr double length_squared() const noexcept
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
        NODISCARD constexpr double angle_dot(const vector3d& vector) const
        {
            if (this == &vector)
                throw exception::same_object_exception("vectors mustn't be the same");

            return this->normalize().dot(vector.normalize());
        }

        /**
         * \brief calculates the angle in radians between this and another vector, all will be normalized
         * \note this method is not constexpr because of the std::acos function, perhaps implement own at some point
         * \throws same_object_exception if this and other vector are the same
         * \throws zero_exception if length of this or other vector is zero
         * \param vector other vector, it will be normalized for you
         * \return angle in radians between this and other vector
         */
        NODISCARD double angle_radians(const vector3d& vector) const
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
        NODISCARD double angle_degrees(const vector3d& vector) const
        {
            return math::radians_to_degrees(angle_radians(vector));
        }

#if defined(CXX17) // C++17 or higher (std::optional)
        /**
         * \brief calculates the normalized refraction of this vector on a normal
         *
         * if there is no refraction, only internal reflection, this method will return std::nullopt
         * \throws zero_exception if length of normal vector is zero
         * \throws zero_exception if refractive mediums are zero
         * \throws negative_exception if refractive index is smaller or equal to zero
         * \note read more at https://en.wikipedia.org/wiki/Snell%27s_law#Vector_form
         * \param normal normal, the vector to refract on, it will be normalized for you
         * \param refractive_medium1 refractive_medium1, this is the refractive index of the medium the vector is coming from, for example air, read more at https://en.wikipedia.org/wiki/Refractive_index
         * \param refractive_medium2 refractive_medium2, this is the refractive index of the medium the vector is going to, for example water, read more at https://en.wikipedia.org/wiki/Refractive_index
         * \return normalized refraction vector of this vector on a normalized(normal)
         */
        NODISCARD constexpr std::optional<vector3d> refraction(const vector3d& normal,
                                                                       const double refractive_medium1,
                                                                       const double refractive_medium2 = 1) const
        {
            //we cannot divide by zero
            if (math::equals(refractive_medium1, 0.) || math::equals(refractive_medium2, 0.))
                throw exception::zero_exception("refractive mediums must not be zero");

            //here we calculate the refractive ratio, aka the ratio between the refractive mediums
            const double refractive_ratio = refractive_medium1 / refractive_medium2;
            if (refractive_ratio <= 0) //we cannot have a negative refractive ratio
                throw exception::negative_exception("refractive ratio must be bigger than zero");

            const vector3d normalized_normal = normal.normalize(); //normalize the normal

            //formula: refraction = r*l + (r*c - sqrt(1 - r^2 * (1 - c^2))) * n
            //https://en.wikipedia.org/wiki/Snell%27s_law#Vector_form
            const double theta_cos_1 = -normalized_normal.dot(this->normalize());
            const double theta_sin_2 = refractive_ratio * math::sqrt(1 - theta_cos_1 * theta_cos_1);

            //check if we've found a total internal reflection
            if (math::greater_than(theta_sin_2, 1)) //this means we have a total internal reflection
                return std::nullopt;

            //no ternary operator because otherwise constexpr doesn't work on make_optional???
            //the compiler will optimize this anyway
            return std::make_optional(
                this->normalize() * refractive_ratio + normalized_normal * (refractive_ratio * theta_cos_1 - math::sqrt(
                    1 - theta_sin_2 * theta_sin_2)));
        }

        /**
         * \brief calculates the reflection of this vector on a normal only if this vector is not behind normal
         *
         * the result will not be normalized, meaning it will have the same length as the original vector
         * \throws zero_exception if length of normal vector is zero
         * \note read more at https://math.stackexchange.com/a/4019883
         * \note formula: r = n (2 * (d . n)) − d
         * \param normal normal, the vector to reflect on, it will be normalized for you
         * \return std::nullopt if vector is behind normal, else reflection of this vector on a normalized(normal)
         */
        NODISCARD constexpr std::optional<vector3d> reflection(const vector3d& normal) const
        {
            const vector3d n = normal.normalize();
            const double dot = n.dot(*this);

            // dot < 0 means the vector is behind the normal
            // this is not what the reflection intends to do, so return nullopt
            if (dot < 0)
                return std::nullopt;

            //no ternary operator because otherwise constexpr doesn't work on make_optional???
            //the compiler will optimize this anyway
            return std::make_optional(n * (2 * dot) - *this);
        }

#elif defined(CXX14) // C++14 (std::unique_ptr)
        /**
         * \brief calculates the normalized refraction of this vector on a normal
         *
         * if there is no refraction, only internal reflection, this method will return nullptr
         * \throws zero_exception if length of normal vector is zero
         * \throws zero_exception if refractive mediums are zero
         * \throws negative_exception if refractive index is smaller or equal to zero
         * \note read more at https://en.wikipedia.org/wiki/Snell%27s_law#Vector_form
         * \param normal normal, the vector to refract on, it will be normalized for you
         * \param refractive_medium1 refractive_medium1, this is the refractive index of the medium the vector is coming from, for example air, read more at https://en.wikipedia.org/wiki/Refractive_index
         * \param refractive_medium2 refractive_medium2, this is the refractive index of the medium the vector is going to, for example water, read more at https://en.wikipedia.org/wiki/Refractive_index
         * \return normalized refraction vector of this vector on a normalized(normal)
         */
        NODISCARD std::unique_ptr<vector3d> refraction(const vector3d& normal, const double refractive_medium1,
                                                      const double refractive_medium2 = 1) const
        {
            //we cannot divide by zero
            if (math::equals(refractive_medium1, 0.) || math::equals(refractive_medium2, 0.))
                throw exception::zero_exception("refractive mediums must not be zero");

            //here we calculate the refractive ratio, aka the ratio between the refractive mediums
            const double refractive_ratio = refractive_medium1 / refractive_medium2;
            if (refractive_ratio <= 0) //we cannot have a negative refractive ratio
                throw exception::negative_exception("refractive ratio must be bigger than zero");

            const vector3d normalized_normal = normal.normalize(); //normalize the normal

            //formula: refraction = r*l + (r*c - sqrt(1 - r^2 * (1 - c^2))) * n
            //https://en.wikipedia.org/wiki/Snell%27s_law#Vector_form
            const double theta_cos_1 = -normalized_normal.dot(this->normalize());
            const double theta_sin_2 = refractive_ratio * math::sqrt(1 - theta_cos_1 * theta_cos_1);

            //check if we've found a total internal reflection
            if (math::greater_than(theta_sin_2, 1)) //this means we have a total internal reflection
                return nullptr;

            return std::make_unique<vector3d>(this->normalize() * refractive_ratio + normalized_normal * (refractive_ratio * theta_cos_1 - math::sqrt(1 - theta_sin_2 * theta_sin_2)));
        }
        
        /**
         * \brief calculates the reflection of this vector on a normal only if this vector is not behind normal
         *
         * the result will not be normalized, meaning it will have the same length as the original vector
         * \throws zero_exception if length of normal vector is zero
         * \note read more at https://math.stackexchange.com/a/4019883
         * \note formula: r = n (2 * (d . n)) − d
         * \param normal normal, the vector to reflect on, it will be normalized for you
         * \return nullptr if vector is behind normal, else reflection of this vector on a normalized(normal)
         */
        NODISCARD std::unique_ptr<vector3d> reflection(const vector3d& normal) const
        {
            const vector3d n = normal.normalize();
            const double dot = n.dot(*this);

            // dot < 0 means the vector is behind the normal
            // this is not what the reflection intends to do, so return nullptr
            return dot < 0
                        ? nullptr
                        : std::make_unique<vector3d>(n * (2 * dot) - *this);
        }
#endif // C++14 (std::unique_ptr)
    };
} // namespace bardcore
