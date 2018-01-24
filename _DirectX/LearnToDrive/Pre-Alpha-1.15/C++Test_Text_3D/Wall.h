
/*
Beginning DirectX 11 Game Programming
By Allen Sherrod and Wendy Jones

Sprite1 - Used to represent a 2D sprite's transformation.
*/


#ifndef _WALL_H_
#define _WALL_H_

#include<xnamath.h>
#include"RigidBody.h"


class Wall : public RigidBody
{
//protected:
	/*
	ID3D11Buffer *VertexBufferW_[9];
	ID3D11ShaderResourceView *ColorMapW_[9];
	string ColorMapFileW_[9];*/
public:
	/*Wall(XMFLOAT3 Pos, XMFLOAT2 StartPos, XMFLOAT2 EndPos, 
		string ColorMapTL, string ColorMapTM, string ColorMapTR,
		string ColorMapML, string ColorMapMM, string ColorMapMR, 
		string ColorMapBL, string ColorMapBM, string ColorMapBR );*/
	Wall(XMFLOAT3 Pos, XMFLOAT2 StartPos, XMFLOAT2 EndPos, vector<string> ColorMap,
		int NumBuffers, int NumColorMap);

	//XMMATRIX GetWorldMatrix();
	//XMFLOAT3 GetPosition();
	/*ID3D11Buffer* GetBuffer(int i);
	string GetColorMapFile(int i);
	ID3D11ShaderResourceView* GetColorMap(int i);

	void SetBuffer(ID3D11Buffer &VertexBuffer, int i);
	void SetColorMap(ID3D11ShaderResourceView &ColorMap, int i);*/
};

#endif