workspace "Lichen"
    architecture "x32"
    configurations { "debug", "release", "profiler" }

project "LichenEngine"
    
    -- kind "SharedLib"
    kind "ConsoleApp"

    language "C++"
    cppdialect "C++17"
    targetdir "bin/"
    targetname "%{prj.name}_%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    objdir "bin/obj/"
    
    files 
    {
        "engine/**.h",
        "engine/**.c",
        "engine/**.hpp",
        "engine/**.cpp",
        
        "extlib/**.h",
        "engine/**.c",
        "engine/**.hpp",
        "engine/**.cpp",
        
        "game/**.h",
        "game/**.c",
        "game/**.hpp",
        "game/**.cpp"
    }

    includedirs
    {
        "extlib/include", 
        "engine/include",
        "game/include"
    }

    libdirs
    {
        "extlib/lib"
    }

    links
    {
        "SDL2",
        "SDL2main",
        "SDL2_image",
        "SDL2_mixer",
        "SDL2_ttf",
        "m",
        "glfw3",
        "gdi32",
        "opengl32",
        "glew32", --compile glew32s to link the static lib on compilation if wanted
        -- "freetype",
        -- "soloud_static_x86",
        -- "irrKlang"
    }

    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"
        -- linkoptions {"-static"}
        
        filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "Full"
        flags{"LinkTimeOptimization"}
        buildoptions {"-mwindows"}
        -- linkoptions {"-static"}
        -- StaticRuntime "On"
        
        filter "configurations:Profiler"
        -- defines {"NDEBUG", "TRACY_ENABLE"}
        optimize "On"
        -- buildoptions {"-static"}