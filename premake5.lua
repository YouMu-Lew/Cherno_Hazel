workspace "Cherno_Hazel"
    architecture "x86_64" -- 64 bits
    configurations { "Debug", "Release" , "Dist" }
    startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories velative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Cherno_Hazel/vendor/GLFW/include"

-- 类似 cpp include 
-- 本质上就是把另一个 premake5.lua 文件中的全部内容复制到当前位置
include "Cherno_Hazel/vendor/GLFW"

project "Sandbox"
    characterset ("Unicode")

    location "%{prj.name}"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

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
        "Cherno_Hazel/src"
    }

    defines{
        "HZ_PLATFORM_WINDOWS"
    }

    prebuildcommands {
        ("{COPY} ../bin/" .. outputdir .. "/Cherno_Hazel/Cherno_Hazel.dll ../bin/" .. outputdir .. "/Sandbox/")
    }

project "Cherno_Hazel"
    characterset ("Unicode")

    location "%{prj.name}"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    includedirs {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
    }

    links {
        "GLFW",
        "opengl32.lib",
    }

    pchheader ("hzpch.h")
    pchsource ("%{prj.name}/src/hzpch.cpp")

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    -- postbuildcommands { 
    --     ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/")
    -- }

    filter "system:windows"
        defines{
            "HZ_PLATFORM_WINDOWS",
            "HZ_BUILD_DLL"
        }

    filter "configurations:Debug"
        defines "HZ_DEBUG"
        defines "HZ_ENABLE_ASSERTS"
        symbols "On"
        -- runtime "Debug"

    filter "configurations:Release"
        defines "HZ_RELEASE"
        optimize "On"
        -- runtime "Release"

    filter "configurations:Dist"
        defines "HZ_DIST"
        optimize "On"
        -- runtime "Release"
