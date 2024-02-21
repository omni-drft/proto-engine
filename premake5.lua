workspace "ProtoEngine"
	configurations { "Release", "Debug" }
	platforms { "Win64" }

project "ProtoEngine"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir "Bin/%{cfg.buildcfg}"
	objdir "Bin/Intermediates/%{cfg.buildcfg}"

	files { "**.cpp", "**.h", "**.hpp" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

	filter "platforms:Win64"
		system "Windows"
		architecture "x86_64"