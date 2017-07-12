#ifndef TPOINT_H
#define TPOINT_H

#include "TStream.h"

class TPoint {
  public:
    TPoint();
    TPoint(const TPoint &cp);
    ~TPoint();
    TPoint &operator=(const TPoint &cp);

    void SetCoordinates(const double &x, const double &y);
    void GetCoordinates(double &x, double &y);

    void Read(TStream &stream);
    void Write(TStream &stream) const;

  private:
    double fX, fY;
};
#endif // TPOINT_H