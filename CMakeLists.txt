cmake_minimum_required(VERSION 3.31)

project(ProtoEngine)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)   
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  

if(NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_DEBUG_POSTFIX "-d")  # Appends "-d" to debug binaries (e.g., ProtoEngine-d.exe)
endif()

find_package(Vulkan REQUIRED)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

add_subdirectory(Vendor/glfw)

file(GLOB IMGUI_SOURCES
    Vendor/imgui/*.cpp
    Vendor/imgui/backends/imgui_impl_glfw.cpp
    Vendor/imgui/backends/imgui_impl_vulkan.cpp
)

add_executable(ProtoEngine 
    Source/Main.cpp
    ${IMGUI_SOURCES}
)

target_include_directories(ProtoEngine PRIVATE 
    Vendor/glfw/include
    Vendor/imgui
    Vendor/imgui/backends
    ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(ProtoEngine PRIVATE
    glfw        
    Vulkan::Vulkan 
)

find_file(VULKAN_DLL
    NAMES vulkan-1.dll
    PATHS ${Vulkan_LIBRARY_DIRS}
    DOC "Path to Vulkan DLL"
)
if(VULKAN_DLL)
    add_custom_command(TARGET ProtoEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${VULKAN_DLL} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
endif()