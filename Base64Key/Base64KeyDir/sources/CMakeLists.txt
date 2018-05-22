
MESSAGE(STATUS "Project-SRC: SRC")

#指定源文件
include_directories(${CMAKE_SOURCE_DIR}/sources)
aux_source_directory(. MAIN_SRCS)
#ADD_EXECUTABLE(Base64Key main.h)
MESSAGE(STATUS "include path exsited ${MAIN_SRCS}")
ADD_EXECUTABLE(Base64Key ${MAIN_SRCS})
#
#SHARED，动态库(扩展名为.so)

#add_library(Base64Key SHARED ${MAIN_SRCS})
#STATIC，静态库(扩展名为.a)
#add_library(Base64Key STATIC ${MAIN_SRCS})
#target_link_libraries(Base64Key   m)
#对应上面ADD_EXECUTABLE 指定 生成可执行文件的输出目录
#这里才是指定的最终可执行文件的输出目录
#但是这里有一个相对路径${PROJECT_BINARY_DIR} 
#这里的值是根据我们在CMake 软件configure 然后 generate 输出makefile文件后
#我们然后到指定的外部构建路径 make 命令
#因此这里的${PROJECT_BINARY_DIR} 相对make 命令执行的目录的

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bindir)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/libdir)


MESSAGE(STATUS "EXE-Name: Base64Key")
