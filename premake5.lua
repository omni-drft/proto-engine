workspace "ProtoEngine"
	-- Releases
	configurations { "ReleaseAlone", "DebugAlone", "ReleaseWithGame", "DebugWithGame" }
	-- Platforms
	platforms { "Win64" }

-- Project ProtoEngine
project "ProtoEngine"
	kind "SharedLib"
	-- Language setup
	language "C++"
	cppdialect "C++17"


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

	-- Debug alone properties
	filter "configurations:DebugAlone"
		defines { "DEBUG" }
		symbols "On"
		targetdir "Bin/%{cfg.buildcfg}"
		objdir "Bin/Intermediates/%{cfg.buildcfg}"
		runtime "Debug"

	-- Release Alone properties
	filter "configurations:ReleaseAlone"
		defines { "NDEBUG" }
		optimize "On"
		targetdir "Bin/%{cfg.buildcfg}"
		objdir "Bin/Intermediates/%{cfg.buildcfg}"
		runtime "Release"

	-- Release With Game properties
	filter "configurations:ReleaseWithGame"
		defines { "NDEBUG" }
		optimize "On"
		targetdir "TestBin/Release"
		objdir "TestBin/Intermediates/Release"
		runtime "Release"
	
	-- Debug With Game properties
	filter "configurations:DebugWithGame"
		defines { "DEBUG" }
		symbols "On"
		targetdir "TestBin/Debug"
		objdir "TestBin/Intermediates/Debug"
		runtime "Debug"

	-- Win64 platform properties
	filter "platforms:Win64"
		system "Windows"
		architecture "x86_64"


-- Project TestGame
project "TestGame"
	kind "ConsoleApp"

	-- Language setup
	language "C++"
	cppdialect "C++17"

	-- Source files	
	files { 
		"Test/*.cpp", 
		"Test/*.h", 
		"Test/*.hpp" 
	}

	links "ProtoEngine"

	includedirs "Include"

	-- Default debug release properties
	filter "configurations:DebugWithGame"
		-- Output directories
		targetdir "TestBin/Debug"
		objdir "TestBin/Intermediates/Debug"
		defines { "DEBUG" }
		symbols "On"
		runtime "Debug"

	-- Release properties
	filter "configurations:ReleaseWithGame"
		-- Output directories
		targetdir "TestBin/Release"
		objdir "TestBin/Intermediates/Release"
		defines { "NDEBUG" }
		optimize "On"
		runtime "Release"

	-- Win64 platform properties
	filter "platforms:Win64"
		system "Windows"
		architecture "x86_64"




