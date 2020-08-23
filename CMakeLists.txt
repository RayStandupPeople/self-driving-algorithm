# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# c++11支持
add_definitions(-std=c++11)
# 项目信息
project (Dp_apollo)
# 源文件变量
aux_source_directory(. DIR_SRCS)
# 指定生成目标
add_executable(Dp_apollo ${DIR_SRCS})
