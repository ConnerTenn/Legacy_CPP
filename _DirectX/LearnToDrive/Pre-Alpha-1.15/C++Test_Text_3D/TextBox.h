
/*
Beginning DirectX 11 Game Programming
By Allen Sherrod and Wendy Jones

Sprite1 - Used to represent a 2D sprite's transformation.
*/


#ifndef _TEXTBOX_H_
#define _TEXTBOX_H_

#include<xnamath.h>
//#include"Level1.h"
#include <string>
#include<vector>
#include "Text.h"
//#include"GameObject.h"

using  namespace std;

class TextBox : public Text
{
protected:
	float ExpandRate_ = 0;

public:
	TextBox(XMFLOAT3 Pos, XMFLOAT2 StartPos, XMFLOAT2 EndPos, vector<string> ColorMapFile,
		int NumBuffers, int NumColorMap, string Message);

	XMMATRIX GetTextBoxMatrix();
	string Get_Message();
	float GetExpandRate();

	void UpdateMessage(string Message, HRESULT* D3DResult, ID3D11Device* D3DDevice_, D3D11_SUBRESOURCE_DATA ResourceData);
	void SetExpandRate(float Rate);

};

#endif 
//*/
