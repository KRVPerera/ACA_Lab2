cmake_minimum_required(VERSION 3.5)
project(BPAnalysis)
#set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/framework.c
        include/framework.h
        src/main.c
        src/predictors.c
        include/predictors.h)

message("Extracting trace files... Please wait.")
#execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzvf ${CMAKE_SOURCE_DIR}/traces/traces.tar.gz
#        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/traces)

add_executable(BPAnalysis ${SOURCE_FILES})