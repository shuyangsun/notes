cmake_minimum_required(VERSION 3.26)

project(CMakeWinMacOS VERSION 2025.03.23.130930 LANGUAGES CXX)

add_executable(main
    WIN32 # Do not show the console when built for Windows.
    MACOSX_BUNDLE # Produce an application that can be opened.
    main.cc
)
