
#version 440 core
#extension GL_ARB_gpu_shader_fp64 : enable
//#extension GL_NV_shader_buffer_load : enable


layout(location = 0) out vec4 Color;

void main()
{
	Color = vec4(1, 1, 1, 1);
}
