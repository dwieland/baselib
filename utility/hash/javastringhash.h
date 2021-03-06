#ifndef __INCLUDE_JAVA_STRING_HASH_H_
#define __INCLUDE_JAVA_STRING_HASH_H_

#include "keyhash.h"

namespace BASE {
    namespace UTIL {


template <typename T>
struct SJavaStringHash
{
    typedef T                               value_type;
    typedef unsigned int                    hash_type;
    typedef SKeyHash<value_type, hash_type> key_hash_type;

    key_hash_type operator()(const value_type& _rValue) const
    {
        hash_type Hash = 0;
        const unsigned char* Byte = reinterpret_cast<const unsigned char*>(&_rValue);

        for (int i = 0; i < sizeof(_rValue); ++i)
        {
            Hash *= 31;
            Hash += Byte[i];
        }

        return key_hash_type(_rValue, Hash);
    }

    key_hash_type operator()(const value_type* _pValue) const
    {
        return operator()(*_pValue);
    }
};

template <typename T>
struct SJavaStringHash<const T> : SJavaStringHash<T>
{
};

template <typename T>
struct SJavaStringHash<T*> : SJavaStringHash<T>
{
    typedef T value_type;
};

template <typename T>
struct SJavaStringHash<const T*> : SJavaStringHash<T*>
{
};

template <>
struct SJavaStringHash<char*>
{
    typedef const char*                     value_type;
    typedef unsigned int                    hash_type;
    typedef SKeyHash<value_type, hash_type> key_hash_type;

    key_hash_type operator()(const char* _pValue) const
    {
        hash_type Hash = 0;
        const unsigned char* Byte = reinterpret_cast<const unsigned char*>(_pValue);

        for (int i = 0; Byte[i] != 0; ++i)
        {
            Hash *= 31;
            Hash += Byte[i];
        }

        return key_hash_type(_pValue, Hash);
    }
};


    } // namespace UTIL
} // namespace BASE

#endif // __INCLUDE_JAVA_STRING_HASH_H_