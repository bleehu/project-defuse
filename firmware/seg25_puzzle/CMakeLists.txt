cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(seg25_puzzle C CXX ASM)

pico_sdk_init()
add_executable(${PROJECT_NAME}
    main.cpp
    display.cpp
    switches.cpp
)
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)
pico_add_extra_outputs(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} pico_stdlib pico_multicore)