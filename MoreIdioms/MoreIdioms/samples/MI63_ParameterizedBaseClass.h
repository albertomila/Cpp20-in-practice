#pragma once
#include "stdafx.h"
#include <stdexcept>
class ISerializable
{
public:
    virtual int serialize (char *& buffer, size_t & buf_size) const = 0;
};

template <class T>
class Serializable : public T,   /// Parameterized Base Class Idiom
                     public ISerializable
{
public:
    Serializable (const T &t = T()) : T(t) {}
    virtual int serialize (char *& buffer, size_t & buf_size) const
    {
        const size_t size = sizeof (T);
        if (size > buf_size)
            throw std::runtime_error("Insufficient memory!");

        memcpy (buffer, static_cast<const T *>(this), size);
        buffer += size;
        buf_size -= size;
        return size;
    }
};

struct PBC_Test
{
    int x;
    float y;
    double z;
};

BEGIN_TEST(ParametrizedBaseClass)
	PBC_Test t;
    t.x = 5;
    t.y = 6.f;
    t.z = 7.f;

    Serializable<PBC_Test> serializable( t );
    
    size_t MAX_SIZE = sizeof(PBC_Test);
    char* buffer = new char[ MAX_SIZE ];

    serializable.serialize( buffer, MAX_SIZE );
END_TEST()