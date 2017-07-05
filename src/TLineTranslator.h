#ifndef TLINETRANSLATOR_H
#define TLINETRANSLATOR_H
#include "TBufferedStream.h"

class TLineTranslator {
  public:
    static const unsigned long fCurrentVersion = 1;
    TLineTranslator();
    ~TLineTranslator();

    void StreamTranslator(TStream &origStream,
                          const unsigned long toVersion) const;
    unsigned int SizeOfClass(const unsigned int &versionNumber) const;
    /****************************
     *   translator methods      *
     ****************************/
    void UpdateAttributes(TBufferedStream &stream, const unsigned long &toVersion) const;

    void UpdateFromV0(TBufferedStream &stream, const unsigned long &toVersion) const;
};
#endif // TLINETRANSLATOR_H