#include <cstdio>
#include <string>
#include <list>
#include <fstream>
#include <iostream>

//
// http://www.mr-edd.co.uk/blog/beginners_guide_streambuf
//

class TMemBuf : public std::streambuf
{
public:
    TMemBuf(const char *begin, const size_t size);
    virtual ~TMemBuf();
    std::streamsize showmanyc();
    void reinit(const char *begin, const size_t size);
    inline const size_t size() const {return end_ - begin_;}    
private:
    int_type underflow();
    int_type uflow();
    int_type pbackfail(int_type ch);
    std::streampos seekoff ( std::streamoff off, std::ios_base::seekdir way,
                            std::ios_base::openmode which = std::ios_base::in | std::ios_base::out );
    std::streampos seekpos ( std::streampos sp,
                            std::ios_base::openmode which = std::ios_base::in | std::ios_base::out);

    // copy ctor and assignment not implemented;
    // copying not allowed
    TMemBuf(const TMemBuf &);
    TMemBuf &operator= (const TMemBuf &);

private:
    const char * begin_;
    const char * end_;
    const char * current_;
};