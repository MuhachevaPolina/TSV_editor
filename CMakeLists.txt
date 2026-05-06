cmake_minimum_required(VERSION 3.15.0)
cmake_policy(SET CMP0016 NEW)

project(tsv-editor VERSION 1.0.0 DESCRIPTION "Табличный редактор TSV")

include_directories(${CMAKE_SOURCE_DIR}/src)
add_subdirectory(src/tsv-editor)

enable_testing()
add_subdirectory(test)
