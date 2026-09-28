cmake_minimum_required(VERSION 3.16)
project(VulkanTriangle CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)

# GLFW: use the prebuilt MinGW binaries downloaded into tools42_deps.
set(GLFW_ROOT "D:/dev/tools42_deps/glfw-3.4.bin.WIN64" CACHE PATH "GLFW prebuilt root")
set(GLFW_INCLUDE "${GLFW_ROOT}/include")
set(GLFW_LIB "${GLFW_ROOT}/lib-mingw-w64/libglfw3.a")

add_executable(triangle main.cpp)
target_include_directories(triangle PRIVATE ${GLFW_INCLUDE})
target_link_libraries(triangle PRIVATE Vulkan::Vulkan ${GLFW_LIB})

# GLFW static build on Windows needs these system libs.
if (WIN32)
    target_link_libraries(triangle PRIVATE gdi32 opengl32)
endif()

# Statically link the GCC/C++ runtime (libstdc++, libgcc, winpthread) so the
# resulting .exe runs on any Windows machine WITHOUT the MinGW bin dir on PATH.
# This removes the dependency on libstdc++-6.dll / libgcc_s_seh-1.dll.
if (MINGW)
    target_link_options(triangle PRIVATE
        -static
        -static-libgcc
        -static-libstdc++)
endif()

if (MSVC)
    target_compile_options(triangle PRIVATE /W4)
else()
    target_compile_options(triangle PRIVATE -Wall -Wextra)
endif()

# ---- Compile shaders (GLSL -> SPIR-V) using glslc from the Vulkan SDK ----
set(SHADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
set(SPV_DIR "${CMAKE_CURRENT_BINARY_DIR}/shaders")
file(MAKE_DIRECTORY ${SPV_DIR})

function(compile_shader SRC OUT)
    add_custom_command(
        OUTPUT ${SPV_DIR}/${OUT}
        COMMAND ${Vulkan_GLSLC_EXECUTABLE} ${SHADER_DIR}/${SRC} -o ${SPV_DIR}/${OUT}
        DEPENDS ${SHADER_DIR}/${SRC}
        COMMENT "Compiling ${SRC} -> ${OUT}"
        VERBATIM)
endfunction()

compile_shader(shader.vert vert.spv)
compile_shader(shader.frag frag.spv)

add_custom_target(shaders DEPENDS ${SPV_DIR}/vert.spv ${SPV_DIR}/frag.spv)
add_dependencies(triangle shaders)
