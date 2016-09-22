# Default CMake Setup. Used for Pandora Builds.

set(lib_base /opt/gcw0-toolchain/usr/mipsel-gcw0-linux-uclibc/sysroot/usr/)
set(sdl_root ${lib_base}/include/SDL)

set(OPENGL 0)

include_directories("${sdl_root}")

link_libraries(cannonball 
    SDL
)

# Linking
link_directories(
    "${sdl_root}/lib"
)

add_definitions(-DPANDORA)
 
# Location for Cannonball to create save files
# Used to auto-generate setup.hpp with various file paths
set(xml_directory home/)
set(sdl_flags "SDL_SWSURFACE")

set(CMAKE_CXX "/opt/gcw0-toolchain/usr/mipsel-linux-g++")
set(CMAKE_CC "/opt/gcw0-toolchain/usr/mipsel-linux-gcc")
set(CMAKE_CXX_FLAGS "-O2 -mips32r2")

