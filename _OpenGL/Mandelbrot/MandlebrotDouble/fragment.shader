
#version 440 core
#extension GL_ARB_gpu_shader_fp64 : enable
//#extension GL_NV_shader_buffer_load : enable

in vec3 Pos;
flat in dvec4 Transfm; //x, y, scale, const

out vec4 Color;

int maxCount = 100; //ove calclation to cpu

dvec2 mul(dvec2 a, dvec2 b)
{
	//dvec2 reg;
	//reg[0] = (a[0] * b[0]) - (a[1] * b[1]);
	//reg[1] = (a[0] * b[1]) + (a[1] * b[0]);
	//return reg;
	return dvec2( (a[0] * b[0]) - (a[1] * b[1]) , (a[0] * b[1]) + (a[1] * b[0]) );
}

float curve(float val, int shift)
{
	return pow(1.0 + (10.0 / (pow(float(maxCount),2))), -(pow(val - float((shift+1) * float(maxCount))/4.0, 2)));
}

void main()
{
	dvec3 dPos = dvec3(Pos);

	dvec2 cnst = { Transfm[3], Transfm[3] };
	dvec2 pos = { Transfm[2] * dPos[0] + Transfm[0], Transfm[2] * dPos[1] + Transfm[1] };
	dvec2 total = { 0, 0 };
	//maxCount = int(float(maxCount) + -0.75 *(log2(float(Transfm[2]))-1.0));//maxCount + 2 * int(-(log2(float(Transfm[2]))-1.0));
	maxCount = maxCount + int(pow(-log2(float(Transfm[2]))-1.0,2.0));
	
	//dmat2 total2 = { {0,0},{0,0} };//; total2[0] = dvec2(0.0, 0.0); total2[1] = dvec2(0.0, 0.0);
	//dmat2 pos2 = { {Transfm[2] * dPos[0] + Transfm[0], Transfm[2] * dPos[1] + Transfm[1]}, {-(Transfm[2] * dPos[1] + Transfm[1]),Transfm[2] * dPos[0] + Transfm[0]} };
	//total = pos;
	//total[0] = 0; total[1] = 0;
	Color = vec4(0, 0, 0, 1);

	int count = 0;
	while (total[0] < 2.0 && count++ < maxCount)
	{
		total = mul(total, total) + pos;
		//total2 = total2 * total2 + pos2;
		//total = total + pos;

		//total = mul(total, total) + cnst;
		//total = total + cnst;

		//count += 1;
	}

	/*if (count == 100)
	{
		Color = vec4(0, 0, 0, 1);
	}
	else
	{
		Color = vec4(1, 1, 1, 1);
	}*/
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
