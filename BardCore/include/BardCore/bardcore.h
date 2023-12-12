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
#ifdef CXX17
#include <optional>
#endif // CXX17

namespace bardcore
{
    namespace exceptions
    {
        /// \brief base class for all exceptions in BardCore
        class bard_exception : public std::exception
        {
        protected:
            std::string msg_;

        public:
            explicit bard_exception(const char* msg) : msg_(msg)
            {
            }

            explicit bard_exception(const std::string& msg): msg_(msg)
            {
            }

            ~bard_exception() noexcept override = default;

            /// \brief returns the message of the exception
            /// \return the message of the exception
            NODISCARD const char* what() const noexcept override
            {
                return msg_.c_str();
            }
        };
    } // namespace bardcore::exceptions
} // namespace bardcore

// BardCore includes
#include "exceptions/zero_exception.h"
#include "exceptions/negative_exception.h"
#include "exceptions/same_object_exception.h"


#endif //BARDCORE_BARDCORE_H
