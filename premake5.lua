workspace "ProtoEngine"
	-- Releases
	configurations { "Release", "Debug" }
	-- Platforms
	platforms { "Win64", "Win32" }

-- Project ProtoEngine
project "ProtoEngine"
	kind "SharedLib"
	-- Language setup
	language "C++"
	cppdialect "C++17"
	-- Output directories
	targetdir "Bin/%{cfg.buildcfg}"

	objdir "Bin/Intermediates/%{cfg.buildcfg}"


	-- Source files	
	files { 
		"Source/*.cpp", 
	}

	-- Library directories
	libdirs { 
		"Dependencies/GLFW/lib-vc2022/",
		"C:/VulkanSDK/1.3.280.0/Lib"
	}

	-- Libraries
	links { 
		"glfw3.lib", 
		"vulkan-1.lib"
	}

	-- Include directories
	includedirs {
		"Dependencies/GLFW/include", 
		"Dependencies/GLM",
		"C:/VulkanSDK/1.3.280.0/Include",
		"Include"
	}

	-- Default debug release properties
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		runtime "Debug"

	-- Release properties
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
		runtime "Release"

	-- Win64 platform properties
	filter "platforms:Win64"
		system "Windows"
		architecture "x86_64"

	-- Win32 platform properties
	filter "platforms:Win32"
		system "Windows"
		architecture "x86"

-- Project TestGame
project "TestGame"
	kind "ConsoleApp"

	-- Language setup
	language "C++"
	cppdialect "C++17"

	-- Output directories
	targetdir "TestBin/%{cfg.buildcfg}"
	objdir "TestBin/Intermediates/%{cfg.buildcfg}"

	-- Source files	
	files { 
		"Test/*.cpp", 
		"Test/*.h", 
		"Test/*.hpp" 
	}

	links "ProtoEngine"

	includedirs "Include"

	-- Default debug release properties
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		runtime "Debug"

	-- Release properties
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
		runtime "Release"

	-- Win64 platform properties
	filter "platforms:Win64"
		system "Windows"
		architecture "x86_64"

	-- Win32 platform properties
	filter "platforms:Win32"
		system "Windows"
		architecture "x86"





