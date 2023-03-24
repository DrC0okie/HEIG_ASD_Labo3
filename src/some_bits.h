/*-----------------------------------------------------------------------------------
File name : some_bits.h
Author(s) : Antoine Rochat
Creation date : 23.03.2022
Description : Helping class to get bit groups
Remark(s) : Provided by the assistant for the laboratory
Compiler : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------*/

#ifndef SOME_BITS
#define SOME_BITS

template<typename T>
class SomeBits {
    size_t shift;
    T mask;
public:
    SomeBits(size_t nombreDeBits, size_t part)
            : shift(part * nombreDeBits),
              mask(T((T(1u) << nombreDeBits) - T(1u))) {

    }
    T operator()(T const& t) {
        return T(mask & (t >> shift));
    }
};

#endif