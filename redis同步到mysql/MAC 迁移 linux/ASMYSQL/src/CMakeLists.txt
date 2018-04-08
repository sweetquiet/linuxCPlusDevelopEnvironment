#指定源文件
include_directories(${CMAKE_SOURCE_DIR}/src)
aux_source_directory(. MAIN_SRCS)

#生成目标
add_executable(aserver-redis-mysql ${MAIN_SRCS})
target_link_libraries(aserver-redis-mysql  libhiredis.a -lmysqlclient  m)




