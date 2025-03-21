cmake_minimum_required(VERSION 3.26)

set(IDX_1 0)
while(IDX_1 LESS 5)
    message([=[Value of IDX_1 is: ]=] "${IDX_1}")
    math(EXPR IDX_1 "${IDX_1} + 1")
endwhile()

message("")

foreach(IDX_2 RANGE 3 12 4)
    message([=[Value of IDX_2 is: ]=] "${IDX_2}")
endforeach()
message([=[Value of IDX_2 outside of "foreach" loop is: ]=] "${IDX_2}") # empty

message("")

set(COLORS "red;green;blue")
# foreach(COLOR IN LISTS "${COLORS}") # does not work
foreach(COLOR IN LISTS COLORS) # works
    message([=[COLOR is ]=] "${WORD}")
endforeach()

message("")

set(FRUITS "apple;kiwi;berry")
foreach(COLOR FRUIT IN ZIP_LISTS COLORS FRUITS)
    message("${COLOR} ${FRUIT}")
endforeach()
