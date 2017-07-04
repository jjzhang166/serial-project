#ifndef TSTREAM_H
#define TSTREAM_H
#include <fstream>
#include <string>

class TStream {
  public:
    TStream();
    TStream(const TStream &cp);
    ~TStream();
    TStream &operator=(const TStream &cp);

    void OpenRead(const std::string &fileName);
    void OpenWrite(const std::string &fileName);

    void CloseRead();
    void CloseWrite();

    TStream &operator>>(double &var);
    TStream &operator<<(const double &var);

  private:
    std::ifstream iStream;
    std::ofstream oStream;
};
#endif // TSTREAM_H