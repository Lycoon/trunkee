// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <vk_mem_alloc.h>
#include <vulkan/vulkan.h>
#include <shaderc/shaderc.hpp>

typedef enum{
	// Forced shader types
	VERTEX =				shaderc_vertex_shader,
	FRAGMENT =				shaderc_fragment_shader,
	COMPUTE =				shaderc_compute_shader,
	GEOMETRY =				shaderc_geometry_shader,
	TESS_CONTROL =			shaderc_tess_control_shader,
	TESS_EVAL =				shaderc_tess_evaluation_shader,

	// Deduce shader type from #pragma annotation in shader
	AUTO =					shaderc_glsl_infer_from_source,

	// Default shaders, for fallback
	DEFAULT_VERTEX =		shaderc_glsl_default_vertex_shader,
	DEFAULT_FRAGMENT =		shaderc_glsl_default_fragment_shader,
	DEFAULT_COMPUTE =		shaderc_glsl_default_compute_shader,
	DEFAULT_GEOMETRY =		shaderc_glsl_default_geometry_shader,
	DEFAULT_TESS_CONTROL =	shaderc_glsl_default_tess_control_shader,
	DEFAULT_TESS_EVAL =		shaderc_glsl_default_tess_evaluation_shader,
	SPIRV_ASSEMBLY =		shaderc_spirv_assembly,
	RAYGEN =				shaderc_raygen_shader,
	ANY_HIT =				shaderc_anyhit_shader,
	CLOSEST_HIT =			shaderc_closesthit_shader,
	MISS =					shaderc_miss_shader,
	INTERSECTION =			shaderc_intersection_shader,
	CALLABLE =				shaderc_callable_shader,
	DEFAULT_RAYGEN =		shaderc_glsl_default_raygen_shader,
	DEFAULT_ANY_HIT =		shaderc_glsl_default_anyhit_shader,
	DEFAULT_CLOSEST_HIT =	shaderc_glsl_default_closesthit_shader,
	DEFAULT_MISS =			shaderc_glsl_default_miss_shader,
	DEFAULT_INTERSECTION =	shaderc_glsl_default_intersection_shader,
	DEFAULT_CALLABLE =		shaderc_glsl_default_callable_shader,
	TASK =					shaderc_task_shader,
	MESH =					shaderc_mesh_shader,
	DEFAULT_TASK =			shaderc_glsl_default_task_shader,
	DEFAULT_MESH =			shaderc_glsl_default_mesh_shader,
} ShaderType;

struct AllocatedBuffer{
	VkBuffer _buffer;
	VmaAllocation _allocation;
};

struct AllocatedImage {
	VkImage _image;
	VmaAllocation _allocation;
};