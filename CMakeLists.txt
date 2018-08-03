
# the property CXX_STANDARD is first mentioned in cmake 3.1.3
cmake_minimum_required (VERSION 3.1.3)

project (DigitalLibrary)

set(Boost_USE_STATIC_LIBS ON)

# Digital Library Server
set(EXEC_NAME "DigitalLibraryServer")

add_executable(${EXEC_NAME} main.cpp UdpServer.cpp DigiLibMap.cpp StudentMap.cpp BookMap.cpp)
set_property(TARGET ${EXEC_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${EXEC_NAME} PROPERTY CXX_STANDARD_REQUIRED true)

# internal list of mandatory boost components
SET(BOOST_MANDATORY_COMPONENTS system)

find_package(Boost "1.52.0" COMPONENTS ${BOOST_MANDATORY_COMPONENTS} REQUIRED)

# add include path for boost to the compiler
include_directories(${Boost_INCLUDE_DIRS})

# now link against the boost library system
target_link_libraries(${EXEC_NAME} ${Boost_SYSTEM_LIBRARY})



#Digital Library Client
set(EXEC_NAME "DigitalLibraryClient")

add_executable(${EXEC_NAME} mainclient.cpp UdpClient.cpp)
set_property(TARGET ${EXEC_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${EXEC_NAME} PROPERTY CXX_STANDARD_REQUIRED true)
target_link_libraries(${EXEC_NAME} ${Boost_SYSTEM_LIBRARY})



# executable name
set(EXEC_NAME "testServer")

add_executable(${EXEC_NAME} mainTest.cpp BoostUnitTest.cpp BookMap.cpp StudentMap.cpp stdafx.cpp)
set_property(TARGET ${EXEC_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${EXEC_NAME} PROPERTY CXX_STANDARD_REQUIRED true)

# internal list of mandatory boost components
SET(BOOST_MANDATORY_COMPONENTS unit_test_framework)
