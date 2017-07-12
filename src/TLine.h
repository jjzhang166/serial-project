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

    void SetBeginPoint(const double &xB, const double &yB, const double &zB);
    void SetEndPoint(const double &xE, const double &yE, const double &zE);
    void GetBeginPoint(double &xB, double &yB, double &zB);
    void GetEndPoint(double &xE, double &yE, double &zE);

    void Read(TStream &stream);//stream!!
    void Write(TStream &stream) const;//stream!!

  private:
    TPoint pB, pE;
};
#endif // TLINE_H