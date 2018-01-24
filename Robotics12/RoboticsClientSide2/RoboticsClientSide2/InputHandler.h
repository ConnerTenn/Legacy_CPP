
#pragma once

#include "Map.h"
#include <Windows.h>


class InputHandler
{
private:
	UINT JoyID;
	int Trigger1;
	int Trigger2;
	std::vector<float> Range;
	int Type;
	uint8_t ID;
	DWORD Value = 0;
	uint8_t SendBuffer[2];

public:
	InputHandler(UINT joyID, int trigger1, int trigger2, std::vector<float> range, int type, uint8_t id)
	{
		JoyID = joyID;
		Trigger1 = trigger1-1;
		Trigger2 = trigger2-1;
		Range = range;
		Type = type;
		ID = id;
	}

	void Update(JOYINFOEX &dataEx)
	{
		if (Type == 0)
		{
			//Trigger: 
			//0: JOY_RETURNX   (0x01)
			//1: JOY_RETURNY   (0x02)
			//2: JOY_RETURNZ   (0x04)
			DWORD data;
			if (Trigger1 == 0) { data = dataEx.dwXpos; }
			else if (Trigger1 == 1) { data = dataEx.dwYpos; }
			else if (Trigger1 == 2) { data = dataEx.dwZpos; }
			else { data = -1; }
			if (dataEx.dwFlags & DWORD(pow(2, Trigger1)) == DWORD(pow(2, Trigger1))) { Value = Map({ 0, 65535 }, Range, data); }
		}
		else if (Type == 1)
		{
			//Trigger: 
			//0: JOY_BUTTON1   (0x01)
			//1: JOY_BUTTON2   (0x02)
			//2: JOY_BUTTON3   (0x04)
			//3: JOY_BUTTON4   (0x08)
			//...
			if (dataEx.dwButtons & DWORD(pow(2, Trigger1))) { Value = Range[0]; } else { Value = Range[1]; }
		}
		else if (Type == 2)
		{
			//Trigger: 
			//0: JOY_BUTTON1   (0x01)
			//1: JOY_BUTTON2   (0x02)
			//2: JOY_BUTTON3   (0x04)
			//3: JOY_BUTTON4   (0x08)
			//...
			Value = (Range[0] + Range[1]) / 2;
			bool trigger1 = false;
			bool trigger2 = false;
			if (dataEx.dwButtons & DWORD(pow(2, Trigger1))) { Value = Range[0]; trigger1 = true; }
			if (dataEx.dwButtons & DWORD(pow(2, Trigger2))) { Value = Range[1]; trigger2 = true; }
			if (trigger1 && trigger2) { Value = (Range[0] + Range[1]) / 2; }
		}
	}

	DWORD GetValue()
	{
		return Value;
	}
	UINT GetJoyID()
	{
		return JoyID;
	}

	void Send(SOCKET *ConnectionSocket)
	{
		uint8_t data = Value;
		if (Type == 0)
		{
			uint8_t data = Value;
			SendBuffer[0] = ID;
			SendBuffer[1] = uint8_t(data);
			send(*ConnectionSocket, (const char *)SendBuffer, 2, 0);
		}
		else if (Type == 1)
		{
			uint8_t data = Value;
			SendBuffer[0] = ID + 100;
			SendBuffer[1] = uint8_t(data);
			send(*ConnectionSocket, (const char *)SendBuffer, 2, 0);
		}
		else if (Type == 2)
		{
			uint8_t data = Value;
			SendBuffer[0] = ID;
			SendBuffer[1] = uint8_t(data);
			send(*ConnectionSocket, (const char *)SendBuffer, 2, 0);
		}
		else if (Type == 3)
		{
			uint8_t data = Value;
			SendBuffer[0] = ID;
			SendBuffer[1] = uint8_t(data);
			send(*ConnectionSocket, (const char *)SendBuffer, 2, 0);
		}
	}
};
