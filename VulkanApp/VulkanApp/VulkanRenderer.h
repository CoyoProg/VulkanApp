#pragma once
#include <vulkan/vulkan.hpp> 
#include <GLFW/glfw3.h>
#include <stdexcept>

#include <vector>
using std::vector;
#include <set>
using std::set;

#include "VulkanUtilities.h"

class VulkanRenderer
{
public:
#ifdef NDEBUG
	static const bool enableValidationLayers = false;
#else
	static const bool enableValidationLayers = true;
#endif
	static const vector<const char*> validationLayers;

	VulkanRenderer();
	~VulkanRenderer();

	int init(GLFWwindow* windowP);
	void clean();

private:
	GLFWwindow* window;
	vk::Instance instance;
	vk::Queue graphicsQueue;

	struct 
	{
		vk::PhysicalDevice physicalDevice;
		vk::Device logicalDevice;
	} mainDevice;

	vk::SurfaceKHR surface;
	vk::Queue presentationQueue;
	vk::SwapchainKHR swapchain;
	vk::Format swapchainImageFormat;
	vk::Extent2D swapchainExtent;
	vector<SwapchainImage> swapchainImages;
	vk::ImageView createImageView(
		vk::Image image, vk::Format format, vk::ImageAspectFlagBits aspectFlags);

	//Debug
	VkDebugUtilsMessengerEXT debugMessenger;
	void setupDebugMessenger();
	VkResult createDebugUtilsMessengerEXT(
		VkInstance instance,
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkDebugUtilsMessengerEXT* pDebugMessenger);
	void destroyDebugUtilsMessengerEXT(VkInstance instance,
		VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
	void populateDebugMessengerCreateInfo(
		VkDebugUtilsMessengerCreateInfoEXT& createInfo);


	//Devices
	void getPhysicalDevice();
	bool checkDeviceSuitable(vk::PhysicalDevice device);
	QueueFamilyIndices getQueueFamilies(vk::PhysicalDevice device);
	void createLogicalDevice();

	//Surface & Swapchain
	vk::SurfaceKHR createSurface();
	void createSwapchain();
	bool checkDeviceExtensionSupport(vk::PhysicalDevice device);
	SwapchainDetails getSwapchainDetails(vk::PhysicalDevice device);
	vk::SurfaceFormatKHR chooseBestSurfaceFormat(
		const vector<vk::SurfaceFormatKHR>& formats);
	vk::PresentModeKHR chooseBestPresentationMode(
		const vector<vk::PresentModeKHR>& presentationModes);
	vk::Extent2D chooseSwapExtent(
		const vk::SurfaceCapabilitiesKHR& surfaceCapabilities);

	//Instance
	void createInstance();
	bool checkInstanceExtensionSupport(const vector<const char*>& checkExtensions);
	bool checkValidationLayerSupport();
	vector<const char*> getRequiredExtensions();
};