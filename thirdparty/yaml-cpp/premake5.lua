project "yaml-cpp"
	kind "StaticLib"
	language "C++"
  cppdialect "C++17"
	staticruntime "On"

  targetdir ("../../bin/Papaya-%{cfg.system}-%{cfg.longname}")
  objdir ("../../bin-obj/Papaya-%{cfg.system}-%{cfg.longname}")

	files {
		"yaml-cpp/src/**.cpp",
    "yaml-cpp/src/**.h",
	}

	includedirs "yaml-cpp/include"

	filter "system:windows"
		systemversion "latest"

  filter "system:macosx"
    defines { "PAPAYA_MACOS", "GL_SILENCE_DEPRECATION", }
    buildoptions "-Wno-deprecated-declarations"
    xcodebuildsettings { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }

		sysincludedirs "yaml-cpp/include"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

  filter "configurations:Dist"
		runtime "Release"
		optimize "Full"