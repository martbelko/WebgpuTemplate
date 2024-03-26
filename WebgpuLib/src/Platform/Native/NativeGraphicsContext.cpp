#if defined(PLATFORM_WEB)
	#error This	file should only be compiled for native build
#endif

#include "Base/Base.h"
#include "Base/Utils.h"
#include "Base/GraphicsContext.h"

#include <webgpu/webgpu.h>
#include <webgpu/webgpu_cpp.h>

#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Base {

	static wgpu::Surface GetGLFWSurface(wgpu::Instance instance, GLFWwindow* window)
	{
		HWND hWnd = glfwGetWin32Window(window);
		HINSTANCE hInstance = GetModuleHandle(NULL);

		wgpu::SurfaceDescriptorFromWindowsHWND windowDesc;
		windowDesc.hinstance = hInstance;
		windowDesc.hwnd = hWnd;
		windowDesc.sType = wgpu::SType::SurfaceDescriptorFromWindowsHWND;

		wgpu::SurfaceDescriptor surfaceDesc;
		surfaceDesc.nextInChain = &windowDesc;

		return instance.CreateSurface(&surfaceDesc);
	}

	void GraphicsContext::Init(GLFWwindow* window, uint32_t width, uint32_t height)
	{
		wgpu::InstanceDescriptor desc = {};
		s_Instance = wgpu::CreateInstance(&desc);

		s_Surface = GetGLFWSurface(s_Instance, window);

		wgpu::RequestAdapterOptions opts;
		opts.compatibleSurface = s_Surface;
		opts.backendType = wgpu::BackendType::D3D12;
		opts.powerPreference = wgpu::PowerPreference::HighPerformance;

		s_Adapter = RequestAdapter(s_Instance, &opts);

		wgpu::DeviceDescriptor deviceDesc;
		deviceDesc.label = "Default Device";
		deviceDesc.defaultQueue.label = "Default Queue";

#ifdef _DEBUG
		/*
		 *	Device extensions toggles
		 *	dump_shaders: Log input WGSL shaders and translated backend shaders (MSL/ HLSL/DXBC/DXIL / SPIR-V).
		 *	disable_symbol_renaming: As much as possible, disable renaming of symbols (variables, function names...)
		 *  emit_hlsl_debug_symbols: Sets the D3DCOMPILE_SKIP_OPTIMIZATION and D3DCOMPILE_DEBUG compilation flags when compiling HLSL code
		 *	use_user_defined_labels_in_backend: Forward object labels to the backend so that they can be seen in native debugging tools like RenderDoc, PIX...
		 */
		const char* const enabledToggles[] = { "dump_shaders", "disable_symbol_renaming", "use_user_defined_labels_in_backend" };
		wgpu::DawnTogglesDescriptor deviceTogglesDesc;
		deviceTogglesDesc.enabledToggles = enabledToggles;
		deviceTogglesDesc.enabledToggleCount = sizeof(enabledToggles) / sizeof(char*);

		deviceDesc.nextInChain = &deviceTogglesDesc;
#endif

		s_Device = RequestDevice(s_Adapter, &deviceDesc);

		s_Device.SetUncapturedErrorCallback([](WGPUErrorType type, char const* message, void* pUserData)
		{
			ERROR("WebGPU Error: {0}", message);
		}, nullptr);
		s_Device.SetLoggingCallback([](WGPULoggingType type, char const* message, void* userdata)
		{
			ERROR("WebGPU log: {0}", message);
		}, nullptr);

		s_Queue = s_Device.GetQueue();
		s_DefaultTextureFormat = wgpu::TextureFormat::BGRA8Unorm;

		wgpu::SwapChainDescriptor swapChainDesc;
		swapChainDesc.format = s_DefaultTextureFormat;
		swapChainDesc.presentMode = wgpu::PresentMode::Fifo;
		swapChainDesc.usage = wgpu::TextureUsage::RenderAttachment;
		swapChainDesc.width = width;
		swapChainDesc.height = height;

		s_SwapChain = s_Device.CreateSwapChain(s_Surface, &swapChainDesc);
	}

}
