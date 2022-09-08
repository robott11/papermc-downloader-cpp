-- premake5.lua
workspace "HelloWorld"
configurations { "Debug", "Release" }

project "PaperMC-tool"
    kind "ConsoleApp"
    language "C++"
    targetdir "build/%{cfg.buildcfg}"
    includedirs {
        "vendor/curl/include",
        "vendor/nlohmann/include"
    }
    links "curl"

    files { "**.h", "**.cpp" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    include "vendor/curl"