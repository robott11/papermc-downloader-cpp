-- premake5.lua
workspace "PaperMC-tool"
    configurations { "Debug", "Release" }
    platforms { "x32", "x64" }

    project "PaperMC-tool"
        kind "ConsoleApp"
        language "C++"
        objdir "build/%{cfg.platform}/%{cfg.buildcfg}/%{prj.name}/obj"
        targetdir "build/%{cfg.platform}/%{cfg.buildcfg}/%{prj.name}/bin"
        
        files { "PaperMC-tool/*.h", "PaperMC-tool/*.cpp" }

        vpaths {
            ["Headers"] = "**.h",
            ["Sources"] = "**.cpp"
         }
        
        includedirs {
            "vendor/curl/include",
            "vendor/nlohmann/include"
        }
        links { "libcurl" }
        include "vendor/curl"

        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"

        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "Speed"