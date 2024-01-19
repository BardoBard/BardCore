#ifndef BARDCORE_H
#define BARDCORE_H

// C++ version has to be 14 or later

#if __cplusplus >= 201402L
    #define CXX14
#endif

#if __cplusplus >= 201703L
    #define CXX17
#endif

#if __cplusplus >= 202002L
    #define CXX20
#endif

#if defined(CXX17) // C++17 or later
    #include <optional>
    #define ENABLE_IF_DERIVED(CLASS, T) typename = std::enable_if_t<std::is_base_of_v<CLASS<T>, T>>
    #define NODISCARD [[nodiscard]]
    #define INLINE inline
#elif defined(CXX14) // C++14
    #include <memory>
    #define ENABLE_IF_DERIVED(CLASS, T) typename = std::enable_if_t<std::is_base_of<CLASS<T>, T>::value>
    #define NODISCARD 
    #define INLINE
#else // earlier than c++ 14
    #error BardCore requires at least C++14
#endif

#define DEPRECATED(msg) [[deprecated(msg)]]

// Standard includes
#include <ostream>
#include <exception>
#include <numeric>
#include <cmath>

namespace bardcore
{
    namespace exception
    {
        /**
         * \brief base class for all exceptions in BardCore
         */
        class bard_exception : public std::exception
        {
        protected:
            std::string msg_{};

        public:
            explicit bard_exception(const char* msg) : msg_(msg)
            {
            }

            explicit bard_exception(const std::string& msg): msg_(msg)
            {
            }

            ~bard_exception() noexcept override = default;

            /**
             * \brief returns the message of the exception
             * \return the message of the exception
             */
            NODISCARD const char* what() const noexcept override
            {
                return msg_.c_str();
            }
        };
    } // namespace bardcore::exceptions
} // namespace bardcore

// BardCore includes
#include "BardCore/exception/zero_exception.h"
#include "BardCore/exception/negative_exception.h"
#include "BardCore/exception/same_object_exception.h"
#include "BardCore/exception/out_of_range_exception.h"

#endif // BARDCORE_H