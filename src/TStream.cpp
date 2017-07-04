#include "TStream.h"
#include <iostream>

TStream::TStream() {}

TStream::TStream(const TStream &cp) {}

TStream::~TStream() {
}
TStream &TStream::operator=(const TStream &cp) {
	throw std::exception();//should not be called!
}
