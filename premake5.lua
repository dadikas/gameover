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

project "gameovereditor"
    location "gameovereditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    flags
    {
        "FatalWarnings"
    }