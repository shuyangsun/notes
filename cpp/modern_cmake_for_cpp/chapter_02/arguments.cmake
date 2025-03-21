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
