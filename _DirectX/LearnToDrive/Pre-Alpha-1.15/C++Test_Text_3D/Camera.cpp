
/*
Beginning DirectX 11 Game Programming
By Allen Sherrod and Wendy Jones

LookAtCamera - Demonstrates a simple target camera.
*/


#include<d3d11.h>
#include<d3dx11.h>
#include"Camera.h"
#include<math.h>


Camera::Camera() : 
position_(XMFLOAT3(0.0f, 0.0f, 0.0f)), target_(XMFLOAT3(0.0f, 0.0f, 0.0f)), 
up_(XMFLOAT3(0.0f, 1.0f, 0.0f)), Direct({0,0})
{

}


Camera::Camera(XMFLOAT3 pos, XMFLOAT3 target) :
position_(pos), target_(target), up_(XMFLOAT3(0.0f, 1.0f, 0.0f)), Direct({ 0, 0 })
{

}

XMMATRIX Camera::GetViewMatrix()
{
	XMMATRIX viewMat = XMMatrixLookAtLH(XMLoadFloat3(&position_),
		XMLoadFloat3(&target_), XMLoadFloat3(&up_));

	return viewMat;
}

XMFLOAT3 Camera::GetPosition()
{
	return position_;
}


void Camera::SetPosition(XMFLOAT3 pos)
{
	position_ = pos;
	target_ = pos;
	target_.z++;
}

void Camera::Move(float Angle, float Amount)
{
	float MoveX = sin(Angle) * Amount;
	float MoveY = cos(Angle) * Amount;

	XMFLOAT3 spritePos(position_.x + MoveX, position_.y + MoveY, position_.z);
	SetPosition(spritePos);

}