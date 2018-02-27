SET(SRC_LIST main.cpp)


SET(IncludePath ~/Desktop/TestCPlus/CPlusBuild/include/hello/)

FIND_PATH(IncludePath hello.h)

IF(NOT IncludePath)

MESSAGE(FATAL_ERROR "include path not exsited")

ENDIF(NOT IncludePath)

MESSAGE(STATUS "include path exsited ${IncludePath}")

INCLUDE_DIRECTORIES(${IncludePath})

SET(LibPath ~/Desktop/TestCPlus/CPlusBuild/libsdir)


FIND_LIBRARY(LIBHELLO_PATH hello ~/Desktop/TestCPlus/CPlusBuild/libsdir)

IF(NOT LIBHELLO_PATH)

MESSAGE(FATAL_ERROR "libhello not found")

ENDIF(NOT LIBHELLO_PATH) 

MESSAGE(STATUS ${LIBHELLO_PATH} " found")

LINK_DIRECTORIES(${LibPath})

ADD_EXECUTABLE(main ${SRC_LIST})

TARGET_LINK_LIBRARIES(main hello)
