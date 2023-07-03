# 定义了SRC_LIST变量包含了该目录下的所有源文件
aux_source_directory(. SRC_LIST)

# 指定生成可执行文件使用SRC_LIST中的文件进行编译
add_executable(chatServer ${SRC_LIST})

# 指定可执行文件需要链接的库文件
target_link_libraries(chatServer muduo_net muduo_base pthread)