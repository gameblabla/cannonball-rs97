/***************************************************************************
    Data Types.

    The Boost library is only used to enforce data type size at compile
    time.

    If you're sure the sizes are correct, it can be removed for your port.

    Copyright Chris White.
    See license.txt for more details.
***************************************************************************/

#pragma once


/** C99 Standard Naming */
#if defined(_MSC_VER)
    typedef signed char int8_t;
    typedef signed short int16_t;
    typedef signed int int32_t;
    typedef signed long long int64_t;

    typedef unsigned char uint8_t;
    typedef unsigned short uint16_t;
    typedef unsigned int uint32_t;
    typedef unsigned long long uint64_t;
#else
    #include <stdint.h>
#endif
