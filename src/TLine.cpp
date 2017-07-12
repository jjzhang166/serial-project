#include "TLine.h"
#include "TLineTranslator.h"
#include "iostream"

TLine::TLine() { 
    pB.SetCoordinates(0., 0.);
    pE.SetCoordinates(0., 0.);
     }
TLine::TLine(const TLine &cp) { (*this) = cp; }
TLine::~TLine() {}
TLine &TLine::operator=(const TLine &cp) {
    pB = cp.pB;
    pE = cp.pE;
    return *this;
}

void TLine::SetBeginPoint(const double &xB, const double &yB) {
    pB.SetCoordinates(xB, yB);
}
void TLine::SetEndPoint(const double &xE, const double &yE) {
    pE.SetCoordinates(xE, yE);
}
void TLine::GetBeginPoint(double &xB, double &yB) {
    pB.GetCoordinates(xB, yB);
}
void TLine::GetEndPoint(double &xE, double &yE) {
    pE.GetCoordinates(xE, yE);
}

void TLine::Read(TStream &stream) {
    TBufferedStream buf(TLineTranslator::UpdateStream(stream, TStream::fCurrentVersion));
    pB.Read(buf);
    pE.Read(buf);
}
void TLine::Write(TStream &stream) const {
    pB.Write(stream);
    pE.Write(stream);
}