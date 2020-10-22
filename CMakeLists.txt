cmake_minimum_required(VERSION 3.10.2)
project(pptrace)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-w")
#add_link_options(-lsodium)
add_executable(pptrace src/main.cpp src/gov.cpp include/gov.h src/setup.cpp include/setup.h src/store.cpp include/store.h src/user.cpp include/user.h include/triple.h)
#add this for lib
target_link_libraries(pptrace libsodium.a)