cmake_minimum_required(VERSION 3.26)

set(VAR_1 True)
if(${VAR_1})
    message([=[${VAR_1} is evaluated to: ]=] True) # printed
else()
    message([=[${VAR_1} is evaluated to: ]=] False)
endif()

if(VAR_1)
    message([=[VAR_1 is evaluated to: ]=] True) # printed
else()
    message([=[VAR_1 is evaluated to: ]=] False)
endif()

if("VAR_1")
    message([=["VAR_1" is evaluated to: ]=] True)
else()
    message([=["VAR_1" is evaluated to: ]=] False) # printed
endif()

message("")

set(VAR_2 False)
if(${VAR_2})
    message([=[${VAR_2} is evaluated to: ]=] True)
else()
    message([=[${VAR_2} is evaluated to: ]=] False) # printed
endif()

if(VAR_2)
    message([=[VAR_2 is evaluated to: ]=] True)
else()
    message([=[VAR_2 is evaluated to: ]=] False) # printed
endif()

if("VAR_2")
    message([=["VAR_2" is evaluated to: ]=] True)
else()
    message([=["VAR_2" is evaluated to: ]=] False) # printed
endif()

message("")

set(FOO BAR)
if(FOO) # same as if(DEFINED FOO)
    message([=[FOO is evaluated to: ]=] True) # printed
else()
    message([=[FOO is evaluated to: ]=] False)
endif()

if(DEFINED FOO)
    message([=[DEFINED FOO is evaluated to: ]=] True) # printed
else()
    message([=[DEFINED FOO is evaluated to: ]=] False)
endif()

if(DEFINED "FOO")
    message([=[DEFINED "FOO" is evaluated to: ]=] True) # printed
else()
    message([=[DEFINED "FOO" is evaluated to: ]=] False)
endif()


if(DEFINED ${FOO})
    message([=[DEFINED ${FOO} is evaluated to: ]=] True)
else()
    message([=[DEFINED ${FOO} is evaluated to: ]=] False) # printed
endif()

if(DEFINED "${FOO}")
    message([=[DEFINED "${FOO}" is evaluated to: ]=] True)
else()
    message([=[DEFINED "${FOO}" is evaluated to: ]=] False) # printed
endif()
