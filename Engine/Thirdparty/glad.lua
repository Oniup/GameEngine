project "glad"
	kind "StaticLib"
	language "C"
	targetdir("%{wks.location}/bin/" .. OutputDir .. "/%{prj.name}")
	objdir("%{wks.location}/bin-int/" .. OutputDir .. "/%{prj.name}")

	includedirs {
		"glad/include",
	}

	files {
		"glad/src/glad.c",
		"glad/include/glad/glad.h",
		"glad/include/KHR/khrplatform.h",
	}

	filter "system:linux"
		pic "On"
		systemversion "latest"
		staticruntime "On"

	filter "system:window"
		systemversion "latest"
		staticruntime "On"

	filter "configurations:Debug"
		defines { "KY_DEBUG" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines { "KY_RELEASE" }
		runtime "Release"
		symbols "On"

	filter "configurations:Dist"
		defines { "KY_DIST" }
		runtime "Release"
		symbols "Off"
