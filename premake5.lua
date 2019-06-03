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

	defines "PL_INTERNAL"

	pchheader "plpch.h"
	pchsource "%{prj.name}/src/plpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/eigen/Eigen"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PL_PLATFORM_WINDOWS"
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

	defines "PL_INTERNAL"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/catch2/**.hpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/catch2/",
		"PlumLearn/src",
		"PlumLearn/vendor/spdlog/include",
		"PlumLearn/vendor/eigen/Eigen"
	}

	links
	{
		"PlumLearn"
	}

	defines "PL_DEBUG"
	runtime "Debug"
	symbols "on"

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PL_PLATFORM_WINDOWS"
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
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"PlumLearn/src"
	}

	links
	{
		"PlumLearn"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PL_RELEASE"
		runtime "Release"
		optimize "on"