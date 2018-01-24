

#include<d3d11.h>
#include<d3dx11.h>
#include<math.h>
#include"Character.h"

Character::Character(XMFLOAT3 Pos = { 0.0f, 0.0f, 0.0f }, XMFLOAT2 StartPos = { 0, 0 }, 
	XMFLOAT2 EndPos = { 0, 0 }, vector<string> ColorMap = { "MissingTexture.png" },
	int NumBuffers = 1, int NumColorMap = 1)
:RigidBody(Pos, StartPos, EndPos, ColorMap, NumBuffers, NumColorMap)
{

}

bool Character::GetGroundState()
{
	return OnGround_;
}

string Character::GetTexState()
{
	return TexState;
}

XMFLOAT2 Character::GetVelosity()
{
	XMFLOAT2 Velosity = { static_cast<float>(VelosityX_), static_cast<float>(VelosityY_) };
	return Velosity;
}

double Character::GetFallSpeed()
{
	return FallSpeed;
}

double Character::GetVelosityX()
{
	return VelosityX_;
}

double Character::GetVelosityY()
{
	return VelosityY_;
}


void Character::MoveAngle(double Angle, float Amount)
{
	double VelosityX = sin(Angle) * Amount;
	double VelosityY = cos(Angle) * Amount;

	XMFLOAT3 spritePos(position_.x + static_cast<float>(VelosityX), position_.y + static_cast<float>(VelosityY), position_.z);
	SetPosition(spritePos);

}

void Character::Move()//double MoveX, double MoveY)
{
	XMFLOAT3 spritePos(position_.x + static_cast<float>(VelosityX_), position_.y + static_cast<float>(VelosityY_), position_.z);
	SetPosition(spritePos);
}

void Character::AddVelosity(double X, double Y)
{
	VelosityX_ += X;
	VelosityY_ += Y;

	//if (VelosityY_ >= 300 * 0.012) { VelosityY_ = 300 * 0.012; }
	//if (VelosityY_ <= -300 * 0.012) { VelosityY_ = -300 * 0.012; }
}

void Character::SetVelosity(double X, double Y)
{
	VelosityX_ = X;
	VelosityY_ = Y;

	//if (VelosityY_ > 300 * 0.012) { VelosityY_ = 300 * 0.012; }
	//if (VelosityY_ < -300 * 0.012) { VelosityY_ = -300 * 0.012; }
}

void Character::SetVelosityX(double X)
{
	VelosityX_ = X;
}

void Character::SetVelosityY(double Y)
{
	VelosityY_ = Y;

	//if (VelosityY_ > 300 * 0.012) { VelosityY_ = 300 * 0.012; }
	//if (VelosityY_ < -300 * 0.012) { VelosityY_ = -300 * 0.012; }
}

void Character::SetFallSpeed(double Speed)
{
	FallSpeed = Speed;
}

void Character::Fall(float dt, vector<Wall> &WallList)
{
	int a = 0;
	{
		///*
		//bool Collide = false;
		OnGround_ = false;
		Character *sprite = this;
		for (Wall &wall : WallList)
		{
			if (this->CollideOnBottom(this->Get_TL_Pos(), this->Get_BR_Pos(),
				wall.Get_TL_Pos(), wall.Get_BR_Pos()))
			{
				OnGround_ = true;
				this->MoveAngle(TAU, wall.Get_TL_Pos().y - this->Get_BR_Pos().y);
			}
		}

		if (!OnGround_)
		{
			//DBOUT("Flying" << "\n");
			this->AddVelosity(0.0 * dt, FallSpeed * dt);
			//PlayerList[a].MoveAngle(PI, Speed * dt);
		}
		else
		{
			this->SetVelosity(0.0, 0.0);
			//DBOUT("Grounded" << "\n");
		}
		//DBOUT("\n" << "\n");

		//
	}
}

void Character::SetTexState(string State)
{
	TexState = State;
}











