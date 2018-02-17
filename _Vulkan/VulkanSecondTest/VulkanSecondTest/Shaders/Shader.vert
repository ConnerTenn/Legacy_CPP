
#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject 
{
    mat4 Model;
    mat4 View;
    mat4 Proj;
} UBO;

layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec3 InColor;
layout(location = 2) in vec2 InTexCoord;

layout(location = 0) out vec3 FragColor;
layout(location = 1) out vec2 FragTexCoord;


out gl_PerVertex 
{
    vec4 gl_Position;
};


void main() 
{
	mat4 model = UBO.Model;
    mat4 view = UBO.View;
    mat4 proj = UBO.Proj;

	proj[0][0] *= -1;

	gl_Position = proj * view * model * vec4(InPosition, 1.0);

	//gl_Position = vec4(InPosition, 1.0) * UBO.Model;
	//gl_Position = gl_Position * UBO.View;
	//gl_Position = gl_Position * UBO.Proj;

	gl_Position.y *= -1;

	FragColor = InColor;
	FragTexCoord = InTexCoord;
}
