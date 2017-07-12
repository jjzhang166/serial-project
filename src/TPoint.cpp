#include "TPoint.h"
#include "TPointTranslator.h"
#include "iostream"

TPoint::TPoint() { fX = fY = 0; }
TPoint::TPoint(const TPoint &cp) { (*this) = cp; }
TPoint::~TPoint() {}
TPoint &TPoint::operator=(const TPoint &cp) {
    fX = cp.fX;
    fY = cp.fY;
    return *this;
}

void TPoint::SetCoordinates(const double &x, const double &y) {
    fX = x;
    fY = y;
}
void TPoint::GetCoordinates(double &x, double &y) {
    x = fX;
    y = fY;
}

void TPoint::Read(TStream &stream) {
    TBufferedStream buf(TPointTranslator::UpdateStream(stream, TStream::fCurrentVersion));
    buf >> fX;
    buf >> fY;
}
void TPoint::Write(TStream &stream) const {
    stream << fX;
    stream << fY;
}