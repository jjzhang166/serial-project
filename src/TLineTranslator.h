#ifndef TLINETRANSLATOR_H
#define TLINETRANSLATOR_H
#include "TBufferedStream.h"
#include "TLine.h"
#include "TPointTranslator.h"

class TLineTranslator {
public:

    static TBufferedStream UpdateStream(TStream &baseStream,
            const unsigned long toVersion) {
        TBufferedStream buf(baseStream);
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

    static void UpdateAttributes(TBufferedStream &stream,
            const unsigned long &toVersion) {
        stream.BeginUpdate();
        /*expects to read the attributes according to the most recent version
            of TLine. However, if any attribute is an object, its
           StreamTranslator will be called in order to account for changes in
           its data structure.*/
        stream << TPointTranslator::UpdateStream(stream, toVersion);
        stream << TPointTranslator::UpdateStream(stream, toVersion);
        stream.EndUpdate(toVersion);
    }

    static void UpdateFromV0(TBufferedStream &stream) {
        stream.BeginUpdate();
        //expects to read fXb, fXe, fYb and fYe (all double variables)
        double aux1, aux2;
        stream.Read(&aux1); // reads fXb
        stream.Write(&aux1);
        stream.Read(&aux2); // reads fXe
        stream.Read(&aux1); // reads fYb
        stream.Write(&aux1);
        stream.Write(&aux2);
        stream.Read(&aux1); // reads fYe
        stream.Write(&aux1);

        // must return fXb, fYb, fXe, fYe (all double variables)
        stream.EndUpdate(1);
    }

    static void UpdateFromV1(TBufferedStream &stream) {
        stream.BeginUpdate();
        //expects to read fXb, fYb, fXe and fYe (all double variables) 

        // must return fXb, fYb, fXe, fYe (all double variables)
        double aux;
        stream.Read(&aux); // reads fXb
        stream.Write(&aux);
        stream.Read(&aux); // reads fYb
        stream.Write(&aux);
        stream.Read(&aux); // reads fXe
        stream.Write(&aux);
        stream.Read(&aux); // reads fYe
        stream.Write(&aux);
        stream.EndUpdate(2);
    }

private:
    TLineTranslator();
    ~TLineTranslator();
};
#endif // TLINETRANSLATOR_H