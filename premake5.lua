workspace "PlumLearn"
	architecture "x64"
	startproject "Sandbox"
	configurations { "Debug", "Release" }
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "PlumLearn"
	location "PlumLearn"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/include",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "configurations:Debug"
		defines "PL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PL_RELEASE"
		runtime "Release"
		optimize "on"

project "PlumLearn.Test"
	location "PlumLearn.Test"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	pchheader "tpch.h"
	pchsource "%{prj.name}/src/tpch.cpp"

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/catch2/**.hpp"
	}

	includedirs
	{
		"%{prj.name}/include",
		"%{prj.name}/vendor/catch2/"
	}

	links
	{
		"PlumLearn"
	}

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/include"
	}

	links
	{
		"PlumLearn"
	}

	filter "configurations:Debug"
		defines "PL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PL_RELEASE"
		runtime "Release"
		optimize "on"