#ifndef TFILESTREAM_H
#define TFILESTREAM_H
#include "TStream.h"
#include <fstream>
#include <string>

class TFileStream : public TStream {
  public:
    TFileStream();
    ~TFileStream();

    void OpenRead(const std::string &fileName);
    void OpenWrite(const std::string &fileName);

    void CloseRead();
    void CloseWrite();
    
    TStream &operator>>(double &var);
    TStream &operator<<(const double &var);

  private:
    std::ifstream fIn;
    std::ofstream fOut;
};
#endif // TFILESTREAM_H