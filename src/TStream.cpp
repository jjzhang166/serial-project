#include "TStream.h"
#include <iostream>
#include <fstream>

TStream::TStream() {
}

TStream::TStream(const unsigned int fromVersion) : fFromVersion(fromVersion) {
}

TStream::TStream(const TStream &other) : fFromVersion(other.fFromVersion) {

}

TStream::~TStream() {
}
