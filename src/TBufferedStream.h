#ifndef TBUFFEREDSTREAM_H
#define TBUFFEREDSTREAM_H
#include "TStream.h"
#include <sstream>

class TBufferedStream : public TStream {
  public:
    TBufferedStream();
    TBufferedStream(const TBufferedStream &cp);
    TBufferedStream(TStream &readBuffer, unsigned int nBytes);
    ~TBufferedStream();
    TBufferedStream &operator=(const TBufferedStream &cp);

    void ReadFromStream(char *dest, unsigned int nBytes);
    void CopyStreamReference(TStream &);
    TStream &operator>>(double &var);
    TStream &operator<<(const double &var);
  private:
    std::istringstream fIn;
    std::ostringstream fOut;
    TStream *fOrigStream;
};
#endif // TBUFFEREDSTREAM_H