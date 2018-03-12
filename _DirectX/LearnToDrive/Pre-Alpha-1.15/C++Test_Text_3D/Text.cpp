

#include<d3d11.h>
#include<d3dx11.h>
#include"Text.h"
#include<math.h>

Text::Text(XMFLOAT3 Pos = { 0.0f, 0.0f, 0.0f }, XMFLOAT2 StartPos = { 0, 0 },
	XMFLOAT2 EndPos = { 0, 0 }, vector<string> ColorMap = { "Tex\\MissingTexture.png" },
	int NumBuffers = 1, int NumColorMap = 1, string Message = "")
	:GameObject(Pos, StartPos, EndPos, ColorMap, NumBuffers, NumColorMap)
{
	transform(Message.begin(), Message.end(), Message.begin(), toupper);
	Message_ = Message;
	//ShowBackground_ = ShowBackground;
	//NumBuffers_ = Message.length();
}

string Text::Get_Message()
{
	return Message_;
}


void Text::UpdateMessage(string Message, HRESULT* D3DResult, ID3D11Device* D3DDevice_, D3D11_SUBRESOURCE_DATA ResourceData)
{
	transform(Message.begin(), Message.end(), Message.begin(), toupper);
	if (Message != Message_)
	{
		Message_ = Message;
		{/*Update Vertex Buffer*/ }
		{
			float Pos_Z = Text_Z;

			_XMFLOAT2 CharStartPos = { position_.x, position_.y };
			_XMFLOAT2 CharEndPos = { position_.x, position_.y - 20 };
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

				CharStartPos.x = CharEndPos.x + 4;// (((Caps[(letter - indexA)][1] - Caps[(letter - indexA)][0]) / FontMapWidth) * static_cast<float>(i));
				CharEndPos.x = CharStartPos.x + ((CharTexEndPos * FontMapWidth - CharTexStartPos * FontMapWidth) * 4);
				//float thisEndY = sprite.GetPosition().y + 20;

				float Z = 0;
				//float Z = sprite.GetPosition().z;
				position_.z = Pos_Z;
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
			vertexDesc.ByteWidth = MaxCharacters * MaxCharacters;//sizeof(VertexPos) * MaxCharacters;

			ZeroMemory(&ResourceData, sizeof(ResourceData));
			ResourceData.pSysMem = vertices;

			ID3D11Buffer *Buffer = VertexBuffer_[0];//Fix
			*D3DResult = D3DDevice_->CreateBuffer(&vertexDesc, &ResourceData, &Buffer);

			if (FAILED(D3DResult))
			{
				DXTRACE_MSG("Failed to create vertex buffer!");
				//return false;
			}
			//DBOUT("ColorMapFile:" << sprite.GetColorMapFile(i).c_str() << "\n");
			//sprite.SetBuffer(*Buffer, 0);
			VertexBuffer_[0] = Buffer;


			/*ID3D11ShaderResourceView *ColorMap = ColorMap_[0];//Fix
			*D3DResult = D3DX11CreateShaderResourceViewFromFile(D3DDevice_, ColorMapFile_[0].c_str(), 0, 0, &ColorMap, 0);
			if (FAILED(D3DResult))
			{
				DXTRACE_MSG("Failed to load the texture image!");
				//return false;
			}
			//sprite.SetColorMap(*ColorMap, 0);
			ColorMap_[0] = ColorMap;
			Pos_Z -= 0.001f;*/
		}
	}
}







