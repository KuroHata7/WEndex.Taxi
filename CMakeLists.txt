cmake_minimum_required(VERSION 2.8.12)
project(testingSomething)

add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(passengergate PassengerGateway.cpp)
target_link_libraries(passengergate ${CONAN_LIBS})

add_executable(drivergate DriverGateway.cpp)
target_link_libraries(drivergate ${CONAN_LIBS})

add_executable(admingate AdminGateway.cpp)
target_link_libraries(admingate ${CONAN_LIBS})