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
protected:
    virtual std::istream &GetReadStream();
    virtual std::ostream &GetWriteStream();
private:
    char *fCharBuf;
    imembuf fBuf;
    std::istream fIn;
    std::ostringstream fOut;
};
#endif // TBUFFEREDSTREAM_H