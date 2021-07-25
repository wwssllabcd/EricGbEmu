cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_FLAGS "--std=c11")

set(INC_PATH
    ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/common 
)

message("INC_PATH=" ${INC_PATH})

include_directories(${INC_PATH})


include_directories(../../SDL2/include) 

#add root include path
include_directories(./)


message("CMAKE_SOURCE_DIR=" ${CMAKE_SOURCE_DIR})


set(SRC_LIST

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


add_executable(ericGbEmu ${SRC_LIST})
