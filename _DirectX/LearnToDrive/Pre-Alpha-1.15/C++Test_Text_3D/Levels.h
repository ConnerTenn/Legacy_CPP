/*
Beginning DirectX 11 Game Programming
By Allen Sherrod and Wendy Jones

Level1 - Demonstrates rendering a 3D object (cube).
*/


#ifndef _LEVELS_H_
#define _LEVELS_H_

#include"Dx11DemoBase.h"
#include<xnamath.h>
#include <iostream>
#include <sstream>

#include <list>
#include <vector>
#include <string>
#include <algorithm>

#include"Player.h"
#include"Scenery.h"
#include"Wall.h"
#include"Camera.h"
#include"Globals.h"
#include"Text.h"
#include"TextBox.h"
#include"GameObject.h"//----


using  namespace std;

class Levels : public Dx11DemoBase
{
public:

	Levels();
	//virtual ~Level1();
	void LoadLevelsContent();
	void UnloadLevelsContent();

	XMFLOAT2 Level1Start = { -2880, 1620 };
	XMFLOAT2 Level1End = { 2880, -1620 };
	void LoadLevel1Content(MSG msg, double Delta, clock_t t1);
	void Level1Loop(MSG msg, double Delta, clock_t t1);
	void UpdateLevel1(double dt);
	void RenderLevel1();
	void UnloadLevel1Content();

	XMFLOAT2 Level2Start = { -2880, 1620 };
	XMFLOAT2 Level2End = { 2880, -1620 };
	void LoadLevel2Content(MSG msg, double Delta, clock_t t1);
	void Level2Loop(MSG msg, double Delta, clock_t t1);
	void UpdateLevel2(double dt);
	void RenderLevel2();
	void UnloadLevel2Content();
	//float a = 0;


	//bool Right = false;
	//bool AntiRight = true;
	bool OnGround = false;

	ID3D11VertexShader* solidColorVS_;
	ID3D11PixelShader* solidColorPS_;

	ID3D11InputLayout* inputLayout_;
	ID3D11Buffer* indexBuffer_;
	ID3D11Buffer* indexBufferText_;

	HRESULT d3dResult;
	D3D11_SUBRESOURCE_DATA resourceData;

	//ID3D11ShaderResourceView* ColorMap1; ID3D11ShaderResourceView* ColorMap2_;//------------------------------------------------------
	//ID3D11ShaderResourceView* ColorMap1;
	//ID3D11ShaderResourceView* ColorMap2;//------------------------------------------------------
	ID3D11SamplerState* colorMapSampler_;
	ID3D11BlendState* alphaBlendState_;

	vector<Player> PlayerList;
	vector<Scenery> SceneryList;
	vector<Wall> WallList;
	vector<Text> TextList;
	vector<TextBox> TextBoxList;

	ID3D11Buffer* mvpCB_;
	XMMATRIX vpMatrix_;

	ID3D11Buffer* viewCB_;
	ID3D11Buffer* projCB_;
	ID3D11Buffer* worldCB_;
	//ID3D11Buffer* AlphaCB_;
	//XMMATRIX viewMatrix_;
	XMMATRIX projMatrix_;

	Camera camera_;


	void DrawString(string Message, float startX, float startY);
};

#endif