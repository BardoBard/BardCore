#ifndef BARDCORE_POINT3D_H
#define BARDCORE_POINT3D_H

#include "vector3d.h"
#include "dimension3.h"


namespace bardcore
{
    class point3d : public dimension3<point3d>
    {
    private:
    public:
        using dimension3::dimension3;

        point3d operator+(const vector3d& vector) const
        {
            return {x + vector.x, y + vector.y, z + vector.z};
        }

        point3d operator+(const point3d& point) const
        {
            return {x + point.x, y + point.y, z + point.z};
        }

        point3d operator-(const vector3d& vector) const
        {
            return {x - vector.x, y - vector.y, z - vector.z};
        }

        point3d operator-(const point3d& point) const
        {
            return {x - point.x, y - point.y, z - point.z};
        }

        /**
         * Gets vector between two points
         *
         * @param point second point
         * @return vector between point1 and point2
         */
        NODISCARD vector3d get_vector(const point3d& point) const
        {
            return vector3d(point - *this);
        }

        /**
         * Calculates the distance between two points
         *
         * @param point point2
         * @return length
         */
        NODISCARD float distance(const point3d& point) const
        {
            //formula: sqrt( (x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2 )
            return std::sqrt(distance_squared(point));
        }

        /**
         * Calculates the distance squared between two points
         *
         * @param point point2
         * @return length^2
         */
        NODISCARD float distance_squared(const point3d& point) const
        {
            //formula: (x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2
            const float x_diff = point.x - x;
            const float y_diff = point.y - y;
            const float z_diff = point.z - z;
            return x_diff * x_diff + y_diff * y_diff + z_diff * z_diff;
        }
    };
} // namespace bardcore
#endif //BARDCORE_POINT3D_H
