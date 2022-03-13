workspace "punkyoi"
	configurations { "Debug", "Release" }

project "Punkyoi"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir "bin/%{cfg.buildcfg}"
	includedirs { "lib/asio-1.22.0/include", "src" }
	links { "pthread", "glfw" }

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
      print("done.")
   end
}
