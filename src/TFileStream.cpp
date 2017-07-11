#include "TFileStream.h"
#include <exception>
#include <iostream>
#include <string>

TFileStream::TFileStream() {
}

TFileStream::~TFileStream() {
    CloseWrite();
    CloseRead();
}

void TFileStream::OpenRead(const std::string &fileName) {
    if (fIn.is_open()) {
        throw std::runtime_error("TFileStream: File is already opened");
    }
    fIn.open(fileName.c_str(), std::ifstream::binary);
    if (!fIn.is_open()) {
        throw std::runtime_error("TFileStream: Could not open file");
    }

    std::string versionString("FileVersion");
    char versionRead[12];
    fIn.read(versionRead, 11); // reads header of inputfile
    versionRead[11] = '\0';     // terminates c-style string

    if (versionString.compare(versionRead) == 0) { // versioned file
        fIn.read(reinterpret_cast<char *>(&fFromVersion),
                  sizeof(fFromVersion));
    } else { // unversioned file aka V0
        fFromVersion = 0;
        fIn.seekg(0, fIn.beg); // goes back to beginning of file
    }
    // fill stream
}
void TFileStream::OpenWrite(const std::string &fileName) {
    if (fOut.is_open()) {
        throw std::runtime_error("TFileStream: File is already opened");
    }
    fOut.open(fileName.c_str(), std::ofstream::binary | std::ofstream::trunc);
    if (!fOut.is_open()) {
        throw std::runtime_error("TFileStream: Could not open file");
    }
    std::string fileInfo("FileVersion");
    fOut.write(fileInfo.c_str(), fileInfo.length());
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

std::istream &TFileStream::GetReadStream() {
    return fIn;
}
std::ostream &TFileStream::GetWriteStream() {
    return fOut;
}