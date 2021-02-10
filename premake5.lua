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
    "include/**.h",
    "thirdparty/spdlog/**.h",
  }

  includedirs {
    "thirdparty/spdlog/include",
    ".",
  }

  filter "configurations:Debug"
    defines "PAPAYA_DEBUG"

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
      ".",
    }

    files {
      "platform/macos/**.mm",
      "platform/macos/**.cpp",
      "platform/macos/**.h",
      "platform/opengl/**.cpp",
      "platform/opengl/**.h",
    }

    links {
      "Cocoa.framework",
      "OpenGL.framework",
    }

  filter "system:windows"
    defines "PAPAYA_WINDOWS"
    symbols "On"
    buildoptions "-std=gnu++17"

    files {
      "platform/windows/**.cpp",
      "platform/windows/**.h",
      "platform/opengl/**.cpp",
      "platform/opengl/**.h",
    }

    links {
      "kernel32",
      "gdi32",
      "OpenGL32",
      "user32",
    }

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

  includedirs {
    "include",
    "thirdparty/spdlog/include",
    ".",
  }

  filter "configurations:Debug"
    defines "PAPAYA_DEBUG"

  filter "configurations:Release"
    defines "PAPAYA_RELEASE"
    optimize "On"

  filter "configurations:Dist"
    defines "PAPAYA_DIST"
    optimize "Full"

  filter "system:macosx"
    defines { "PAPAYA_MACOS", "GL_SILENCE_DEPRECATION", }
    buildoptions "-Wno-deprecated-declarations"
    xcodebuildsettings = { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" },

    sysincludedirs {
      "include",
      "thirdparty/spdlog/include",
      "."
    }

    links {
      "Cocoa.framework",
      "OpenGL.framework",
    }

  filter "system:windows"
    defines "PAPAYA_WINDOWS"
    buildoptions "-std=gnu++17"

    links {
      "kernel32",
      "gdi32",
      "OpenGL32",
      "user32",
    }

  filter "system:linux"
    defines "PAPAYA_LINUX"