// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <curses.h>
#include <vector>
#include <map>
#include <time.h>

#include "Map.h"
#include "KeyHandler.h"

#pragma comment(lib, "ws2_32.lib")

//using namespace std;


WSADATA Wsdata;
SOCKET ConnectionSocket;
struct addrinfo *server, client;
//struct addrinfo *server;
//struct addrinfo client;
//char SendBuffer[5];
uint8_t SendBuffer[2];
//char* port = "366";
char* port = "666";
//char* ip = "192.168.0.10";
char* ip = "192.168.42.1";


enum KeyCode
{
	K_a = 0x41,
	K_b = 0x42,
	K_c = 0x43,
	K_d = 0x44,
	K_e = 0x45,
	K_f = 0x46,
	K_g = 0x47,
	K_h = 0x48,
	K_i = 0x49,
	K_j = 0x4A,
	K_k = 0x4B,
	K_l = 0x4C,
	K_m = 0x4D,
	K_n = 0x4E,
	K_o = 0x4F,
	K_p = 0x50,
	K_q = 0x51,
	K_r = 0x52,
	K_s = 0x53,
	K_t = 0x54,
	K_u = 0x55,
	K_v = 0x56,
	K_w = 0x57,
	K_x = 0x58,
	K_y = 0x59,
	K_z = 0x5A
};

std::map<int, bool> Keys = { };
std::vector<int> Keys2;

void UpdateKeys()
{
	for (auto& Key : Keys)
	{
		Key.second = GetAsyncKeyState(Key.first) < 0 ? true : false;
	}
}

template <class T>
const char * ToString(T In)
{
	return &*to_string(In).c_str();
}

void NetInit()
{
	WSAStartup(MAKEWORD(2, 2), &Wsdata);
	printw("SYSTEM::Connecting...");
	refresh();

	client.ai_family = AF_INET;
	client.ai_socktype = SOCK_STREAM;
	client.ai_protocol = IPPROTO_TCP;

	getaddrinfo(ip, port, &client, &server);

	ConnectionSocket = socket(server->ai_family, server->ai_socktype, server->ai_protocol);

	if (connect(ConnectionSocket, server->ai_addr, server->ai_addrlen) == SOCKET_ERROR)
	{
		printw("ERROR:: Error Connecting to address.\n");
		//printw("Error:%s", WSAGetLastError());
		refresh();
		WSACleanup();
		//NetInit();
		exit(0);
	}
}

void OnClose();

void main()
{
	initscr();
	(void)echo();
	clock_t t1;
	int Delta = 0;

	NetInit();
	atexit(OnClose);

	int DriveSpeed = 20;
	float DriveSpeedModifierWait = 0;
	float DriveSpeedModifierWaitMax = 50;
	int ArmSpeed = 100;
	float ArmSpeedModifierWait = 0;
	float ArmSpeedModifierWaitMax = 50;
	std::string DriveSpeedBar = "";
	std::string ArmSpeedBar = "";

	//DriveXaxis
	//DriveYaxis
	//ArmExtend
	//WristPitch
	//Claw
	//ArmPitch

	//vector<float> PWMRange = { -100, 100 };
	//float PWMMid = (PWMRange[0] + PWMRange[1]) / 2.0;

	KeyHandler DriveXAxis(KeyCode::K_d, KeyCode::K_a, PWMMidDrive, 00);
	//KeyHandler DriveYAxis(KeyCode::K_w, KeyCode::K_s, 50.0, "01");
	KeyHandler DriveYAxis(KeyCode::K_w, KeyCode::K_s, PWMMidDrive, 01);
	//KeyHandler DriveYAxis(KeyCode::K_w, KeyCode::K_s, 50.0, "01");

	//Arm Rotation
	KeyHandler ArmRotation(KeyCode::K_f, KeyCode::K_h, PWMMidArm, 02);
	//Claw Rotation
	KeyHandler ClawRotation(KeyCode::K_j, KeyCode::K_l, PWMMidArm, 03);
	//Claw Grip
	KeyHandler ClawGrip(KeyCode::K_o, KeyCode::K_u, PWMMidArm, 04);
	//Claw Pivot
	KeyHandler ClawPivot(KeyCode::K_k, KeyCode::K_i, PWMMidArm, 05);
	//Arm ExtensionB
	KeyHandler ArmExtension(KeyCode::K_y, KeyCode::K_r, PWMMidArm, 06);
	//Arm Pivot
	KeyHandler ArmPivot(KeyCode::K_t, KeyCode::K_g, PWMMidArm, 07);

	//test
	KeyHandler TestA(KeyCode::K_v, false, 01);
	KeyHandler TestB(KeyCode::K_b, false, 02);

	//float DriveXaxisPWM = Map({ 0, 100 }, PWMRange, 50);
	//float DriveYaxisPWM = Map({ 0, 100 }, PWMRange, 50);

	//float ArmXaxisPWM = Map({ 0, 100 }, PWMRange, 50);
	//float ArmYaxisPWM = Map({ 0, 100 }, PWMRange, 50);
	//float ArmZaxisPWM = Map({ 0, 100 }, PWMRange, 50);
	//float ArmRotationPWM = Map({ 0, 100 }, PWMRange, 50);
	//float ArmGrip = Map({ 0, 10 }, PWMRange, 50);

	/*
	Drive Speed Increace: X
	Drive Speed Decreace: Z

	Arm Speed Increace: M
	Arm Speed Decreace: N
	*/

	bool Run = true;
	while (Run)
	{ 
		t1 = clock();
		if (GetFocus() == NULL)
		{
			UpdateKeys();

			{/*Graphics*/}
			{
				clear();
				printw("==========================\n");
				printw("|      Robot Status      |\n");
				printw("==========================\n");
				printw("\n");
				printw("Drive Speed: %s%", std::to_string(DriveSpeed).c_str());
				printw("  \t%s\n", DriveSpeedBar.c_str());
				printw("Arm Speed: %s", std::to_string(ArmSpeed).c_str());
				printw("    \t%s\n", ArmSpeedBar.c_str());
				//printw("Drive X Axis PWM: %s%\n", to_string(DriveXaxisPWM).c_str());
				//printw("Drive Y Axis PWM: %s%\n", to_string(DriveYaxisPWM).c_str());
				printw("Drive X Axis PWM: %s%\n", std::to_string(DriveXAxis.GetPwm()).c_str());
				printw("Drive Y Axis PWM: %s%\n", std::to_string(DriveYAxis.GetPwm()).c_str());
				printw("\n");
				printw("ArmRotation PWM: %s%\n", std::to_string(ArmRotation.GetPwm()).c_str());
				printw("ClawRotation PWM: %s%\n", std::to_string(ClawRotation.GetPwm()).c_str());
				printw("ClawSlider PWM: %s%\n", std::to_string(ClawGrip.GetPwm()).c_str());
				printw("ClawPivot PWM: %s%\n", std::to_string(ClawPivot.GetPwm()).c_str());
				printw("ArmExtension PWM: %s%\n", std::to_string(ArmExtension.GetPwm()).c_str());
				printw("ArmPivot PWM: %s%\n", std::to_string(ArmPivot.GetPwm()).c_str());
				printw("TestA Push Button: %s%\n", std::to_string(TestA.GetGpio()).c_str());
				printw("TestB Push Button: %s%\n", std::to_string(TestB.GetGpio()).c_str());
				printw("\n");
				printw("Delta Time: %s%\n", std::to_string(Delta).c_str());

				int Size1 = Map({ 0, 100 }, { 0, 25 }, DriveSpeed);
				DriveSpeedBar = "|" + std::string(Size1, '=') + std::string(25 - Size1, ' ') + "|";
				int Size2 = Map({ 0, 100 }, { 0, 25 }, ArmSpeed);
				ArmSpeedBar = "|" + std::string(Size2, '=') + std::string(25 - Size2, ' ') + "|";
			}

			{/*Modifiers*/}
			{
				DriveSpeedModifierWait -= Delta;
				if (DriveSpeedModifierWait < 0) { DriveSpeedModifierWait = 0; }
				if (Keys[KeyCode::K_z] && DriveSpeedModifierWait == 0) { DriveSpeed -= 2; DriveSpeedModifierWait = DriveSpeedModifierWaitMax; }
				else if (Keys[KeyCode::K_x] && DriveSpeedModifierWait == 0) { DriveSpeed += 2; DriveSpeedModifierWait = DriveSpeedModifierWaitMax; }
				if (DriveSpeed < 0) { DriveSpeed = 0; } if (DriveSpeed > 100) { DriveSpeed = 100; }

				ArmSpeedModifierWait -= Delta;
				if (ArmSpeedModifierWait < 0) { ArmSpeedModifierWait = 0; }
				if (Keys[KeyCode::K_n] && ArmSpeedModifierWait == 0) { ArmSpeed -= 2; ArmSpeedModifierWait = ArmSpeedModifierWaitMax; }
				else if (Keys[KeyCode::K_m] && ArmSpeedModifierWait == 0) { ArmSpeed += 2; ArmSpeedModifierWait = ArmSpeedModifierWaitMax; }
				if (ArmSpeed < 0) { ArmSpeed = 0; } if (ArmSpeed > 100) { ArmSpeed = 100; }
			}

			{/*Drive Controlls*/}
			{
				DriveXAxis.Update(DriveSpeed, {85, 45});
				DriveYAxis.Update(DriveSpeed, {80, 40});
				/*if (Keys[KeyCode::K_d] && !Keys[KeyCode::K_a])
				{
					DriveXaxisPWM = Map({ 0, 100 }, PWMRange, 50.0 + 50.0 * (DriveSpeed / 100.0));
				}
				else if (Keys[KeyCode::K_a] && !Keys[KeyCode::K_d])
				{
					DriveXaxisPWM = Map({ 0, 100 }, PWMRange, 50.0 - 50.0 * (DriveSpeed / 100.0));
				}
				else
				{
					DriveXaxisPWM = PWMMid;
				}

				if (Keys[KeyCode::K_w] && !Keys[KeyCode::K_s])
				{
					DriveYaxisPWM = Map({ 0, 100 }, PWMRange, 50.0 + 50.0 * (DriveSpeed / 100.0));
				}
				else if (Keys[KeyCode::K_s] && !Keys[KeyCode::K_w])
				{
					DriveYaxisPWM = Map({ 0, 100 }, PWMRange, 50.0 - 50.0 * (DriveSpeed / 100.0));
				}
				else
				{
					DriveYaxisPWM = PWMMid;
				}*/
			}

			{/*Arm Controlls*/}
			{
				ArmRotation.Update(3.0*ArmSpeed/3.0, PWMRangeArm);
				ClawRotation.Update(ArmSpeed, PWMRangeArm);
				ClawGrip.Update(ArmSpeed, PWMRangeArm);
				ClawPivot.Update(ArmSpeed, PWMRangeArm);
				ArmExtension.Update(ArmSpeed, PWMRangeArm);
				ArmPivot.Update(ArmSpeed, PWMRangeArm);

				TestA.UpdatePush();
				TestB.UpdatePush();
				//Slide in out
				//up and down
				//3 for hand; left/right, rotate up/down, rotate left/right
				//claw

				//_ & _ for slide in & out          Z
				//J & L for slide left & right      X
				//_ & _ for slide up & down         Y
				//I & K for rotate up and down      
				//U & O for rotate left and right   
				//p claw grip toggle

			}

			{/*Send Data*/} 
			{
				//SendBuffer = "123456";
				//SendBuffer[0] = '1';
				//SendBuffer[1] = '2';
				//SendBuffer[2] = '3';
				//SendBuffer[3] = '4';
				//SendBuffer[4] = '5';
				////SendBuffer = "12345";
				//send(ConnectionSocket, SendBuffer.c_str(), 6, 0);
				DriveXAxis.SendPwm(&ConnectionSocket);
				DriveYAxis.SendPwm(&ConnectionSocket);
				ArmRotation.SendPwm(&ConnectionSocket);
				ClawRotation.SendPwm(&ConnectionSocket);
				ClawGrip.SendPwm(&ConnectionSocket);
				ClawPivot.SendPwm(&ConnectionSocket);
				ArmExtension.SendPwm(&ConnectionSocket);
				ArmPivot.SendPwm(&ConnectionSocket);

				TestA.SendGpio(&ConnectionSocket);
				TestB.SendGpio(&ConnectionSocket);
			}

			Sleep(10);
			refresh();

			if (Keys[VK_ESCAPE]) { Run = false; }
		}
		Delta = static_cast<int>(clock() - t1);
	}
}


void OnClose()
{
	closesocket(ConnectionSocket);
	WSACleanup();
}

