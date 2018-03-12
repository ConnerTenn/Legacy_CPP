
/*
struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VOut VShader(float4 position : POSITION, float4 color : COLOR)
{
	VOut output;

	output.position = position;
	output.color = color;

	return output;
}


float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
	float4 val1 = { 0, sin(position[1] / 1.5) / 2.0, 0, 0 };
	float4 val2 = { 0, 0, sin(position[0] / 1.5) / 2.0, 0 };
	return val1 + val2 + color;
}
*/


cbuffer MatrixBuffer : register(b0)
{
	matrix WorldMatrix;
	matrix ViewMatrix;
	matrix ProjectionMatrix;
};

cbuffer ShaderValues : register(b1)
{
	float4 Value;
};

struct VertexInputType
{
	float4 Position : POSITION;
	float4 Color : COLOR;
};

struct PixelInputType
{
	float4 Position : SV_POSITION;
	float4 Color : COLOR;
};


PixelInputType VShader(VertexInputType input)
{
	PixelInputType output;

	input.Position.w = 1.0f;
	output.Position = mul(input.Position, WorldMatrix);
	output.Position = mul(output.Position, ViewMatrix);
	output.Position = mul(output.Position, ProjectionMatrix);

	output.Color = input.Color;

	output.Color[0] += cos(Value[0]) / 2.0f;
	output.Color[1] += cos(Value[1] + 0.1f) / 2.0f;
	output.Color[2] += cos(Value[2] + 1.1f) / 2.0f;

	return output;
}

float4 PShader(PixelInputType input) : SV_TARGET
{
	float4 output = input.Color;

	return output;
}
