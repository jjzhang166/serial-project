#include "TBFileStream.h"
#include <exception>
#include <iostream>
#include <string>

TBFileStream::TBFileStream() {
}

TBFileStream::~TBFileStream() {
    CloseWrite();
    CloseRead();
}

void TBFileStream::OpenRead(const std::string &fileName) {
    if (fIn.is_open()) {
        throw std::runtime_error("TBFileStream: File is already opened");
    }
    fIn.open(fileName.c_str(), std::ifstream::binary);
    if (!fIn.is_open()) {
        throw std::runtime_error("TBFileStream: Could not open file");
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
}
void TBFileStream::OpenWrite(const std::string &fileName) {
    if (fOut.is_open()) {
        throw std::runtime_error("TBFileStream: File is already opened");
    }
    fOut.open(fileName.c_str(), std::ofstream::binary | std::ofstream::trunc);
    if (!fOut.is_open()) {
        throw std::runtime_error("TBFileStream: Could not open file");
    }
    std::string fileInfo("FileVersion");
    fOut.write(fileInfo.c_str(), fileInfo.length());
    const unsigned long temp = fCurrentVersion;
    fOut.write(reinterpret_cast<const char *>(&temp), sizeof(temp));
}

void TBFileStream::CloseRead() {
    if (fIn.is_open()) {
        fIn.close();
    }
}

void TBFileStream::CloseWrite() {
    if (fOut.is_open()) {
        fOut.close();
    }
}

void TBFileStream::Read(double *p, int size){
    fIn.read(reinterpret_cast<char *> (p), size*sizeof(double));
    if (fIn.bad()){
        throw std::runtime_error("TBFileStream:Could not read from stream");
    }
}
    
void TBFileStream::Write(const double *var, int size){
    fOut.write(reinterpret_cast<const char *> (var), size*sizeof(double));
    if (fOut.bad()) {
        throw std::runtime_error("TBFileStream:Could not write to stream");
    }
}