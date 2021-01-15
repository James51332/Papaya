workspace "Papaya"
  configurations { "Debug", "Release", "Dist" }
  architecture "x86_64"

builddir = ("bin/Papaya-%{cfg.system}-%{cfg.longname}")
objectdir = ("bin-obj/Papaya-%{cfg.system}-%{cfg.longname}")

project "Papaya"
  location "Papaya"
  kind "StaticLib"
  language "C++"
  cppdialect "C++17"

  targetdir (builddir)
  objdir (objectdir)

  files {
    "main/**.cpp",
    "main/**.h",
    "platform/**.cpp",
    "platform/**.h",
    "include/**.h",
    "thirdparty/spdlog/**.h"
  }

  sysincludedirs {
    "thirdparty/spdlog/include",
    ".",
  }

  filter "configurations:Debug"
    defines "PAPAYA_DEBUG"

  filter "system:macosx"
    defines "PAPAYA_MACOS"
    xcodebuildsettings = { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }

  filter "system:windows"
    defines "PAPAYA_WINDOWS"

  filter "system:linux"
    defines "PAPAYA_LINUX"

project "Sandbox"
  location "Sandbox"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  links "Papaya"

  targetdir (builddir)
  objdir (objectdir)

  files {
    "tests/**.cpp",
    "tests/**.h",
  }

  sysincludedirs {
    "include",
    "thirdparty/spdlog/include",
    ".",
  }

  filter "configurations:Debug"
    defines "PAPAYA_DEBUG"

  filter "system:macosx"
    defines "PAPAYA_MACOS"
    xcodebuildsettings = { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }

  filter "system:windows"
    defines "PAPAYA_WINDOWS"

  filter "system:linux"
    defines "PAPAYA_LINUX"