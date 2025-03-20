cmake_minimum_required(VERSION 3.26)

message(STATUS "Hello!")
message(STATUS message ("Hello!"))

set(NAME "Shuyang")

message(STATUS "Strings can be
multi-line too. My name
is ${NAME}.
")

message(STATUS "==========================")

message(STATUS [[# This is no longer a comment.
Another multi-line string, but]])

message(STATUS [==[
not interpreted. My name
is ${NAME}.]==])


message(STATUS "hello;WORLD")
message(STATUS hello;WORLD)
message(() () ())

set(MyString1 "Text1")
set([[My String2]] "Text2")
set("My String 3" "Text3")
message(STATUS ${MyString1})
message(STATUS ${My\ String2})
message(STATUS ${My\ String\ 3})
