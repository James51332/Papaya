workspace "Papaya"
  architecture "x86_64"
  startproject "Editor"
  
  configurations 
  { 
    "Debug", 
    "Release", 
    "Dist"
  }

  flags
	{
		"MultiProcessorCompile"
	}

builddir = ("bin/Papaya-" .. string.capitalized("%{cfg.system}") .. "-%{cfg.longname}")
objectdir = ("bin-obj/Papaya-" .. string.capitalized("%{cfg.system}") .. "-%{cfg.longname}")

includes = {}
includes["spdlog"] = "thirdparty/spdlog/include"
includes["glm"] = "thirdparty/glm"
includes["stb_image"] = "thirdparty/stb_image"
includes["opengl"] = "thirdparty/opengl"
includes["imgui"] = "thirdparty/imgui"
includes["entt"] = "thirdparty/entt/single_include"
includes["yaml-cpp"] = "thirdparty/yaml-cpp/yaml-cpp/include"

group "Dependencies"
  include "thirdparty/imgui"
  include "thirdparty/yaml-cpp"
group ""

project "Papaya"
  location "papaya"
  kind "StaticLib"
  language "C++"
  cppdialect "C++17"
  staticruntime "On"

  pchheader "papayapch.h"
  pchsource "papayapch.cpp"

  targetdir (builddir)
  objdir (objectdir)

  files {
    "papayapch.cpp",
    "main/**.cpp",
    "main/**.h",
    "thirdparty/opengl/**.h",
    "thirdparty/spdlog/**.h",
    "thirdparty/stb_image/**.h",
    "thirdparty/stb_image/**.cpp",
    "thirdparty/glm/**.h",
    "thirdparty/glm/**.inl"
  }

  includedirs {
    "."
  }

  sysincludedirs {
    "include",
    includes["spdlog"],
    includes["glm"],
    includes["stb_image"],
    includes["opengl"],
    includes["imgui"],
    includes["entt"],
    includes["yaml-cpp"]
  }

  links 
  {
    "ImGui",
    "yaml-cpp"
  }

  filter "configurations:Debug"
    runtime "Debug"
    defines "PAPAYA_DEBUG"
    symbols "On"

  filter "configurations:Release"
    runtime "Release"
    defines "PAPAYA_RELEASE"
    optimize "On"

  filter "configurations:Dist"
    runtime "Release"  
    defines "PAPAYA_DIST"
    optimize "Full"

  filter "system:macosx"
    buildoptions "-Wno-deprecated-declarations"
    
    defines 
    { 
      "PAPAYA_MACOS", 
      "GL_SILENCE_DEPRECATION" 
    }

    files 
    {
      "platform/macos/**.mm",
      "platform/macos/**.cpp",
      "platform/macos/**.h",
      "platform/opengl/**.cpp",
      "platform/opengl/**.h"
    }

  filter "action:vs*"
    characterset "ASCII"
    defines "_CRT_SECURE_NO_WARNINGS"

  filter { "system:windows", "action:gmake" }
    buildoptions "-std=gnu++17"

  filter "system:windows"
    defines "PAPAYA_WINDOWS"
    systemversion "latest"

    files 
    {
      "platform/windows/**.cpp",
      "platform/windows/**.h",
      "platform/opengl/**.cpp",
      "platform/opengl/**.h"
    }

  filter "system:linux"
    defines "PAPAYA_LINUX"

project "Editor"
  location "papaya"
  language "C++"
  cppdialect "C++17"
  staticruntime "On"
  
  pchheader "papayapch.h"
  pchsource "papayapch.cpp"

  targetdir (builddir)
  objdir (objectdir)
  
  files 
  {
    "papayapch.cpp",
    "editor/**.cpp",
    "editor/**.h"
  }
  
  includedirs 
  {
    "."
  }

  sysincludedirs 
  {
    "include",
    includes["spdlog"],
    includes["glm"],
    includes["stb_image"],
    includes["opengl"],
    includes["imgui"],
    includes["entt"],
    includes["yaml-cpp"]
  }

  links 
  {
    "Papaya"
  }

  filter "configurations:Debug"
    runtime "Debug"
    defines "PAPAYA_DEBUG"
    symbols "On"

  filter "configurations:Release"
    runtime "Release"
    defines "PAPAYA_RELEASE"
    optimize "On"

  filter "configurations:Dist"
    runtime "Release"
    defines "PAPAYA_DIST"
    optimize "Full"

  filter "system:macosx"
    kind "ConsoleApp"
    buildoptions "-Wno-deprecated-declarations"

    defines 
    { 
      "PAPAYA_MACOS", 
      "GL_SILENCE_DEPRECATION" 
    }

    links 
    {
      "Cocoa.framework"
    }

  filter "action:vs*"
    characterset "ASCII"
    defines "_CRT_SECURE_NO_WARNINGS"
    debugdir "$(SolutionDir)"

  filter "action:xcode4"
    debugdir "$(SRCROOT)/../"
  
  filter { "system:windows", "action:gmake" }
    buildoptions "-std=gnu++17"
  
  filter { "system:windows", "Debug" }
    kind "ConsoleApp"

  filter { "system:windows", "Release or Dist" }
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

project "Sandbox"
  location "sandbox"
  language "C++"
  cppdialect "C++17"
  staticruntime "On"
  
  pchheader "papayapch.h"
  pchsource "papayapch.cpp"

  targetdir (builddir)
  objdir (objectdir)
  
  files 
  {
    "papayapch.cpp",
    "tests/**.cpp",
    "tests/**.h"
  }
  
  includedirs 
  {
    "."
  }

  sysincludedirs 
  {
    "include",
    includes["spdlog"],
    includes["glm"],
    includes["stb_image"],
    includes["opengl"],
    includes["imgui"],
    includes["entt"],
    includes["yaml-cpp"]
  }

  links 
  {
    "Papaya"
  }

  filter "configurations:Debug"
    runtime "Debug"
    defines "PAPAYA_DEBUG"
    symbols "On"

  filter "configurations:Release"
    runtime "Release"
    defines "PAPAYA_RELEASE"
    optimize "On"

  filter "configurations:Dist"
    runtime "Release"
    defines "PAPAYA_DIST"
    optimize "Full"

  filter "system:macosx"
    kind "ConsoleApp"
    buildoptions "-Wno-deprecated-declarations"
    
    defines 
    { 
      "PAPAYA_MACOS", 
      "GL_SILENCE_DEPRECATION" 
    }

    links 
    {
      "Cocoa.framework"
    }

  filter "action:vs*"
    characterset "ASCII"
    defines "_CRT_SECURE_NO_WARNINGS"
    debugdir "$(SolutionDir)"
  
  filter "action:xcode4"
    debugdir "$(SRCROOT)/../"

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

    links 
    {
      "kernel32",
      "gdi32",
      "OpenGL32",
      "user32"
    }

  filter "system:linux"
    defines "PAPAYA_LINUX"
