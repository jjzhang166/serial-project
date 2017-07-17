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
    fIn.open(fileName.c_str());
    if (!fIn.is_open()) {
        throw std::runtime_error("TFileStream: Could not open file");
    }

    fFromVersion = 0;
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
    fOut.write(reinterpret_cast<const char *> (&temp), sizeof (temp));
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

void TFileStream::Read(double *p, int size) {
    char buf[100];
    if (!fIn) {
        throw std::runtime_error("TFileStream: input stream not set.");
    }
    if (size) {
        for (int c = 0; c < size; c++) fIn >> p[c];
        fIn.getline(buf, 100);
    }
}

void TFileStream::Write(const double *p, int size) {
    for (int c = 0; c < size; c++) fOut << p[c] << std::endl;
}