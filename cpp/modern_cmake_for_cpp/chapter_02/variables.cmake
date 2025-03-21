cmake_minimum_required(VERSION 3.26)

set(MyString1 "Text1")
set([[My String2]] "Text2")
set("My String 3" "Text3")
message(STATUS ${MyString1})
message(STATUS ${My\ String2})
message(STATUS ${My\ String\ 3})

set(MY_VAR_1 "value of MY_VAR_1")
set(MY_VAR_2 MY_VAR_1)
set(${MY_VAR_2} "value of something")
message("Value of MY_VAR_1: " \ ${MY_VAR_1}) # value of something
message("Value of MY_VAR_2: " \ ${MY_VAR_2}) # MY_VAR_1

set(MY_VAR_3 "value of MY_VAR_3")
set(MY_VAR_4 "value of MY_VAR_4")
set(VAR_IDX 3)
message(${MY_VAR_${VAR_IDX}}) # value of MY_VAR_3


message("")
message([=[System variable PATH (printed with "$ENV{PATH}"): ]=] $ENV{PATH})
message("")
message([=[Normal variable PATH (printed with "${PATH}"): ]=] ${PATH})
