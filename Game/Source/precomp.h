#pragma once

#ifdef WIN32
#include <Windows.h>
#endif

// extern libs
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
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
