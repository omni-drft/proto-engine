workspace "ProtoEngine"
	-- Releases
	configurations { "Release", "Debug" }
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
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		targetdir "Bin/%{cfg.buildcfg}"
		objdir "Bin/Intermediates/%{cfg.buildcfg}"
		runtime "Debug"

	-- Release Alone properties
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
		targetdir "Bin/%{cfg.buildcfg}"
		objdir "Bin/Intermediates/%{cfg.buildcfg}"
		runtime "Release"

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
		"TestGame/*.cpp", 
		"TestGame/*.h", 
		"TestGame/*.hpp" 
	}

	links "ProtoEngine"

	includedirs "Include"

	-- Default debug release properties
	filter "configurations:Debug"
		-- Output directories
		targetdir "Bin/Debug"
		objdir "Bin/Intermediates/Debug"
		defines { "DEBUG" }
		symbols "On"
		runtime "Debug"

	-- Release properties
	filter "configurations:Release"
		-- Output directories
		targetdir "Bin/Release"
		objdir "Bin/Intermediates/Release"
		defines { "NDEBUG" }
		optimize "On"
		runtime "Release"

	-- Win64 platform properties
	filter "platforms:Win64"
		system "Windows"
		architecture "x86_64"




