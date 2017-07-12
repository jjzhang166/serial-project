#ifndef TBUFFEREDSTREAM_H
#define TBUFFEREDSTREAM_H
#include "TStream.h"
#include <sstream>

class TBufferedStream : public TStream {
public:
    TBufferedStream(TStream &readBuffer, unsigned int nBytes);
    TBufferedStream(const TBufferedStream &readBuffer);
    ~TBufferedStream();
    TBufferedStream &operator= (const TBufferedStream &);
    void TransferBuffers();
    virtual TBufferedStream &operator<< (const TBufferedStream &other);
    using TStream::operator<<;
protected:
    virtual std::istream &GetReadStream();
    virtual std::ostream &GetWriteStream();
private:
    std::istream fIn;
    std::ostringstream fOut;
    char *fCharBuf;
    TMemBuf fBuf;
};
#endif // TBUFFEREDSTREAM_H