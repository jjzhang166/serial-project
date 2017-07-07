#ifndef TBUFFEREDSTREAM_H
#define TBUFFEREDSTREAM_H
#include "TStream.h"
#include <sstream>

class TBufferedStream : public TStream {
  public:
    TBufferedStream(TStream &readBuffer, unsigned int nBytes);
    TBufferedStream(TStream &readBuffer);
    TBufferedStream(TBufferedStream &readBuffer);
    ~TBufferedStream();
    void TransferBuffers();
protected:
    std::istream *GetReadStream();
    std::ostream *GetWriteStream();
  private:
    std::istream *fIn;
    std::ostringstream *fOut;
};
#endif // TBUFFEREDSTREAM_H