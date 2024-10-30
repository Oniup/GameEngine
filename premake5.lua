workspace "Kryos Game Engine"
	architecture "x64"
	configurations { 
		"Debug",
		"Release",
		"Dist",
	}
	startproject "KryosEditor"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Engine"
include "Editor"