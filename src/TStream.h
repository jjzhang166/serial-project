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
    virtual std::streamsize StreamSize(TStream *stream);
    static const unsigned long fCurrentVersion = 3;
    unsigned long fFromVersion;

protected:
    void ReadFromStream(TStream &stream, char * &dest,
            const unsigned int &nBytes);
    virtual std::istream &GetReadStream() = 0;
    virtual std::ostream &GetWriteStream() = 0;
};
#endif // TSTREAM_H