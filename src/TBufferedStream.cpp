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
    unsigned int nBytes = strlen(other.fCharBuf);
    fCharBuf = new char[nBytes];
    memcpy(fCharBuf, other.fCharBuf, nBytes);
    fBuf.reinit(fCharBuf, nBytes);
    fOut.str(other.fOut.str());
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
    unsigned int nBytes = fOut.str().size();
    fCharBuf = new char[nBytes];
    memcpy(fCharBuf, fOut.str().c_str(), nBytes);
    fBuf.reinit(fCharBuf, nBytes);
    fOut.str("");
}

std::istream &TBufferedStream::GetReadStream() { return fIn; }
std::ostream &TBufferedStream::GetWriteStream() { return fOut; }