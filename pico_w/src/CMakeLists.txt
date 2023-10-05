cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_COMPILER C:/Tools/Dev/mingw64/bin/gcc.exe)
set(CMAKE_CXX_COMPILER C:/Tools/Dev/mingw64/bin/g++.exe)

include("C:/Program Files/Raspberry Pi/Pico SDK v1.5.1/pico-sdk/pico_sdk_init.cmake")

project(gce_project)

pico_sdk_init()

add_executable(gce_pico_w_server
  "server/main.c"
)

target_link_libraries(gce_pico_w_server pico_stdlib)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(gce_pico_w_server)