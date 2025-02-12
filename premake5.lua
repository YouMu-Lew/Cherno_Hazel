workspace "Cherno_Hazel"
    architecture "x86_64" -- 64 bits
    configurations { "Debug", "Release" , "Dist" }
    startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
        "%{prj.name}/src"
    }

    pchheader ("hzpch.h")
    pchsource ("%{prj.name}/src/hzpch.cpp")

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    postbuildcommands { 
        ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/")
    }

    filter "system:windows"
        defines{
            "HZ_PLATFORM_WINDOWS",
            "HZ_BUILD_DLL"
        }

    filter "configurations:Debug"
        defines "HZ_DEBUG"
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
