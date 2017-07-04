#include "TFileStream.h"
#include <iostream>

TFileStream::TFileStream() {}

TFileStream::TFileStream(const TFileStream &cp) {}

TFileStream::~TFileStream() {
    CloseWrite();
    CloseRead();
}
TFileStream &TFileStream::operator=(const TFileStream &cp) {
    throw std::exception();//should not be called!!!
}

void TFileStream::OpenRead(const std::string &fileName) {
    if (fIn.is_open()) {
        throw std::exception();
    }
    fIn.open(fileName.c_str(), std::ifstream::binary);
    if (!fIn.is_open()) {
        throw std::exception();
    }

    std::string versionString("FileVersion");
    char versionRead[12];
    fIn.read(versionRead, 11); // reads header of inputfile
    versionRead[11] = '\0';    // terminates c-style string

    if (strcmp(versionString.c_str(), versionRead) == 0) { // versioned file
        fIn.read(reinterpret_cast<char *>(&fFromVersion), sizeof(fFromVersion));
    } else { // unversioned file aka V0
        fFromVersion = 0;
        fIn.seekg(0, fIn.beg); // goes back to beginning of file
    }
    //fill stream
}
void TFileStream::OpenWrite(const std::string &fileName) {
    if (fOut.is_open()) {
        throw std::exception();
    }
    fOut.open(fileName.c_str(), std::ofstream::binary);
    if (!fOut.is_open()) {
        throw std::exception();
    }
    std::string fileInfo("FileVersion");
    fOut.write(fileInfo.c_str(),std::strlen(fileInfo.c_str()));
    const unsigned long temp = fCurrentVersion;
    fOut.write(reinterpret_cast<const char *>(&temp), sizeof(temp));
}

void TFileStream::CloseRead() {
    if (fIn.is_open()) {
        fIn.close();
    }
}

void TFileStream::CloseWrite() {
    if (fOut.is_open()) {
        fOut.close();
    }
}

void TFileStream::ReadFromStream(char *dest, unsigned int nBytes){
    if(dest != NULL) delete [] dest;
    dest = new char[nBytes];

    fIn.read(dest, nBytes); 
}

TStream &TFileStream::operator>>(double &var) {
    fIn.read(reinterpret_cast<char *>(&var), sizeof(var));
    if (fIn.bad()) {
        throw std::exception();
    }
    return *this;
}
TStream &TFileStream::operator<<(const double &var) {
    fOut.write(reinterpret_cast<const char *>(&var), sizeof(var));
    if (fOut.bad()) {
        throw std::exception();
    }
    return *this;
}