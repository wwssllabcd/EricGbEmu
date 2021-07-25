cmake_minimum_required(VERSION 3.10)

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

message("SDL2_LIBRARY =" ${SDL2_LIBRARY})
message("SDL2_INCLUDE_DIR =" ${SDL2_INCLUDE_DIR})
message("SDL2_INCLUDE_DIRS =" ${SDL2_INCLUDE_DIRS})
message("SDL2_IMAGE_INCLUDE_DIR =" ${SDL2_IMAGE_INCLUDE_DIR})
message("SDL2_TTF_INCLUDE_DIR =" ${SDL2_TTF_INCLUDE_DIR})

set(MY_SDL2_INC_DIR 
    ${SDL2_INCLUDE_DIR} 
    ${SDL2_INCLUDE_DIRS} 
    ${SDL2_IMAGE_INCLUDE_DIR} 
    ${SDL2_TTF_INCLUDE_DIR} 
)

message("MY_SDL2_INC_DIR =" ${MY_SDL2_INC_DIR})
include_directories(${SDL2_INC_DIR})
                    
message("SDL2_LIBRARIES =" ${SDL2_LIBRARIES})
#add_library(${SDL2_LIBRARIES})


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

add_executable(eric_gb_emu ${SRC_CODE_LIST})


target_include_directories(eric_gb_emu ${MY_SDL2_INC_DIR})
target_link_libraries(eric_gb_emu ${SDL2_LIBRARIES})