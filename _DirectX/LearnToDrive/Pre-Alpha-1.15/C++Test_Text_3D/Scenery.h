
/*
Beginning DirectX 11 Game Programming
By Allen Sherrod and Wendy Jones

Sprite1 - Used to represent a 2D sprite's transformation.
*/


#ifndef _SCENERY_H_
#define _SCENERY_H_

#include<xnamath.h>
#include"GameObject.h"


class Scenery : public GameObject
{
protected:
public:
	Scenery(XMFLOAT3 Pos, XMFLOAT2 StartPos, XMFLOAT2 EndPos, vector<string> ColorMap, 
		int NumBuffers, int NumColorMap);
};

#endif