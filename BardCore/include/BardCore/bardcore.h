#ifndef BARDCORE_BARDCORE_H
#define BARDCORE_BARDCORE_H

#if __cplusplus >= 201703L
    #define CXX17
#endif

#if __cplusplus >= 202002L
    #define CXX20
#endif

#ifdef CXX17 // C++17 or later
    #define NODISCARD [[nodiscard]]
    #define INLINE inline
#else
    #define INLINE 
    #define NODISCARD
#endif

// Standard includes
#include <ostream>

namespace bardcore
{
} // namespace bardcore

#endif //BARDCORE_BARDCORE_H
