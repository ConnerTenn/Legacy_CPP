
#version 440 core
#extension GL_ARB_gpu_shader_fp64 : enable
//#extension GL_NV_shader_buffer_load : enable

in vec3 FragPos;
//flat in dvec3 Transfm; //x, y, scale, const
//flat in dvec3 Const; //MaxCount, Constant, Power,

layout(std140, binding = 1) uniform ShaderData
{
	//					//base alignment	//aligned offset
	dvec2 Pos;			//16				//0->15
	double Scale;		//8					//16->23
	double Constant;	//8					//24->31
	int MaxCount;		//4					//32->35
	int Power;			//4					//36->39
	float AspectRatio;	//4					//40->43
};


layout(location = 0) out vec4 Color;

int maxCount = 100;

dvec2 mul(dvec2 a, dvec2 b)
{
	return dvec2( (a[0] * b[0]) - (a[1] * b[1]) , (a[0] * b[1]) + (a[1] * b[0]) );
}

float curve(float val, int shift)
{
	return pow(1.0f + (10.0f / (pow(float(maxCount),2))), -(pow(val - float((shift+1) * float(maxCount))/4.0f, 2)));
}

void main()
{
	dvec3 dFragPos = dvec3(FragPos);

	dvec2 cnst = { Constant, Constant };
	int power = Power;
	dvec2 pos = { (AspectRatio) * Scale * dFragPos[0] + Pos[0], Scale * dFragPos[1] + Pos[1] };
	dvec2 total = { 0, 0 };
	//dvec2 total = pos;
	//maxCount = int(float(maxCount) + -0.75 *(log2(float(Transfm[2]))-1.0));//maxCount + 2 * int(-(log2(float(Transfm[2]))-1.0));
	//maxCount = maxCount + int(pow(-log2(float(Transfm[2]))-1.0,2.0));
	maxCount = MaxCount;


	Color = vec4(0, 0, 0, 1);

	int count = 0;
	int i;
	while (pow(float(total[0]),2) + pow(float(total[1]),2) < 4.0 && count++ < maxCount)
	{
		for (i = 0; i < power; i = i + 1)
		{
			total = mul(total, total);
		}

		//total2 = total2 * total2 + pos2;
		total = total + pos;

		//total = mul(total, total) + cnst;
		//total = total + cnst;

		//count += 1;
	}

	//Color[1] = count / float(MaxCount);
	if (count < maxCount)
	{
		Color[0] = curve(count, 0);
		Color[1] = curve(count, 1);
		Color[2] = curve(count, 2);
	}
	//Color = vec4(sin(count), cos(count), 0, 1);
	//color = vec4(pos[0]/2.0+0.5, pos[1] / 2.0 + 0.5, 0, 1);
	//Color = vec4(1, 1, 1, 1);
}
