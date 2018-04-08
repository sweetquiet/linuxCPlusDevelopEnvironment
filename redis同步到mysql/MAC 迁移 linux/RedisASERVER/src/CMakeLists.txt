#指定源文件
include_directories(${CMAKE_SOURCE_DIR}/src)
aux_source_directory(. MAIN_SRCS)

#生成目标
add_executable(aserver-mysql-redis ${MAIN_SRCS})
target_link_libraries(aserver-mysql-redis  libhiredis.a   -lmysqlclient  m)




