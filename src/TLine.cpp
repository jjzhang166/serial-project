#include "TLine.h"
#include "iostream"

TLine::TLine() { fXb = fXe = fYe = fYe = 0; }
TLine::TLine(const TLine &cp) { (*this) = cp; }
TLine::~TLine() {}
TLine &TLine::operator=(const TLine &cp) {
    fXb = cp.fXb;
    fXe = cp.fXe;
    fYb = cp.fYb;
    fYe = cp.fYe;
    return *this;
}

void TLine::SetBeginPoint(const double &xB, const double &yB) {
    fXb = xB;
    fYb = yB;
}
void TLine::SetEndPoint(const double &xE, const double &yE) {
    fXe = xE;
    fYe = yE;
}
void TLine::GetBeginPoint(double &xB, double &yB) {
    xB = fXb;
    yB = fYb;
}
void TLine::GetEndPoint(double &xE, double &yE) {
    xE = fXe;
    yE = fYe;
}

void TLine::Read(TStream &stream) {
    stream >> fXb;
    stream >> fXe;
    stream >> fYb;
    stream >> fYe;
}
void TLine::Write(TStream &stream) const{
    stream << fXb;
    stream << fXe;
    stream << fYb;
    stream << fYe;
}