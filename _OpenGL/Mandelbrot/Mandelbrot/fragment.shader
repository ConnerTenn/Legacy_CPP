
#version 330 core
in vec3 Pos;
in vec4 Transfm;

out vec4 Color;

vec2 mul(vec2 a, vec2 b)
{
	vec2 reg;
	reg[0] = (a[0] * b[0]) - (a[1] * b[1]);
	reg[1] = (a[0] * b[1]) + (a[1] * b[0]);
	return reg;
}

void main()
{
	vec2 cnst = vec2(Transfm[3], Transfm[3]);
	vec2 pos = vec2(Transfm[2] * Pos[0] + Transfm[0], Transfm[2] * Pos[1] + Transfm[1]);
	vec2 total;
	//total = pos;
	total[0] = 0; total[1] = 0;
	Color = vec4(0, 0, 0, 1);

	int count = 0;
	while (total[0] < 2.0 && count < 200)
	{
		//total = total * total + in;
		//this->Num[0] * In.Num[0] - this->Num[1] * In.Num[1]
		//this->Num[0] * In.Num[1] + this->Num[1] * In.Num[0]
		//vec2 reg;
		//reg[0] = (total[0] * total[0]) - (total[1] * total[1]);
		//reg[1] = (total[0] * total[1]) + (total[1] * total[0]);
		//total = reg;
		//total = mul(total, total);

		//total[0] = total[0] + pos[0];
		//total[1] = total[1] + pos[1];
		//total = total + pos;

		total = mul(total, total);
		total = total + pos;

		//total = mul(total, total);
		//total = total + cnst;

		count += 1;
	}

	/*if (count == 100)
	{
		Color = vec4(0, 0, 0, 1);
	}
	else
	{
		Color = vec4(1, 1, 1, 1);
	}*/
	Color[1] = count / 100.0;
	//Color = vec4(sin(count), cos(count), 0, 1);
	//color = vec4(pos[0]/2.0+0.5, pos[1] / 2.0 + 0.5, 0, 1);
}
