cmake_minimum_required(VERSION 3.10)
project(main)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(RedLED RedLED.cpp)
target_link_libraries(RedLED PRIVATE wiringPi boost_system)

add_executable(Button Button.cpp)
target_link_libraries(Button PRIVATE wiringPi boost_system)

add_executable(SoundSensor SoundSensor.cpp)
target_link_libraries(SoundSensor PRIVATE wiringPi boost_system)

add_executable(LightSensor LightSensor.cpp)
target_link_libraries(LightSensor PRIVATE wiringPi boost_system)	