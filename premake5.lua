workspace "ProtoEngine"
    configurations {"Debug", "Release"}
    architecture "x86_64"

    filter "configurations:Debug"
      defines { "_DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "_NDEBUG" }
      optimize "On"

    project "Engine"
        kind "SharedLib"
        language "C++"
        cppdialect "C++17"
        targetdir "bin/%{cfg.buildcfg}"
        architecture "x86_64"
        defines {"ENGINE_EXPORTS"}
        files {
            "source/**.cc", 
            "source/**.h",
            "include/**.h"
        }
        includedirs {
            "vendor/glfw/include",
            "include",
            "vendor/glm",
            os.getenv("VULKAN_SDK") .. "/Include"
        }
        libdirs {
            "vendor/glfw",
            os.getenv("VULKAN_SDK") .. "/Lib"
        }
        prebuildcommands {
            'cmake -S vendor/glfw -B vendor/glfw/build -DCMAKE_BUILD_TYPE=%{cfg.buildcfg} -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF',
            'cmake --build vendor/glfw/build --config %{cfg.buildcfg} --target glfw'
          }
        filter "configurations:Release"
            libdirs { "vendor/glfw/build/src/Release" }
            links { "glfw3", "vulkan-1" }
        filter "configurations:Debug"
            libdirs { "vendor/glfw/build/src/Debug" }
            links { "glfw3", "vulkan-1" }

        

    project "Sandbox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        targetdir "bin/%{cfg.buildcfg}"
        architecture "x86_64"
        files { 
            "sandbox_source/**.cc", 
            "sandbox_source/**.cpp", 
            "sandbox_source/**.h", 
            "sandbox_source/**.hpp"
        }
        includedirs {
            "include"
        }
        links "Engine"
