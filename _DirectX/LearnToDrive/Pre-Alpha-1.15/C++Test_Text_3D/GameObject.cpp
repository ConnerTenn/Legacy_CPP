
/*
Beginning DirectX 11 Game Programming
By Allen Sherrod and Wendy Jones

GameObject - Used to represent a 2D sprite's transformation.
*/


#include<d3d11.h>
#include<d3dx11.h>
#include"GameObject.h"
#include<math.h>

#define PI 3.14159265358979323

GameObject::GameObject(XMFLOAT3 Pos = { 0.0f, 0.0f, 0.0f }, XMFLOAT2 StartPos = { 0, 0 }, 
	XMFLOAT2 EndPos = { 0, 0 }, vector<string> ColorMapFile = { "Tex\\MissingTexture.png" },
	int NumBuffers = 1, int NumColorMap = 1)
{
	StartPos_ = StartPos;
	EndPos_ = EndPos;
	rotation_ = 0;
	scale_.x = scale_.y = 1.0f;
	SetPosition(Pos);
	//VertexBuffer_ = { NULL };
	//ColorMap_ = { NULL };
	ColorMapFile_ = ColorMapFile;
	NumBuffers_ = NumBuffers;
	NumColorMap_ = NumColorMap;
	for (int i = 0; i < NumBuffers; i++)
	{
		VertexBuffer_.push_back(NULL);
	}
	for (int i = 0; i < NumColorMap; i++)
	{
		ColorMap_.push_back(NULL);
	}
}


XMMATRIX GameObject::GetWorldMatrix()
{
	XMMATRIX translation = XMMatrixTranslation(position_.x, position_.y, position_.z);
	XMMATRIX rotationZ = XMMatrixRotationZ(rotation_);
	XMMATRIX scale = XMMatrixScaling(scale_.x, scale_.y, 1.0f);

	return  rotationZ * scale * translation;
}

XMFLOAT3 GameObject::GetPosition()
{
	return position_;
}

ID3D11Buffer* GameObject::GetBuffer(int i)
{
	return VertexBuffer_[i];
}

XMFLOAT2 GameObject::GetStartPos()
{
	return StartPos_;
}

XMFLOAT2 GameObject::GetEndPos()
{
	return EndPos_;
}

XMFLOAT2 GameObject::Get_TL_Pos()
{
	XMFLOAT2 Pos;
	Pos.x = StartPos_.x + position_.x;
	Pos.y = StartPos_.y + position_.y;
	return Pos;
}

XMFLOAT2 GameObject::Get_BR_Pos()
{
	XMFLOAT2 Pos;
	Pos.x = EndPos_.x + position_.x;
	Pos.y = EndPos_.y + position_.y;
	return Pos;
}

string GameObject::GetColorMapFile(int i)
{
	return ColorMapFile_[i];
}

ID3D11ShaderResourceView* GameObject::GetColorMap(int i)
{
	return ColorMap_[i];
}

/*ID3D11Buffer* GameObject::GetIndices()
{
	return Indices_;
}*/

unsigned int GameObject::GetBufferNum()
{
	return NumBuffers_;
}

unsigned int GameObject::GetColormapNum()
{
	return NumColorMap_;
}

XMFLOAT2 GameObject::GetScale()
{
	return scale_;
}

bool GameObject::Collide(XMFLOAT2 Self_TL_Pos_, XMFLOAT2 Self_BR_Pos_,
	XMFLOAT2 Object_TL_Pos_, XMFLOAT2 Object_BR_Pos_)
{
	XMFLOAT2 Self_TL_Pos = Self_TL_Pos_;
	XMFLOAT2 Self_TR_Pos = { Self_BR_Pos_.x, Self_TL_Pos_.y };
	XMFLOAT2 Self_BR_Pos = Self_BR_Pos_;
	XMFLOAT2 Self_BL_Pos = { Self_TL_Pos_.x, Self_BR_Pos_.y };
	XMFLOAT2 ObjectStartPos = Object_TL_Pos_;
	XMFLOAT2 ObjectEndPos = Object_BR_Pos_;
	/*Self_TL_Pos.x--;
	Self_TL_Pos.y++;
	Self_TR_Pos.x--;
	Self_TR_Pos.y++;
	Self_BR_Pos.x++;
	Self_BR_Pos.y--;
	Self_BL_Pos.x++;
	Self_BL_Pos.y--;*/

	if (Self_TL_Pos.x > ObjectStartPos.x && Self_TL_Pos.x < ObjectEndPos.x &&
		Self_TL_Pos.y > ObjectEndPos.y && Self_TL_Pos.y < ObjectStartPos.y)//Top Left Corner
	{
		return true;
	}

	if (Self_TR_Pos.x > ObjectStartPos.x && Self_TR_Pos.x < ObjectEndPos.x &&
		Self_TR_Pos.y > ObjectEndPos.y && Self_TR_Pos.y < ObjectStartPos.y)//Top Right Corner
	{
		return true;
	}

	if (Self_BR_Pos.x > ObjectStartPos.x && Self_BR_Pos.x < ObjectEndPos.x &&
		Self_BR_Pos.y > ObjectEndPos.y && Self_BR_Pos.y < ObjectStartPos.y)//Bottom Right Corner
	{
		return true;
	}

	if (Self_BL_Pos.x > ObjectStartPos.x && Self_BL_Pos.x < ObjectEndPos.x &&
		Self_BL_Pos.y > ObjectEndPos.y && Self_BL_Pos.y < ObjectStartPos.y)//Bottom Left Corner
	{
		return true;
	}

	return false;
}

bool GameObject::CollideOnBottom(XMFLOAT2 Self_TL_Pos_, XMFLOAT2 Self_BR_Pos_,
	XMFLOAT2 Object_TL_Pos_, XMFLOAT2 Object_BR_Pos_)
{
	XMFLOAT2 Self_TL_Pos = Self_TL_Pos_;
	XMFLOAT2 Self_TR_Pos = { Self_BR_Pos_.x, Self_TL_Pos_.y };
	XMFLOAT2 Self_BR_Pos = Self_BR_Pos_;
	XMFLOAT2 Self_BL_Pos = { Self_TL_Pos_.x, Self_BR_Pos_.y };
	XMFLOAT2 ObjectStartPos = Object_TL_Pos_;
	XMFLOAT2 ObjectEndPos = Object_BR_Pos_;
	//Self_TL_Pos.x--;
	Self_BR_Pos.y-=1;

	Self_BR_Pos.x -= 1;
	Self_TR_Pos.x -= 1;

	Self_BL_Pos.x += 1;
	Self_TL_Pos.x += 1;

	Self_BL_Pos.y-=1;

	/*if (Self_TL_Pos.x > ObjectStartPos.x && Self_TL_Pos.x < ObjectEndPos.x &&
		Self_TL_Pos.y > ObjectEndPos.y && Self_TL_Pos.y < ObjectStartPos.y)//Top Left Corner
	{
		return true;
	}

	if (Self_TR_Pos.x > ObjectStartPos.x && Self_TR_Pos.x < ObjectEndPos.x &&
		Self_TR_Pos.y > ObjectEndPos.y && Self_TR_Pos.y < ObjectStartPos.y)//Top Right Corner
	{
		return true;
	}*/

	if (Self_BR_Pos.x > ObjectStartPos.x && Self_BR_Pos.x < ObjectEndPos.x &&
		Self_BR_Pos.y > ObjectEndPos.y && Self_BR_Pos.y < ObjectStartPos.y)//Bottom Right Corner
	{
		return true;
	}

	if (Self_BL_Pos.x > ObjectStartPos.x && Self_BL_Pos.x < ObjectEndPos.x &&
		Self_BL_Pos.y > ObjectEndPos.y && Self_BL_Pos.y < ObjectStartPos.y)//Bottom Left Corner
	{
		return true;
	}

	return false;
}

bool GameObject::CollideOnTop(XMFLOAT2 Self_TL_Pos_, XMFLOAT2 Self_BR_Pos_,
	XMFLOAT2 Object_TL_Pos_, XMFLOAT2 Object_BR_Pos_)
{
	XMFLOAT2 Self_TL_Pos = Self_TL_Pos_;
	XMFLOAT2 Self_TR_Pos = { Self_BR_Pos_.x, Self_TL_Pos_.y };
	XMFLOAT2 Self_BR_Pos = Self_BR_Pos_;
	XMFLOAT2 Self_BL_Pos = { Self_TL_Pos_.x, Self_BR_Pos_.y };
	XMFLOAT2 ObjectStartPos = Object_TL_Pos_;
	XMFLOAT2 ObjectEndPos = Object_BR_Pos_;
	Self_TL_Pos.y+=2;
	//Self_BR_Pos.y--;
	Self_TR_Pos.y+=2;
	//Self_BL_Pos.y+=2;

	Self_BR_Pos.x -= 1;
	Self_TR_Pos.x -= 1;

	Self_BL_Pos.x += 1;
	Self_TL_Pos.x += 1;

	if (Self_TL_Pos.x > ObjectStartPos.x && Self_TL_Pos.x < ObjectEndPos.x &&
	Self_TL_Pos.y > ObjectEndPos.y && Self_TL_Pos.y < ObjectStartPos.y)//Top Left Corner
	{
	return true;
	}

	if (Self_TR_Pos.x > ObjectStartPos.x && Self_TR_Pos.x < ObjectEndPos.x &&
	Self_TR_Pos.y > ObjectEndPos.y && Self_TR_Pos.y < ObjectStartPos.y)//Top Right Corner
	{
	return true;
	}

		/*if (Self_BR_Pos.x > ObjectStartPos.x && Self_BR_Pos.x < ObjectEndPos.x &&
		Self_BR_Pos.y > ObjectEndPos.y && Self_BR_Pos.y < ObjectStartPos.y)//Bottom Right Corner
	{
		return true;
	}

	if (Self_BL_Pos.x > ObjectStartPos.x && Self_BL_Pos.x < ObjectEndPos.x &&
		Self_BL_Pos.y > ObjectEndPos.y && Self_BL_Pos.y < ObjectStartPos.y)//Bottom Left Corner
	{
		return true;
	}*/

	return false;
}

bool GameObject::CollideOnRight(XMFLOAT2 Self_TL_Pos_, XMFLOAT2 Self_BR_Pos_,
	XMFLOAT2 Object_TL_Pos_, XMFLOAT2 Object_BR_Pos_)
{
	XMFLOAT2 Self_TL_Pos = Self_TL_Pos_;
	XMFLOAT2 Self_TR_Pos = { Self_BR_Pos_.x, Self_TL_Pos_.y };
	XMFLOAT2 Self_BR_Pos = Self_BR_Pos_;
	XMFLOAT2 Self_BL_Pos = { Self_TL_Pos_.x, Self_BR_Pos_.y };
	XMFLOAT2 ObjectStartPos = Object_TL_Pos_;
	XMFLOAT2 ObjectEndPos = Object_BR_Pos_;
	//Self_TL_Pos.x--;
	Self_BR_Pos.x += 2;
	Self_TR_Pos.x += 2;
	//Self_BL_Pos.y--;

	/*if (Self_TL_Pos.x > ObjectStartPos.x && Self_TL_Pos.x < ObjectEndPos.x &&
	Self_TL_Pos.y > ObjectEndPos.y && Self_TL_Pos.y < ObjectStartPos.y)//Top Left Corner
	{
	return true;
	}*/

	if (Self_TR_Pos.x > ObjectStartPos.x && Self_TR_Pos.x < ObjectEndPos.x &&
	Self_TR_Pos.y > ObjectEndPos.y && Self_TR_Pos.y < ObjectStartPos.y)//Top Right Corner
	{
	return true;
	}

	if (Self_BR_Pos.x > ObjectStartPos.x && Self_BR_Pos.x < ObjectEndPos.x &&
		Self_BR_Pos.y > ObjectEndPos.y && Self_BR_Pos.y < ObjectStartPos.y)//Bottom Right Corner
	{
		return true;
	}

	/*if (Self_BL_Pos.x > ObjectStartPos.x && Self_BL_Pos.x < ObjectEndPos.x &&
		Self_BL_Pos.y > ObjectEndPos.y && Self_BL_Pos.y < ObjectStartPos.y)//Bottom Left Corner
	{
		return true;
	}*/

	return false;
}

bool GameObject::CollideOnLeft(XMFLOAT2 Self_TL_Pos_, XMFLOAT2 Self_BR_Pos_,
	XMFLOAT2 Object_TL_Pos_, XMFLOAT2 Object_BR_Pos_)
{
	XMFLOAT2 Self_TL_Pos = Self_TL_Pos_;
	XMFLOAT2 Self_TR_Pos = { Self_BR_Pos_.x, Self_TL_Pos_.y };
	XMFLOAT2 Self_BR_Pos = Self_BR_Pos_;
	XMFLOAT2 Self_BL_Pos = { Self_TL_Pos_.x, Self_BR_Pos_.y };
	XMFLOAT2 ObjectStartPos = Object_TL_Pos_;
	XMFLOAT2 ObjectEndPos = Object_BR_Pos_;
	Self_TL_Pos.x -= 2;
	//Self_BR_Pos.x += 0.5;
	//Self_TR_Pos.x += 0.5;
	Self_BL_Pos.x -= 2;

	if (Self_TL_Pos.x > ObjectStartPos.x && Self_TL_Pos.x < ObjectEndPos.x &&
	Self_TL_Pos.y > ObjectEndPos.y && Self_TL_Pos.y < ObjectStartPos.y)//Top Left Corner
	{
		return true;
	}

	/*if (Self_TR_Pos.x > ObjectStartPos.x && Self_TR_Pos.x < ObjectEndPos.x &&
		Self_TR_Pos.y > ObjectEndPos.y && Self_TR_Pos.y < ObjectStartPos.y)//Top Right Corner
	{
		return true;
	}

	if (Self_BR_Pos.x > ObjectStartPos.x && Self_BR_Pos.x < ObjectEndPos.x &&
		Self_BR_Pos.y > ObjectEndPos.y && Self_BR_Pos.y < ObjectStartPos.y)//Bottom Right Corner
	{
		return true;
	}*/

	if (Self_BL_Pos.x > ObjectStartPos.x && Self_BL_Pos.x < ObjectEndPos.x &&
	Self_BL_Pos.y > ObjectEndPos.y && Self_BL_Pos.y < ObjectStartPos.y)//Bottom Left Corner
	{
	return true;
	}

	return false;
}

void GameObject::SetPosition(XMFLOAT3& position)
{
	position_ = position;
}

void GameObject::SetRotation(float rotation)
{
	rotation_ = rotation;
}

void GameObject::SetScale(XMFLOAT2& scale)
{
	scale_ = scale;
}

void GameObject::SetBuffer(ID3D11Buffer& VertexBuffer, int i)
{
	//VertexBuffer_.push_back(&VertexBuffer);
	VertexBuffer_[i] = { &VertexBuffer };
}

void GameObject::SetColorMap(ID3D11ShaderResourceView& ColorMap, int i)
{
	//ColorMap_.push_back(&ColorMap);
	ColorMap_[i] = { &ColorMap };
}

void GameObject::SetScale(XMFLOAT2 Scale)
{
	scale_ = Scale;
}

void GameObject::Shutdown()
{

	{/*Clear Data*/ }

	{/*Clear Buffer Data*/}
	{
		for (int i = 0; i < NumBuffers_; i++)
		{
			if (VertexBuffer_[i]) { VertexBuffer_[i]->Release(); }
			VertexBuffer_[i] = 0;
		}
		
		VertexBuffer_.clear();
	}

	{/*Clear ColourMap Data*/ }
	{
		for (int i = 0; i < NumColorMap_; i++)
		{
			if (ColorMap_[i]) { ColorMap_[i]->Release(); }
			ColorMap_[i] = 0;
		}

		ColorMap_.clear();
		ColorMapFile_.clear();
	}
}








