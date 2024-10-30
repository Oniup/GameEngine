project "GLAD"
	kind "StaticLib"
	language "C"
	-- targetdir("../../bin/" .. outputdir .. "/%{prj.name}")
	-- objdir("../../bin-int/" .. outputdir .. "/%{prj.name}")
	targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs {
		"glad/include",
	}

	files {
		"glad/src/glad.c",
		"glad/include/glad/glad.h",
		"glad/include/KHR/khrplatform.h",
	}

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
