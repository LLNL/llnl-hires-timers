add_executable(timing-test timing-test.cpp)
target_link_libraries(timing-test adept_timing)

include_directories(${PROJECT_SOURCE_DIR}/src)
