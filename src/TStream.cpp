#include "TStream.h"

TStream::TStream() {}

TStream::TStream(const TStream &cp) {}

TStream::~TStream() {
	CloseWrite();
	CloseRead();
}
TStream &TStream::operator=(const TStream &cp) { return *this; }

void TStream::OpenRead(const std::string &fileName) {
	if(fIn.is_open()){
		throw std::exception();
	}
	fIn.open(fileName.c_str(), std::ifstream::binary);
	if(!fIn.is_open()){
		throw std::exception();
	}
}
void TStream::OpenWrite(const std::string &fileName) {
	if(fOut.is_open()){
		throw std::exception();
	}
	fOut.open(fileName.c_str(), std::ofstream::binary);
	if(!fOut.is_open()){
		throw std::exception();
	}
}

void TStream::CloseRead(){
	if(fIn.is_open()){
		fIn.close();
	}
}

void TStream::CloseWrite(){
	if(fOut.is_open()){
		fOut.close();
	}
}

TStream &TStream::operator>>(double &var){
	fIn.read(reinterpret_cast<char*>(&var),sizeof(var));
	//fIn>>var;
	if (fIn.bad()){
		throw std::exception();
	}
	return *this;
}
TStream &TStream::operator<<(const double &var){
	fOut.write(reinterpret_cast<const char*>(&var),sizeof(var));
	//fOut<<var;
	if (fOut.bad()){
		throw std::exception();
	}
	return *this;
}