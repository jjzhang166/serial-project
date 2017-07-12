#ifndef TLINE_H
#define TLINE_H

#include "TStream.h"
#include "TPoint.h"

class TLine {
  public:
    TLine();
    TLine(const TLine &cp);
    ~TLine();
    TLine &operator=(const TLine &cp);

    void SetBeginPoint(const double &xB, const double &yB);
    void SetEndPoint(const double &xE, const double &yE);
    void GetBeginPoint(double &xB, double &yB);
    void GetEndPoint(double &xE, double &yE);

    void Read(TStream &stream);//stream!!
    void Write(TStream &stream) const;//stream!!

  private:
    TPoint pB, pE;
};
#endif // TLINE_H