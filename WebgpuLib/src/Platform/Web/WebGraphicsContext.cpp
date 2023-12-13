#if !defined(PLATFORM_WEB)
	#error This file should only be compiled for web/emscripten build
#endif

#include "Base/Utils.h"
#include "Base/GraphicsContext.h"

#include <webgpu/webgpu_cpp.h>

#include <emscripten/emscripten.h>
#include <emscripten/html5_webgpu.h>

#include <iostream>
#include <cassert>

namespace Base {

	void GraphicsContext::Init(GLFWwindow* window, uint32_t width, uint32_t height)
	{
		wgpu::InstanceDescriptor desc = {};
		s_Instance = wgpu::CreateInstance(&desc);

		wgpu::SurfaceDescriptorFromCanvasHTMLSelector canvasDesc;
		canvasDesc.selector = "canvas";
		canvasDesc.sType = wgpu::SType::SurfaceDescriptorFromCanvasHTMLSelector;

		wgpu::SurfaceDescriptor surfaceDesc;
		surfaceDesc.nextInChain = &canvasDesc;
		s_Surface = s_Instance.CreateSurface(&surfaceDesc);

		wgpu::RequestAdapterOptions opts;
		opts.compatibleSurface = s_Surface;
		opts.backendType = wgpu::BackendType::D3D12;
		opts.powerPreference = wgpu::PowerPreference::HighPerformance;

		s_Adapter = RequestAdapter(s_Instance, &opts);

		wgpu::DeviceDescriptor deviceDesc;
		deviceDesc.label = "SVGscape_Device";
		deviceDesc.defaultQueue.label = "SVGscape_Queue";

		s_Device = RequestDevice(s_Adapter, &deviceDesc);

		s_Queue = s_Device.GetQueue();
		s_DefaultTextureFormat = s_Surface.GetPreferredFormat(s_Adapter); // TODO: Maybe use different format?

		wgpu::SwapChainDescriptor swapChainDesc;
		swapChainDesc.format = s_DefaultTextureFormat;
		swapChainDesc.presentMode = wgpu::PresentMode::Fifo;
		swapChainDesc.usage = wgpu::TextureUsage::RenderAttachment;
		swapChainDesc.width = width;
		swapChainDesc.height = height;

		s_SwapChain = s_Device.CreateSwapChain(s_Surface, &swapChainDesc);
	}

}
