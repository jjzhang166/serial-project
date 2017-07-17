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
    virtual TStream &operator>>(double &var) = 0;
    virtual TStream &operator<<(const double &var) = 0;

    static const unsigned long fCurrentVersion = 3;
    unsigned long fFromVersion;

};
#endif // TSTREAM_H