#include "TStream.h"
#include <iostream>
#include <fstream>
TStream::TStream() {}

TStream::~TStream() {}

TStream &TStream::operator>>(double &var) {
    std::istream &in = GetReadStream();
    in.read(reinterpret_cast<char *>(&var), sizeof(var));
    if (in.bad()) {
        throw std::runtime_error("TStream:Could not read from stream");
    }
    return *this;
}
TStream &TStream::operator<<(const double &var) {
    std::ostream &out = GetWriteStream();
    out.write(reinterpret_cast<const char *>(&var), sizeof(var));
    if (out.bad()) {
        throw std::runtime_error("TStream:Could not write to stream");
    }
    return *this;
}

std::streamsize TStream::StreamSize(TStream *stream) {
    std::istream &in = stream->GetReadStream();
    // double w, x, y, z;
    // in->read(reinterpret_cast<char *>(&w), sizeof(double));
    // in->read(reinterpret_cast<char *>(&x), sizeof(double));
    // in->read(reinterpret_cast<char *>(&y), sizeof(double));
    // in->read(reinterpret_cast<char *>(&z), sizeof(double));
    // std::cout << w << std::endl;
    // std::cout << x << std::endl;
    // std::cout << y << std::endl;
    // std::cout << z << std::endl;
    in.seekg (0, in.end );
    int fsize = in.tellg();//doesnt work
    in.seekg (0, in.beg );
    if (fsize == -1) {
        throw std::runtime_error("TStream: Could not get stream size");
    }
    return fsize;
}

void TStream::ReadFromStream(TStream &stream, char * &dest,
                             const unsigned int &nBytes) {
    std::istream &in = stream.GetReadStream();
    in.read(dest, nBytes);
}