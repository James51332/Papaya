workspace "Papaya"
  configurations { "Debug", "Release", "Dist" }
  architecture "x86_64"
  startproject "Sandbox"

builddir = ("bin/Papaya-%{cfg.system}-%{cfg.longname}")
objectdir = ("bin-obj/Papaya-%{cfg.system}-%{cfg.longname}")

include "thirdparty/imgui"

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
    "include/**.h",
    "thirdparty/opengl/**.h",
    "thirdparty/spdlog/**.h",
    "thirdparty/stb_image/**.h",
    "thirdparty/stb_image/**.cpp",
    "thirdparty/glm/**.h",
    "thirdparty/glm/**.inl",
  }

  includedirs {
    "thirdparty/spdlog/include",
    "thirdparty/glm",
    "thirdparty/stb_image",
    "thirdparty/opengl",
    "thirdparty/imgui",
    ".",
  }

  links {
    "ImGui"
  }

  filter "configurations:Debug"
    defines "PAPAYA_DEBUG"
    symbols "On"

  filter "configurations:Release"
    defines "PAPAYA_RELEASE"
    optimize "On"

  filter "configurations:Dist"
    defines "PAPAYA_DIST"
    optimize "Full"

  filter "system:macosx"
    defines { "PAPAYA_MACOS", "GL_SILENCE_DEPRECATION", }
    xcodebuildsettings = { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }
    buildoptions "-Wno-deprecated-declarations"

    sysincludedirs {
      "thirdparty/spdlog/include",
      "thirdparty/glm",
      "thirdparty/stb_image",
      "thirdparty/imgui",
      ".",
    }

    files {
      "platform/macos/**.mm",
      "platform/macos/**.cpp",
      "platform/macos/**.h",
      "platform/opengl/**.cpp",
      "platform/opengl/**.h",
    }

  filter "action:vs*"
    characterset "ASCII"
    defines "_CRT_SECURE_NO_WARNINGS"

  filter { "system:windows", "action:gmake" }
    buildoptions "-std=gnu++17"

  filter "system:windows"
    defines "PAPAYA_WINDOWS"
    systemversion "latest"

    files {
      "platform/windows/**.cpp",
      "platform/windows/**.h",
      "platform/opengl/**.cpp",
      "platform/opengl/**.h",
    }

  filter "system:linux"
    defines "PAPAYA_LINUX"

project "Sandbox"
  location "Sandbox"
  language "C++"
  cppdialect "C++17"
  
  targetdir (builddir)
  objdir (objectdir)
  
  files {
    "tests/**.cpp",
    "tests/**.h",
    "tests/**.png",
  }
  
  includedirs {
    "include",
    "thirdparty/spdlog/include",
    "thirdparty/glm",
    "thirdparty/opengl",
    "thirdparty/imgui",
    ".",
  }
  
  links {
    "Papaya"
  }

  filter "configurations:Debug"
    defines "PAPAYA_DEBUG"
    symbols "On"

  filter "configurations:Release"
    defines "PAPAYA_RELEASE"
    optimize "On"

  filter "configurations:Dist"
    defines "PAPAYA_DIST"
    optimize "Full"

  filter "system:macosx"
    kind "ConsoleApp"
    defines { "PAPAYA_MACOS", "GL_SILENCE_DEPRECATION", }
    buildoptions "-Wno-deprecated-declarations"
    xcodebuildsettings = { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }

    sysincludedirs {
      "include",
      "thirdparty/spdlog/include",
      "thirdparty/glm",
      "thirdparty/imgui",
      "."
    }

    links {
      "Cocoa.framework"
    }

  filter "action:vs*"
    characterset "ASCII"
    defines "_CRT_SECURE_NO_WARNINGS"
    debugdir "$(SolutionDir)"

  filter { "system:windows", "action:gmake" }
    buildoptions "-std=gnu++17"
  
  filter { "system:windows", "Debug" }
    kind "ConsoleApp"

  filter { "system:windows", "Release or Dist"}
    kind "WindowedApp"
    entrypoint "mainCRTStartup"

  filter "system:windows"
    defines "PAPAYA_WINDOWS"
    systemversion "latest"

    links {
      "kernel32",
      "gdi32",
      "OpenGL32",
      "user32",
    }

  filter "system:linux"
    defines "PAPAYA_LINUX"