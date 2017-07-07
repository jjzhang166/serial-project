#include "TBufferedStream.h"
#include <iostream>
#include <stdexcept>
#include <iostream>

TBufferedStream::TBufferedStream(TStream &readBuffer, unsigned int nBytes) {
    char *temp;
    TStream::ReadFromStream(&readBuffer, temp, nBytes);
    // for (int i = 0; i < nBytes; ++i)
    // {
    //     std::cout<<temp[i];
    // }
    // std::cout<<std::endl;
    fOut = new std::ostringstream();
    imembuf buf(temp, nBytes);
    fIn = new std::istream(&buf);
    fIn->clear();
    // double w, x, y, z;
    // fIn->read(reinterpret_cast<char *>(&w), sizeof(double));
    // fIn->read(reinterpret_cast<char *>(&x), sizeof(double));
    // fIn->read(reinterpret_cast<char *>(&y), sizeof(double));
    // fIn->read(reinterpret_cast<char *>(&z), sizeof(double));
    // std::cout << w << std::endl;
    // std::cout << x << std::endl;
    // std::cout << y << std::endl;
    // std::cout << z << std::endl;
    return;
}

TBufferedStream::TBufferedStream(TStream &readBuffer) {
    unsigned int nBytes = (unsigned int)TStream::StreamSize(&readBuffer);
    char *temp;
    TStream::ReadFromStream(&readBuffer, temp, nBytes);
    imembuf buf(temp, nBytes);
    fIn = new std::istream(&buf);
    fOut = new std::ostringstream();
}
// whyy
TBufferedStream::TBufferedStream(TBufferedStream &readBuffer) {
    // std::istream *in = readBuffer.GetReadStream();
    // double w, x, y, z;
    // in->read(reinterpret_cast<char *>(&w), sizeof(double));
    // in->read(reinterpret_cast<char *>(&x), sizeof(double));
    // in->read(reinterpret_cast<char *>(&y), sizeof(double));
    // in->read(reinterpret_cast<char *>(&z), sizeof(double));
    // std::cout << w << std::endl;
    // std::cout << x << std::endl;
    // std::cout << y << std::endl;
    // std::cout << z << std::endl;
    unsigned int nBytes = (unsigned int)TStream::StreamSize(&readBuffer);
    char *temp;
    TStream::ReadFromStream(&readBuffer, temp, nBytes);
    imembuf buf(temp, nBytes);
    fIn = new std::istream(&buf);
    // double w, x, y, z;
    // fIn->read(reinterpret_cast<char *>(&w), sizeof(double));
    // fIn->read(reinterpret_cast<char *>(&x), sizeof(double));
    // fIn->read(reinterpret_cast<char *>(&y), sizeof(double));
    // fIn->read(reinterpret_cast<char *>(&z), sizeof(double));
    // std::cout << w << std::endl;
    // std::cout << x << std::endl;
    // std::cout << y << std::endl;
    // std::cout << z << std::endl;
    fOut = new std::ostringstream();
}

TBufferedStream::~TBufferedStream() {
    if (!fIn->eof()) { // returning without consuming the buffer
        throw std::runtime_error(
            "TBufferedStream: I still have data to be read");
    }
    delete fIn;
    delete fOut;
}

void TBufferedStream::TransferBuffers() {
    if (!fIn->eof()) { // transfering without consuming the buffer
        throw std::runtime_error(
            "TBufferedStream: I still have data to be read before transfer!");
    }
    delete fIn;
    char *temp;
    unsigned int nBytes = 0;
    imembuf buf(temp, nBytes);
    fIn = new std::istream(&buf);
}

std::istream *TBufferedStream::GetReadStream() { return fIn; }
std::ostream *TBufferedStream::GetWriteStream() { return fOut; }