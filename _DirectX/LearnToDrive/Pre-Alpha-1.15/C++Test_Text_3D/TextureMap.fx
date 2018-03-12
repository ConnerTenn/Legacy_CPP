/*
    Beginning DirectX 11 Game Programming
    By Allen Sherrod and Wendy Jones

    Texture Mapping Shader for 3D Objects
*/


Texture2D ColorMap1 : register( t0 );
SamplerState colorSampler_ : register( s0 );


cbuffer cbChangesEveryFrame : register( b0 )
{
    matrix worldMatrix;
};

cbuffer cbNeverChanges : register( b1 )
{
    matrix viewMatrix;
};

cbuffer cbChangeOnResize : register( b2 )
{
    matrix projMatrix;
};

cbuffer AlphaVar : register( b3 )
{
	float2 Alpha;
};

struct VS_Input
{
    float4 pos  : POSITION;
    float2 tex0 : TEXCOORD0;
	//float Alpha : ALPHA;
};

struct PS_Input
{
    float4 pos  : SV_POSITION;
    float2 tex0 : TEXCOORD0;
	//float Alpha : ALPHA;
};

PS_Input VS_Main( VS_Input vertex )
{
    PS_Input vsOut = ( PS_Input )0;
    vsOut.pos = mul( vertex.pos, worldMatrix );
    vsOut.pos = mul( vsOut.pos, viewMatrix );
    vsOut.pos = mul( vsOut.pos, projMatrix );
    vsOut.tex0 = vertex.tex0;
	//vsOut.Alpha = Alpha;
	//Alpha.a = Aplha.a + 1;

    return vsOut;
}


float4 PS_Main( PS_Input frag ) : SV_TARGET
{
    float4 colour;
    colour = ColorMap1.Sample( colorSampler_, frag.tex0 );
    //colour.a = frag.Alpha;
    //colour = (1.0f, 1.0f, 1.0f, 0.0f);
    //colour = (colour[0], colour[1], colour[2]);
	//colour.a = Alpha[0];
    return colour;
}




