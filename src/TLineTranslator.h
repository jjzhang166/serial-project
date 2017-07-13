#ifndef TLINETRANSLATOR_H
#define TLINETRANSLATOR_H
#include "TBufferedStream.h"
#include "TLine.h"
#include "TPointTranslator.h"

class TLineTranslator {
public:

    static TBufferedStream UpdateStream(TStream &baseStream,
            const unsigned long toVersion) {
        // reads N bytes (depending on stream.fFromVersion)
        TBufferedStream buf(baseStream, SizeOfClass(baseStream.fFromVersion));
        /*
            switch (stream.fFromVersion) {

            case 0: //TLine had changes in version 1
                UpdateFromV0(buf); // returns v1 buffer
                if (toVersion == buf.fFromVersion)
                    break;

            case 1: //TLine had changes in version 2
                UpdateFromV1(buf); // returns v2 buffer
                if (toVersion == buf.fFromVersion)
                    break;

            case 2://TLine had no changes in version 3
            case 3://TLine had changes in version 4
                UpdateFromV2(buf); // returns v4 buffer
                if (toVersion == buf.fFromVersion)
                    break;

            default:  UpdateAttributes(buf, toVersion);
            }
         */
        switch (baseStream.fFromVersion) {

            case 0: // TLine had changes in version 1
                UpdateFromV0(buf); // returns v1 buffer
                if (toVersion == buf.fFromVersion) {
                    break;
                }
            case 1: // TLine had changes in version 2
                UpdateFromV1(buf); // returns v2 buffer
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
        switch (versionNumber) {
            case 0:
                // stream << fXb;
                // stream << fXe;
                // stream << fYb;
                // stream << fYe;
                totalSize += 4 * sizeof (double);
                break;
            case 1:
                // stream << fXb;
                // stream << fYb;
                // stream << fXe;
                // stream << fYe;
                totalSize += 4 * sizeof (double);
                break;
            default: //2 onwards
                //pB.Write(stream);
                //pE.Write(stream);
                totalSize += 2 * TPointTranslator::SizeOfClass(versionNumber);
                break;
        }
        return totalSize;
    }

    static void UpdateAttributes(TBufferedStream &baseStream,
            const unsigned long &toVersion) {
        /*expects to read the attributes according to the most recent version
            of TLine. However, if any attribute is an object, its
           StreamTranslator will be called in order to account for changes in
           its data structure.*/
        baseStream << TPointTranslator::UpdateStream(baseStream, toVersion);
        baseStream << TPointTranslator::UpdateStream(baseStream, toVersion);
        baseStream.fFromVersion = toVersion;
    }

    static void UpdateFromV0(TBufferedStream &stream) {
        //expects to read fXb, fXe, fYb and fYe (all double variables)
        double aux1, aux2;
        stream >> aux1; // reads fXb
        stream << aux1;
        stream >> aux2; // reads fXe
        stream >> aux1; // reads fYb
        stream << aux1;
        stream << aux2;
        stream >> aux1; // reads fYe
        stream << aux1;

        stream.fFromVersion = 1;
        // must return fXb, fYb, fXe, fYe (all double variables)
    }

    static void UpdateFromV1(TBufferedStream &stream) {
        //expects to read fXb, fYb, fXe and fYe (all double variables) 
        stream.fFromVersion = 2;
        // must return fXb, fYb, fXe, fYe (all double variables)
        //does nothing, since the use of TPoint preserves the file structure.
    }

private:
    TLineTranslator();
    ~TLineTranslator();
};
#endif // TLINETRANSLATOR_H