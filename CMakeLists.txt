cmake_minimum_required(VERSION 3.5)
project(BPAnalysis)
#set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/framework.c
        include/framework.h
        src/main.c
        src/predictors.c
        include/predictors.h
        include/statemachine.h
        src/statemachine.c include/fourcoltwobitbht.h src/fourcoltwobitbht.c.c)

message("Extracting trace files... Please wait.")

execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/traces OUTPUT_QUIET ERROR_QUIET)
execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzvf  ${CMAKE_SOURCE_DIR}/traces/traces.tar.gz -C ${CMAKE_CURRENT_BINARY_DIR}/traces
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/traces
        TIMEOUT 10 ERROR_QUIET)
message("Trace files are extracted")

add_executable(BPAnalysis ${SOURCE_FILES})
target_link_libraries(BPAnalysis m)
