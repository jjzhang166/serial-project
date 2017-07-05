#include "TFileStream.h"
#include <exception>
#include <iostream>

TFileStream::TFileStream() {
    fIn = new std::ifstream();
    fOut = new std::ofstream();
}

TFileStream::~TFileStream() {
    CloseWrite();
    CloseRead();
    delete fOut;
    delete fIn;
}

void TFileStream::OpenRead(const std::string &fileName) {
    if (fIn->is_open()) {
        throw std::runtime_error("TFileStream: File is already opened");
    }
    fIn->open(fileName.c_str(), std::ifstream::binary);
    if (!fIn->is_open()) {
        throw std::runtime_error("TFileStream: Could not open file");
    }

    std::string versionString("FileVersion");
    char versionRead[12];
    fIn->read(versionRead, 11); // reads header of inputfile
    versionRead[11] = '\0';     // terminates c-style string

    if (strcmp(versionString.c_str(), versionRead) == 0) { // versioned file
        fIn->read(reinterpret_cast<char *>(&fFromVersion),
                  sizeof(fFromVersion));
    } else { // unversioned file aka V0
        fFromVersion = 0;
        fIn->seekg(0, fIn->beg); // goes back to beginning of file
    }
    // fill stream
}
void TFileStream::OpenWrite(const std::string &fileName) {
    if (fOut->is_open()) {
        throw std::exception();
    }
    fOut->open(fileName.c_str(), std::ofstream::binary);
    if (!fOut->is_open()) {
        throw std::exception();
    }
    std::string fileInfo("FileVersion");
    fOut->write(fileInfo.c_str(), std::strlen(fileInfo.c_str()));
    const unsigned long temp = fCurrentVersion;
    fOut->write(reinterpret_cast<const char *>(&temp), sizeof(temp));
}

void TFileStream::CloseRead() {
    if (fIn->is_open()) {
        fIn->close();
    }
}

void TFileStream::CloseWrite() {
    if (fOut->is_open()) {
        fOut->close();
    }
}

std::istream *TFileStream::GetReadStream() {
    if (!fIn){
        throw std::runtime_error("TFileStream: there is no in stream");
    }
    return fIn;
}
std::ostream *TFileStream::GetWriteStream() {
    if (!fOut){
        throw std::runtime_error("TFileStream: there is no out stream");
    }
    return fOut;
}