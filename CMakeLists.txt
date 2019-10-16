# Ozi XML main cmake file

cmake_minimum_required(VERSION 3.3)

project(ozixml VERSION 0.0.1)

# Option to install targets to env location
if(DEFINED ENV{OZIXMLHOME})
     message("-- Will install OZIXMLHOME binaries and libraries to location: " $ENV{OZIXMLHOME})
	 set(CMAKE_INSTALL_PREFIX $ENV{OZIXMLHOME})
else(DEFINED ENV{OZIXMLHOME})
     message("-- Will install OZIXMLHOME binaries and libraries to location: " ${CMAKE_CURRENT_BINARY_DIR})
	 set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})
endif(DEFINED ENV{OZIXMLHOME})


# Disable some windows specific warnings for using more modern c functions
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(MSVC)

# Options
option(WITH_testing "Allows tests to be run" ON)

if(WITH_testing MATCHES ON)
   enable_testing()
endif(WITH_testing MATCHES ON)

find_file(HAVE_STDINT_HEADER stdint.h)
if(HAVE_STDINT_HEADER)
   message("** stdint.h found")
   add_definitions(-DSWORD_HAVE_STDINT_HEADER)
else(HAVE_STDINT_HEADER)
   message("** stdint.h not found")
endif(HAVE_STDINT_HEADER)

find_file(HAVE_WCHAR_HEADER wchar.h)
if(HAVE_WCHAR_HEADER)
   message("** wchar.h found")
   add_definitions(-DSWORD_HAVE_WCHAR_H)
else(HAVE_WCHAR_HEADER)
   message("** wchar.h not found")
endif(HAVE_WCHAR_HEADER)

find_file(HAVE_STDBOOL_HEADER stdbool.h)
if(HAVE_STDBOOL_HEADER)
   message("** stdbool.h found")
   add_definitions(-DSWORD_HAVE_STDBOOL)
else(HAVE_STDBOOL_HEADER)
   message("** stdbool.h not found")
endif(HAVE_STDBOOL_HEADER)

option(USE_single_header "Builds ozixml as a single header file" OFF)

set(OZIXML_LIB_SOURCES
   ozi-xml.c
)

add_library(ozixml SHARED "${OZIXML_LIB_SOURCES}")
add_library(ozixmlstat STATIC "${OZIXML_LIB_SOURCES}")