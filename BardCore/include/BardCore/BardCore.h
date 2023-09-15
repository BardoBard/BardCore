#ifndef BARDCORE_BARDCORE_H
#define BARDCORE_BARDCORE_H

#if !__has_cpp_attribute(nodiscard)
#error "We really should have NODISCARD"
#endif

#if __cplusplus >= 201703L
#define CXX17
#endif

#if __cplusplus >= 202002L
#define CXX20
#endif

#ifdef CXX17
#define NODISCARD [[nodiscard]]
#else
#define NODISCARD
#endif


#include <ostream>

namespace bardcore
{
}

#endif //BARDCORE_BARDCORE_H
