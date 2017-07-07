#include "TMemBuf.h"

#include <cassert>


TMemBuf::TMemBuf(const char *begin, const size_t size) :
begin_(begin),
end_(begin + size),
current_(begin_)
{
    assert(std::less_equal<const char *>()(begin_, end_));
}

TMemBuf::int_type TMemBuf::underflow()
{
    if (current_ == end_)
        return traits_type::eof();

    return traits_type::to_int_type(*current_);
}

TMemBuf::int_type TMemBuf::uflow()
{
    if (current_ == end_)
        return traits_type::eof();

    return traits_type::to_int_type(*current_++);
}

TMemBuf::int_type TMemBuf::pbackfail(int_type ch)
{
    if (current_ == begin_ || (ch != traits_type::eof() && ch != current_[-1]))
        return traits_type::eof();

    return traits_type::to_int_type(*--current_);
}

std::streamsize TMemBuf::showmanyc()
{
    assert(std::less_equal<const char *>()(current_, end_));
    return end_ - current_;
}


std::streampos TMemBuf::seekoff ( std::streamoff off, std::ios_base::seekdir way,
                                           std::ios_base::openmode which )
{
    if (way == std::ios_base::beg)
    {
        current_ = begin_ + off;
    }
    else if (way == std::ios_base::cur)
    {
        current_ += off;
    }
    else if (way == std::ios_base::end)
    {
        current_ = end_;
    }

    if (current_ < begin_ || current_ > end_)
        return -1;


    return current_ - begin_;
}

std::streampos TMemBuf::seekpos ( std::streampos sp,
                                           std::ios_base::openmode which )
{
    current_ = begin_ + sp;

    if (current_ < begin_ || current_ > end_)
        return -1;

    return current_ - begin_;
}