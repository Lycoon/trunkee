// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "vk_types.h"
#include "vk_mesh.h"

#include <vector>
#include <functional>
#include <deque>
#include <glm/glm.hpp>

#include "Camera.h"
#include "event/EventManager.h"

constexpr unsigned int FRAME_OVERLAP = 2;

struct GPUCameraData
{
	glm::mat4 view;
	glm::mat4 proj;
	glm::mat4 viewproj;
};

struct FrameData
{
	VkSemaphore _presentSemaphore, _renderSemaphore;
	VkFence _renderFence;

	VkCommandPool _commandPool;
	VkCommandBuffer _mainCommandBuffer;

	AllocatedBuffer cameraBuffer;
	VkDescriptorSet globalDescriptor;
};

struct Material
{
	VkPipeline pipeline;
	VkPipelineLayout pipelineLayout;
};

struct RenderObject
{
	Mesh* mesh;
	Material* material;
	glm::mat4 transformMatrix;
};

struct MeshPushConstants
{
	glm::vec4 data;
	glm::mat4 render_matrix;
};

struct DeletionQueue
{
	std::deque<std::function<void()>> deletors;

	void push_function(std::function<void()>&& function) {
		deletors.push_back(function);
	}

	void flush() {
		// reverse iterate the deletion queue to execute all the functions
		for (auto it = deletors.rbegin(); it != deletors.rend(); it++) {
			(*it)(); //call the function
		}

		deletors.clear();
	}
};

class VulkanEngine
{
	const char* SHADER_FOLDER = "shaders/";

public:
	bool _isInitialized{ false };
	int _frameNumber{ 0 };

	VkExtent2D _windowExtent{ 1700 , 900 };
	struct SDL_Window* _window{ nullptr };

	void Init();
	void Cleanup();
	void Draw();
	void Run();

	bool CompileShaderFromFile(const char* shaderPath, const char* shaderEntryPoint, ShaderType shaderType, std::vector<uint32_t>& shaderBinary);
	bool LoadFile(const char* filePath, std::string& fileContent);
	bool LoadShaderModule(const char* shaderPath, ShaderType shaderType, VkShaderModule* outShaderModule);

	Camera _camera;
	VkInstance _instance;
	VkDebugUtilsMessengerEXT _debug_messenger;
	VkPhysicalDevice _chosenGPU;
	VkDevice _device;
	VkSurfaceKHR _surface;
	FrameData _frames[FRAME_OVERLAP];

	VkSwapchainKHR _swapchain;
	VkFormat _swapchainImageFormat;
	std::vector<VkImage> _swapchainImages;
	std::vector<VkImageView> _swapchainImageViews;

	VkQueue _graphicsQueue; //queue we will submit to
	uint32_t _graphicsQueueFamily; //family of that queue

	VkRenderPass _renderPass;
	std::vector<VkFramebuffer> _framebuffers;

	VkPipelineLayout _meshPipelineLayout;
	VkPipeline _meshPipeline;

	DeletionQueue _mainDeletionQueue;
	VmaAllocator _allocator;

	VkImageView _depthImageView;
	AllocatedImage _depthImage;
	VkFormat _depthFormat;

	VkDescriptorSetLayout _globalSetLayout;
	VkDescriptorPool _descriptorPool;

	std::vector<RenderObject> _renderables;
	std::unordered_map<std::string, Material> _materials;
	std::unordered_map<std::string, Mesh> _meshes;

	Material* CreateMaterial(VkPipeline pipeline, VkPipelineLayout layout, const std::string& name); //create material and add it to the map
	Material* GetMaterial(const std::string& name); //returns nullptr if it can't be found
	Mesh* GetMesh(const std::string& name); //returns nullptr if it can't be found
	void DrawObjects(VkCommandBuffer cmd, RenderObject* first, int count);
	AllocatedBuffer CreateBuffer(size_t allocSize, VkBufferUsageFlags usage, VmaMemoryUsage memoryUsage);
	FrameData& GetCurrentFrame();

private:
	void InitVulkan();
	void InitSwapchain();
	void InitCommands();
	void InitDefaultRenderpass();
	void InitFramebuffers();
	void InitSyncStructures();
	void InitPipelines();
	void InitScene();
	void InitDescriptors();

	void LoadMeshes();
	void UploadMesh(Mesh& mesh);
};

class PipelineBuilder 
{
public:
	std::vector<VkPipelineShaderStageCreateInfo> _shaderStages;
	VkPipelineVertexInputStateCreateInfo _vertexInputInfo;
	VkPipelineInputAssemblyStateCreateInfo _inputAssembly;
	VkViewport _viewport;
	VkRect2D _scissor;
	VkPipelineRasterizationStateCreateInfo _rasterizer;
	VkPipelineColorBlendAttachmentState _colorBlendAttachment;
	VkPipelineMultisampleStateCreateInfo _multisampling;
	VkPipelineLayout _pipelineLayout;
	VkPipelineDepthStencilStateCreateInfo _depthStencil;

	VkPipeline BuildPipeline(VkDevice device, VkRenderPass pass);
};