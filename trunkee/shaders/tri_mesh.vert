#version 460

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 vColor;

layout (location = 0) out vec3 outColor;

layout(set = 0, binding = 0) uniform CameraBuffer{
	mat4 view;
	mat4 proj;
	mat4 viewproj;
} cameraData;

layout( push_constant ) uniform Constants {
 vec4 data;
 mat4 mvp;
} constants;

void main()
{
	gl_Position = constants.mvp * vec4(vPosition, 1.0f);
	outColor = vColor;
}
