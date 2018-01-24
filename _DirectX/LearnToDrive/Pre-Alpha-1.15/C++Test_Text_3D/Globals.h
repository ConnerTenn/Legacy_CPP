
/*
Beginning DirectX 11 Game Programming
By Allen Sherrod and Wendy Jones

Sprite1 - Used to represent a 2D sprite's transformation.
*/


#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include<xnamath.h>
#include<d3d11.h>
#include<d3dx11.h>
#include<DxErr.h>

#include<Windows.h>
#include<memory>

#include<time.h>

#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
//#include <unordered_map>
#include <vector>
//#include"Level1.h"

#define DBOUT( s )								\
{												\
	std::wostringstream os_;					\
	os_ << s;									\
	OutputDebugStringW(os_.str().c_str());		\
}

#define PI 3.14159265358979323
#define TAU 6.2831853071795864769

struct VertexPos
{
	XMFLOAT3 pos;
	XMFLOAT2 tex0;
};

//Level1 demo;
const float Width = 960;
const float Height = 540;
const float Pixel_Size = 2;//# of screen pixels wide 1 game pixel is
const float MaxScreenSpeed = 0.2f;
const enum SpriteOrder
{
	Text_Z = 100,
	TextBackground_Z = 200,
	Wall_Z = 300,
	Player_Z = 400,
	Scenery_Z = 500,
};

const int MaxCharacters = 150;
const XMFLOAT2 TextBoxPos = { 0, 150 };
const int indexA = static_cast<char>('A');
const int indexZ = static_cast<char>('Z');

const int indexa = static_cast<char>('a');
const int indexz = static_cast<char>('z');

//void Print(char Text);
//vector<Wall> WallList;

const float FontMapWidth = 279.0f;
const std::map<std::string, std::vector<int>> StringCodes =
{
	{ "A", { 1, 6 } },//			A
	{ "B", { 7, 12 } },//			B
	{ "C", { 13, 18 } },//			C
	{ "D", { 19, 24 } },//			D
	{ "E", { 25, 30 } },//			E
	{ "F", { 31, 36 } },//			F
	{ "G", { 37, 42 } },//			G
	{ "H", { 43, 48 } },//			H
	{ "I", { 49, 52 } },//			I
	{ "J", { 53, 58 } },//			J
	{ "K", { 59, 63 } },//			K
	{ "L", { 64, 68 } },//			L
	{ "M", { 69, 74 } },//			M
	{ "N", { 75, 80 } },//			N
	{ "O", { 81, 86 } },//			O
	{ "P", { 87, 92 } },//			P
	{ "Q", { 93, 98 } },//			Q
	{ "R", { 99, 104 } },//			R
	{ "S", { 105, 110 } },//		S
	{ "T", { 111, 116 } },//		T
	{ "U", { 117, 122 } },//		U
	{ "V", { 123, 128 } },//		V
	{ "W", { 129, 134 } },//		W
	{ "X", { 135, 140 } },//		X
	{ "Y", { 141, 146 } },//		Y
	{ "Z", { 147, 152 } },//		Z
	{ "0", { 153, 157 } },//		0
	{ "1", { 158, 161 } },//		1
	{ "2", { 162, 166 } },//		2
	{ "3", { 167, 171 } },//		3
	{ "4", { 172, 176 } },//		4
	{ "5", { 177, 181 } },//		5
	{ "6", { 182, 186 } },//		6
	{ "7", { 187, 191 } },//		7
	{ "8", { 192, 196 } },//		8
	{ "9", { 197, 201 } },//		9				''
	{ ".", { 217, 218 } },//		.
	{ "?", { 255, 260 } },//		?
	{ "!", { 221, 222 } },//		!
	{ "'", { 211, 212 } },//		'
	{ ",", { 208, 210 } },//		,
	{ "#", { 261, 266 } },//		,
	{ "-", { 267, 272 } },//		,
	{ "|", { 273, 274 } },//		,

	{ "<00>", { 278, 276 } },//		NO GAP
	{ "<01>", { 278, 277 } },//		NEW LINE
	{ "<02>", { 277, 277 } },//		SLIM GAP
	{ " ", { 275, 278 } },//		SPACE

	{ "", { 275, 278 } }//				OTHER
};

const enum KeyCodes
{
	A_ = 0x41,
	B_ = 0x42,
	C_ = 0x43,
	D_ = 0x44,
	E_ = 0x45,
	F_ = 0x46,
	G_ = 0x47,
	H_ = 0x48,
	I_ = 0x49,
	J_ = 0x4A,
	K_ = 0x4B,
	L_ = 0x4C,
	M_ = 0x4D,
	N_ = 0x4E,
	O_ = 0x4F,
	P_ = 0x50,
	Q_ = 0x51,
	R_ = 0x52,
	S_ = 0x53,
	T_ = 0x54,
	U_ = 0x55,
	V_ = 0x56,
	W_ = 0x57,
	X_ = 0x58,
	Y_ = 0x59,
	Z_ = 0x5A,
	_0_ = 0x30,
	_1_ = 0x31,
	_2_ = 0x32,
	_3_ = 0x33,
	_4_ = 0x34,
	_5_ = 0x35,
	_6_ = 0x36,
	_7_ = 0x37,
	_8_ = 0x38,
	_9_ = 0x39
};


#endif