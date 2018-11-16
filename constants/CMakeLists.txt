#1.cmake verson，指定cmake版本
cmake_minimum_required(VERSION 3.10)

aux_source_directory(./src DIR_CONSTANTS_SRCS)

# 生成链接库
add_library (constants ${DIR_CONSTANTS_SRCS})