/*
Beginning DirectX 11 Game Programming
By Allen Sherrod and Wendy Jones

Levels - Demonstrates rendering a 3D object (cube).
*/

#include"Levels.h"


void Levels::LoadLevel1Content(MSG msg, double Delta, clock_t t1)
{
	{}

	{/*Scenery*/}//2880, 1620
	{
		Scenery Sprite_1({ 0.0f, 0.0f, 0.0f }, Level1Start, Level1End,
		{ "Tex\\Background_Test_LT.png" }, 1, 1);
		SceneryList.push_back(Sprite_1);

		Scenery Sprite_2({ -90.0f, 0.0f, 0.0f }, { -30, 50}, { 30, -10 },
		{ "Tex\\Yellow.png" }, 1, 1);
		SceneryList.push_back(Sprite_2);
	}

	{/*Players*/}
	{
		Player Sprite_1({ 0.0f, 2.0f, 0.0f }, { -26, 14 }, { 26, -14 }, 
		{ "Tex\\Player\\SnailR.png", "Tex\\Player\\SnailL.png" }, 1, 2);
		PlayerList.push_back (Sprite_1);
	}

	{/*Walls*/}
	{
		Wall Sprite_1({ 0.0f, -26.0f, 0.0f }, { -100, 14 }, { 100, -14 },
		{ "Tex\\T_L_Test.png", "Tex\\T_M_Test.png", "Tex\\T_R_Test.png",
		"Tex\\M_L_Test.png", "Tex\\M_M_Test.png", "Tex\\M_R_Test.png",
		"Tex\\B_L_Test.png", "Tex\\B_M_Test.png", "Tex\\B_R_Test.png" }, 9, 9);
		WallList.push_back(Sprite_1);

		Wall Sprite_2({ 100.0f, -80.0f - 26.0f, 0.0f }, { -100, 16 }, { 100, -16 },
		{ "Tex\\T_L_Test.png", "Tex\\T_M_Test.png", "Tex\\T_R_Test.png",
		"Tex\\M_L_Test.png", "Tex\\M_M_Test.png", "Tex\\M_R_Test.png",
		"Tex\\B_L_Test.png", "Tex\\B_M_Test.png", "Tex\\B_R_Test.png" }, 9, 9);
		WallList.push_back(Sprite_2);

		Wall Sprite_3({ 0.0f, -Height / 2.0f, 0.0f }, { -Width / 2.0f, 20 }, { Width / 2.0f, -14 },
		{ "Tex\\T_L_Test.png", "Tex\\T_M_Test.png", "Tex\\T_R_Test.png",
		"Tex\\M_L_Test.png", "Tex\\M_M_Test.png", "Tex\\M_R_Test.png",
		"Tex\\B_L_Test.png", "Tex\\B_M_Test.png", "Tex\\B_R_Test.png" }, 9, 9);
		WallList.push_back(Sprite_3);

		Wall Sprite_4({ Width / 2.0f, -Height / 2.0f, 0.0f }, { -50, 100 }, { 10, -10 },
		{ "Tex\\T_L_Test.png", "Tex\\T_M_Test.png", "Tex\\T_R_Test.png",
		"Tex\\M_L_Test.png", "Tex\\M_M_Test.png", "Tex\\M_R_Test.png",
		"Tex\\B_L_Test.png", "Tex\\B_M_Test.png", "Tex\\B_R_Test.png" }, 9, 9);
		WallList.push_back(Sprite_4);

		Wall Sprite_5({ -Width / 2.0f, -Height / 2.0f, 0.0f }, { -10, 100 }, { 50, -10 },
		{ "Tex\\T_L_Test.png", "Tex\\T_M_Test.png", "Tex\\T_R_Test.png",
		"Tex\\M_L_Test.png", "Tex\\M_M_Test.png", "Tex\\M_R_Test.png",
		"Tex\\B_L_Test.png", "Tex\\B_M_Test.png", "Tex\\B_R_Test.png" }, 9, 9);
		WallList.push_back(Sprite_5);

		Wall Sprite_6({ 0.0f, Level1End.y + 20, 0.0f }, { -Width / 2.0f, 20 }, { Width / 2.0f, -14 },
		{ "Tex\\T_L_Test.png", "Tex\\T_M_Test.png", "Tex\\T_R_Test.png",
		"Tex\\M_L_Test.png", "Tex\\M_M_Test.png", "Tex\\M_R_Test.png",
		"Tex\\B_L_Test.png", "Tex\\B_M_Test.png", "Tex\\B_R_Test.png" }, 9, 9);
		WallList.push_back(Sprite_6);
	}

	{/*Text*/}//2880, 1620
	{
		Text Sprite_1({ -420.0f, -180.0f, 0.0f }, { -120, 50 }, { -60, -10 },
		{ "Tex\\Font.png" }, 1, 1, "This Update will Focus On Increacing<01>Preformance!");
		TextList.push_back(Sprite_1);
	}

	{/*TextBox*/}
	{//                              168
		TextBox Sprite_1({ -628 / 2 + 8, 168 + 168 / 2 - 30, 0.0f }, { -120, 50 }, { -60, -10 },
		{ "Tex\\TextBackground.png", "Tex\\Font2.png" }, 2, 2, 
		"#-----------#<01><02><02>| FIRST LEVEL <02><02>|<01>#-----------#");
		TextBoxList.push_back(Sprite_1);
	}

	{/*Initilize Players*/}
	{
		float Pos_Z = Player_Z;
		for (Player &sprite : PlayerList)// Set Vvertex buffer for each object
		{
			for (int i = 0; i < sprite.GetColormapNum(); i++)
			{
				float Z = 0;
				//float Z = sprite.GetPosition().z;
				sprite.SetPosition(XMFLOAT3(sprite.GetPosition().x, sprite.GetPosition().y, Pos_Z));
				float TLF[3] = { sprite.GetStartPos().x, sprite.GetStartPos().y, Z };
				float TRF[3] = { sprite.GetEndPos().x, sprite.GetStartPos().y, Z };
				float BLF[3] = { sprite.GetStartPos().x, sprite.GetEndPos().y, Z };
				float BRF[3] = { sprite.GetEndPos().x, sprite.GetEndPos().y, Z };

				VertexPos vertices[] =
				{
					{ XMFLOAT3(BLF[0], BLF[1], BLF[2]), XMFLOAT2(0.0f, 1.0f) }, //    Front
					{ XMFLOAT3(BRF[0], BRF[1], BRF[2]), XMFLOAT2(1.0f, 1.0f) },
					{ XMFLOAT3(TRF[0], TRF[1], TRF[2]), XMFLOAT2(1.0f, 0.0f) },
					{ XMFLOAT3(TLF[0], TLF[1], TLF[2]), XMFLOAT2(0.0f, 0.0f) },
				};

				D3D11_BUFFER_DESC vertexDesc;
				ZeroMemory(&vertexDesc, sizeof(vertexDesc));
				vertexDesc.Usage = D3D11_USAGE_DEFAULT;
				vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				vertexDesc.ByteWidth = sizeof(VertexPos)* 24;

				ZeroMemory(&resourceData, sizeof(resourceData));
				resourceData.pSysMem = vertices;

				ID3D11Buffer *Buffer = sprite.GetBuffer(0);//Fix
				d3dResult = d3dDevice_->CreateBuffer(&vertexDesc, &resourceData, &Buffer);

				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to create vertex buffer!");
				}

				//DBOUT("ColorMapFile:" << sprite.GetColorMapFile(i).c_str() << "\n");
				sprite.SetBuffer(*Buffer, 0);

				ID3D11ShaderResourceView *ColorMap = sprite.GetColorMap(i);//Fix
				string ColorMapFile = sprite.GetColorMapFile(i);
				d3dResult = D3DX11CreateShaderResourceViewFromFile(d3dDevice_, ColorMapFile.c_str(), 0, 0, &ColorMap, 0);
				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to load the texture image!");
				}
				sprite.SetColorMap(*ColorMap, i);

				Pos_Z--;
			}
		}
	}

	{/*Initilize Walls*/}
	{
		float Pos_Z = Wall_Z;
		for (Wall &sprite : WallList)// Set Vvertex buffer for each object
		{
			/*WORD indices[] =
			{
				//Front
				3, 1, 0,
				2, 1, 3,
				//Back
				2, 0, 1,
				3, 0, 2,
			};
			D3D11_BUFFER_DESC indexDesc;
			ZeroMemory(&indexDesc, sizeof(indexDesc));
			indexDesc.Usage = D3D11_USAGE_DEFAULT;
			indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			indexDesc.ByteWidth = sizeof(WORD)* 36;
			indexDesc.CPUAccessFlags = 0;
			resourceData.pSysMem = indices;
			ID3D11Buffer* IndexBuffer = sprite.GetIndices();
			d3dResult = d3dDevice_->CreateBuffer(&indexDesc, &resourceData, &IndexBuffer);
			if (FAILED(d3dResult))
			{
				DXTRACE_MSG("Failed to create index buffer!");
				return false;
			}
			sprite.SetIndices(*IndexBuffer);*/

			float Z = 0;
			//float Z = sprite.GetPosition().z;
			sprite.SetPosition(XMFLOAT3(sprite.GetPosition().x, sprite.GetPosition().y, Pos_Z));

			float ImageSize = 10.0f;
			float TileSize = ImageSize * Pixel_Size;
			float TL[3] = { sprite.GetStartPos().x, sprite.GetStartPos().y, Z };
			float TR[3] = { sprite.GetEndPos().x, sprite.GetStartPos().y, Z };
			float BL[3] = { sprite.GetStartPos().x, sprite.GetEndPos().y, Z };
			float BR[3] = { sprite.GetEndPos().x, sprite.GetEndPos().y, Z };

			float MTL[3] = { sprite.GetStartPos().x + TileSize, sprite.GetStartPos().y - TileSize, Z };
			float MTR[3] = { sprite.GetEndPos().x - TileSize, sprite.GetStartPos().y - TileSize, Z };
			float MBL[3] = { sprite.GetStartPos().x + TileSize, sprite.GetEndPos().y + TileSize, Z };
			float MBR[3] = { sprite.GetEndPos().x - TileSize, sprite.GetEndPos().y + TileSize, Z };

			VertexPos verticesTL[] =
			{
				{ XMFLOAT3(TL[0], MTL[1], Z), XMFLOAT2(0.0f, 1.0f) }, //    Front
				{ XMFLOAT3(MTL[0], MTL[1], Z), XMFLOAT2(1.0f, 1.0f) },
				{ XMFLOAT3(MTL[0], TR[1], Z), XMFLOAT2(1.0f, 0.0f) },
				{ XMFLOAT3(TL[0], TL[1], Z), XMFLOAT2(0.0f, 0.0f) },
			};
			VertexPos verticesTM[] =
			{
				{ XMFLOAT3(MTL[0], MTL[1], Z), XMFLOAT2(0.0f, 1.0f) }, //    Front
				{ XMFLOAT3(MTR[0], MTR[1], Z), XMFLOAT2((MTR[0] - MTL[0]) / TileSize, 1.0f) },
				{ XMFLOAT3(MTR[0], TR[1], Z), XMFLOAT2((MTR[0] - MTL[0]) / TileSize, 0.0f) },
				{ XMFLOAT3(MTL[0], TL[1], Z), XMFLOAT2(0.0f, 0.0f) },
			};
			VertexPos verticesTR[] =
			{
				{ XMFLOAT3(MTR[0], MTR[1], Z), XMFLOAT2(0.0f, 1.0f) }, //    Front
				{ XMFLOAT3(TR[0], MTR[1], Z), XMFLOAT2(1.0f, 1.0f) },
				{ XMFLOAT3(TR[0], TR[1], Z), XMFLOAT2(1.0f, 0.0f) },
				{ XMFLOAT3(MTR[0], TR[1], Z), XMFLOAT2(0.0f, 0.0f) },
			};

			VertexPos verticesML[] =
			{
				{ XMFLOAT3(TL[0], MBL[1], Z), XMFLOAT2(0.0f, (MTL[1] - MBL[1]) / TileSize) }, //    Front
				{ XMFLOAT3(MBL[0], MBL[1], Z), XMFLOAT2(1.0f, (MTL[1] - MBL[1]) / TileSize) },
				{ XMFLOAT3(MTL[0], MTL[1], Z), XMFLOAT2(1.0f, 0.0f) },
				{ XMFLOAT3(TL[0], MTL[1], Z), XMFLOAT2(0.0f, 0.0f) },
			};
			VertexPos verticesMM[] =
			{
				{ XMFLOAT3(MBL[0], MBL[1], Z), XMFLOAT2(0.0f, (MTL[1] - MBL[1]) / TileSize) }, //    Front
				{ XMFLOAT3(MBR[0], MBR[1], Z), XMFLOAT2((MTR[0] - MTL[0]) / TileSize, (MTL[1] - MBL[1]) / TileSize) },
				{ XMFLOAT3(MTR[0], MTR[1], Z), XMFLOAT2((MTR[0] - MTL[0]) / TileSize, 0.0f) },
				{ XMFLOAT3(MTL[0], MTL[1], Z), XMFLOAT2(0.0f, 0.0f) },
			};
			VertexPos verticesMR[] =
			{
				{ XMFLOAT3(MBR[0], MBR[1], Z), XMFLOAT2(0.0f, (MTL[1] - MBL[1]) / TileSize) }, //    Front
				{ XMFLOAT3(TR[0], MBR[1], Z), XMFLOAT2(1.0f, (MTL[1] - MBL[1]) / TileSize) },
				{ XMFLOAT3(TR[0], MTR[1], Z), XMFLOAT2(1.0f, 0.0f) },
				{ XMFLOAT3(MTR[0], MTR[1], Z), XMFLOAT2(0.0f, 0.0f) },
			};

			VertexPos verticesBL[] =
			{
				{ XMFLOAT3(BL[0], BL[1], Z), XMFLOAT2(0.0f, 1.0f) }, //    Front
				{ XMFLOAT3(MBL[0], BL[1], Z), XMFLOAT2(1.0f, 1.0f) },
				{ XMFLOAT3(MBL[0], MBL[1], Z), XMFLOAT2(1.0f, 0.0f) },
				{ XMFLOAT3(BL[0], MBL[1], Z), XMFLOAT2(0.0f, 0.0f) },
			};
			VertexPos verticesBM[] =
			{
				{ XMFLOAT3(MBL[0], BL[1], Z), XMFLOAT2(0.0f, 1.0f) }, //    Front
				{ XMFLOAT3(MBR[0], BR[1], Z), XMFLOAT2((MTR[0] - MTL[0]) / TileSize, 1.0f) },
				{ XMFLOAT3(MBR[0], MBR[1], Z), XMFLOAT2((MTR[0] - MTL[0]) / TileSize, 0.0f) },
				{ XMFLOAT3(MBL[0], MBL[1], Z), XMFLOAT2(0.0f, 0.0f) },
			};
			VertexPos verticesBR[] =
			{
				{ XMFLOAT3(MBR[0], BR[1], Z), XMFLOAT2(0.0f, 1.0f) }, //    Front
				{ XMFLOAT3(BR[0], BR[1], Z), XMFLOAT2(1.0f, 1.0f) },
				{ XMFLOAT3(BR[0], MBR[1], Z), XMFLOAT2(1.0f, 0.0f) },
				{ XMFLOAT3(MBR[0], MBR[1], Z), XMFLOAT2(0.0f, 0.0f) },
			};

			D3D11_BUFFER_DESC vertexDesc;
			ZeroMemory(&vertexDesc, sizeof(vertexDesc));
			vertexDesc.Usage = D3D11_USAGE_DEFAULT;
			vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vertexDesc.ByteWidth = sizeof(VertexPos)* 24;

			{/*Add 9 Vertex Buffers*/}
			{
				ZeroMemory(&resourceData, sizeof(resourceData));
				resourceData.pSysMem = verticesTL;
				ID3D11Buffer *Buffer = sprite.GetBuffer(0);
				d3dResult = d3dDevice_->CreateBuffer(&vertexDesc, &resourceData, &Buffer);
				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to create vertex buffer!");
				}
				sprite.SetBuffer(*Buffer, 0);

				ZeroMemory(&resourceData, sizeof(resourceData));
				resourceData.pSysMem = verticesTM;
				Buffer = sprite.GetBuffer(1);
				d3dResult = d3dDevice_->CreateBuffer(&vertexDesc, &resourceData, &Buffer);
				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to create vertex buffer!");
				}
				sprite.SetBuffer(*Buffer, 1);

				ZeroMemory(&resourceData, sizeof(resourceData));
				resourceData.pSysMem = verticesTR;
				Buffer = sprite.GetBuffer(2);
				d3dResult = d3dDevice_->CreateBuffer(&vertexDesc, &resourceData, &Buffer);
				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to create vertex buffer!");
				}
				sprite.SetBuffer(*Buffer, 2);

				ZeroMemory(&resourceData, sizeof(resourceData));
				resourceData.pSysMem = verticesML;
				Buffer = sprite.GetBuffer(3);
				d3dResult = d3dDevice_->CreateBuffer(&vertexDesc, &resourceData, &Buffer);
				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to create vertex buffer!");
				}
				sprite.SetBuffer(*Buffer, 3);

				ZeroMemory(&resourceData, sizeof(resourceData));
				resourceData.pSysMem = verticesMM;
				Buffer = sprite.GetBuffer(4);
				d3dResult = d3dDevice_->CreateBuffer(&vertexDesc, &resourceData, &Buffer);
				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to create vertex buffer!");
				}
				sprite.SetBuffer(*Buffer, 4);

				ZeroMemory(&resourceData, sizeof(resourceData));
				resourceData.pSysMem = verticesMR;
				Buffer = sprite.GetBuffer(5);
				d3dResult = d3dDevice_->CreateBuffer(&vertexDesc, &resourceData, &Buffer);
				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to create vertex buffer!");
				}
				sprite.SetBuffer(*Buffer, 5);

				ZeroMemory(&resourceData, sizeof(resourceData));
				resourceData.pSysMem = verticesBL;
				Buffer = sprite.GetBuffer(6);
				d3dResult = d3dDevice_->CreateBuffer(&vertexDesc, &resourceData, &Buffer);
				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to create vertex buffer!");
				}
				sprite.SetBuffer(*Buffer, 6);

				ZeroMemory(&resourceData, sizeof(resourceData));
				resourceData.pSysMem = verticesBM;
				Buffer = sprite.GetBuffer(7);
				d3dResult = d3dDevice_->CreateBuffer(&vertexDesc, &resourceData, &Buffer);
				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to create vertex buffer!");
				}
				sprite.SetBuffer(*Buffer, 7);

				ZeroMemory(&resourceData, sizeof(resourceData));
				resourceData.pSysMem = verticesBR;
				Buffer = sprite.GetBuffer(8);
				d3dResult = d3dDevice_->CreateBuffer(&vertexDesc, &resourceData, &Buffer);
				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to create vertex buffer!");
				}
				sprite.SetBuffer(*Buffer, 8);
			}

			{/*Add 9 Colour Maps*/}
			{
				ID3D11ShaderResourceView *ColorMap = sprite.GetColorMap(0);
				string ColorMapFile = sprite.GetColorMapFile(0);
				d3dResult = D3DX11CreateShaderResourceViewFromFile(d3dDevice_, ColorMapFile.c_str(), 0, 0, &ColorMap, 0);
				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to load the texture image!");
				}
				sprite.SetColorMap(*ColorMap, 0);

				ColorMap = sprite.GetColorMap(1);
				ColorMapFile = sprite.GetColorMapFile(1);
				d3dResult = D3DX11CreateShaderResourceViewFromFile(d3dDevice_, ColorMapFile.c_str(), 0, 0, &ColorMap, 0);
				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to load the texture image!");
				}
				sprite.SetColorMap(*ColorMap, 1);

				ColorMap = sprite.GetColorMap(2);
				ColorMapFile = sprite.GetColorMapFile(2);
				d3dResult = D3DX11CreateShaderResourceViewFromFile(d3dDevice_, ColorMapFile.c_str(), 0, 0, &ColorMap, 0);
				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to load the texture image!");
				}
				sprite.SetColorMap(*ColorMap, 2);

				ColorMap = sprite.GetColorMap(3);
				ColorMapFile = sprite.GetColorMapFile(3);
				d3dResult = D3DX11CreateShaderResourceViewFromFile(d3dDevice_, ColorMapFile.c_str(), 0, 0, &ColorMap, 0);
				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to load the texture image!");
				}
				sprite.SetColorMap(*ColorMap, 3);

				ColorMap = sprite.GetColorMap(4);
				ColorMapFile = sprite.GetColorMapFile(4);
				d3dResult = D3DX11CreateShaderResourceViewFromFile(d3dDevice_, ColorMapFile.c_str(), 0, 0, &ColorMap, 0);
				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to load the texture image!");
				}
				sprite.SetColorMap(*ColorMap, 4);

				ColorMap = sprite.GetColorMap(5);
				ColorMapFile = sprite.GetColorMapFile(5);
				d3dResult = D3DX11CreateShaderResourceViewFromFile(d3dDevice_, ColorMapFile.c_str(), 0, 0, &ColorMap, 0);
				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to load the texture image!");
				}
				sprite.SetColorMap(*ColorMap, 5);

				ColorMap = sprite.GetColorMap(6);
				ColorMapFile = sprite.GetColorMapFile(6);
				d3dResult = D3DX11CreateShaderResourceViewFromFile(d3dDevice_, ColorMapFile.c_str(), 0, 0, &ColorMap, 0);
				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to load the texture image!");
				}
				sprite.SetColorMap(*ColorMap, 6);

				ColorMap = sprite.GetColorMap(7);
				ColorMapFile = sprite.GetColorMapFile(7);
				d3dResult = D3DX11CreateShaderResourceViewFromFile(d3dDevice_, ColorMapFile.c_str(), 0, 0, &ColorMap, 0);
				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to load the texture image!");
				}
				sprite.SetColorMap(*ColorMap, 7);

				ColorMap = sprite.GetColorMap(8);
				ColorMapFile = sprite.GetColorMapFile(8);
				d3dResult = D3DX11CreateShaderResourceViewFromFile(d3dDevice_, ColorMapFile.c_str(), 0, 0, &ColorMap, 0);
				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to load the texture image!");
				}
				sprite.SetColorMap(*ColorMap, 8);
			}
			Pos_Z--;
		}
	}

	{/*Initilize Scenery*/}
	{
		float Pos_Z = Scenery_Z;
		for (Scenery &sprite : SceneryList)// Set Vvertex buffer for each object
		{
			/*WORD indices[] =
			{
				//Front
				3, 1, 0,
				2, 1, 3,
				//Back
				2, 0, 1,
				3, 0, 2,
			};
			D3D11_BUFFER_DESC indexDesc;
			ZeroMemory(&indexDesc, sizeof(indexDesc));
			indexDesc.Usage = D3D11_USAGE_DEFAULT;
			indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			indexDesc.ByteWidth = sizeof(WORD)* 36;
			indexDesc.CPUAccessFlags = 0;
			resourceData.pSysMem = indices;
			ID3D11Buffer* IndexBuffer = sprite.GetIndices();
			d3dResult = d3dDevice_->CreateBuffer(&indexDesc, &resourceData, &IndexBuffer);
			if (FAILED(d3dResult))
			{
				DXTRACE_MSG("Failed to create index buffer!");
				return false;
			}
			sprite.SetIndices(*IndexBuffer);*/

			for (int i = 0; i < sprite.GetBufferNum(); i++)
			{
				float Z = 0;
				//float Z = sprite.GetPosition().z;
				sprite.SetPosition(XMFLOAT3(sprite.GetPosition().x, sprite.GetPosition().y, Pos_Z));
				float TLF[3] = { sprite.GetStartPos().x, sprite.GetStartPos().y, -1.0f + Z };
				float TRF[3] = { sprite.GetEndPos().x, sprite.GetStartPos().y, -1.0f + Z };
				float BLF[3] = { sprite.GetStartPos().x, sprite.GetEndPos().y, -1.0f + Z };
				float BRF[3] = { sprite.GetEndPos().x, sprite.GetEndPos().y, -1.0f + Z };

				float TLB[3] = { sprite.GetStartPos().x, sprite.GetStartPos().y, 1.0f + Z };
				float TRB[3] = { sprite.GetEndPos().x, sprite.GetStartPos().y, 1.0f + Z };
				float BLB[3] = { sprite.GetStartPos().x, sprite.GetEndPos().y, 1.0f + Z };
				float BRB[3] = { sprite.GetEndPos().x, sprite.GetEndPos().y, 1.0f + Z };

				VertexPos vertices[] =
				{
					{ XMFLOAT3(BLF[0], BLF[1], BLF[2]), XMFLOAT2(0.0f, 1.0f) }, //    Front
					{ XMFLOAT3(BRF[0], BRF[1], BRF[2]), XMFLOAT2(1.0f, 1.0f) },
					{ XMFLOAT3(TRF[0], TRF[1], TRF[2]), XMFLOAT2(1.0f, 0.0f) },
					{ XMFLOAT3(TLF[0], TLF[1], TLF[2]), XMFLOAT2(0.0f, 0.0f) },
				};

				D3D11_BUFFER_DESC vertexDesc;
				ZeroMemory(&vertexDesc, sizeof(vertexDesc));
				vertexDesc.Usage = D3D11_USAGE_DEFAULT;
				vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				vertexDesc.ByteWidth = sizeof(VertexPos)* 24;

				ZeroMemory(&resourceData, sizeof(resourceData));
				resourceData.pSysMem = vertices;

				ID3D11Buffer *Buffer = sprite.GetBuffer(i);//Fix
				d3dResult = d3dDevice_->CreateBuffer(&vertexDesc, &resourceData, &Buffer);

				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to create vertex buffer!");
				}

				sprite.SetBuffer(*Buffer, i);

				ID3D11ShaderResourceView *ColorMap = sprite.GetColorMap(i);//Fix
				string ColorMapFile = sprite.GetColorMapFile(i);//Fix
				d3dResult = D3DX11CreateShaderResourceViewFromFile(d3dDevice_, ColorMapFile.c_str(), 0, 0, &ColorMap, 0);
				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to load the texture image!");
				}
				sprite.SetColorMap(*ColorMap, i);
				Pos_Z--;
			}
		}
	}

	{/*Initilize Text*/}
	{
		float Pos_Z = Text_Z;
		for (Text &sprite : TextList)// Set Vertex buffer for each object
		{
			string Message = sprite.Get_Message();
			transform(Message.begin(), Message.end(), Message.begin(), toupper);

			_XMFLOAT2 CharStartPos = { 0, 0 };
			_XMFLOAT2 CharEndPos = { 0, 0 - 20 };

			sprite.SetPosition(XMFLOAT3(sprite.GetPosition().x, sprite.GetPosition().y, Pos_Z));
			
			{/*Create Text*/}
			{
				VertexPos vertices[MaxCharacters * 4];
				int Count = 0;
				for (int i = 0; i < MaxCharacters; i++)
				{
					float CharTexStartPos = 0;
					float CharTexEndPos = 0;

					string letter = "";
					if (i < Message.length())
					{
						//letter = sprite.Get_Message()[i];
						letter = Message[i];
					}

					if (letter == "<")
					{
						string Special = "<00>";
						Special[1] = Message[i + 1];
						Special[2] = Message[i + 2];
						letter = Special;
						i += 3;
					}

					auto search = StringCodes.find(letter);
					if (search != StringCodes.end())
					{
						CharTexStartPos = search->second[0] / FontMapWidth;
						CharTexEndPos = search->second[1] / FontMapWidth;
					}
					else
					{
						CharTexStartPos = 261 / FontMapWidth;
						CharTexEndPos = 264 / FontMapWidth;
					}

					if (letter == "<01>")
					{
						//CharStartPos.y -= 20 + 4;
						CharStartPos = { 0, CharStartPos.y - (20 + 4) };
						//CharEndPos.y -= 20 + 4;
						CharEndPos = { 0, CharEndPos.y - (20 + 4) };
					}

					CharStartPos.x = CharEndPos.x + 4;// (((Caps[(letter - indexA)][1] - Caps[(letter - indexA)][0]) / FontMapWidth) * static_cast<float>(i));
					CharEndPos.x = CharStartPos.x + ((CharTexEndPos * FontMapWidth - CharTexStartPos * FontMapWidth) * 4);
					//float thisEndY = sprite.GetPosition().y + 20;

					float Z = 0;
					//float Z = sprite.GetPosition().z;
					float TLF[3] = { CharStartPos.x, CharStartPos.y, Z };
					float TRF[3] = { CharEndPos.x, CharStartPos.y, Z };
					float BLF[3] = { CharStartPos.x, CharEndPos.y, Z };
					float BRF[3] = { CharEndPos.x, CharEndPos.y, Z };

					vertices[Count * 4 + 0] = { XMFLOAT3(BLF[0], BLF[1], BLF[2]), XMFLOAT2(CharTexStartPos, 1.0f) };
					vertices[Count * 4 + 1] = { XMFLOAT3(BRF[0], BRF[1], BRF[2]), XMFLOAT2(CharTexEndPos, 1.0f) };
					vertices[Count * 4 + 2] = { XMFLOAT3(TRF[0], TRF[1], TRF[2]), XMFLOAT2(CharTexEndPos, 0.0f) };
					vertices[Count * 4 + 3] = { XMFLOAT3(TLF[0], TLF[1], TLF[2]), XMFLOAT2(CharTexStartPos, 0.0f) };
					Count++;
				}//End Char Build loop
				D3D11_BUFFER_DESC vertexDesc;
				ZeroMemory(&vertexDesc, sizeof(vertexDesc));
				vertexDesc.Usage = D3D11_USAGE_DEFAULT;
				vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				vertexDesc.ByteWidth = sizeof(VertexPos)* 4 * MaxCharacters;//sizeof(VertexPos) * MaxCharacters;

				ZeroMemory(&resourceData, sizeof(resourceData));
				resourceData.pSysMem = vertices;

				ID3D11Buffer *Buffer = sprite.GetBuffer(0);//Fix
				d3dResult = d3dDevice_->CreateBuffer(&vertexDesc, &resourceData, &Buffer);

				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to create vertex buffer!");
				}
				//DBOUT("ColorMapFile:" << sprite.GetColorMapFile(i).c_str() << "\n");
				sprite.SetBuffer(*Buffer, 0);
			}
					
			ID3D11ShaderResourceView *ColorMap = sprite.GetColorMap(0);//Fix
			string ColorMapFile = sprite.GetColorMapFile(0);
			d3dResult = D3DX11CreateShaderResourceViewFromFile(d3dDevice_, ColorMapFile.c_str(), 0, 0, &ColorMap, 0);
			if (FAILED(d3dResult))
			{
				DXTRACE_MSG("Failed to load the texture image!");
			}
			sprite.SetColorMap(*ColorMap, 0);

			Pos_Z -= 0.001f;
		}//End List Loop
	}

	{/*Initilize TextBox*/}
	{
		float Pos_Z = TextBackground_Z;
		for (TextBox &sprite : TextBoxList)// Set Vertex buffer for each object
		{
			sprite.SetPosition(XMFLOAT3(sprite.GetPosition().x, sprite.GetPosition().y, Pos_Z));

			{/*Create Background*/}
			{
				//float Z = TextBackground_Z;
				//float Z = Pos_Z;
				float Z = 0.001f;
				//float Z = sprite.GetPosition().z;
				//{ -628 / 2, 168 / 2 }, { 628 / 2, -168 / 2 }
				//sprite.SetPosition(XMFLOAT3(sprite.GetPosition().x, sprite.GetPosition().y, TextBackground_Z));
				//float Elevation = 150.0f;
				float TLF[3] = { -628 / 2, 168 / 2, Z };
				float TRF[3] = { 628 / 2, 168 / 2, Z };
				float BLF[3] = { -628 / 2, -168 / 2,  Z };
				float BRF[3] = { 628 / 2, -168 / 2, Z };

				float TLB[3] = { -628 / 2, 168 / 2, Z };
				float TRB[3] = { 628 / 2, 168 / 2, Z };
				float BLB[3] = { -628 / 2, -168 / 2, Z };
				float BRB[3] = { 628 / 2, -168 / 2, Z };

				VertexPos vertices[] =
				{
					{ XMFLOAT3(BLF[0], BLF[1], BLF[2]), XMFLOAT2(0.0f, 1.0f) }, //    Front
					{ XMFLOAT3(BRF[0], BRF[1], BRF[2]), XMFLOAT2(1.0f, 1.0f) },
					{ XMFLOAT3(TRF[0], TRF[1], TRF[2]), XMFLOAT2(1.0f, 0.0f) },
					{ XMFLOAT3(TLF[0], TLF[1], TLF[2]), XMFLOAT2(0.0f, 0.0f) },
				};

				D3D11_BUFFER_DESC vertexDesc;
				ZeroMemory(&vertexDesc, sizeof(vertexDesc));
				vertexDesc.Usage = D3D11_USAGE_DEFAULT;
				vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				vertexDesc.ByteWidth = sizeof(VertexPos)* 24;

				ZeroMemory(&resourceData, sizeof(resourceData));
				resourceData.pSysMem = vertices;

				ID3D11Buffer *Buffer = sprite.GetBuffer(0);//Fix
				d3dResult = d3dDevice_->CreateBuffer(&vertexDesc, &resourceData, &Buffer);

				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to create vertex buffer!");
				}

				sprite.SetBuffer(*Buffer, 0);
			}


			string Message = sprite.Get_Message();
			transform(Message.begin(), Message.end(), Message.begin(), toupper);

			_XMFLOAT2 CharStartPos = { 0, 0 };
			_XMFLOAT2 CharEndPos = { 0, 0 - 20 };

			{/*Create Text*/}
			{
				VertexPos vertices[MaxCharacters * 4];
				int Count = 0;
				for (int i = 0; i < MaxCharacters; i++)
				{
					float CharTexStartPos = 0;
					float CharTexEndPos = 0;

					string letter = "";
					if (i < Message.length())
					{
						//letter = sprite.Get_Message()[i];
						letter = Message[i];
					}

					if (letter == "<")
					{
						string Special = "<00>";
						Special[1] = Message[i + 1];
						Special[2] = Message[i + 2];
						letter = Special;
						i += 3;
					}

					auto search = StringCodes.find(letter);
					if (search != StringCodes.end())
					{
						CharTexStartPos = search->second[0] / FontMapWidth;
						CharTexEndPos = search->second[1] / FontMapWidth;
					}
					else
					{
						CharTexStartPos = 261 / FontMapWidth;
						CharTexEndPos = 264 / FontMapWidth;
					}

					if (letter == "<01>")
					{
						//CharStartPos.y -= 20 + 4;
						CharStartPos = { 0, CharStartPos.y - (20 + 4) };
						//CharEndPos.y -= 20 + 4;
						CharEndPos = { 0, CharEndPos.y - (20 + 4) };
					}

					CharStartPos.x = CharEndPos.x + 4;// (((Caps[(letter - indexA)][1] - Caps[(letter - indexA)][0]) / FontMapWidth) * static_cast<float>(i));
					CharEndPos.x = CharStartPos.x + ((CharTexEndPos * FontMapWidth - CharTexStartPos * FontMapWidth) * 4);
					//float thisEndY = sprite.GetPosition().y + 20;

					float Z = 0;
					//float Z = sprite.GetPosition().z;
					float TLF[3] = { CharStartPos.x, CharStartPos.y, Z };
					float TRF[3] = { CharEndPos.x, CharStartPos.y, Z };
					float BLF[3] = { CharStartPos.x, CharEndPos.y, Z };
					float BRF[3] = { CharEndPos.x, CharEndPos.y, Z };

					vertices[Count * 4 + 0] = { XMFLOAT3(BLF[0], BLF[1], BLF[2]), XMFLOAT2(CharTexStartPos, 1.0f) };
					vertices[Count * 4 + 1] = { XMFLOAT3(BRF[0], BRF[1], BRF[2]), XMFLOAT2(CharTexEndPos, 1.0f) };
					vertices[Count * 4 + 2] = { XMFLOAT3(TRF[0], TRF[1], TRF[2]), XMFLOAT2(CharTexEndPos, 0.0f) };
					vertices[Count * 4 + 3] = { XMFLOAT3(TLF[0], TLF[1], TLF[2]), XMFLOAT2(CharTexStartPos, 0.0f) };
					Count++;
				}//End Char Build loop

				D3D11_BUFFER_DESC vertexDesc;
				ZeroMemory(&vertexDesc, sizeof(vertexDesc));
				vertexDesc.Usage = D3D11_USAGE_DEFAULT;
				vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				vertexDesc.ByteWidth = sizeof(VertexPos) * 4 * MaxCharacters;//sizeof(VertexPos) * MaxCharacters;

				ZeroMemory(&resourceData, sizeof(resourceData));
				resourceData.pSysMem = vertices;

				ID3D11Buffer *Buffer = sprite.GetBuffer(1);//Fix
				d3dResult = d3dDevice_->CreateBuffer(&vertexDesc, &resourceData, &Buffer);

				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to create vertex buffer!");
				}
				//DBOUT("ColorMapFile:" << sprite.GetColorMapFile(i).c_str() << "\n");
				sprite.SetBuffer(*Buffer, 1);
			}

			for (int i = 0; i < sprite.GetColormapNum(); i++)
			{
				ID3D11ShaderResourceView *ColorMap = sprite.GetColorMap(i);//Fix
				string ColorMapFile = sprite.GetColorMapFile(i);
				d3dResult = D3DX11CreateShaderResourceViewFromFile(d3dDevice_, ColorMapFile.c_str(), 0, 0, &ColorMap, 0);
				if (FAILED(d3dResult))
				{
					DXTRACE_MSG("Failed to load the texture image!");
				}
				sprite.SetColorMap(*ColorMap, i);
			}

			Pos_Z -= 0.002f;
		}//End List Loop
	}
		
	camera_.SetPosition(XMFLOAT3(0.0f, 2.0f, 0.0f));

	Level1Loop(msg, Delta, t1);
}


void Levels::UnloadLevel1Content()
{
	{}

	{/*Clear Player Data*/}
	{
		for (Player &sprite : PlayerList)
		{
			sprite.Shutdown();
		}

		PlayerList.clear();
	}

	{/*Clear Scenery Data*/}
	{
		for (Scenery &sprite : SceneryList)
		{
			sprite.Shutdown();
		}

		SceneryList.clear();
	}
	
	{/*Clear Wall Data*/}
	{
		for (Wall &sprite : WallList)
		{
			sprite.Shutdown();
		}

		WallList.clear();
	}
	
	{/*Clear Text Data*/}
	{
		for (Text &sprite : TextList)
		{
			sprite.Shutdown();
		}

		TextList.clear();
	}
	
	{/*Clear TextBox Data*/}
	{
		for (TextBox &sprite : TextBoxList)
		{
			sprite.Shutdown();
		}

		TextBoxList.clear();
	}
}


void Levels::UpdateLevel1(double dt)
{
	if (GetFocus() == hwnd_)//Only recieve input if the window is in focus
	{
		//float Speed = 300.0f;
		float Speed = 0.5f * 1000.0f;
		int a = 0;
		
		
		{/*MOVE*/}
		{
			float OffsetX = 0.0f;
			float OffsetY = 0.0f;
			bool CollideTop = false;
			bool CollideBottom = false;
			bool CollideLeft = false;
			bool CollideRight = false;
			bool ReDo = false;

			for (Wall &wall : WallList)
			{
				if (PlayerList[0].CollideOnTop(PlayerList[0].Get_TL_Pos(), PlayerList[0].Get_BR_Pos(),
					wall.Get_TL_Pos(), wall.Get_BR_Pos()))
				{
					CollideTop = true;
					OffsetY = -abs(PlayerList[0].Get_TL_Pos().y - wall.Get_BR_Pos().y) - 1;
				}
				if (PlayerList[0].CollideOnBottom(PlayerList[0].Get_TL_Pos(), PlayerList[0].Get_BR_Pos(),
					wall.Get_TL_Pos(), wall.Get_BR_Pos()))
				{
					CollideBottom = true;
					OffsetY = abs(wall.Get_TL_Pos().y - PlayerList[0].Get_BR_Pos().y);
				}
				if (PlayerList[0].CollideOnLeft(PlayerList[0].Get_TL_Pos(), PlayerList[0].Get_BR_Pos(),
					wall.Get_TL_Pos(), wall.Get_BR_Pos()))
				{
					CollideLeft = true;
					OffsetX = abs(wall.Get_BR_Pos().x - PlayerList[0].Get_TL_Pos().x);
				}
				if (PlayerList[0].CollideOnRight(PlayerList[0].Get_TL_Pos(), PlayerList[0].Get_BR_Pos(),
					wall.Get_TL_Pos(), wall.Get_BR_Pos()))
				{
					CollideRight = true;
					OffsetX = -abs(PlayerList[0].Get_BR_Pos().x - wall.Get_TL_Pos().x);
				}
			}
			
			if (GetAsyncKeyState(VK_DOWN) < 0)
			{
				DBOUT("OffsetX:" << OffsetX << "   OffsetY:" << OffsetY << "\n");
			}

			if (abs(OffsetY) <= abs(OffsetX))
			{
				PlayerList[0].MoveAngle(TAU, OffsetY);
			}
			else
			{
				PlayerList[0].MoveAngle(TAU / 4.0, OffsetX);
				ReDo = true;
			}

			if (ReDo)
			{
				bool CollideTop = false;
				bool CollideBottom = false;
				for (Wall &wall : WallList)
				{
					if (PlayerList[0].CollideOnTop(PlayerList[0].Get_TL_Pos(), PlayerList[0].Get_BR_Pos(),
						wall.Get_TL_Pos(), wall.Get_BR_Pos()))
					{
						CollideTop = true;
					}
					if (PlayerList[0].CollideOnBottom(PlayerList[0].Get_TL_Pos(), PlayerList[0].Get_BR_Pos(),
						wall.Get_TL_Pos(), wall.Get_BR_Pos()))
					{
						CollideBottom = true;
					}
				}
			}

			//PlayerList[0].SetVelosityY(0);
			if (CollideTop || CollideBottom)
			{
				PlayerList[0].SetVelosityY(0);
			}
			if (!CollideBottom)
			{
				if (GetAsyncKeyState(VK_UP) < 0 && PlayerList[0].GetVelosityY() > 0)
				{
					PlayerList[0].AddVelosity(0.0, -Speed * 3 * dt);
				}
				else
				{
					PlayerList[0].AddVelosity(0.0, -Speed * 6 * dt);
				}
			}
			if (GetAsyncKeyState(VK_UP) < 0 && !CollideTop && CollideBottom)
			{
				if (PlayerList[0].GetVelosityY() < Speed)
				{
					PlayerList[0].AddVelosity(0.0, Speed * 1.5);
				}
			}

			PlayerList[0].SetVelosityX(0);
			if (GetAsyncKeyState(VK_LEFT) < 0 && !CollideLeft)
			{
				PlayerList[0].SetVelosityX(-Speed);
				PlayerList[a].SetTexState("Left");
			}
			if (GetAsyncKeyState(VK_RIGHT) < 0 && !CollideRight)
			{
				PlayerList[0].SetVelosityX(Speed);
				PlayerList[a].SetTexState("Right");
			}

			PlayerList[0].MoveAngle(TAU, PlayerList[0].GetVelosityY() * dt);
			PlayerList[0].MoveAngle(TAU / 4, PlayerList[0].GetVelosityX() * dt);
		}

		if (GetAsyncKeyState(R_) < 0)
		{
			PlayerList[0].SetPosition(XMFLOAT3{ 0.0f, 2.0f, PlayerList[0].GetPosition().z });
		}

		{/*Camera Movements*/}
		{
			float SnapSpeed = 0.3f;
			float X_Dist = (PlayerList[0].GetPosition().x - camera_.GetPosition().x);
			float Y_Dist = (PlayerList[0].GetPosition().y - camera_.GetPosition().y);

			if ((X_Dist) > 0.0f && camera_.GetPosition().x < Level1End.x - Width / 2)//Right
			{
				camera_.Move(TAU / 4.0f, abs(X_Dist / SnapSpeed * dt));
			}
			if (camera_.GetPosition().x > Level1End.x - Width / 2)//Outside Boarder
			{
				camera_.SetPosition({ Level1End.x - Width / 2, camera_.GetPosition().y, camera_.GetPosition().z });
			}

			if ((X_Dist) < 0.0f && camera_.GetPosition().x > Level1Start.x + Width / 2)//Left
			{
				camera_.Move((3 * TAU) / 4.0f, abs(X_Dist / SnapSpeed * dt));
			}
			if (camera_.GetPosition().x < Level1Start.x + Width / 2)//Outside Boarder
			{
				camera_.SetPosition({ Level1Start.x + Width / 2, camera_.GetPosition().y, camera_.GetPosition().z });
			}
			if ((Y_Dist) > 0.0f && camera_.GetPosition().y < Level1Start.y - Height / 2)//Up
			{
				camera_.Move(TAU, abs(Y_Dist / SnapSpeed * dt));
			}
			if (camera_.GetPosition().y > Level1Start.y - Height / 2)//Outside Boarder
			{
				camera_.SetPosition({ camera_.GetPosition().x, Level1Start.y - Height / 2, camera_.GetPosition().z });
			}

			if ((Y_Dist) < 0.0f && camera_.GetPosition().y > Level1End.y + Height / 2)//Down
			{
				camera_.Move(PI, abs(Y_Dist / SnapSpeed * dt));
			}
			if (camera_.GetPosition().y < Level1End.y + Height / 2)//Outside Boarder
			{
				camera_.SetPosition({ camera_.GetPosition().x, Level1End.y + Height / 2, camera_.GetPosition().z });
			}
		}

		/*if (GetAsyncKeyState(VK_DOWN) < 0)
		{
			text.UpdateMessage("Hello!!!", &d3dResult, d3dDevice_, resourceData);
		}*/

		{/*Collide Sign*/}
		{
			for (Player &sprite : PlayerList)
			{
				for (TextBox &text : TextBoxList)
				{
					//float TextScaleX = text.GetScale().x;
					//float TextScaleY = text.GetScale().y;

					if (sprite.Collide(sprite.Get_TL_Pos(), sprite.Get_BR_Pos(),
						text.GetStartPos(), text.GetEndPos()))
					{
						/*
						if (TextScaleX < 1)
						{
							text.SetExpandRate(0.005f);//FIX------------------------------
						}
						else
						{
							text.SetExpandRate(0.0f);
						}*/
						text.SetScale({ 1.0f, 1.0f });
					}
					else
					{
						/*
						if (TextScaleX > 0)
						{
							text.SetExpandRate(-0.005f);//FIX------------------------------
						}
						else
						{
							text.SetExpandRate(0.0f);
						}*/
						text.SetScale({ 0.0f, 0.0f });
					}

					//text.SetScale({ TextScaleX + text.GetExpandRate(), TextScaleY + text.GetExpandRate() });
				}
			}
		}

		//PlayerList[a].Move();
		
	}
	//camera_.SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));
}

void Levels::RenderLevel1()
{
	if (d3dContext_ == 0)
		return;

	float clearColor[4] = { 0.0f, 0.0f, 0.25f, 1.0f };
	d3dContext_->ClearRenderTargetView(backBufferTarget_, clearColor);
	d3dContext_->ClearDepthStencilView(depthStencilView_, D3D11_CLEAR_DEPTH, 1.0f, 0);
	
	unsigned int stride = sizeof(VertexPos);
	static float ap = stride;
	unsigned int offset = 0;

	XMMATRIX rotationMat = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
	XMMATRIX translationMat = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	XMMATRIX ScaleMat = XMMatrixScaling(1.0f, 1.0f, 1.0f);

	XMMATRIX viewMat = camera_.GetViewMatrix();
	viewMat = XMMatrixTranspose(viewMat);

	for (Scenery &sprite : SceneryList)
	{
		d3dContext_->IASetInputLayout(inputLayout_);
		ID3D11Buffer *Buffer = sprite.GetBuffer(0);//Fix
		d3dContext_->IASetVertexBuffers(0, 1, &Buffer, &stride, &offset);

		d3dContext_->IASetIndexBuffer(indexBuffer_, DXGI_FORMAT_R16_UINT, 0);
		d3dContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		d3dContext_->VSSetShader(solidColorVS_, 0, 0);
		d3dContext_->PSSetShader(solidColorPS_, 0, 0);

		ID3D11ShaderResourceView *ColorMap = sprite.GetColorMap(0);//Fix
		d3dContext_->PSSetShaderResources(0, 1, &ColorMap);

		d3dContext_->PSSetSamplers(0, 1, &colorMapSampler_);

		XMMATRIX worldMat = ScaleMat * rotationMat * translationMat;
		worldMat = sprite.GetWorldMatrix() * ScaleMat * rotationMat * translationMat;
		worldMat = XMMatrixTranspose(worldMat);

		d3dContext_->UpdateSubresource(worldCB_, 0, 0, &worldMat, 0, 0);
		//d3dContext_->UpdateSubresource(viewCB_, 0, 0, &viewMatrix_, 0, 0);
		d3dContext_->UpdateSubresource(viewCB_, 0, 0, &viewMat, 0, 0);
		d3dContext_->UpdateSubresource(projCB_, 0, 0, &projMatrix_, 0, 0);

		d3dContext_->VSSetConstantBuffers(0, 1, &worldCB_);
		d3dContext_->VSSetConstantBuffers(1, 1, &viewCB_);
		d3dContext_->VSSetConstantBuffers(2, 1, &projCB_);

		d3dContext_->DrawIndexed(36, 0, 0);
	}
	for (Player &sprite : PlayerList)
	{
		for (int i = 0; i < sprite.GetColormapNum(); i++)
		{
			d3dContext_->IASetInputLayout(inputLayout_);

			ID3D11Buffer *Buffer = sprite.GetBuffer(0);//Fix
			d3dContext_->IASetVertexBuffers(0, 1, &Buffer, &stride, &offset);

			d3dContext_->IASetIndexBuffer(indexBuffer_, DXGI_FORMAT_R16_UINT, 0);
			d3dContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			d3dContext_->VSSetShader(solidColorVS_, 0, 0);
			d3dContext_->PSSetShader(solidColorPS_, 0, 0);

			ID3D11ShaderResourceView *ColorMap;
			//DBOUT("State:" << sprite.GetTexState().c_str() << "\n");
			//int tex = 0;
			if (sprite.GetTexState() == "Right")
			{
				ColorMap = sprite.GetColorMap(0);
			}
			else if (sprite.GetTexState() == "Left")
			{
				ColorMap = sprite.GetColorMap(1);
			}

			d3dContext_->PSSetShaderResources(0, 1, &ColorMap);

			d3dContext_->PSSetSamplers(0, 1, &colorMapSampler_);

			XMMATRIX worldMat = ScaleMat * rotationMat * translationMat;
			worldMat = sprite.GetWorldMatrix() * ScaleMat * rotationMat * translationMat;
			worldMat = XMMatrixTranspose(worldMat);

			//XMFLOAT2 Alpha = { 1.0f, 1.0f };

			d3dContext_->UpdateSubresource(worldCB_, 0, 0, &worldMat, 0, 0);
			//d3dContext_->UpdateSubresource(viewCB_, 0, 0, &viewMatrix_, 0, 0);
			d3dContext_->UpdateSubresource(viewCB_, 0, 0, &viewMat, 0, 0);
			d3dContext_->UpdateSubresource(projCB_, 0, 0, &projMatrix_, 0, 0);
			//d3dContext_->UpdateSubresource(AlphaCB_, 0, 0, &Alpha, 0, 0);

			d3dContext_->VSSetConstantBuffers(0, 1, &worldCB_);
			d3dContext_->VSSetConstantBuffers(1, 1, &viewCB_);
			d3dContext_->VSSetConstantBuffers(2, 1, &projCB_);
			//d3dContext_->VSSetConstantBuffers(3, 1, &AlphaCB_);

			d3dContext_->DrawIndexed(36, 0, 0);
		}
	}
	for (Wall &sprite : WallList)
	{
		for (int i = 0; i < 9; i++)
		{

			//string a = sprite.GetColorMapFile(i);
			//DBOUT(a.c_str() << "\n");

			d3dContext_->IASetInputLayout(inputLayout_);

			ID3D11Buffer *Buffer = sprite.GetBuffer(i);
			d3dContext_->IASetVertexBuffers(0, 1, &Buffer, &stride, &offset);

			d3dContext_->IASetIndexBuffer(indexBuffer_, DXGI_FORMAT_R16_UINT, 0);
			d3dContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			d3dContext_->VSSetShader(solidColorVS_, 0, 0);
			d3dContext_->PSSetShader(solidColorPS_, 0, 0);

			ID3D11ShaderResourceView *ColorMap = sprite.GetColorMap(i);
			d3dContext_->PSSetShaderResources(0, 1, &ColorMap);

			d3dContext_->PSSetSamplers(0, 1, &colorMapSampler_);

			XMMATRIX worldMat = ScaleMat * rotationMat * translationMat;
			worldMat = sprite.GetWorldMatrix() * ScaleMat * rotationMat * translationMat;
			worldMat = XMMatrixTranspose(worldMat);

			d3dContext_->UpdateSubresource(worldCB_, 0, 0, &worldMat, 0, 0);
			//d3dContext_->UpdateSubresource(viewCB_, 0, 0, &viewMatrix_, 0, 0);
			d3dContext_->UpdateSubresource(viewCB_, 0, 0, &viewMat, 0, 0);
			d3dContext_->UpdateSubresource(projCB_, 0, 0, &projMatrix_, 0, 0);

			d3dContext_->VSSetConstantBuffers(0, 1, &worldCB_);
			d3dContext_->VSSetConstantBuffers(1, 1, &viewCB_);
			d3dContext_->VSSetConstantBuffers(2, 1, &projCB_);

			d3dContext_->DrawIndexed(36, 0, 0);
		}
	}
	for (TextBox &sprite : TextBoxList)
	{
		for (int i = 0; i < 2; i++)
		{
			d3dContext_->IASetInputLayout(inputLayout_);
			ID3D11Buffer *Buffer = sprite.GetBuffer(i);//Fix
			d3dContext_->IASetVertexBuffers(0, 1, &Buffer, &stride, &offset);

			d3dContext_->IASetIndexBuffer(indexBufferText_, DXGI_FORMAT_R16_UINT, 0);
			d3dContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			d3dContext_->VSSetShader(solidColorVS_, 0, 0);
			d3dContext_->PSSetShader(solidColorPS_, 0, 0);

			ID3D11ShaderResourceView *ColorMap = sprite.GetColorMap(i);//Fix
			d3dContext_->PSSetShaderResources(0, 1, &ColorMap);

			d3dContext_->PSSetSamplers(0, 1, &colorMapSampler_);

			XMMATRIX worldMat;
			if (i == 0)
			{
				//XMFLOAT2 scale = sprite.GetScale();
				worldMat = sprite.GetTextBoxMatrix() * ScaleMat * rotationMat * translationMat;
			}
			else
			{
				worldMat = sprite.GetWorldMatrix() * ScaleMat * rotationMat * translationMat;
			}
			worldMat = XMMatrixTranspose(worldMat);
			d3dContext_->UpdateSubresource(worldCB_, 0, 0, &worldMat, 0, 0);
			//d3dContext_->UpdateSubresource(viewCB_, 0, 0, &viewMatrix_, 0, 0);
			XMMATRIX viewmat = viewMat;
			viewmat = XMMatrixTranslation(0, 0, 0);
			//viewmat = XMMatrixTranspose(viewmat);
			d3dContext_->UpdateSubresource(viewCB_, 0, 0, &viewmat, 0, 0);
			d3dContext_->UpdateSubresource(projCB_, 0, 0, &projMatrix_, 0, 0);

			d3dContext_->VSSetConstantBuffers(0, 1, &worldCB_);
			d3dContext_->VSSetConstantBuffers(1, 1, &viewCB_);
			d3dContext_->VSSetConstantBuffers(2, 1, &projCB_);
			if (i == 0)
			{
				d3dContext_->DrawIndexed(6, 0, 0);
			}
			else
			{
				d3dContext_->DrawIndexed(MaxCharacters * 6, 0, 0);
			}
		}
	}
	for (Text &sprite : TextList)
	{
		d3dContext_->IASetInputLayout(inputLayout_);
		ID3D11Buffer *Buffer = sprite.GetBuffer(0);//Fix
		d3dContext_->IASetVertexBuffers(0, 1, &Buffer, &stride, &offset);

		d3dContext_->IASetIndexBuffer(indexBufferText_, DXGI_FORMAT_R16_UINT, 0);
		d3dContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		d3dContext_->VSSetShader(solidColorVS_, 0, 0);
		d3dContext_->PSSetShader(solidColorPS_, 0, 0);

		ID3D11ShaderResourceView *ColorMap = sprite.GetColorMap(0);//Fix
		d3dContext_->PSSetShaderResources(0, 1, &ColorMap);

		d3dContext_->PSSetSamplers(0, 1, &colorMapSampler_);

		XMMATRIX worldMat = sprite.GetWorldMatrix() * ScaleMat * rotationMat * translationMat;
		worldMat = XMMatrixTranspose(worldMat);

		d3dContext_->UpdateSubresource(worldCB_, 0, 0, &worldMat, 0, 0);
		//d3dContext_->UpdateSubresource(viewCB_, 0, 0, &viewMatrix_, 0, 0);
		//viewMat = XMMatrixTranslation(0, 0, 0);
		d3dContext_->UpdateSubresource(viewCB_, 0, 0, &viewMat, 0, 0);
		d3dContext_->UpdateSubresource(projCB_, 0, 0, &projMatrix_, 0, 0);

		d3dContext_->VSSetConstantBuffers(0, 1, &worldCB_);
		d3dContext_->VSSetConstantBuffers(1, 1, &viewCB_);
		d3dContext_->VSSetConstantBuffers(2, 1, &projCB_);

		d3dContext_->DrawIndexed(MaxCharacters * 6, 0, 0);
	}

	//DrawString("Custom", 30, 30);

	swapChain_->Present(0, 0);
}



/*


void Levels::DrawString(string Message, float startX, float startY)
{
	D3D11_BUFFER_DESC vertexDesc;
	ID3D11Buffer *vertexBuffer;
	ZeroMemory(&vertexDesc, sizeof(vertexDesc));
	vertexDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	const int sizeOfSprite = sizeof(VertexPos)* 6;
	const int maxLetters = 1164;

	vertexDesc.ByteWidth = sizeOfSprite * maxLetters;

	d3dResult = d3dDevice_->CreateBuffer(&vertexDesc, 0, &vertexBuffer);

	// Size in bytes for a single sprite.
	//int sizeOfSprite = sizeof(VertexPos)* 6;

	// Demo's dynamic buffer setup for max of 24 letters.
	//int maxLetters = 1164;

	int length = Message.length();

	// Clamp for strings too long.
	if (length > maxLetters)
		length = maxLetters;

	// Char's width on screen.
	float charWidth = 16.0f / 800.0f;
	//float charWidth = 52.0f / 800.0f;

	// Space between chars on screen.
	float GapWidth = 4.0f;

	// Char's height on screen.
	float charHeight = 32.0f / 640.0f;
	//float charHeight = 55.0f / 640.0f;

	// Char's texel width.
	//float texelWidth = 32.0f / 864.0f;
	//float texelWidth = 32.0f / FontMapWidth;
	float texelWidth = 16.0f / 800.0f;

	// verts per-triangle (3) * total triangles (2) = 6.
	const int verticesPerLetter = 6;

	D3D11_MAPPED_SUBRESOURCE mapResource;
	HRESULT d3dResult = d3dContext_->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);

	if (FAILED(d3dResult))
	{
		DXTRACE_MSG("Failed to map resource!");
		//return false;
	}

	// Point to our vertex buffer's internal data.
	VertexPos *spritePtr = (VertexPos*)mapResource.pData;

	const int indexA = static_cast<char>('A');
	const int indexZ = static_cast<char>('Z');

	const int indexa = static_cast<char>('a');
	const int indexz = static_cast<char>('z');

	float thisStartX = startX;
	float thisEndX = startX;

	_XMFLOAT2 CharStartPos = { startX, startY };
	_XMFLOAT2 CharEndPos = { startX, startY - 20 };

	for (int i = 0; i < length; ++i)
	{


		//int texLookup = 0;
		//float tuStart = 0;
		//float tuEnd = 0;
		//int letter = static_cast<char>(message[i]);

		float CharTexStartPos = 0;
		float CharTexEndPos = 0;

		string letter = "";
		letter = Message[i];

		if (letter == "<")
		{
			string Special = "<00>";
			Special[1] = Message[i + 1];
			Special[2] = Message[i + 2];
			letter = Special;
			i += 3;
		}

		auto search = StringCodes.find(letter);
		if (search != StringCodes.end())
		{
			CharTexStartPos = search->second[0] / FontMapWidth;
			CharTexEndPos = search->second[1] / FontMapWidth;
		}
		else
		{
			CharTexStartPos = 261 / FontMapWidth;
			CharTexEndPos = 264 / FontMapWidth;
		}

		//float tuStart = 0.0f + (texelWidth * static_cast<float>(texLookup));
		//float tuEnd = tuStart + texelWidth;
		thisStartX = thisEndX + GapWidth;// (((Caps[(letter - indexA)][1] - Caps[(letter - indexA)][0]) / FontMapWidth) * static_cast<float>(i));
		thisEndX = thisStartX + ((CharTexEndPos * FontMapWidth - CharTexStartPos * FontMapWidth) * 4);
		float thisEndY = startY + charHeight;

		spritePtr[0 + i * 6].pos = XMFLOAT3(thisEndX, thisEndY, 10.0f);   //top right       Grid Coords
		spritePtr[1 + i * 6].pos = XMFLOAT3(thisEndX, startY, 10.0f);     //bottom right
		spritePtr[2 + i * 6].pos = XMFLOAT3(thisStartX, startY, 10.0f);   //bottom left
		spritePtr[3 + i * 6].pos = XMFLOAT3(thisStartX, startY, 10.0f);   //bottom left
		spritePtr[4 + i * 6].pos = XMFLOAT3(thisStartX, thisEndY, 10.0f); //top left
		spritePtr[5 + i * 6].pos = XMFLOAT3(thisEndX, thisEndY, 10.0f);   //top right

		spritePtr[0 + i * 6].tex0 = XMFLOAT2(CharTexEndPos, 0.0f);   //top right            screen/texture coords
		spritePtr[1 + i * 6].tex0 = XMFLOAT2(CharTexEndPos, 1.0f);   //bottom right
		spritePtr[2 + i * 6].tex0 = XMFLOAT2(CharTexStartPos, 1.0f); //bottom left
		spritePtr[3 + i * 6].tex0 = XMFLOAT2(CharTexStartPos, 1.0f); //bottom left
		spritePtr[4 + i * 6].tex0 = XMFLOAT2(CharTexStartPos, 0.0f); //top left
		spritePtr[5 + i * 6].tex0 = XMFLOAT2(CharTexEndPos, 0.0f);   //top right

		//spritePtr += 6;
	}

	unsigned int stride = sizeof(VertexPos);
	static float ap = stride;
	unsigned int offset = 0;

	XMMATRIX rotationMat = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
	XMMATRIX translationMat = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	XMMATRIX ScaleMat = XMMatrixScaling(1.0f, 1.0f, 1.0f);

	XMMATRIX viewMat = camera_.GetViewMatrix();
	viewMat = XMMatrixTranspose(viewMat);

	XMMATRIX translation = XMMatrixTranslation(startX, startY, 0.0f);
	XMMATRIX rotationZ = XMMatrixRotationZ(0.0f);
	XMMATRIX scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);

	XMMATRIX Thisworldmat = rotationZ * scale * translation;

	d3dContext_->Unmap(vertexBuffer, 0);


	d3dContext_->IASetInputLayout(inputLayout_);
	ID3D11Buffer *Buffer = vertexBuffer;
	d3dContext_->IASetVertexBuffers(0, 1, &Buffer, &stride, &offset);

	d3dContext_->IASetIndexBuffer(indexBuffer_, DXGI_FORMAT_R16_UINT, 0);
	d3dContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	d3dContext_->VSSetShader(solidColorVS_, 0, 0);
	d3dContext_->PSSetShader(solidColorPS_, 0, 0);

	ID3D11ShaderResourceView *ColorMap = TextList[0].GetColorMap(0);//Fix
	d3dContext_->PSSetShaderResources(0, 1, &ColorMap);

	d3dContext_->PSSetSamplers(0, 1, &colorMapSampler_);

	XMMATRIX worldMat = ScaleMat * rotationMat * translationMat;
	worldMat = Thisworldmat * ScaleMat * rotationMat * translationMat;
	worldMat = XMMatrixTranspose(worldMat);

	d3dContext_->UpdateSubresource(worldCB_, 0, 0, &worldMat, 0, 0);
	//d3dContext_->UpdateSubresource(viewCB_, 0, 0, &viewMatrix_, 0, 0);
	d3dContext_->UpdateSubresource(viewCB_, 0, 0, &viewMat, 0, 0);
	d3dContext_->UpdateSubresource(projCB_, 0, 0, &projMatrix_, 0, 0);

	d3dContext_->VSSetConstantBuffers(0, 1, &worldCB_);
	d3dContext_->VSSetConstantBuffers(1, 1, &viewCB_);
	d3dContext_->VSSetConstantBuffers(2, 1, &projCB_);

	//d3dContext_->DrawIndexed(36, 0, 0);


	d3dContext_->Draw(6 * length, 0);
}

*/