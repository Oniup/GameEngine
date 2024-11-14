project "KryosEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	targetdir("%{wks.location}/bin/" .. OutputDir .. "/%{prj.name}")
	objdir("%{wks.location}/bin-int/" .. OutputDir .. "/%{prj.name}")

	files {
		"Source/**.h",
		"Source/**.cpp",
	}

	includedirs {
		"Source",
		"%{wks.location}/Engine/Source",
		"%{wks.location}/Engine/Thirdparty/fmt/include",
		"%{wks.location}/Engine/Thirdparty/glfw/include",
		"%{wks.location}/Engine/Thirdparty/glad/include",
		"%{wks.location}/Engine/Thirdparty/glm",
		"%{wks.location}/Engine/Thirdparty/imgui",
	}

	links {
		"Kryos",
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
				"/utf-8"
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
		optimize "On"
		symbols "On"

	filter "configurations:Dist"
		kind "WindowedApp"
		defines { "KY_DIST" }
		runtime "Release"
		optimize "On"
		symbols "Off"