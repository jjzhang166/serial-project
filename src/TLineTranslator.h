#ifndef TLINETRANSLATOR_H
#define TLINETRANSLATOR_H
#include "TBufferedStream.h"

class TLineTranslator {
public:
    static const unsigned long fCurrentVersion = 1;

    static TBufferedStream UpdateStream(TStream &baseStream,
            const unsigned long toVersion) {
        // reads N bytes (depending on stream.fFromVersion)
        TBufferedStream buf(baseStream, SizeOfClass(baseStream.fFromVersion));
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
        switch (baseStream.fFromVersion) {

            case 0: // TLine had changes in version 1
                UpdateFromV0(buf, 1); // returns v1 buffer
                if (toVersion == buf.fFromVersion)
                    break;

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
            default:
                // stream << fXb;
                // stream << fYb;
                // stream << fXe;
                // stream << fYe;
                totalSize += 4 * sizeof (double);
                break;
        }
        return totalSize;
    }

    static void UpdateAttributes(TBufferedStream &/*stream*/,
            const unsigned long &/*toVersion*/) {
        /*expects to read the attributes according to the most recent version
            of TLine. However, if any attribute is an object, its StreamTranslator
            will be called in order to account for changes in its data structure.
            In V1, this method will do nothing, since the attributes are all
            of the primitive type double*/
    }

    static void UpdateFromV0(TBufferedStream &stream,
            const unsigned long &/*toVersion*/) {
        /*expects to read fXb, fXe, fYb and fYe (all double variables)
            parameter toVersion isn't used because there aren't any other
            custom classes to be translated, just default types*/
        double aux1, aux2;
        stream >> aux1; // reads fXb
        stream << aux1;
        stream >> aux2; // reads fXe
        stream >> aux1; // reads fYb
        stream << aux1;
        stream << aux2;
        stream >> aux1; // reads fYe
        stream << aux1;
        
        stream.TransferBuffers();
        stream.fFromVersion = 1;
        // must return fXb, fYb, fXe, fYe (all double variables)
    }

private:
    TLineTranslator();
    ~TLineTranslator();
};
#endif // TLINETRANSLATOR_H