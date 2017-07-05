#include "TStream.h"
#include <iostream>

TStream::TStream() {}

TStream::~TStream() {}

TStream &TStream::operator>>(double &var) {
    std::istream *in = GetReadStream();
    in->read(reinterpret_cast<char *>(&var), sizeof(var));
    if (in->bad()) {
        throw std::runtime_error("TStream:Could not read from stream");
    }
    return *this;
}
TStream &TStream::operator<<(const double &var) {
    std::ostream *out = GetWriteStream();
    out->write(reinterpret_cast<const char *>(&var), sizeof(var));
    if (out->bad()) {
        throw std::runtime_error("TStream:Could not write to stream");
    }
    return *this;
}

std::streamsize TStream::StreamSize(TStream *stream) {
    std::istream *in = stream->GetReadStream();
    std::streampos fsize = 0;
    fsize = in->tellg();
    in->seekg(0, std::ios::end);
    fsize = in->tellg() - fsize;
    std::cout<<fsize<<std::endl;
    if (fsize < 0) {
        std::runtime_error("TStream: Could not get stream size");
    }
    return (std::streamsize)fsize;
}

void TStream::ReadFromStream(TStream *stream, char * &dest,
                             const unsigned int &nBytes) {
    if (!dest)
        delete[] dest;
    dest = new char[nBytes];
    std::istream *in = stream->GetReadStream();
    in->read(dest, nBytes);
}