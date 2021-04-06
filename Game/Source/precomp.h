#pragma once

#ifdef WIN32
#include <Windows.h>
#endif // WIN32

// extern libs
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "misc/cpp/imgui_stdlib.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define SPDLOG_NO_EXCEPTIONS
#include <spdlog/spdlog.h>
#include <stb_image.h>

// Global data
#include "Asserts.h"
#include "Data/WindowData.h"

// classes
#include <Camera/Camera.h>
#include <Entities/Light.h>
#include <Input/Input.h>
#include <Logger/Log.h>
#include <Render/Renderer.h>
#include <Render/Texture.h>
#include <Window/Window.h>

// STL
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <unordered_set>
#include <utility>
#include <vector>
