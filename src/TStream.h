#ifndef TSTREAM_H
#define TSTREAM_H
#include <iostream>
#include <streambuf>
#include "TMemBuf.h"

class TStream {
public:
    TStream();
    TStream(const unsigned int fromVersion);
    TStream(const TStream&);
    ~TStream();
    virtual TStream &operator>>(double &var);
    virtual TStream &operator<<(const double &var);
    virtual void Read(char *dest, const size_t &nBytes) = 0;
    virtual void Write(const char *source, const size_t &nBytes) = 0;
 
    static const unsigned long fCurrentVersion = 3;
    unsigned long fFromVersion;

};
#endif // TSTREAM_H