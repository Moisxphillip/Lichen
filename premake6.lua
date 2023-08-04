-- TODO fix engine library and game compilation

workspace "Lichen"
    architecture "x32"
    configurations { "debug", "release" }

project "engine"
    
    kind "StaticLib"
    -- kind "ConsoleApp"

    language "C++"
    cppdialect "C++17"
    targetdir "bin/"
    targetname "%{prj.name}_%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    objdir "obj/"
    location "engine"
    
    files 
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.c",
        "%{prj.name}/**.hpp",
        "%{prj.name}/**.cpp"
    }

    includedirs
    {
        "./extlib/include", 
        "/engine/lib" --,
        -- "/game/lib"
    }

    libdirs
    {
        "./extlib/lib"
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
        "opengl32",
        "glew32",
        "soloud_static_x86",
        "irrKlang"
    }

    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"
        
    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"

project "game"

    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/"
    targetname "%{prj.name}_%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    objdir "obj/"
    location "game"

    files 
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.c",
        "%{prj.name}/**.hpp",
        "%{prj.name}/**.cpp"
    }

    includedirs
    {
        "./extlib/include", 
        "/engine/lib",
        "/game/lib"
    }

    libdirs
    {
        "./extlib/lib",
        "./bin/"
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
        "opengl32",
        "glew32",
        "soloud_static_x86",
        "irrKlang"
    }