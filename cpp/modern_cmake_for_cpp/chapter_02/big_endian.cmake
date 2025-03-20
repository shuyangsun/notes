cmake_minimum_required(VERSION 3.26)

include(TestBigEndian)
if(IS_BIG_ENDIAN)
    message("Big endian system")
else()
    message("Little endian system")
endif()
