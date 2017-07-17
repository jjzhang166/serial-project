#ifndef TPOINTTRANSLATOR_H
#define TPOINTTRANSLATOR_H
#include "TBufferedStream.h"
#include "TPoint.h"

class TPointTranslator {
public:

    static TBufferedStream UpdateStream(TStream &baseStream,
            const unsigned long toVersion) {
        // reads N bytes (depending on stream.fFromVersion)
        TBufferedStream buf(baseStream);
        // TPoint didnt exist prior to version 2
        if (baseStream.fFromVersion < 2) {
            throw std::runtime_error("TPointTranslator:Trying to read a TPoint "
                    "from a version prior to its creation");
        }

        switch (baseStream.fFromVersion) {
            case 2:
                UpdateFromV2(buf); // returns v3 buffer
                if (toVersion == buf.fFromVersion) {
                    break;
                }
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
            case 2:
                // stream << fX;
                // stream << fY;
                totalSize += 2 * sizeof (double);
                break;
            default: // 3 onwards
                // stream << fX;
                // stream << fY;
                // stream << fZ;
                totalSize += 3 * sizeof (double);
                break;
        }
        return totalSize;
    }

    static void UpdateAttributes(TBufferedStream & stream,
            const unsigned long & toVersion) {
        stream.BeginUpdate();
        /*expects to read the attributes according to the most recent version
            of TLine. However, if any attribute is an object, its
           StreamTranslator will be called in order to account for changes in
           its data structure.*/
        double aux;
        stream >> aux; // reads fX
        stream << aux;
        stream >> aux; // reads fY
        stream << aux;
        stream >> aux; // reads fZ
        stream << aux;
        stream.EndUpdate(toVersion);
    }

    static void UpdateFromV2(TBufferedStream &stream) {
        stream.BeginUpdate();
        //expects to read fX and fY(all double variables)
        double aux;
        stream >> aux; // reads fX
        stream << aux;
        stream >> aux; // reads fY
        stream << aux;
        aux = 0.; // creates fZ default value
        stream << aux;

        // must return fX, fY and fZ(all double variables)
        stream.EndUpdate(3);
    }

private:
    TPointTranslator();
    ~TPointTranslator();
};
#endif // TPOINTTRANSLATOR_H