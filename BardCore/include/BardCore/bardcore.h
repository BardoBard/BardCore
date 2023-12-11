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
#include <exception>

namespace bardcore
{
    namespace exceptions
    {
        class bard_exception : public std::exception
        {
        public:
            using std::exception::exception;
        };
    } // namespace bardcore::exceptions
} // namespace bardcore

// BardCore includes
#include "exceptions/zero_exception.h"
#include "exceptions/negative_exception.h"
#include "exceptions/same_object_exception.h"


#endif //BARDCORE_BARDCORE_H
