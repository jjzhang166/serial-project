#ifndef TPOINTTRANSLATOR_H
#define TPOINTTRANSLATOR_H
#include "TBufferedStream.h"
#include "TPoint.h"

class TPointTranslator {
  public:
    static TBufferedStream UpdateStream(TStream &baseStream,
                                        const unsigned long toVersion) {
        // reads N bytes (depending on stream.fFromVersion)
        TBufferedStream buf(baseStream, SizeOfClass(baseStream.fFromVersion));
        // TPoint didnt exist prior to version 2
        if (baseStream.fFromVersion < 2) {
            throw std::runtime_error("TPointTranslator:Trying to read a TPoint "
                                     "from a version prior to its creation");
        }

        switch (baseStream.fFromVersion) {
            //no old versions, current is the most recent one
        default:
            UpdateAttributes(buf, toVersion);
        }
        return buf;
    }

    static unsigned int SizeOfClass(const unsigned int &versionNumber) {
        unsigned int totalSize = 0;
        if (versionNumber < 2) {
            throw std::runtime_error(
                "TPointTranslator:Trying to calculate the size of a TPoint "
                "from a version prior to its creation");
        }
        switch (versionNumber) {
            //no old versions, current is the most recent one
        default:
            //stream << fX;
            //stream << fY;
            totalSize += 2 * sizeof(double);
            break;
        }
        return totalSize;
    }

    static void UpdateAttributes(TBufferedStream & /*stream*/,
                                 const unsigned long & /*toVersion*/) {
        /*expects to read the attributes according to the most recent version
            of TLine. However, if any attribute is an object, its
           StreamTranslator will be called in order to account for changes in
           its data structure. In V1, this method will do nothing, since the
           attributes are all of the primitive type double*/
    }

  private:
    TPointTranslator();
    ~TPointTranslator();
};
#endif // TPOINTTRANSLATOR_H