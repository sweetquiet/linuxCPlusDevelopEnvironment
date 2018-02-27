# CMake 最低版本要求，低于3.8 构建过程会被终止。 

CMAKE_MINIMUM_REQUIRED(VERSION 3.8)


PROJECT(NEWHELLO)

SET(CMAKE_INSTALL_PREFIX ~/Desktop/TestCPlusLibUse/TempPrefix) 


# 打印相关消息消息

MESSAGE(STATUS "Project: using lib for NEWHELLO")                
MESSAGE(STATUS "Project Directory: ${PROJECT_SOURCE_DIR}")
MESSAGE(STATUS "Prefix Directory: ${CMAKE_INSTALL_PREFIX}")  

IF (UNIX)
   MESSAGE("这个是UNIX操作系统")
ENDIF (UNIX)

ADD_SUBDIRECTORY(src binout)