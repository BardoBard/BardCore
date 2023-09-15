#ifndef BARDCORE_MATH_H
#define BARDCORE_MATH_H

namespace bardcore
{
    class math
    {
    public:
        inline static constexpr float pi = 3.14159265358979323846f;

        static float get_degrees_from_radians(const float radians)
        {
            return radians * 180.0f / math::pi;
        }

        static float get_radians_from_degrees(const float degrees)
        {
            return degrees * math::pi / 180.0f;
        }
    };
}
#endif //BARDCORE_MATH_H
