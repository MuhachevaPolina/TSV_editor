cmake_minimum_required(VERSION 3.15.0)
cmake_policy(SET CMP0016 NEW)

project(tsv-editor VERSION 1.0.0 DESCRIPTION "Табличный редактор TSV")

enable_testing()
# add_subdirectory(test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt5 REQUIRED COMPONENTS Network)

find_package(GTest REQUIRED)

include_directories(${CMAKE_SOURCE_DIR})
add_subdirectory(src/tsv-editor)
# add_subdirectory(src/server)
# add_subdirectory(src/client)
# add_subdirectory(test)
# add_subdirectory(test/client)

# enable_testing()

add_library(test_utils STATIC
    test/testUtilities.cpp
)

target_include_directories(test_utils PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(test_utils PUBLIC
    Qt5::Core
    Qt5::Widgets
    Qt5::Network
)

add_executable(tests
    test/Test_TSVTable.cpp
)

# add_executable(app
#     src/main.cpp
# )

target_include_directories(tests PUBLIC
    ${CMAKE_SOURCE_DIR}
)

# add_executable(main
#     src/main.cpp
# )

target_link_libraries(tests PRIVATE
    TSVEditor
    test_utils
    GTest::gtest_main 
    GTest::gtest
    Qt5::Core
    Qt5::Widgets
    Qt5::Network
)

# target_link_libraries(app PRIVATE

#     Qt5::Core
#     Qt5::Widgets
#     Qt5::Network
# )


include(GoogleTest)
gtest_discover_tests(tests)
