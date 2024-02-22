workspace "ProtoEngine"
	configurations { "Release", "Debug", "InputDebug", "ShaderDebug" }
	platforms { "Win64" }

project "ProtoEngine"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir "Bin/%{cfg.buildcfg}"
	objdir "Bin/Intermediates/%{cfg.buildcfg}"

	files { "**.cpp", "**.h", "**.hpp" }

	libdirs { "Dependencies/GLEW/lib/Release/x64/", "Dependencies/GLFW/lib-vc2022/" }
	links { "glew32s.lib", "glfw3.lib", "opengl32"}

	includedirs { "Dependencies/GLEW/include", "Dependencies/GLFW/include", "Dependencies/GLM" }

	filter "configurations:Debug"
		defines { "DEBUG", "GLEW_STATIC" }
		symbols "On"

	filter "configurations:InputDebug"
		defines { "DEBUG", "INPUT_DEBUG", "GLEW_STATIC" }
		symbols "On"

	filter "configurations:ShaderDebug"
		defines { "DEBUG", "SHADER_DEBUG", "GLEW_STATIC" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG", "GLEW_STATIC" }
		optimize "On"

	filter "platforms:Win64"
		system "Windows"
		architecture "x86_64"