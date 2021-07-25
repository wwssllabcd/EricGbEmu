cmake_minimum_required(VERSION 3.10)

project(eric_gb_emu LANGUAGES C)

message("PROJECT_NAME =" ${PROJECT_NAME})


set(CMAKE_C_FLAGS "--std=c11")

message("CMAKE_SOURCE_DIR=" ${CMAKE_SOURCE_DIR})

set(INC_PATH
    ${CMAKE_SOURCE_DIR} 
    ${CMAKE_SOURCE_DIR}/common 
)
message("INC_PATH=" ${INC_PATH})
include_directories(${INC_PATH})


# ------- SDL2 ------- 
find_package(SDL2 REQUIRED)
message("SDL2_INCLUDE_DIR =" ${SDL2_INCLUDE_DIRS})
message("SDL2_LIBRARIES =" ${SDL2_LIBRARIES})

include_directories(${SDL2_INCLUDE_DIRS})
                    

# ------- source code ------- 
set(SRC_CODE_LIST

   ./common/utility/Util.c
   ./common/utility/show_msg.c

   ./opcode/opcode_map.c
   ./opcode/opcode_impl.c

   ./boot/boot_rom.c

   ./main.c
   ./adapter_sdl.c
   ./cpu_cycle.c
   ./cpu.c
   ./debug.c
   ./input.c
   ./mmu.c
   ./video.c
)

add_executable(${PROJECT_NAME} ${SRC_CODE_LIST})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

