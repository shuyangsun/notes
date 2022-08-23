#ifndef CPP_NOTES_INCLUDE_CPP_NOTES_UTIL_PRINT_H_
#define CPP_NOTES_INCLUDE_CPP_NOTES_UTIL_PRINT_H_

#include <iostream>
#include <boost/type_index.hpp>

#define PRINT_TYPE(x) std::cout << boost::typeindex::type_id_with_cvr<decltype(x)>().pretty_name() << std::endl;
#define PRINTLN_TYPE(x) PRINT_TYPE(x) << std::endl;

namespace cppn::util {

}  // namespace cppn::util

#endif  // CPP_NOTES_INCLUDE_CPP_NOTES_UTIL_PRINT_H_
