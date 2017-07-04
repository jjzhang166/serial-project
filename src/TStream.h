#ifndef TSTREAM_H
#define TSTREAM_H
#include <iostream>

class TStream {
  public:
    TStream();
    TStream(const TStream &cp);
    ~TStream();
    TStream &operator=(const TStream &cp);

    virtual void ReadFromStream(char *dest, unsigned int nBytes) = 0;
    virtual TStream &operator>>(double &var) = 0;
    virtual TStream &operator<<(const double &var) = 0;

    static const unsigned long fCurrentVersion = 1;
    unsigned long fFromVersion;
};
#endif // TSTREAM_H