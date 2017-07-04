#ifndef TFILESTREAM_H
#define TFILESTREAM_H
#include "TStream.h"
#include <fstream>
#include <string>

class TFileStream : public TStream {
  public:
    TFileStream();
    TFileStream(const TFileStream &cp);
    ~TFileStream();
    TFileStream &operator=(const TFileStream &cp);

    void OpenRead(const std::string &fileName);
    void OpenWrite(const std::string &fileName);

    void CloseRead();
    void CloseWrite();
    void ReadFromStream(char *dest, unsigned int nBytes);
    TStream &operator>>(double &var);
    TStream &operator<<(const double &var);

  private:
    std::ifstream fIn;
    std::ofstream fOut;
};
#endif // TFILESTREAM_H