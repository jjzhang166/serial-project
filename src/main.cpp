#include "TLine.h"
#include "TBFileStream.h"
#include "TBufferedStream.h"
#include "TFileStreamFactory.h"
#include <iostream>
#include <string>
#include <string.h>

int main(int argc, char *argv[]) {    
    if (argc != 2 || strlen(argv[1]) != 1) {
        std::cout << "usage:" << argv[0] << " [0,1]"
                  << " - 0 for reading 1 for writing" << std::endl;
        return 1;
    }
    if (argv[1][0] != '0' && argv[1][0] != '1')
    {
    	std::cout << "Usage:" << argv[0] << " [0,1]"
                  << " - 0 for reading 1 for writing" << std::endl;
        return 1;
    }
    bool isSaving = false;
    if (argv[1][0] == '1') {
        isSaving = true;
    }
    std::string fileName("../outFiles/datav");
    TLine testLine;
    if (isSaving) {
    	fileName.append(std::to_string(TStream::fCurrentVersion));
    	fileName.append(".dat");
        std::cout << "printing..." << std::endl;
        TBFileStream out;
        out.OpenWrite(fileName);
        testLine.SetBeginPoint(0., 0., 0.);
        testLine.SetEndPoint(1.e23, 1., 0.);

        testLine.Write(out);
    } else {
        std::cout << "Which version should I read from? " << std::endl;
        unsigned int versionNumber;
        std::cin >> versionNumber;
        fileName.append(std::to_string(versionNumber));
    	fileName.append(".dat");
        TStream *in = TFileStreamFactory::openReadFileStream(fileName);
        std::cout << "reading from version " << in->fFromVersion << " @ version "
              << TStream::fCurrentVersion << std::endl;
        testLine.Read(*in);
        delete in;
    }
    double x, y,z;
    testLine.GetBeginPoint(x, y,z);
    std::cout << x << "\t" << y <<  "\t" << z << std::endl;
    testLine.GetEndPoint(x, y,z);
    std::cout << x << "\t" << y <<  "\t" << z << std::endl;

    return 0;
}