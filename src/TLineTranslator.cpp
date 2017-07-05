#include "TLineTranslator.h"
#include "TBufferedStream.h"

#include <exception>

TLineTranslator::TLineTranslator() {}
TLineTranslator::~TLineTranslator() {}

void TLineTranslator::StreamTranslator(TStream &stream,
                                       const unsigned long toVersion) const {
    // reads N bytes (depending on stream.fFromVersion)
    // double w,x,y,z;
    // stream>>w;
    // stream>>x;
    // stream>>y;
    // stream>>z;
    // std::cout<<w<<std::endl;
    // std::cout<<x<<std::endl;
    // std::cout<<y<<std::endl;
    // std::cout<<z<<std::endl;
    // return;
    TBufferedStream buf(stream, SizeOfClass(stream.fFromVersion));
    /*
        switch (stream.fFromVersion) {

        case 0: //TLine had changes in version 1
            UpdateFromV0(buf, 1); // returns v1 buffer
            if (toVersion == buf.fFromVersion)
                break;

        case 1: //TLine had changes in version 2
            UpdateFromV1(buf, 2); // returns v2 buffer
            if (toVersion == buf.fFromVersion)
                break;

        case 2://TLine had no changes in version 3
        case 3://TLine had changes in version 4
            UpdateFromV2(buf, 4); // returns v4 buffer
            if (toVersion == buf.fFromVersion)
                break;

        default:  UpdateAttributes(buf, toVersion);
        }
    */
    switch (stream.fFromVersion) {

    case 0:                   // TLine had changes in version 1
        UpdateFromV0(buf, 1); // returns v1 buffer
        if (toVersion == buf.fFromVersion)
            break;

    default:
        UpdateAttributes(buf, toVersion);
    }
}
unsigned int
TLineTranslator::SizeOfClass(const unsigned int &versionNumber) const {
    unsigned int totalSize = 0;
    switch (versionNumber) {
    case 0:
        // stream << fXb;
        // stream << fXe;
        // stream << fYb;
        // stream << fYe;
        totalSize += 4 * sizeof(double);
        break;
    default:
        // stream << fXb;
        // stream << fYb;
        // stream << fXe;
        // stream << fYe;
        totalSize += 4 * sizeof(double);
        break;
    }
    return totalSize;
}

void TLineTranslator::UpdateAttributes(TBufferedStream &stream,
                                       const unsigned long &toVersion) const {
    /*expects to read the attributes according to the most recent version
        of TLine. However, the if there are objects, their StreamTranslator
        will be called in order to account for changes in their data structures.
        In V1, this method will do nothing, once the attributes are all
        of type the primitive type double*/
}

void TLineTranslator::UpdateFromV0(TBufferedStream &stream,
                                   const unsigned long &toVersion) const {
    /*expects to read fXb, fXe, fYb and fYe (all double variables)
        parameter toVersion isnt used because there arent any other
        custom classes to be translated, just default types*/
    TBufferedStream cp(stream);
    double aux1, aux2;
    cp >> aux1; // reads fXb
    std::cout<<aux1<<std::endl;
    stream << aux1;
    cp >> aux2; // reads fXe
    cp >> aux1; // reads fYb
    std::cout<<aux1<<std::endl;
    std::cout<<aux2<<std::endl;
    stream << aux1;
    stream << aux2;
    cp >> aux1; // reads fYe
    std::cout<<aux1<<std::endl;
    stream << aux1;

    stream.TransferBuffers();
    stream.fFromVersion = 1;
    // must return fXb, fYb, fXe, fYe (all double variables)
}