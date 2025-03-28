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

-- 类似 cpp include 
-- 本质上就是把另一个 premake5.lua 文件中的全部内容复制到当前位置
include "Cherno_Hazel/vendor/GLFW"
include "Cherno_Hazel/vendor/Glad"
include "Cherno_Hazel/vendor/imgui"

project "Sandbox"
    characterset ("Unicode")

    location "%{prj.name}"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    -- Off -> Sets <RuntimeLibrary> to "MultiThreadedDLL"
    -- On -> Sets <RuntimeLibrary> to "MultiThreaded"
    staticruntime "Off"

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
    
    prebuildcommands {
        ("{COPY} ../bin/" .. outputdir .. "/Cherno_Hazel/Cherno_Hazel.dll ../bin/" .. outputdir .. "/Sandbox/")
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
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"

    staticruntime "Off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    includedirs {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.imgui}",
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
        "%{prj.name}/src/**.cpp"
    }

    -- 如果只是在 Sandbox 构建之前复制
    -- 那么当仅有 Hazel 项目变更时，最新的 dll 文件并不会被复制到 Sandbox
    -- 因为 Sandbox 没有更改，所以不会被重新构建
    -- 因此为了确保 Sandbox 构建时，总是复制最新的 dll 文件
    -- 直接在 Hazel 构建结束后，复制 dll 文件
    -- 虽然可能会导致，在最初的构建时，Sandbox 文件夹还不存在的问题
    -- 但只需再构建一次即可
    postbuildcommands { 
        ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/")
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
