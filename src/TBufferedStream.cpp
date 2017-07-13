#include "TBufferedStream.h"
#include <iostream>
#include <stdexcept>
#include <iostream>
#include <string.h>

//TBufferedStream::TBufferedStream() : TStream(0), fSize(0) {
//    nAllocatedBytes = 10;
//    fBuffer = new char[nAllocatedBytes];
//    fFirst = fBuffer;
//    fSize = 0;
//    fLast = fBuffer - 1 + fSize;
//}

TBufferedStream::TBufferedStream(TStream &readBuffer, const size_t &nBytes) : TStream(readBuffer.fFromVersion) {
    nAllocatedBytes = nBytes + SIZE_INCREMENT;
    fBuffer = new char[nAllocatedBytes];
    fFirst = fBuffer;
    readBuffer.Read(fBuffer, nBytes);
    fSize = nBytes;
    fLast = fBuffer - 1 + fSize;
}

TBufferedStream::TBufferedStream(const TBufferedStream &other) : TStream(other), fBuffer(NULL) {
    *this = other;
}

TBufferedStream &TBufferedStream::operator=(const TBufferedStream &other) {
    nAllocatedBytes = other.nAllocatedBytes;
    if (fBuffer) delete[] fBuffer;
    fBuffer = new char[nAllocatedBytes];
    memcpy(fBuffer, other.fBuffer, other.fSize);
    fSize = other.fSize;
    fFirst = fBuffer;
    fLast = fBuffer - 1 + fSize;
    return *this;
}

TBufferedStream::~TBufferedStream() {
    delete []fBuffer;
}

TBufferedStream &TBufferedStream::operator<<(TBufferedStream &other) {
    const unsigned int nBytesOther = other.fSize;
    char temp[nBytesOther];
    other.Read(temp, nBytesOther);
    Write(temp, nBytesOther);
    return *this;
}

TBufferedStream &TBufferedStream::operator<<(const TBufferedStream &other) {
    const unsigned int nBytesOther = other.fSize;
    char temp[nBytesOther];
    other.ConstRead(temp, nBytesOther);
    Write(temp, nBytesOther);
    return *this;
}

void TBufferedStream::Read(char *dest, const size_t &nBytes) {
    if (nBytes > fSize) {
        std::string msg("TBufferedStream: Cannot read ");
        msg.append(std::to_string(nBytes));
        msg.append(" bytes; there are only ");
        msg.append(std::to_string(fSize));
        msg.append(" available.");
        throw std::runtime_error(msg);
    }
    char *endBuffer = fBuffer + nAllocatedBytes;

    if (fFirst + nBytes < endBuffer) {
        // direct reading (we do not need to cycle to the beginning of the buffer to read)
        memcpy(dest, fFirst, nBytes);
        fFirst += nBytes;
    } else {
        // we need to read past the end of the buffer. 
        const size_t nBytesRead(endBuffer - fFirst);
        memcpy(dest, fFirst, nBytesRead);
        if (nBytes != nBytesRead) {
            memcpy(dest + nBytesRead, fBuffer, nBytes - nBytesRead);
        }
        fFirst = fBuffer + nBytes - nBytesRead;
    }

    fSize -= nBytes;
}

void TBufferedStream::ConstRead(char *dest, const size_t &nBytes) const {
    if (nBytes > fSize) {
        std::string msg("TBufferedStream: Cannot read ");
        msg.append(std::to_string(nBytes));
        msg.append(" bytes; there are only ");
        msg.append(std::to_string(fSize));
        msg.append(" available.");
        throw std::runtime_error(msg);
    }
    char *endBuffer = fBuffer + nAllocatedBytes;

    if (fFirst + nBytes < endBuffer) {
        // direct reading (we do not need to cycle to the beginning of the buffer to read)
        memcpy(dest, fFirst, nBytes);
    } else {
        // we need to read past the end of the buffer. 
        const size_t nBytesRead(endBuffer - fFirst);
        memcpy(dest, fFirst, nBytesRead);
        if (nBytes != nBytesRead) {
            memcpy(dest + nBytesRead, fBuffer, nBytes - nBytesRead);
        }
    }
}

void TBufferedStream::Write(const char *source, const size_t &nBytes) {
    if (fSize + nBytes > nAllocatedBytes) {
        size_t oldSize = fSize;
        size_t newAllocatedBytes = oldSize + nBytes + SIZE_INCREMENT;
        char *temp = new char[newAllocatedBytes];
        ConstRead(temp, oldSize);
        memcpy(temp + oldSize, source, nBytes);
        delete[] fBuffer;
        fBuffer = temp;
        nAllocatedBytes = newAllocatedBytes;
        fFirst = fBuffer;
        fSize = oldSize + nBytes;
        fLast = fBuffer - 1 + fSize;
    } else {
        char *endBuffer = fBuffer + nAllocatedBytes;

        if (fLast + nBytes < endBuffer) {
            // direct writing (we do not need to cycle to the beginning of the buffer to write)
            memcpy(fLast + 1, source, nBytes);
            fLast += nBytes;
        } else {
            // we need to write past the end of the buffer. 
            const size_t nBytesWritten(endBuffer - fLast - 1);
            memcpy(fLast + 1, source, nBytesWritten);
            if (nBytes != nBytesWritten) {
                memcpy(fBuffer, source + nBytesWritten, nBytes - nBytesWritten);
            }
            fLast = fBuffer - 1 + nBytes - nBytesWritten;
        }

        fSize += nBytes;
    }
}

void TBufferedStream::Print(){
    std::cout << "fSize=" << fSize << std::endl;
    double temp[fSize/8];
    ConstRead(reinterpret_cast<char*>(temp), fSize);
    for (unsigned int i = 0; i < fSize/8; ++i) {
        std::cout << temp[i] << " ";
    }
    std::cout << std::endl;
}