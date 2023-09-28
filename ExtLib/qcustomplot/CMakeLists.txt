find_package(Qt6 COMPONENTS PrintSupport REQUIRED)
set(CMAKE_AUTOMOC ON)
add_library(qcustomplot STATIC qcustomplot.cpp)
target_link_libraries(qcustomplot PRIVATE Qt6::PrintSupport)
target_include_directories(qcustomplot INTERFACE .)

