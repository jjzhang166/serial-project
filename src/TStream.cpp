#include "TStream.h"

TStream::TStream() {}

TStream::TStream(const TStream &cp) {}

TStream::~TStream() {
	CloseWrite();
	CloseRead();
}
TStream &TStream::operator=(const TStream &cp) { return *this; }

void TStream::OpenRead(const std::string &fileName) {
	if(iStream.is_open()){
		throw std::exception();
	}
	iStream.open(fileName.c_str(), std::ifstream::binary);
	if(!iStream.is_open()){
		throw std::exception();
	}
}
void TStream::OpenWrite(const std::string &fileName) {
	if(oStream.is_open()){
		throw std::exception();
	}
	oStream.open(fileName.c_str(), std::ofstream::binary);
	if(!oStream.is_open()){
		throw std::exception();
	}
}

void TStream::CloseRead(){
	if(iStream.is_open()){
		iStream.close();
	}
}

void TStream::CloseWrite(){
	if(oStream.is_open()){
		oStream.close();
	}
}

TStream &TStream::operator>>(double &var){
	iStream.read(reinterpret_cast<char*>(&var),sizeof(var));
	//iStream>>var;
	if (iStream.bad()){
		throw std::exception();
	}
	return *this;
}
TStream &TStream::operator<<(const double &var){
	oStream.write(reinterpret_cast<const char*>(&var),sizeof(var));
	//oStream<<var;
	if (oStream.bad()){
		throw std::exception();
	}
	return *this;
}