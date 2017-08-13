#include "catch.hpp"

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan_sdl/vulkan_sdl.h>

SCENARIO("Vulkan SDL is being tested.", "[vulkan_sdl]")
{
  SDL_Window* window = nullptr;
  // TODO: Initialize SDL window...

  VkInstance instance = nullptr;
  // TODO: Initialize Vulkan instance...

  VkSurfaceKHR surface;
  VkSDLSurfaceCreateInfo info { nullptr, 0, window };
  vkCreateSDLSurface(instance, &info, nullptr, &surface);
}