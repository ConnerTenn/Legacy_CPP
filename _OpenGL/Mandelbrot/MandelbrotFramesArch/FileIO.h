
#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#define BI_RGB 0L

struct BMPFileHeader
{
	uint16_t bfType;
	uint32_t bfSize;
	uint16_t bfReserved1;
	uint16_t bfReserved2;
	uint32_t bfOffBits;
};

struct BMPInfoHeader
{
	uint32_t biSize;
	uint32_t biWidth;
	uint32_t biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	uint32_t biXPelsPerMeter;
	uint32_t biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
};

void SaveImage(int width, int height, std::string filename, GLuint tex)
{
	char* buff = new char[width * height * 3];
	if (!buff) { return; }

	glBindTexture(GL_TEXTURE_2D, tex);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_BGR, GL_UNSIGNED_BYTE, (void *)buff);
	glBindTexture(GL_TEXTURE_2D, 0);

	//std::ofstream out; out.open(filename.c_str());
	//std::FILE *Out = fopen(filename.c_str(), "wb"); if (!Out) { return; }
	FILE *out;
	//int err = fopen_s(&out, filename.c_str(), "wb");
	out = fopen(filename.c_str(), "wb");
	//if (err != 0) { return; }

	//BITMAPFILEHEADER bitmapFileHeader;
	//BITMAPINFOHEADER bitmapInfoHeader;
	BMPFileHeader bitmapFileHeader;
	BMPInfoHeader bitmapInfoHeader;
	bitmapFileHeader.bfType = 0x4D42;
	bitmapFileHeader.bfSize = width*height * 3;
	bitmapFileHeader.bfReserved1 = 0;
	bitmapFileHeader.bfReserved2 = 0;
	bitmapFileHeader.bfOffBits = 14 + sizeof(BMPInfoHeader);

	bitmapInfoHeader.biSize = sizeof(BMPInfoHeader);
	bitmapInfoHeader.biWidth = width - 1;
	bitmapInfoHeader.biHeight = height - 1;
	bitmapInfoHeader.biPlanes = 1;
	bitmapInfoHeader.biBitCount = 24;
	bitmapInfoHeader.biCompression = BI_RGB;
	bitmapInfoHeader.biSizeImage = 0;
	bitmapInfoHeader.biXPelsPerMeter = 0; // ?
	bitmapInfoHeader.biYPelsPerMeter = 0; // ?
	bitmapInfoHeader.biClrUsed = 0;
	bitmapInfoHeader.biClrImportant = 0;

	//Workaround for alignment gap
	fwrite(&bitmapFileHeader, 2, 1, out);
	fwrite(&bitmapFileHeader.bfSize, 12, 1, out);
	fwrite(&bitmapInfoHeader, sizeof(BMPInfoHeader), 1, out);

	fwrite(buff, width*height * 3, 1, out);
	fclose(out);

	//out.write((char *)&bitmapFileHeader, sizeof(BITMAPFILEHEADER));
	//out.write((char *)&bitmapInfoHeader, sizeof(BITMAPFILEHEADER));
	//out.write((char *)buff, width*height * 3);
	//out.close();

	delete[] buff;
}

struct ShaderData
{
	//XPos,YPos,Scale,	MaxCount, Constant, Power,
	//					//base alignment	//aligned offset
	double Pos[2];		//16				//0
	double Scale;		//8					//16
	double Constant;	//8					//24
	int MaxCount;		//4					//32
	int Power;			//4					//36
	float AspectRatio;	//4					//40->43
};

std::vector<ShaderData> ReadPathFile()
{
	std::cout << "Reading From File\n";
	std::vector<ShaderData> out;
	std::ifstream pathFile;
	pathFile.open("Path.dat");

	pathFile.precision(std::numeric_limits<double>::max_digits10 + 2);
	
	std::string in;
	int pos;
	while (!pathFile.eof())
	{
		ShaderData data;
		std::getline(pathFile, in);

		if (in.length() > 0)
		{
			pos = int(in.find(" "));
			data.Pos[0] = std::stod(in.substr(0, pos));
			in.erase(0, pos + 1);

			pos = int(in.find(" "));
			data.Pos[1] = std::stod(in.substr(0, pos));
			in.erase(0, pos + 1);

			pos = int(in.find(" "));
			data.Scale = std::stod(in.substr(0, pos));
			in.erase(0, pos + 1);

			pos = int(in.find(" "));
			data.Constant = std::stod(in.substr(0, pos));
			in.erase(0, pos + 1);

			pos = int(in.find(" "));
			data.MaxCount = std::stoi(in.substr(0, pos));
			in.erase(0, pos + 1);

			pos = int(in.find(" "));
			data.Power = std::stoi(in.substr(0, pos));
			in.erase(0, pos + 1);

			out.push_back(data);
		}
	}

	pathFile.close();
	std::cout << "Done Reading From File\n";
	return out;
}

void WritePathFile(std::vector<ShaderData> pathData)
{
	std::cout << "Writing to File\n";
	std::ofstream pathFile;
	pathFile.open("Path.dat");
	
	for (int i = 0; i < pathData.size(); i++)
	{
		pathFile.precision(std::numeric_limits<double>::max_digits10 + 2);
		pathFile << pathData[i].Pos[0] << " " << pathData[i].Pos[1] << " " << pathData[i].Scale << " " << pathData[i].Constant << " " << pathData[i].MaxCount << " " << pathData[i].Power << "\n";
	}

	pathFile.close();
	std::cout << "Done Writing to File\n";
}
