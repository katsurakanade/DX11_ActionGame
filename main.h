#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX

// Base
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <assert.h>
#include <math.h>
#include <map>
#include <vector>
#include <string>
#include <chrono>
#include <unordered_map>
#include <memory>
#include <utility>
#include <functional>
#include <random>

#pragma warning(push)
#pragma warning(disable:4005)

// DirectX
#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx11.h>
#include <DirectXMath.h>
#include <xaudio2.h>

// Imgui
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>

#pragma warning(pop)

#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "ole32.lib")

#define SCREEN_WIDTH		(1920)
#define SCREEN_HEIGHT	(1080)
#define FIELD_X 101

// Getter
HWND GetWindow();
HINSTANCE GetHinstance();
// ForDebug
void DebugOutputString(const char* str, ...);