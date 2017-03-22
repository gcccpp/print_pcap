cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

project(print_pcap)

set(CMAKE_CXX_FLAGS_INIT "-Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIE")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=gnu++11")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core REQUIRED)

set(SOURCES_DIR ${CMAKE_SOURCE_DIR})

set(MAIN ${SOURCES_DIR}/main.cpp)

set(MAIN_SOURCES
        ${MAIN}
        )


set(PRIVATE_CLASSES
        parser
        filter
        )

set(CMAKE_PREFIX_PATH ${SOURCES_DIR})

foreach( class ${PRIVATE_CLASSES} )
        set(FILE ${class}.cpp)
        list( APPEND SOURCES ${CMAKE_PREFIX_PATH}/${FILE} )
        set(FILE ${class}.h)
        list( APPEND HEADERS S{CMAKE_PREFIX_PATH}/${FILE} )
endforeach()

add_executable(${PROJECT_NAME} ${MAIN_SOURCES} ${SOURCES})
target_link_libraries(${PROJECT_NAME} pcap)
qt5_use_modules(${PROJECT_NAME} Core)
