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
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    externalincludedirs
    {
        "%{prj.name}/include/gameover",
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
