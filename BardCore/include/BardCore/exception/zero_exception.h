#pragma once

#include "BardCore/bardcore.h"

namespace bardcore
{
    namespace exception
    {
        class zero_exception : public bard_exception
        {
        public:
            using bard_exception::bard_exception;
        };
    } // namespace bardcore::exceptions
} // namespace bardcore
