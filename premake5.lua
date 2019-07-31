-- premake5.lua
-- https://git-scm.com/book/en/v2/Git-Tools-Submodules
workspace "CachapaDS"
   architecture "x64"
   startproject "PressF"
   configurations { "Debug", "Release", "Dist"}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "PressF"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17" --StaticLib

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
   
   files { 

   }

   includedirs {

   }

   libdirs
   {

   }

   links {

   }


   filter "configurations:Debug"
      defines { "_CRT_SECURE_NO_WARNINGS", "DEBUG"}
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"


project "TestPlayground"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17" --StaticLib

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
   
   
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"