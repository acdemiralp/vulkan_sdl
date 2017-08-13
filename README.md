#### Getting Started
- Copy the header ```vulkan_sdl.h``` to your project. Ensure the native Vulkan definitions ```VK_USE_PLATFORM_ANDROID_KHR```, ```VK_USE_PLATFORM_WIN32_KHR```, etc are defined correctly prior to including this file.
- This header defines one structure ```VkSDLSurfaceCreateInfo``` and one function ```vkCreateSDLSurface```.
- The structure ```VkSDLSurfaceCreateInfo``` is defined similarly to the native Vulkan structures ```VkAndroidSurfaceCreateInfoKHR```, ```VkWin32SurfaceCreateInfoKHR```, etc but contains a ```SDL_Window*``` rather than platform-specific window information:
    ```cpp
    struct VkSDLSurfaceCreateInfo
    {
      const void* pNext;
      VkFlags     flags;  
      SDL_Window* pWindow;
    };
    ``` 
- The function ```vkCreateSDLSurface``` is defined similarly to the native Vulkan functions ```vkCreateAndroidSurfaceKHR```, ```vkCreateWin32SurfaceKHR```, etc and accepts a ```VkSDLSurfaceCreateInfo*```:
    ```cpp
    inline VkResult vkCreateSDLSurface(
      VkInstance                    instance, 
      const VkSDLSurfaceCreateInfo* pCreateInfo, 
      const VkAllocationCallbacks*  pAllocator, 
      VkSurfaceKHR*                 pSurface);
    ``` 
- Example usage:
    ```cpp
    #define VK_USE_PLATFORM_WIN32_KHR
    #include <vulkan_sdl/vulkan_sdl.h>
    void main()
    {
        SDL_Window* window;
        // Initialize SDL window...

        VkInstance instance;
        // Initialize Vulkan instance...

        VkSurfaceKHR surface;
        VkSDLSurfaceCreateInfo info { /* pNext */ nullptr, /* flags */ 0, window };
        vkCreateSDLSurface(instance, &info, nullptr, &surface);
    }
    ``` 
- Supports all window systems supported by Vulkan (i.e. Android, Mir, Wayland, Win32, XCB, Xlib).

