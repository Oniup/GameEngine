include "Thirdparty"

project "Kryos"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "Off"
	targetdir("%{wks.location}/bin/" .. OutputDir .. "/%{prj.name}")
	objdir("%{wks.location}/bin-int/" .. OutputDir .. "/%{prj.name}")

	files {
		"Source/**.h",
		"Source/**.cpp",

		-- glm library
		"Thirdparty/glm/glm/**.ini",
		"Thirdparty/glm/glm/**.hpp",

		-- fmt Library
		"Thirdparty/fmt/include/**.h",
	}

	includedirs {
		"Source",
		"Thirdparty/fmt/include",
		"Thirdparty/glfw/include",
		"Thirdparty/glad/include",
		"Thirdparty/imgui/imgui",
		"Thirdparty/imgui",
		"Thirdparty/glm",
	}

	links {
		"glfw",
		"glad",
		"imgui",
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS",
		"FMT_HEADER_ONLY",
		"GLFW_INCLUDE_NONE",

		VersionMajor,
		VersionMinor,
		VersionPatch,
	}

	filter "system:windows"
		systemversion "latest"
		defines { "KY_PLATFORM_WINDOWS" }
		filter "action:vs*"
			buildoptions {
				"/utf-8",
			}
			-- disablewarnings {
			-- 	"C26439",
			-- }

	filter "configurations:Debug"
		defines { "KY_DEBUG" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines { "KY_RELEASE" }
		runtime "Release"
		optimize "on"
		symbols "On"

	filter "configurations:Dist"
		defines { "KY_DIST" }
		runtime "Release"
		optimize "On"
		symbols "Off"
