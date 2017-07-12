#include "TPoint.h"
#include "TPointTranslator.h"
#include "iostream"

TPoint::TPoint() { fX = fY = fZ = 0; }
TPoint::TPoint(const TPoint &cp) { (*this) = cp; }
TPoint::~TPoint() {}
TPoint &TPoint::operator=(const TPoint &cp) {
    fX = cp.fX;
    fY = cp.fY;
    fZ = cp.fZ;
    return *this;
}

void TPoint::SetCoordinates(const double &x, const double &y, const double &z) {
    fX = x;
    fY = y;
    fZ = z;
}
void TPoint::GetCoordinates(double &x, double &y, double &z) {
    x = fX;
    y = fY;
    z = fZ;
}

void TPoint::Read(TStream &stream) {
    TBufferedStream buf(TPointTranslator::UpdateStream(stream, TStream::fCurrentVersion));
    buf >> fX;
    buf >> fY;
    buf >> fZ;
}
void TPoint::Write(TStream &stream) const {
    stream << fX;
    stream << fY;
    stream << fZ;
}