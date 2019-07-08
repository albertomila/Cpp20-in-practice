#pragma once
#include "stdafx.h"
//problem
/*
#include <streambuf>  // for std::streambuf
#include <ostream>    // for std::ostream

namespace  std 
{
    class streambuf;
    class ostream 
    {
        explicit ostream(std::streambuf * buf);
        //...
    };
}
class fdoutbuf : public std::streambuf
{
public:
    explicit fdoutbuf( int fd );
    //...
};

class fdostream : public std::ostream
{
protected:
    fdoutbuf buf;
public:
    explicit fdostream( int fd ) 
        : buf( fd ), std::ostream( &buf ) 
        // This is not allowed: buf can't be initialized before std::ostream.
        // std::ostream needs a std::streambuf object defined inside fdoutbuf.
    {
    }
};
*/

#include <streambuf>  // for std::streambuf
#include <ostream>    // for std::ostream
//#include <unistd.h>   // for POSIX write

//////////////////////////////////////////////////////////////////////////
class fdoutbuf : public std::streambuf
{
public:
    explicit fdoutbuf(int fd) 
        : fd_(fd) 
    {
    }

    virtual int overflow(int ch) // overridden function
    {
        //write(fd_, &ch, 1); // Use POSIX write to output characters
        return 0;
    }
private:
    int fd_;
};

//////////////////////////////////////////////////////////////////////////
struct fdostream_pbase // A newly introduced class
{
    fdoutbuf sbuffer; // The member moved 'up' the hierarchy.
    explicit fdostream_pbase(int fd)
        : sbuffer(fd)
    {
    }
};

//////////////////////////////////////////////////////////////////////////
class fdostream
    : protected fdostream_pbase // This class will be initialized before the next one.
    , public std::ostream
{
public:
    explicit fdostream(int fd)
        : fdostream_pbase(fd)   // Initialize the newly added base before std::ostream.
        , std::ostream(&sbuffer) //  Now safe to pass the pointer
    {
    }
    //...
};


BEGIN_TEST(BaseFromMember)
    fdostream standard_out(1);
    standard_out << "Hello, World\n";
END_TEST()