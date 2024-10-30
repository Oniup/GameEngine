project "KryosEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"Source/**.h",
		"Source/**.cpp",
	}

	includedirs {
		"%{wks.location}/Engine/Source",
		"%{wks.location}/Engine/Thirdparty/glfw/include",
		"%{wks.location}/Engine/Thirdparty/glad/include",
		"%{wks.location}/Engine/Thirdparty/fmt/include/",
		"%{wks.location}/Engine/Thirdparty/glm",
	}

	links {
		"Kryos",
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
		optimize "On"
		symbols "On"

	filter "configurations:Dist"
		kind "WindowedApp"
		defines { "KY_DIST" }
		runtime "Release"
		optimize "On"
		symbols "Off"