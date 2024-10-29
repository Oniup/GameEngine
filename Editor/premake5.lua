project "OniunEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir("../bin/" .. outputdir .. "/%{prj.name}")
	objdir("../bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"Source/**.h",
		"Source/**.cpp",
	}

	includedirs {
		"../Engine/Source",
		"../Engine/Thirdparty/glfw/include",
		"../Engine/Thirdparty/glad/include",
		"../Engine/Thirdparty/glm",
	}

	links {
		"Oniun",
	}

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
		optimize "On"
		symbols "On"

	filter "configurations:Dist"
		kind "WindowedApp"
		defines { "O_DIST" }
		runtime "Release"
		optimize "On"
		symbols "Off"