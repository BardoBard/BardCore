#ifndef BARDCORE_POINT3D_H
#define BARDCORE_POINT3D_H

#include "BardCore/interfaces/dimension3.h"
#include "BardCore/math/vector3d.h"


namespace bardcore
{
    /**
     * \brief 3D point
     * \note inherits from dimension3
     * \note this class is also constexpr
     */
    class point3d : public dimension3<point3d>
    {
    public:
        using dimension3::dimension3;
        
        /**
         * \brief calculates the vector from this point to another point
         * \note formula: (b) -> b - this
         * \param point point
         * \return vector between two points
         */
        NODISCARD constexpr vector3d get_vector(const point3d& point) const noexcept
        {
            return vector3d(point - *this);
        }

        /**
         * \brief calculates the center between two points
         * \note formula: (a + b) / 2
         * \param point other point
         * \return center between two points
         */
        NODISCARD constexpr point3d center(const point3d& point) const noexcept
        {
            return point3d((point.x + x) / 2.f, (point.y + y) / 2.f, (point.z + z) / 2.f);
        }
        
        /**
         * \brief calculates the distance between two points
         * \note formula: sqrt(Σ (a_i - b_i)^2)
         * \param point other point
         * \return distance between two points
         */
        NODISCARD constexpr float distance(const point3d& point) const noexcept
        {
            return math::sqrt(distance_squared(point));
        }
        
        /**
         * \brief calculates the distance squared between two points
         * \note formula: Σ (a_i - b_i)^2
         * \param point other point
         * \return distance squared between two points
         */
        NODISCARD constexpr float distance_squared(const point3d& point) const noexcept
        {
            const float x_diff = point.x - x;
            const float y_diff = point.y - y;
            const float z_diff = point.z - z;
            return x_diff * x_diff + y_diff * y_diff + z_diff * z_diff;
        }
    };
} // namespace bardcore
#endif //BARDCORE_POINT3D_H
