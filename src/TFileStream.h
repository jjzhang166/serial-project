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
    
    virtual void Read(double *p, int size=1);
    virtual void Write(const double *var, int size=1);

    void CloseRead();
    void CloseWrite();
    
  private:
    std::ifstream fIn;
    std::ofstream fOut;
};
#endif // TFILESTREAM_H