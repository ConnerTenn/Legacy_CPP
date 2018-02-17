
#include "Globals.h"
#include "VulkanFunctions.h"

void RecreateSwapChain();

void OnWindowResized(GLFWwindow* window, int width, int height)
{
	if (width == 0 || height == 0) { return; }

	RecreateSwapChain();
}

void InitWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	Window = glfwCreateWindow(Width, Height, "Vulkan Window", nullptr, nullptr);

	glfwSetWindowSizeCallback(Window, OnWindowResized);
}



void InitVulkan()
{
	CreateInstance();
	CreateSurface();
	PickPhysicalDevice();
	CreateLogicalDevice();
	CreateSwapChain();
	CreateImageViews();
	CreateRenderPass();
	CreateDescriptorSetLayout();
	CreateGraphicsPipeline();
	CreateCommandPool();
	CreateDepthResources();
	CreateFramebuffers();
	CreateTextureImage();
	CreateTextureImageView();
	CreateTextureSampler();
	CreateVertexBuffer();
	CreateIndexBuffer();
	CreateUniformBuffer();
	CreateDescriptorPool();
	CreateDescriptorSet();
	CreateCommandBuffers();
	CreateSemaphores();
}

void RecreateSwapChain()
{
	vkDeviceWaitIdle(Device);

	for (const VkFramebuffer &swapChainFramebuffers : SwapChainFramebuffers)
	{
		vkDestroyFramebuffer(Device, swapChainFramebuffers, nullptr);
	}

	vkDestroyImage(Device, DepthImage, nullptr);
	vkFreeMemory(Device, DepthImageMemory, nullptr);
	vkDestroyImageView(Device, DepthImageView, nullptr);

	vkDestroyPipeline(Device, GraphicsPipeline, nullptr);
	vkDestroyRenderPass(Device, RenderPass, nullptr);
	vkDestroyPipelineLayout(Device, PipelineLayout, nullptr);

	for (const VkImageView &swapChainImageViews : SwapChainImageViews)
	{
		vkDestroyImageView(Device, swapChainImageViews, nullptr);
	}

	CreateSwapChain();
	CreateImageViews();
	CreateRenderPass();
	CreateGraphicsPipeline();
	CreateDepthResources();
	CreateFramebuffers();
	CreateCommandBuffers();
}

void Shutdown()
{
	vkDestroySemaphore(Device, ImageAvailableSemaphore, nullptr);
	vkDestroySemaphore(Device, RenderFinishedSemaphore, nullptr);

	vkDestroyDescriptorPool(Device, DescriptorPool, nullptr);

	vkFreeMemory(Device, UniformBufferMemory, nullptr);
	vkDestroyBuffer(Device, UniformBuffer, nullptr);
	vkFreeMemory(Device, UniformStagingBufferMemory, nullptr);
	vkDestroyBuffer(Device, UniformStagingBuffer, nullptr);

	vkDestroySampler(Device, TextureSampler, nullptr);
	vkDestroyImageView(Device, TextureImageView, nullptr);
	vkDestroyImage(Device, TextureImage, nullptr);
	vkFreeMemory(Device, TextureImageMemory, nullptr);

	vkFreeMemory(Device, IndexBufferMemory, nullptr);
	vkDestroyBuffer(Device, IndexBuffer, nullptr);
	vkFreeMemory(Device, VertexBufferMemory, nullptr);
	vkDestroyBuffer(Device, VertexBuffer, nullptr);

	vkDestroyImage(Device, DepthImage, nullptr);
	vkFreeMemory(Device, DepthImageMemory, nullptr);
	vkDestroyImageView(Device, DepthImageView, nullptr);

	vkDestroyCommandPool(Device, CommandPool, nullptr);

	vkDestroyPipeline(Device, GraphicsPipeline, nullptr);
	vkDestroyPipelineLayout(Device, PipelineLayout, nullptr);
	vkDestroyDescriptorSetLayout(Device, DescriptorSetLayout, nullptr);
	vkDestroyRenderPass(Device, RenderPass, nullptr);

	for (const VkFramebuffer &swapChainFramebuffers : SwapChainFramebuffers)
	{
		vkDestroyFramebuffer(Device, swapChainFramebuffers, nullptr);
	}
	for (const VkImageView &swapChainImageViews : SwapChainImageViews)
	{
		vkDestroyImageView(Device, swapChainImageViews, nullptr);
	}

	vkDestroySwapchainKHR(Device, SwapChain, nullptr);

	vkDestroyDevice(Device, nullptr);

	vkDestroySurfaceKHR(Instance, Surface, nullptr);
	vkDestroyInstance(Instance, nullptr);

	glfwDestroyWindow(Window);

	glfwTerminate();
}

void UpdateUniformBuffer()
{
	static auto startTime = std::chrono::high_resolution_clock::now();

	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = (float)fmod(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() / 1000.0, 10.0);

	UniformBufferObject ubo = {};
	//ubo.Model = glm::rotate(glm::mat4(), time * (float)(0.25 * TAU), glm::vec3(0.0f, 1.0f, 0.0f));
	//ubo.Model = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, fmodf(30.0f * time, 32.0f) - 30.0f));
	
	//ubo.View = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//ubo.View = glm::lookAt(glm::vec3(-2.0 * cos(time * 0.5 * TAU), 2.0 * sin(time * 0.5 * TAU), 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//ubo.View = glm::lookAt(glm::vec3(1.0f, 1.0f, 0.8f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//ubo.View = glm::translate(ubo.View, glm::vec3(0.0f, 0.0f, -20.0f));

	//ubo.Proj = glm::perspective((float)(0.25 * TAU), SwapChainExtent.width / (float)SwapChainExtent.height, 0.001f, 1000.0f);
	//ubo.Proj[0][0] *= -1;
	//ubo.Proj[1][1] *= -1;
	//ubo.Proj[2][2] *= -1;
	//ubo.Proj[3][2] *= -1;

	//glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
	//glm::vec3 cameraPos(0.0f, 0.0f, -1.0f);
	//glm::vec3 cameraLookAt(0.0f, 0.0f, 1.0f);
	glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraPos(sin(time * 0.5 * TAU), 0, -cos(time * 0.5 * TAU));
	glm::vec3 cameraLookAt(0.0f, 0.0f, 0.0f);


	//cameraLookAt = cameraLookAt + cameraPos;

	ubo.Model = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
	ubo.View = glm::lookAt(cameraPos, cameraLookAt, cameraUp);
	ubo.Proj = glm::perspective((float)(0.25 * TAU), SwapChainExtent.width / (float)SwapChainExtent.height, 0.001f, 1000.0f);

	void* data;
	vkMapMemory(Device, UniformStagingBufferMemory, 0, sizeof(ubo), 0, &data);
	memcpy(data, &ubo, sizeof(ubo));
	vkUnmapMemory(Device, UniformStagingBufferMemory);

	CopyBuffer(UniformStagingBuffer, UniformBuffer, sizeof(ubo));
}

void Draw()
{
	uint32_t imageIndex;
	VkResult result;

	/*Acquire an image from the swap chain*/ 
	result = vkAcquireNextImageKHR(Device, SwapChain, std::numeric_limits<uint64_t>::max(), ImageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);
	if (result == VK_ERROR_OUT_OF_DATE_KHR) { RecreateSwapChain(); return; }

	/*Execute the command buffer with that image as attachment in the framebuffer*/ 
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { ImageAvailableSemaphore };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &CommandBuffers[imageIndex];

	VkSemaphore signalSemaphores[] = { RenderFinishedSemaphore };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	vkQueueSubmit(GraphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
	

	/*Return the image to the swap chain for presentation*/
	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = { SwapChain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr; // Optional

	result = vkQueuePresentKHR(PresentQueue, &presentInfo);
	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) { RecreateSwapChain(); }
}

void Loop()
{
	while (!glfwWindowShouldClose(Window))
	{
		glfwPollEvents();

		UpdateUniformBuffer();

		Draw();
	}
	vkDeviceWaitIdle(Device);
}

void main()
{
	InitWindow();
	InitVulkan();

	Loop();

	Shutdown();
}