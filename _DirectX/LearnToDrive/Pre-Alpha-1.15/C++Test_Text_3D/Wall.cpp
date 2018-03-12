

#include<d3d11.h>
#include<d3dx11.h>
#include"Wall.h"
#include<math.h>

/*Wall::Wall(XMFLOAT3 Pos = { 0.0f, 0.0f, 0.0f }, XMFLOAT2 StartPos = { 0, 0 }, XMFLOAT2 EndPos = { 0, 0 }, 
	string ColorMapTL = "", string ColorMapTM = "", string ColorMapTR = "",
	string ColorMapML = "", string ColorMapMM = "", string ColorMapMR = "",
	string ColorMapBL = "", string ColorMapBM = "", string ColorMapBR = "")
	:RigidBody(Pos, StartPos, EndPos, { "Tex\\MissingTexture.png" })
{
	ColorMapFileW_[0] = ColorMapTL;
	ColorMapFileW_[1] = ColorMapTM;
	ColorMapFileW_[2] = ColorMapTR;

	ColorMapFileW_[3] = ColorMapML;
	ColorMapFileW_[4] = ColorMapMM;
	ColorMapFileW_[5] = ColorMapMR;

	ColorMapFileW_[6] = ColorMapBL;
	ColorMapFileW_[7] = ColorMapBM;
	ColorMapFileW_[8] = ColorMapBR;
}*/

Wall::Wall(XMFLOAT3 Pos = { 0.0f, 0.0f, 0.0f }, XMFLOAT2 StartPos = { 0, 0 }, 
	XMFLOAT2 EndPos = { 0, 0 }, vector<string> ColorMap = { "MissingTexture.png" },
	int NumBuffers = 1, int NumColorMap = 1)
:RigidBody(Pos, StartPos, EndPos, ColorMap, NumBuffers, NumColorMap)
{

}
/*
ID3D11Buffer* Wall::GetBuffer(int i)
{
	return VertexBufferW_[i];
}

string Wall::GetColorMapFile(int i)
{
	return ColorMapFileW_[i];
}

ID3D11ShaderResourceView* Wall::GetColorMap(int i)
{
	return ColorMapW_[i];
}


void Wall::SetBuffer(ID3D11Buffer &VertexBuffer, int i)
{
	VertexBufferW_[i] = &VertexBuffer;
}

void Wall::SetColorMap(ID3D11ShaderResourceView &ColorMap, int i)
{
	ColorMapW_[i] = &ColorMap;
}*/