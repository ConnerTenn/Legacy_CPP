
#ifndef _KEYHANDLER_
#define _KEYHANDLER_

#include <iostream>
#include <string>
//#include <Windows.h>
#include <vector>

#include "Map.h"

//using namespace std;


//std::vector<float> PWMRange = { -100, 100 };
std::vector<float> PWMRangeDrive = { 85, 45 };
std::vector<float> PWMRangeArm = { 50, 110 };
float PWMMidDrive = (PWMRangeDrive[0] + PWMRangeDrive[1]) / 2.0;
float PWMMidArm = (PWMRangeArm[0] + PWMRangeArm[1]) / 2.0;

class KeyHandler
{
private:
	uint8_t ID;
	float PWM;
	bool Gpio = false;
	//float Value;
	int _Key1;
	int _Key2;
	bool _Key1Pressed = false;
	bool _Key2Pressed = false;

	uint8_t SendBuffer[2];

public:
	KeyHandler(int Key1, int Key2, float pwm, uint8_t Id)
	{
		_Key1 = Key1;
		_Key2 = Key2;
		PWM = pwm;
		//Value = value;
		ID = Id;
	}
	KeyHandler(int Key1, bool gpio, uint8_t Id)
	{
		_Key1 = Key1;
		Gpio = gpio;
		//Value = value;
		ID = Id;
	}
	/*KeyHandler(int Key1, int Key2, bool gpio, uint8_t Id)
	{
		_Key1 = Key1;
		_Key2 = Key2;
		Gpio = gpio;
		//Value = value;
		ID = Id;
	}*/

	void Update(float Speed, std::vector<float> Range = PWMRangeDrive)
	{
		_Key1Pressed = GetAsyncKeyState(_Key1);
		_Key2Pressed = GetAsyncKeyState(_Key2);

		if (_Key1Pressed && !_Key2Pressed)
		{
			//PWM = Map({ 0, 100 }, PWMRange, 50.0 + 50.0 * (Speed / 100.0));
			//Value = 50.0 + 50.0 * (Speed / 100.0);
			PWM = Map({ 0, 100 }, Range, 50.0 + 50.0 * (Speed / 100.0));
		}
		else if (_Key2Pressed && !_Key1Pressed)
		{
			//PWM = Map({ 0, 100 }, PWMRange, 50.0 - 50.0 * (Speed / 100.0));
			//Value = 50.0 - 50.0 * (Speed / 100.0);
			PWM = Map({ 0, 100 }, Range, 50.0 - 50.0 * (Speed / 100.0));
		}
		else
		{
			//PWM = PWMMid;
			//Value = 50.0;
			PWM = Map({ 0, 100 }, Range, 50);
		}
	}

	void UpdatePush()
	{
		_Key1Pressed = GetAsyncKeyState(_Key1);

		if (_Key1Pressed)
		{
			Gpio = true;
		}
		else
		{
			Gpio = false;
		}
	}

	void UpdateFlip()
	{
		if (GetAsyncKeyState(_Key1) && !_Key1Pressed)
		{
			if (Gpio) { Gpio = false; }
			else if (!Gpio) { Gpio = true; }
			_Key1Pressed = true;
		}
		if (!GetAsyncKeyState(_Key1))
		{
			_Key1Pressed = false;
		}
	}

	float GetPwm()
	{
		return PWM;
	}

	bool GetGpio()
	{
		return Gpio;
	}

	void SendPwm(SOCKET *ConnectionSocket)
	{
		/*std::string SendBuffer = "12";
		SendBuffer[0] = ID[0];
		SendBuffer[1] = ID[1];
		std::string value = std::to_string(int(PWM));
		std::string buf = "";
		if (int(PWM) < 1000)
		{
			buf += "0";
		}
		if (int(PWM) < 100)
		{
			buf += "0";
		}
		SendBuffer = SendBuffer + buf + value;
		send(*ConnectionSocket, SendBuffer.c_str(), 6, 0);*/
		
		SendBuffer[0] = ID;
		SendBuffer[1] = uint8_t(PWM);
		send(*ConnectionSocket, (const char *)SendBuffer, 2, 0);
	}
	void SendGpio(SOCKET *ConnectionSocket)
	{
		SendBuffer[0] = ID + 100;
		SendBuffer[1] = uint8_t(Gpio);
		send(*ConnectionSocket, (const char *)SendBuffer, 2, 0);
	}
};


#endif


