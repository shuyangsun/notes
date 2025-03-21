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
    message([=["VAR_1" is evaluated to: ]=] True) # printed
else()
    message([=["VAR_1" is evaluated to: ]=] False)
endif()

if(${VAR_1})
    message([=[${VAR_1} is evaluated to: ]=] True) # printed
else()
    message([=[${VAR_1} is evaluated to: ]=] False)
endif()

if("${VAR_1}")
    message([=["${VAR_1}" is evaluated to: ]=] True) # printed
else()
    message([=["${VAR_1}" is evaluated to: ]=] False)
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

if(${VAR_2})
    message([=[${VAR_2} is evaluated to: ]=] True)
else()
    message([=[${VAR_2} is evaluated to: ]=] False) # printed
endif()

if("${VAR_2}")
    message([=["${VAR_2}" is evaluated to: ]=] True)
else()
    message([=["${VAR_2}" is evaluated to: ]=] False) # printed
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

message("")

if("1.3.2" LESS_EQUAL "1.3.15")
    message([=["1.3.2" LESS_EQUAL "1.3.15" is evaluated to: ]=] True) # printed
else()
    message([=["1.3.2" LESS_EQUAL "1.3.15" is evaluated to: ]=] False)
endif()

if("1.3.2" STRLESS_EQUAL "1.3.15")
    message([=["1.3.2" STRLESS_EQUAL "1.3.15" is evaluated to: ]=] True)
else()
    message([=["1.3.2" STRLESS_EQUAL "1.3.15" is evaluated to: ]=] False) # printed
endif()

if("1.3.2" VERSION_LESS_EQUAL "1.3.15")
    message([=["1.3.2" VERSION_LESS_EQUAL "1.3.15" is evaluated to: ]=] True) # printed
else()
    message([=["1.3.2" VERSION_LESS_EQUAL "1.3.15" is evaluated to: ]=] False)
endif()
