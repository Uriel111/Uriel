cmake_minimum_required(VERSION 3.1)
aux_source_directory(. DIR_ASIO)
add_library(Asio ${DIR_ASIO})