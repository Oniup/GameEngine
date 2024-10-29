workspace "Oniun"
	architecture "x64"
	configurations { 
		"Debug",
		"Release",
		"Dist",
	}
	startproject "OniunEditor"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Engine"
include "Editor"