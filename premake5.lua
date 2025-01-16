dofile("premake-cmake/cmake.lua")
workspace "gameover"
    startproject "gameovereditor"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
    }

tdir = "bin/%{cfg.buildcfg}/%{prj.name}"
odir = "bin-obj/%{cfg.buildcfg}/%{prj.name}"
--vendors dependencies
vendors = {}
vendors["SDL2"] = "vendors/sdl2"
vendors["SPDLOG"] = "vendors/spdlog"
vendors["GLAD"] = "vendors/glad"
--Process Glad 
include "vendors/glad"

project "gameover"
    location "gameover"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    
    targetdir (tdir)
    objdir (odir)

    files{
        "%{prj.name}/include/**.h",
        "%{prj.name}/include/**.cpp",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/**.natvis",
    }

    externalincludedirs
    {
        "%{prj.name}/include",
        "%{vendors.SDL2}/include",
        "%{vendors.SPDLOG}/include",
        "%{vendors.GLAD}/include",
    }
    

    flags
    {
        "FatalWarnings"
    }

    defines
    {
        "GLFW_INCLUDE_NONE" -- to avoid include glfw3.h
    }

    filter {"system:windows", "configurations:*"}
        systemversion "latest"

        defines
        {
            "GAMEOVER_PLATFORM_WINDOWS"
        }

    filter {"system:linux", "configurations:*"}
        defines
        {
            "GAMEOVER_PLATFORM_LINUX"
        }
    
    filter "configurations:Debug"
        defines
        {
            "GAMEOVER_CONFIG_DEBUG"
        }
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        defines
        {
            "GAMEOVER_CONFIG_RELEASE"
        }
        runtime "Release"
        symbols "off"
        optimize "on"
        
        

project "gameovereditor"
    location "gameovereditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    links "gameover"

    targetdir (tdir)
    objdir (odir)

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    externalincludedirs
    {
        "gameover/include",
        "%{vendors.SPDLOG}/include",
    }

    flags
    {
        "FatalWarnings"
    }

    filter {"system:windows", "configurations:*"}
    systemversion "latest"
        defines
        {
            "GAMEOVER_PLATFORM_WINDOWS"
        }
        libdirs{
            "%{vendors.SDL2}/lib"
        }
        links{
            "SDL2",
            "GLAD",
        }

    filter {"system:linux", "configurations:*"}
        defines
        {
            "GAMEOVER_PLATFORM_LINUX"
        }

        links{
            "SDL2",
            "GLAD",
            "dl",
        }

    filter "configurations:Debug"
        defines
        {
            "GAMEOVER_CONFIG_DEBUG"
        }
        runtime "Debug"
        symbols "on"

    
    filter "configurations:Release"
        defines
        {
            "GAMEOVER_CONFIG_RELEASE"
        }
        runtime "Release"
        symbols "off"
        optimize "on"

-- require "cmake"