
/*
Beginning DirectX 11 Game Programming
By Allen Sherrod and Wendy Jones

Sprite1 - Used to represent a 2D sprite's transformation.
*/


#ifndef _RIGID_BODY_H_
#define _RIGID_BODY_H_

#include<xnamath.h>
#include"GameObject.h"


class RigidBody : public GameObject
{
protected:
public:
	RigidBody(XMFLOAT3 Pos, XMFLOAT2 StartPos, XMFLOAT2 EndPos, vector<string> ColorMap,
		int NumBuffers, int NumColorMap);
};

#endif