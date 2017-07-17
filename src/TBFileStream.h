#ifndef TBFILESTREAM_H
#define TBFILESTREAM_H
#include "TStream.h"
#include <fstream>
#include <string>

class TBFileStream : public TStream {
  public:
    TBFileStream();
    ~TBFileStream();

    void OpenRead(const std::string &fileName);
    void OpenWrite(const std::string &fileName);

    void CloseRead();
    void CloseWrite();
    
    TStream &operator>>(double &var);
    TStream &operator<<(const double &var);

  protected:
    virtual void Read(char *dest, const size_t &nBytes);
    virtual void Write(const char *source, const size_t &nBytes);

  private:
    std::ifstream fIn;
    std::ofstream fOut;
};
#endif // TBFILESTREAM_H