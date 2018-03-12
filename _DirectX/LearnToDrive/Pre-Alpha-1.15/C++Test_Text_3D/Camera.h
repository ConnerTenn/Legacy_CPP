
/*
Beginning DirectX 11 Game Programming
By Allen Sherrod and Wendy Jones

Sprite1 - Used to represent a 2D sprite's transformation.
*/


#ifndef _CAMERA_H_
#define _CAMERA_H_

#include<xnamath.h>


class Camera
{
private:
	XMFLOAT3 position_;
	XMFLOAT3 target_;
	XMFLOAT3 up_;
	XMFLOAT2 Direct;

public:
	Camera();
	Camera(XMFLOAT3 pos, XMFLOAT3 target);

	XMMATRIX GetViewMatrix();
	XMFLOAT3 GetPosition();

	void Move(float Angle, float Amount);//Move the camera
	void SetPosition(XMFLOAT3 pos);
};

#endif