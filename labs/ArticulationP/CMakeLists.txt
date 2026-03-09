set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ArticulationPointLib ArticulationPoint/Graph.cpp
        ArticulationPoint/Graph.h)

add_executable(ArticulationPoint ArticulationPoint/ArticulationPoint.cpp)
target_link_libraries(ArticulationPoint PRIVATE ArticulationPointLib)

target_include_directories(ArticulationPointLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/ArticulationP)

add_subdirectory(ArticulationPointTest)

target_compile_definitions(ArticulationPointTest PRIVATE
        TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}")