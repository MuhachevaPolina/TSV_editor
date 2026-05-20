add_library(TSVEditor STATIC
    TSVTable.cpp
    TSVTableView.cpp
    TSVTableModel.cpp
    AppViewer.cpp
)

target_include_directories(TSVEditor PUBLIC
    ${CMAKE_SOURCE_DIR})

target_link_libraries(TSVEditor PRIVATE
    Qt5::Core
    Qt5::Widgets
    Qt5::Network
)