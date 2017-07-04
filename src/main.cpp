#include "TLine.h"
#include "TStream.h"
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc != 2 || strlen(argv[1]) != 1) {
        std::cout << "usage:" << argv[0] << " [0,1]"
                  << " - 0 for reading 1 for writing" << std::endl;
        return 1;
    }
    bool isSaving = false;
    if (argv[1][0] == '1') {
        isSaving = true;
    }
    std::string fileName("../outFiles/datav0.dat");
    TLine testLine;
    if (isSaving) {
        std::cout << "printing..." << std::endl;
        TStream out;
        out.OpenWrite(fileName);
        testLine.SetBeginPoint(0., 0.);
        testLine.SetEndPoint(1.e23, 1.);

        testLine.Write(out);
    } else {
        std::cout << "reading..." << std::endl;
        TStream in;
        in.OpenRead(fileName);
        testLine.Read(in);
    }
    double x, y;
    testLine.GetBeginPoint(x, y);
    std::cout << x << "\t" << y << std::endl;
    testLine.GetEndPoint(x, y);
    std::cout << x << "\t" << y << std::endl;

    return 0;
}