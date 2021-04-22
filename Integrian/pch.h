#pragma once

#ifndef PCH_H
#define PCH_H

// SDL libs
#pragma comment(lib, "sdl2.lib")
#pragma comment(lib, "SDL2main.lib")

// OpenGL libs
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"Glu32.lib")

// SDL extension libs 
#pragma comment(lib, "SDL2_image.lib")  
#pragma comment(lib, "SDL2_ttf.lib") 
#pragma comment(lib, "SDL2_mixer.lib")  

// SDL and OpenGL Includes
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_video.h>
#include <GL\GLU.h>

// ImGui
#include "imgui.h"
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl.h"

#include "TypeDefines.h"
#include "Structs.h"
#include "MathFunctions.h"
#include "Utility Functions.h"
#include "ExceptionHandler.h"
#include "Logger.h"

template<typename Type>
constexpr void SafeDelete(Type*& pData)
{
	if (pData)
	{
		delete pData;
		pData = nullptr;
	}
}

constexpr bool AlwaysFalse()
{
	return false;
}

#endif //PCH_H