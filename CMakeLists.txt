CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(DogeUtility)

# DogeUtility
add_library(DogeUtility SHARED ${CMAKE_SOURCE_DIR}/DogeUtility.cpp)
target_link_libraries(DogeUtility uuid)

