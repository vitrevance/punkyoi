workspace "punkyoi"
configurations { "Debug", "Release" }

project "Punkyoi"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    includedirs { "src", "lib/asio-1.22.0/include", "lib/SOIL2/src/SOIL2", "lib/taojson/include", "lib/PEGTL/include" }
    libdirs { "lib/SOIL2/lib"}
    links { "pthread", "glfw", "GL", "GLEW", "soil2" }

    files { "src/**.h", "src/**.cpp" }
    
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

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