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
    virtual ~TStream();
    virtual void Read(double *p, int size=1)=0;
    virtual void Write(const double *var, int size=1) = 0;

    static const unsigned long fCurrentVersion = 3;
    unsigned long fFromVersion;

};
#endif // TSTREAM_H