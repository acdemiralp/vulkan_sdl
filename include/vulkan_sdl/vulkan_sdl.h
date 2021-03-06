#ifndef VULKAN_SDL_H_
#define VULKAN_SDL_H_

#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_video.h>
#include <vulkan/vulkan.h>

#ifdef VK_USE_PLATFORM_XCB_KHR
#include <X11/Xlib-xcb.h>
#endif

struct VkSDLSurfaceCreateInfo
{
  const void* pNext;
  VkFlags     flags;
  SDL_Window* pWindow;
};

inline VkResult vkCreateSDLSurface(
  VkInstance                    instance, 
  const VkSDLSurfaceCreateInfo* pCreateInfo, 
  const VkAllocationCallbacks*  pAllocator, 
  VkSurfaceKHR*                 pSurface)
{
  SDL_SysWMinfo sysInfo;
  SDL_VERSION(&sysInfo.version);
  if(!SDL_GetWindowWMInfo(pCreateInfo->pWindow, &sysInfo))
    return VK_ERROR_INITIALIZATION_FAILED;
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
  if (sysInfo.subsystem == SDL_SYSWM_ANDROID)
  {
    VkAndroidSurfaceCreateInfoKHR createInfo {
      VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR,
      pCreateInfo->pNext,
      pCreateInfo->flags,
      sysInfo.info.android.window};
    return vkCreateAndroidSurfaceKHR(instance, &createInfo, pAllocator, pSurface);
  }
#endif
#if defined(VK_USE_PLATFORM_MIR_KHR)
  if (sysInfo.subsystem == SDL_SYSWM_MIR)
  {
    VkMirSurfaceCreateInfoKHR createInfo {
      VK_STRUCTURE_TYPE_MIR_SURFACE_CREATE_INFO_KHR,
      pCreateInfo->pNext,
      pCreateInfo->flags,
      sysInfo.info.mir.connection,
      sysInfo.info.mir.surface};
    return vkCreateMirSurfaceKHR(instance, &createInfo, pAllocator, pSurface);
  }
#endif
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
  if (sysInfo.subsystem == SDL_SYSWM_WAYLAND)
  {
    VkWaylandSurfaceCreateInfoKHR createInfo{
      VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR,
      pCreateInfo->pNext,
      pCreateInfo->flags,
      sysInfo.info.wl.display,
      sysInfo.info.wl.surface};
    return vkCreateWaylandSurfaceKHR(instance, &createInfo, pAllocator, pSurface);
  }
#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)
  if (sysInfo.subsystem == SDL_SYSWM_WINDOWS)
  {
    VkWin32SurfaceCreateInfoKHR createInfo{
      VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
      pCreateInfo->pNext,
      pCreateInfo->flags,
#if SDL_MAJOR_VERSION >= 2 && SDL_MINOR_VERSION >= 0 && SDL_PATCHLEVEL >= 6
      sysInfo.info.win.hinstance,
#else
      reinterpret_cast<HINSTANCE>(GetWindowLong(sysInfo.info.win.window, /* GWL_HINSTANCE */ -6)),
#endif
      sysInfo.info.win.window};
    return vkCreateWin32SurfaceKHR(instance, &createInfo, pAllocator, pSurface);
  }
#endif
#if defined(VK_USE_PLATFORM_XCB_KHR)
  if (sysInfo.subsystem == SDL_SYSWM_X11)
  {
    VkXcbSurfaceCreateInfoKHR createInfo{
      VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR,
      pCreateInfo->pNext,
      pCreateInfo->flags,
      XGetXCBConnection(sysInfo.info.x11.display),
      sysInfo.info.x11.window};
    return vkCreateXcbSurfaceKHR(instance, &createInfo, pAllocator, pSurface);
  }
#endif
#if defined(VK_USE_PLATFORM_XLIB_KHR)
  if (sysInfo.subsystem == SDL_SYSWM_X11)
  {
    VkXlibSurfaceCreateInfoKHR createInfo{
      VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR,
      pCreateInfo->pNext,
      pCreateInfo->flags,
      sysInfo.info.x11.display,
      sysInfo.info.x11.window};
    return vkCreateXlibSurfaceKHR(instance, &createInfo, pAllocator, pSurface);
  }
#endif
  return VK_ERROR_INITIALIZATION_FAILED;
}

#endif
