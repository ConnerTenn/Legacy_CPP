

#include<d3d11.h>
#include<d3dx11.h>
#include"RigidBody.h"
#include<math.h>

RigidBody::RigidBody(XMFLOAT3 Pos = { 0.0f, 0.0f, 0.0f }, XMFLOAT2 StartPos = { 0, 0 }, 
	XMFLOAT2 EndPos = { 0, 0 }, vector<string> ColorMap = { "Tex\\MissingTexture.png" },
	int NumBuffers = 1, int NumColorMap = 1)
:GameObject(Pos, StartPos, EndPos, ColorMap, NumBuffers, NumColorMap)
{

}