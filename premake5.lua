workspace "punkyoi"
configurations { "Debug", "Release" }
platforms { "x86_64" }

project "Punkyoi"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    includedirs { "src", "lib/asio-1.22.0/include", "lib/stb-image", "lib/taojson/include", "lib/PEGTL/include", "lib/miniaudio" }
    libdirs { "lib/SOIL2/lib"}
    defines { "GLEW_STATIC" }

    files { "src/**.h", "src/**.cpp" }
    
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter "system:windows"
        defines { "__windows", "_WIN32_WINDOWS" }
        libdirs { "lib/win_precomp" }
        includedirs { "lib/win_precomp" }
        links { "opengl32", "glfw3", "glew32s" }

    filter "system:linux"
        defines { "__linux" }
        links { "pthread", "glfw", "GL", "GLEW" }

newaction {
    trigger     = "clean",
    description = "clean the software",
    execute     = function ()
        print("clean the build...")
        os.rmdir("./bin")
        os.rmdir("./obj")
        os.rmdir("./lib/SOIL2/make")
        os.rmdir("./lib/SOIL2/obj")
        os.rmdir("./lib/SOIL2/lib")
        print("done.")
    end
}