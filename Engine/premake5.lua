include "Thirdparty"

project "Kryos"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "Off"
	targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

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
		"Thirdparty/glfw/include",
		"Thirdparty/glad/include",
		"Thirdparty/fmt/include",
		"Thirdparty/glm",
	}

	links {
		"GLFW",
		"GLAD",
	}

	defines {
		"FMT_HEADER_ONLY",
	}

	filter "system:windows"
		systemversion "latest"
		defines { "KY_PLATFORM_WINDOWS" }
		filter "action:vs*"
			buildoptions {
				"/utf-8"
			}

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
		symbols "On"
