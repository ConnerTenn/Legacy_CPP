
#version 440 core
#extension GL_ARB_gpu_shader_fp64 : enable
//#extension GL_NV_shader_buffer_load : enable

in vec3 FragPos;
in vec3 FragColour;
//flat in dvec3 Transfm; //x, y, scale, const
//flat in dvec3 Const; //MaxCount, Constant, Power,

/*layout(std140, binding = 1) uniform ShaderData
{
	//					//base alignment	//aligned offset
	dvec2 Pos;			//16				//0->15
	double Scale;		//8					//16->23
	double Constant;	//8					//24->31
	int MaxCount;		//4					//32->35
	int Power;			//4					//36->39
	float AspectRatio;	//4					//40->43
};*/


layout(location = 0) out vec4 Color;


void main()
{
	
	Color = vec4(FragColour, 1.0);
}
