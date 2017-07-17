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
    
    virtual void Read(double *p, int size=1);
    virtual void Write(const double *var, int size=1);

    void CloseRead();
    void CloseWrite();

  private:
    std::ifstream fIn;
    std::ofstream fOut;
};
#endif // TBFILESTREAM_H