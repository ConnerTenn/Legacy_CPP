
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <fstream>
#include <string>


void SaveImage(int width, int height, std::string filename, GLint tex)
{
	char* buff = new char[width * height * 4];
	if (!buff) { return; }

	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, buff);//use BGR File Format
	//glBindBuffer(GL_TEXTURE_BUFFER, tex);
	//glBindTexture(GL_TEXTURE_2D, tex);
	//glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, (void *)buff);
	std::cout << glewGetErrorString(glGetError()) << "\n";
	//glGetTextureImage(tex, 0, GL_RGB, GL_UNSIGNED_BYTE, width * height * 4, (void *)buff);

	//std::ofstream out; out.open(filename.c_str());
	//std::FILE *Out = fopen(filename.c_str(), "wb"); if (!Out) { return; }
	
	
	FILE *out;
	errno_t err = fopen_s(&out, filename.c_str(), "wb");
	if (err != 0) { return; }

	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;

	bitmapFileHeader.bfType = 0x4D42;
	bitmapFileHeader.bfSize = width*height * 3;
	bitmapFileHeader.bfReserved1 = 0;
	bitmapFileHeader.bfReserved2 = 0;
	bitmapFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
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

	fwrite(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, out);
	fwrite(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, out);
	fwrite(buff, width*height * 3, 1, out);
	fclose(out);

	//out.write((char *)&bitmapFileHeader, sizeof(BITMAPFILEHEADER));
	//out.write((char *)&bitmapInfoHeader, sizeof(BITMAPFILEHEADER));
	//out.write((char *)buff, width*height * 3);
	//out.close();

	
	
	delete[] buff;
}

