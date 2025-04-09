workspace "Cherno_Hazel"
	architecture "x86_64" -- 64 bits
	configurations { "Debug", "Release" , "Dist" }
	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories velative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Cherno_Hazel/vendor/GLFW/include"
IncludeDir["Glad"] = "Cherno_Hazel/vendor/Glad/include"
IncludeDir["imgui"] = "Cherno_Hazel/vendor/imgui"
IncludeDir["glm"] = "Cherno_Hazel/vendor/glm"

-- 类似 cpp include 
-- 本质上就是把另一个 premake5.lua 文件中的全部内容复制到当前位置
group "Dependencies"
	include "Cherno_Hazel/vendor/GLFW"
	include "Cherno_Hazel/vendor/Glad"
	include "Cherno_Hazel/vendor/imgui"
group ""

project "Sandbox"
	characterset ("Unicode")

	location "%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	-- Off -> Sets <RuntimeLibrary> to "MultiThreadedDLL"
	-- On -> Sets <RuntimeLibrary> to "MultiThreaded"
	staticruntime "On"

	links{
		"Cherno_Hazel"
	}

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Cherno_Hazel/vendor/spdlog/include",
		"Cherno_Hazel/src",
		"%{IncludeDir.glm}",
		"Cherno_Hazel/vendor",
	}

	filter "system:windows"
		defines{
			"HZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "On"


project "Cherno_Hazel"
	characterset ("Unicode")

	location "%{prj.name}"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"

	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs {
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
	}

	links {
		"GLFW",
		"Glad",
		"imgui",
		"opengl32.lib",
	}

	pchheader ("hzpch.h")
	pchsource ("%{prj.name}/src/hzpch.cpp")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/**.hpp",
		"%{prj.name}/vendor/glm/**.inl",
	}

	filter "system:windows"
		defines{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		-- defines "HZ_ENABLE_ASSERTS"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		optimize "On"
		runtime "Release"

	filter "configurations:Dist"
		defines "HZ_DIST"
		optimize "On"
		runtime "Release"
