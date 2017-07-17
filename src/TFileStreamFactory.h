/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TFileStreamFactory.h
 * Author: quinelato
 *
 * Created on July 17, 2017, 2:33 PM
 */

#ifndef TFILESTREAMFACTORY_H
#define TFILESTREAMFACTORY_H

#include <string>
#include "TStream.h"
#include "TBFileStream.h"
#include "TFileStream.h"

class TFileStreamFactory {
public:
    static TStream *openReadFileStream(const std::string &fileName){
        TBFileStream *file = new TBFileStream();
        file->OpenRead(fileName);
        if (file->fFromVersion == 0){
            file->CloseRead();
            delete file;
            TFileStream *ascii_file = new TFileStream();
            ascii_file->OpenRead(fileName);
            return ascii_file;
        } else {
            return file;
        }
    }
private:

};

#endif /* TFILESTREAMFACTORY_H */

