
set_project("Cherno_Hazel")
set_allowedarchs("windows|x64")-- 仅允许windows平台x64架构下编译
-- set_allowedmodes("debug", "release", "dist")
set_languages("c17", "cxx20")

-- add_rules("plugin.vsxmake.autoupdate")
add_rules("mode.debug", "mode.releasedbg","mode.release")

target("Cherno_Hazel")
    set_kind("shared")
    -- set_extension(".dll")

    set_targetdir("bin/$(mode)-$(arch)/Cherno_Hazel/")
    set_objectdir("bin-int/$(mode)-$(arch)/Cherno_Hazel/")

    add_includedirs("Cherno_Hazel/vendor/spdlog/include", {public = true}) -- 通过额外的{public|interface = true}属性设置，将includedirs导出给依赖的子target `Sandbox`

    add_files("Cherno_Hazel/src/**.cpp")
    add_headerfiles("Cherno_Hazel/src/(**.h)", {install = false}) -- 保留目录结构，并禁用默认的头文件安装，仅用于 vs project 文件列表展示、编译

    if is_plat("windows") then
        add_defines("HZ_PLATFORM_WINDOWS", "HZ_BUILD_DLL")
    end

target("Sandbox")
    set_kind("binary")

    set_targetdir("bin/$(mode)-$(arch)/Sandbox/")
    set_objectdir("bin-int/$(mode)-$(arch)/Sandbox/")

    add_deps("Cherno_Hazel")

    add_includedirs("Cherno_Hazel/src")

    add_files("Sandbox/src/**.cpp")
    add_headerfiles("Sandbox/src/(**.h)", {install = false})

    add_defines("HZ_PLATFORM_WINDOWS")
