#ifndef CPP_NOTES_INCLUDE_CPP_NOTES_UTIL_PRINT_H_
#define CPP_NOTES_INCLUDE_CPP_NOTES_UTIL_PRINT_H_

#include <iostream>

namespace cppn::util {

template<std::size_t N>
inline void PLN() {  // Print Line Number
    std::cout << '[' << N << "]: ";
}

template<std::size_t N>
inline void PLNA() {  // Print Line Number Above
    PLN<N - 1>();
}

template<std::size_t N>
inline void PLNB() {  // Print Line Number Below
    PLN<N + 1>();
}

}  // namespace cppn::util

#endif  // CPP_NOTES_INCLUDE_CPP_NOTES_UTIL_PRINT_H_
