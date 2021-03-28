cmake_minimum_required(VERSION 3.1)
aux_source_directory(. DIR_LIB_SORCES)
add_library(ThreadPool SHARED ${DIR_LIB_SORCES})
set_target_properties(ThreadPool PROPERTIES output_name "ThreadPool")