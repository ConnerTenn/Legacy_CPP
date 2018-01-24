
/*
Beginning DirectX 11 Game Programming
By Allen Sherrod and Wendy Jones

Sprite1 - Used to represent a 2D sprite's transformation.
*/


#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include<xnamath.h>
//#include"Level1.h"
#include <string>
#include<vector>
#include"Globals.h"


using  namespace std;


class GameObject
{
protected:
//public:
	XMFLOAT3 position_;
	float rotation_;
	XMFLOAT2 scale_;
	XMFLOAT2 StartPos_;
	XMFLOAT2 EndPos_;
	//ID3D11Buffer *VertexBuffer_;
	vector<ID3D11Buffer*> VertexBuffer_;
	//ID3D11ShaderResourceView *ColorMap_;
	vector<ID3D11ShaderResourceView*> ColorMap_;
	//string ColorMapFile_;
	vector<string> ColorMapFile_;
	unsigned int NumBuffers_;
	unsigned int NumColorMap_;
	//ID3D11Buffer* Indices_;

public:
	GameObject(XMFLOAT3 Pos, XMFLOAT2 StartPos, XMFLOAT2 EndPos, vector<string> ColorMapFile, 
		int NumBuffers, int NumColorMap);

	XMMATRIX GetWorldMatrix();
	XMFLOAT3 GetPosition();
	ID3D11Buffer* GetBuffer(int i);
	XMFLOAT2 GetStartPos();
	XMFLOAT2 GetEndPos();
	XMFLOAT2 Get_TL_Pos();
	XMFLOAT2 Get_BR_Pos();
	string GetColorMapFile(int i);
	ID3D11ShaderResourceView* GetColorMap(int i);
	//ID3D11Buffer* GetIndices();
	unsigned int GetBufferNum();
	unsigned int GetColormapNum();
	XMFLOAT2 GetScale();
	bool Collide(XMFLOAT2 Self_TL_Pos_, XMFLOAT2 Self_BR_Pos_,
		XMFLOAT2 Object_TL_Pos_, XMFLOAT2 Object_BR_Pos_);
	bool CollideOnRight(XMFLOAT2 SelfStartPos, XMFLOAT2 SelfEndPos,
		XMFLOAT2 ObjectStartPos, XMFLOAT2 ObjectEndPos);
	bool CollideOnLeft(XMFLOAT2 SelfStartPos, XMFLOAT2 SelfEndPos,
		XMFLOAT2 ObjectStartPos, XMFLOAT2 ObjectEndPos);
	bool CollideOnBottom(XMFLOAT2 SelfStartPos, XMFLOAT2 SelfEndPos,
		XMFLOAT2 ObjectStartPos, XMFLOAT2 ObjectEndPos);
	bool CollideOnTop(XMFLOAT2 SelfStartPos, XMFLOAT2 SelfEndPos,
		XMFLOAT2 ObjectStartPos, XMFLOAT2 ObjectEndPos);

	void SetPosition(XMFLOAT3& position);
	void SetRotation(float rotation);
	void SetScale(XMFLOAT2& scale);
	void SetBuffer(ID3D11Buffer& VertexBuffer, int i);
	void SetColorMap(ID3D11ShaderResourceView& ColorMap, int i);
	void SetScale(XMFLOAT2 Scale);

	void Shutdown();
	//void SetIndices(ID3D11Buffer& Indices);
};

#endif