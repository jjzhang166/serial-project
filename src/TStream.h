#ifndef TSTREAM_H
#define TSTREAM_H
#include <iostream>
#include <streambuf>

//struct imembuf: std::streambuf {
//    imembuf(char const* base, size_t size) {
//        char* p(const_cast<char*>(base));
//        this->setg(p, p, p + size);
//    }
//};
//typedef struct imembuf imembuf;
#include "TMemBuf.h"
typedef TMemBuf imembuf;

struct imemstream : virtual imembuf, std::istream {

    imemstream(char const* base, size_t size)
    : imembuf(base, size),
    std::istream(static_cast<std::streambuf*> (this)) {
    }
};

typedef struct imemstream imemstream;

class TStream {
public:
    TStream();
    ~TStream();
    TStream &operator>>(double &var);
    TStream &operator<<(const double &var);
    virtual std::streamsize StreamSize(TStream *stream);
    static const unsigned long fCurrentVersion = 1;
    unsigned long fFromVersion;

protected:
    void ReadFromStream(TStream &stream, char * &dest,
            const unsigned int &nBytes);
    virtual std::istream &GetReadStream() = 0;
    virtual std::ostream &GetWriteStream() = 0;
};
#endif // TSTREAM_H