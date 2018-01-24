
/*
Beginning DirectX 11 Game Programming
By Allen Sherrod and Wendy Jones

Sprite1 - Used to represent a 2D sprite's transformation.
*/


#ifndef _PLAYER_H_
#define _PLAYER_H_

#include<xnamath.h>
#include"Character.h"


class Player : public Character //Add Game Object Constructor
{
protected:
public:
	Player(XMFLOAT3 Pos, XMFLOAT2 StartPos, XMFLOAT2 EndPos, vector<string> ColorMap,
		int NumBuffers, int NumColorMap);
};

#endif