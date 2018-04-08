###最低版本要求
cmake_minimum_required(VERSION 2.8)

###项目信息
project(FREE C)

###添加编译选项
ADD_DEFINITIONS(-Wall)
ADD_DEFINITIONS(-Werror)
ADD_DEFINITIONS(-Wunused)
ADD_DEFINITIONS(-std=gnu99)

###指定Debug编译模式("$ cmake -DCMAKE_BUILD_TYPE=Debug ..")
if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Setting build type to 'Debug' as none was specified.")
  set(CMAKE_BUILD_TYPE Debug)         #开发期间默认为Debug模式
  #set(CMAKE_BUILD_TYPE Release)
endif() 
set(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} -O0 -g -ggdb -funsigned-char")
set(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} -O3")

#set(LIB_NOT_COMPILED Lib_not_compiled)
###指定编译结果生成路径
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

###创建定制目标, 编译依赖对象
set(DEPS_SYSTEM_INCLUDE "/usr/include/")
set(DEPS_MYSQLSYSTEM_INCLUDE "/usr/include/mysql")
set(DEPS_MYSQLSYSTEM_LIB "/usr/lib64/mysql")
set(DEPS_INCLUDE "${CMAKE_BINARY_DIR}/deps/include")
set(DEPS_LIB "${CMAKE_BINARY_DIR}/deps/lib")
set(DEPS_BIN "${CMAKE_BINARY_DIR}/bin")
file(MAKE_DIRECTORY ${DEPS_LIB})
file(MAKE_DIRECTORY ${DEPS_INCLUDE})
file(MAKE_DIRECTORY ${DEPS_BIN})
link_directories(${DEPS_LIB})
include_directories(${DEPS_INCLUDE})
link_directories(${DEPS_MYSQLSYSTEM_LIB})
include_directories(${DEPS_MYSQLSYSTEM_INCLUDE})

#编译redis
set(REDIS_SRC "${CMAKE_SOURCE_DIR}/deps/redis")
set(REDIS_SERVER "redis-server")
set(REDIS_CLI "redis-cli")
set(REDIS_CLI_LIB "libhiredis.a")
if((NOT EXISTS ${DEPS_BIN}/${REDIS_SERVER}) OR (NOT EXISTS ${DEPS_LIB}/${REDIS_CLI_LIB}))
  message(STATUS "building ${REDIS_SRC}")

  if(LIB_NOT_COMPILED)
  execute_process(
    COMMAND make distclean
    WORKING_DIRECTORY ${REDIS_SRC})
  execute_process(
	  #COMMAND make MALLOC=libc -j 8
	COMMAND make MALLOC=jemalloc -j 8
    WORKING_DIRECTORY ${REDIS_SRC})
  endif()

  execute_process(
    COMMAND cp src/${REDIS_SERVER}  ${DEPS_BIN}
    WORKING_DIRECTORY ${REDIS_SRC})
  execute_process(
    COMMAND cp src/${REDIS_CLI}  ${DEPS_BIN}
    COMMAND cp deps/hiredis/${REDIS_CLI_LIB}  ${DEPS_LIB}
    COMMAND cp deps/hiredis/hiredis.h  ${DEPS_INCLUDE}
    COMMAND cp deps/hiredis/read.h  ${DEPS_INCLUDE}
    COMMAND cp deps/hiredis/sds.h  ${DEPS_INCLUDE}
    WORKING_DIRECTORY ${REDIS_SRC})
  
  message(STATUS "done")
endif()


###编译子目录
add_subdirectory(src)


