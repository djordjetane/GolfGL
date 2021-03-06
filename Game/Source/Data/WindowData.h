#pragma once

struct WindowData
{
    inline static int width = 1280;
    inline static int height = 720;
    inline static constexpr char *windowTitle = "GolfGL";
    inline static constexpr char *glslVersion = "#version 330";
    inline static bool fxaa = true;
    inline static bool vsync = true;

    inline static const std::string GetResolution()
    {
        return std::to_string(width).append("x").append(std::to_string(height));
    }

    // Just to avoid massive number of casting
    inline static float W = 1280.f;
    inline static float H = 720.f;
};
