#include "TBufferedStream.h"
#include <iostream>
#include <stdexcept>
#include <iostream>
#include <string.h>

TBufferedStream::TBufferedStream(TStream &readBuffer, unsigned int nBytes) : fBuf(NULL, 0), fIn(&fBuf) {
    fCharBuf = new char[nBytes];
    ReadFromStream(readBuffer, fCharBuf, nBytes);
    fBuf.reinit(fCharBuf, nBytes);
    fIn.clear();
}

TBufferedStream::TBufferedStream(const TBufferedStream &other) : fBuf(NULL,0), fIn(&fBuf) {
    *this = other;
}

TBufferedStream &TBufferedStream::operator= (const TBufferedStream &other) {
    unsigned int nBytes = other.fBuf.size();
    fCharBuf = new char[nBytes];
    memcpy(fCharBuf, other.fCharBuf, nBytes);
    fBuf.reinit(fCharBuf, nBytes);
    fOut.str(other.fOut.str());
    return *this;
}

TBufferedStream::~TBufferedStream() {
    delete []fCharBuf;
}

void TBufferedStream::TransferBuffers() {
    if (fBuf.showmanyc()) { // transfering without consuming the buffer
        throw std::runtime_error(
            "TBufferedStream: I still have data to be read before transfer!");
    }
    delete[] fCharBuf;
    unsigned int nBytes = fOut.tellp();
    fCharBuf = new char[nBytes];
    memcpy(fCharBuf, fOut.str().c_str(), nBytes);
    fBuf.reinit(fCharBuf, nBytes);
    fOut.str("");
}

TBufferedStream &TBufferedStream::operator<< (const TBufferedStream &other) {
    const unsigned int nBytesOther = other.fBuf.size();
    fOut.write(other.fCharBuf, nBytesOther);

    return *this;
}

std::istream &TBufferedStream::GetReadStream() { return fIn; }
std::ostream &TBufferedStream::GetWriteStream() { return fOut; }