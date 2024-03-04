workspace "ProtoEngine"
	-- Releases
	configurations { "Release", "Debug", "InputDebug", "ShaderDebug" }
	-- Platforms
	platforms { "Win64" }

-- Project ProtoEngine
project "ProtoEngine"
	kind "ConsoleApp"
	-- Language setup
	language "C++"
	cppdialect "C++17"
	-- Output directories
	targetdir "Bin/%{cfg.buildcfg}"
	objdir "Bin/Intermediates/%{cfg.buildcfg}"

	-- Source files	
	files { 
		"**.cpp", 
		"**.h", 
		"**.hpp" 
	}

	-- Library directories
	libdirs { 
		"Dependencies/GLEW/lib/Release/x64/", 
		"Dependencies/GLFW/lib-vc2022/",
		"Dependencies/FREETYPE/lib"
	}

	-- Libraries
	links { 
		"glew32s.lib", 
		"glfw3.lib", 
		"opengl32",
		"freetype.lib"
	}

	-- Include directories
	includedirs {
		"Dependencies/GLEW/include", 
		"Dependencies/GLFW/include", 
		"Dependencies/GLM",
		"Dependencies/FREETYPE/include",
		"Dependencies/SPDLOG/include"
	}

	-- Default debug release properties
	filter "configurations:Debug"
		defines { "DEBUG", "GLEW_STATIC" }
		symbols "On"

	-- Input debug properties
	filter "configurations:InputDebug"
		defines { "DEBUG", "INPUT_DEBUG", "GLEW_STATIC" }
		symbols "On"

	-- Shader debug properties
	filter "configurations:ShaderDebug"
		defines { "DEBUG", "SHADER_DEBUG", "GLEW_STATIC" }
		symbols "On"
	
	-- Release properties
	filter "configurations:Release"
		defines { "NDEBUG", "GLEW_STATIC" }
		optimize "On"

	-- Windows platform properties
	filter "platforms:Win64"
		system "Windows"
		architecture "x86_64"