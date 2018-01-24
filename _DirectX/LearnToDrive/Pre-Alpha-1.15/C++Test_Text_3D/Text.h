
/*
Beginning DirectX 11 Game Programming
By Allen Sherrod and Wendy Jones

Sprite1 - Used to represent a 2D sprite's transformation.
*/


#ifndef _TEXT_H_
#define _TEXT_H_

#include<xnamath.h>
//#include"Level1.h"
#include <string>
#include<vector>
#include"Globals.h"
#include"GameObject.h"

using  namespace std;

class Text : public GameObject
{
protected:
	string Message_;

public:
	Text(XMFLOAT3 Pos, XMFLOAT2 StartPos, XMFLOAT2 EndPos, vector<string> ColorMapFile,
		int NumBuffers, int NumColorMap, string Message);
	
	string Get_Message();

	void UpdateMessage(string Message, HRESULT* D3DResult, ID3D11Device* D3DDevice_, D3D11_SUBRESOURCE_DATA ResourceData);

};

#endif