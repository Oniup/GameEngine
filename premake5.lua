workspace "Kryos Game Engine"
	architecture "x64"
	configurations { 
		"Debug",
		"Release",
		"Dist",
	}
	startproject "KryosEditor"

OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
VersionMajor = "KY_VERSION_MAJOR=0"
VersionMinor = "KY_VERSION_MINOR=0"
VersionPatch = "KY_VERSION_PATCH=0"

include "Engine"
include "Editor"