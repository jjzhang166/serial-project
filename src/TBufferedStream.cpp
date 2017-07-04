#include "TBufferedStream.h"
#include "TFileStream.h"
#include <iostream>

TBufferedStream::TBufferedStream() :fOrigStream(NULL){}

TBufferedStream::TBufferedStream(const TBufferedStream &cp){
    *this = cp;
}

TBufferedStream::TBufferedStream(TStream &readBuffer, unsigned int nBytes){
    char *temp;
    readBuffer.ReadFromStream(temp, nBytes);
    fOut.write( temp, nBytes);
    fOrigStream = &readBuffer;
}
TBufferedStream::~TBufferedStream() {
    if(!fIn.eof()){//returning without consuming the buffer
        throw std::exception();
    }
}

TBufferedStream &TBufferedStream::operator=(const TBufferedStream &cp) {
    this->fOrigStream = cp.fOrigStream;
    return *this;
}
void TBufferedStream::ReadFromStream(char *dest, unsigned int nBytes){
    if(dest != NULL) delete [] dest;
    dest = new char[nBytes];

    fIn.read(dest, nBytes); 
}

void TBufferedStream::CopyStreamReference(TStream &origStream){
    fOrigStream = &origStream;
}

TStream &TBufferedStream::operator>>(double &var) {
    if (fIn.eof()){//the buffer has been read, moving to original stream
        return fOrigStream->operator>>(var);
    }
    fIn.read(reinterpret_cast<char *>(&var), sizeof(var));
    return *this;
}
TStream &TBufferedStream::operator<<(const double &var) {
    fOut.write(reinterpret_cast<const char *>(&var), sizeof(var));
    return *this;
}