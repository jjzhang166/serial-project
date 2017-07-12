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

TStream &TStream::operator>>(double &var) {
    Read(reinterpret_cast<char *> (&var), sizeof (var));
    return *this;
}

TStream &TStream::operator<<(const double &var) {
    Write(reinterpret_cast<const char *> (&var), sizeof (var));
    return *this;
}
