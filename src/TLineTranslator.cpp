#include "TLineTranslator.h"
#include "TBufferedStream.h"

#include <exception>

TLineTranslator::TLineTranslator() {
    throw std::exception(); // should not be called!
}
TLineTranslator::TLineTranslator(const TLineTranslator &cp) {
    throw std::exception(); // should not be called!
}
TLineTranslator::~TLineTranslator() {
    throw std::exception(); // should not be called!
}
TLineTranslator &TLineTranslator::operator=(const TLineTranslator &cp) {
    throw std::exception(); // should not be called!
}

void TLineTranslator::StreamTranslator(TStream &stream,
                                       const unsigned long toVersion) const {
	//reads N bytes (depending on stream.fFromVersion)
	TBufferedStream buf(stream,SizeOfClass(stream.fFromVersion));
/*
    switch (stream.fFromVersion) {

    case 0: {
        UpdateFromV0(buf, 1); // returns v1 buffer
        if (toVersion == buf.fFromVersion)
            break;
    }

    case 1: {
        UpdateFromV1(buf, 2); // returns v2 buffer
        if (toVersion == buf.fFromVersion)
            break;
    }
    case 2://TLine had no changes in version 3
    case 3:{
    	UpdateFromV2(buf, 4); // returns v4 buffer
        if (toVersion == buf.fFromVersion)
            break;
    }
    default: { UpdateAttributes(buf, toVersion); }
    }
*/
}
unsigned int TLineTranslator::SizeOfClass(const unsigned int versionNumber) const{
	unsigned int totalSize = 0;
	switch(versionNumber){
		case 0:
		//stream << fXb;
    	//stream << fXe;
    	//stream << fYb;
    	//stream << fYe;
    	totalSize += 4*sizeof(double);
    	break;
    	default:
    		throw std::exception();
	}
	return totalSize;
}
void TLineTranslator::UpdateFromV0(TBufferedStream &stream,
                                   const unsigned long toVersion) const {
	/*expects to read fXb, fXe, fYb and fYe (all double variables)
		parameter toVersion isnt used because there arent any other
		custom classes to be translated, just default types*/

		TBufferedStream cp(stream);
		//stream.clear();
		stream.fFromVersion = 1;
		double aux1, aux2;
		cp >> aux1; //reads fXb
		stream << aux1;
		cp >> aux1; //reads fXe
		cp >> aux2; //reads fYb
		stream << aux2;
		stream << aux1;



	//must return fXb, fYb, fXe, fYe (all double variables)
}