cmake_minimum_required(VERSION 3.10)

project(DNS_SNIFFER_PP VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES src/*.cpp)

# if (WIN32)
# 	file(GLOB PCAP_SOURCES src/packet_capture/win/*.cpp)
# else()
# 	file(GLOB PCAP_SOURCES src/packet_capture/unix/*.cpp)
# endif()

add_executable(sniffer ${SOURCES} main.cpp)

target_include_directories(sniffer PUBLIC include)