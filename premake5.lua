-- premake5.lua
-- https://git-scm.com/book/en/v2/Git-Tools-Submodules



outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
libName = "CachapaDS"
libType = "StaticLib" -- uncomment for .lib 
-- libType = "SharedLib" -- uncomment for dll
appName = "Playground"

workspace(libName)
   architecture "x64"
   startproject(appName)
   configurations { "Debug", "Release", "Dist"}




project(libName)
   location(libName)
   kind (libType)
   language "C++"
   cppdialect "C++17"

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

   files { 
      "%{prj.name}/src/**.cpp",
      "%{prj.name}/cds/**.h",
   }

   filter "configurations:Debug"
      defines { "_CRT_SECURE_NO_WARNINGS", "DEBUG"}
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"



project(appName)
   location(appName)
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17" --StaticLib

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


   includedirs{
      libName
   }
   links{libName}
   
   files { 
      "%{prj.name}/*/**.cpp",
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
   
   filter "system:windows"
		systemversion "latest"