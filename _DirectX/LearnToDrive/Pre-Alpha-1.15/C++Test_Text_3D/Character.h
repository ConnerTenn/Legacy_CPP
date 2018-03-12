
/*
Beginning DirectX 11 Game Programming
By Allen Sherrod and Wendy Jones

Sprite1 - Used to represent a 2D sprite's transformation.
*/


#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include<xnamath.h>
#include"RigidBody.h"
#include"Wall.h"
//#include"Level1.h"


class Character : public RigidBody
{
protected:
	double VelosityX_;
	double VelosityY_;
	bool OnGround_ = false;
	double FallSpeed = -4;
	string TexState = "Right";
public:
	Character(XMFLOAT3 Pos, XMFLOAT2 StartPos, XMFLOAT2 EndPos, vector<string> ColorMap,
		int NumBuffers, int NumColorMap);

	bool GetGroundState();
	string GetTexState();
	XMFLOAT2 GetVelosity();
	double GetFallSpeed();
	double GetVelosityX();
	double GetVelosityY();

	void MoveAngle(double Angle, float Amount);//Move the Character
	void Move();// double MoveX, double MoveY);//Move the Character
	void Fall(float dt, vector<Wall> &WallList);
	void AddVelosity(double X, double Y);
	void SetVelosity(double X, double Y);
	void SetVelosityY(double Y);
	void SetVelosityX(double X);
	void SetFallSpeed(double Speed);
	void SetTexState(string State);
	void SetGroundState(bool OnGround);
};

#endif