
#version 440 core
#extension GL_ARB_gpu_shader_fp64 : enable
//#extension GL_NV_shader_buffer_load : enable

layout(location = 0) in dvec3 Position;
layout(location = 1) in dvec4 Transform;

out vec3 Pos;
flat out dvec4 Transfm;


void main()
{
	gl_Position = vec4(Position, 1.0f);
	
	/*vec2 total; total[0] = 
		0; total[1] = 0;

	int count = 0;
	while (total[0] < 2.0 && count < 100)
	{
		//total = total * total + in;
		//this->Num[0] * In.Num[0] - this->Num[1] * In.Num[1], this->Num[0] * In.Num[1] + this->Num[1] * In.Num[0]
		total[0] = total[0] * pos[0] - total[1] * pos[1];
		total[1] = total[0] * pos[1] - total[1] * pos[0];

		total[0] = total[0] + pos[0];
		total[1] = total[1] + pos[1];

		count+=1;
	}

	if (count == 100)
	{
		ourColor = vec4(0, 0, 0, 1);
	}
	else
	{
		ourColor = vec4(1, 1, 1, 1);
	}*/
	
	Pos = vec3(Position);
	Transfm = Transform;
}
