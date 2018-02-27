
# CMake 最低版本要求，低于3.8 构建过程会被终止。 

CMAKE_MINIMUM_REQUIRED(VERSION 3.8)


#定义工程名称

PROJECT(HELLO) 

#设定前缀默认安装目录

SET(CMAKE_INSTALL_PREFIX ~/Desktop/TestCPlus/TempPrefix) 

# 打印相关消息消息

MESSAGE(STATUS "Project: HEllo-Test")                
MESSAGE(STATUS "Project Directory: ${PROJECT_SOURCE_DIR}")
MESSAGE(STATUS "Prefix Directory: ${CMAKE_INSTALL_PREFIX}")  

IF (UNIX)
   MESSAGE("这个是UNIX操作系统")
ENDIF (UNIX)

#这里ADD 是添加 工程根目录的CMakeList cmake时 

#要执行哪些子目录的CMakelist 对应工程目录结构的

#这个指令用于向当前工程添加存放源文件的子目录，并可以指定中间二进制和目标二进制存放的位置

#安装脚本
INSTALL(PROGRAMS run.sh DESTINATION ${PROJECT_BINARY_DIR}/bindir)

#ADD_SUBDIRECTORY(DOC doc)

#由于我们使用CMake软件指定外部构建的 build 路径了
#因此下面的makefile 生成文件的目录 libout binout 目录 是相对于
#外部构建路径build 的指定路径的

#这里我们修改了默认Cmake的 library生成的makefile 目录 lib 改为 libout
#这里 并不是指定生成的 最终lib 库 .a  等文件最终的生成目录

ADD_SUBDIRECTORY(LIB libout)

#这里我们修改了默认Cmake的 bin生成的makefile 目录 lib 改为 libout
#这里 并不是指定生成的 最终hellobin 可执行文件的最终的生成目录

ADD_SUBDIRECTORY(SRC binout)


#设置输出项目工程文档

ADD_SUBDIRECTORY(DOC docout)






