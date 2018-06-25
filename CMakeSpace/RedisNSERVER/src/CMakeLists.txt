#指定源文件
include_directories(${CMAKE_SOURCE_DIR}/src)
aux_source_directory(. MAIN_SRCS)

#生成目标
add_executable(nserver-mysql-redis ${MAIN_SRCS})
target_link_libraries(nserver-mysql-redis libhiredis.a   -lmysqlclient  m)




