CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(DogeUtility)

set(CRYPTOPP_DIR /mnt/e/thirdparty/cryptopp850)

# DogeUtility
add_library(DogeUtility SHARED ${CMAKE_SOURCE_DIR}/DogeUtility.cpp)
target_include_directories(DogeUtility PRIVATE ${CRYPTOPP_DIR})
target_link_libraries(DogeUtility uuid)
target_link_libraries(DogeUtility ${CRYPTOPP_DIR}/libcryptopp.so)

