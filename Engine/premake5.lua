include "Thirdparty"

project "Oniun"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "Off"

	files {
		"Source/**.h",
		"Source/**.cpp",

		"Thirdparty/glm/glm/**.ini",
		"Thirdparty/glm/glm/**.hpp",
	}

	includedirs {
		"Source",
		"Thirdparty/glfw/include",
		"Thirdparty/glad/include",
		"Thirdparty/glm",
	}

	links {
		"GLFW",
		"GLAD",
	}

	targetdir("../bin/" .. outputdir .. "/%{prj.name}")
	objdir("../bin-int/" .. outputdir .. "/%{prj.name}")

	filter "system:windows"
		systemversion "latest"
		defines { "O_PLATFORM_WINDOWS" }

	filter "configurations:Debug"
		defines { "O_DEBUG" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines { "O_RELEASE" }
		runtime "Release"
		optimize "on"
		symbols "On"

	filter "configurations:Dist"
		defines { "O_DIST" }
		runtime "Release"
		optimize "On"
		symbols "On"
