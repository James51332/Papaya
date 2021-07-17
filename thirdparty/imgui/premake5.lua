project "ImGui"
	kind "StaticLib"
	language "C++"
  cppdialect "C++17"
	staticruntime "On"

  targetdir ("../../bin/Papaya-%{cfg.system}-%{cfg.longname}")
  objdir ("../../bin-obj/Papaya-%{cfg.system}-%{cfg.longname}")

	files
	{
		"imgui/imconfig.h",
		"imgui/imgui.h",
		"imgui/imgui.cpp",
		"imgui/imgui_draw.cpp",
		"imgui/imgui_internal.h",
		"imgui/imgui_widgets.cpp",
		"imgui/imgui_tables.cpp",
		"imgui/imstb_rectpack.h",
		"imgui/imstb_textedit.h",
		"imgui/imstb_truetype.h",
		"imgui/imgui_demo.cpp"
	}

	filter "system:windows"
		systemversion "latest"

  filter "system:macosx"
    defines { "PAPAYA_MACOS", "GL_SILENCE_DEPRECATION", }
    buildoptions "-Wno-deprecated-declarations"
    xcodebuildsettings { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

  filter "configurations:Dist"
		runtime "Release"
		optimize "Full"