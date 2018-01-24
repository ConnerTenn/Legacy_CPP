
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

extern "C"
{
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavutil/channel_layout.h>
#include <libavutil/common.h>
#include <libavutil/imgutils.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
}

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
	errno_t err = fopen_s(&out, filename.c_str(), "wb");
	if (err != 0) { return; }

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



#define INBUF_SIZE 4096
#define AUDIO_INBUF_SIZE 20480
#define AUDIO_REFILL_THRESH 4096
typedef void(__cdecl *lib_av_register_all)(void);
typedef AVCodec* (__cdecl *lib_avcodec_find_encoder)(AVCodecID);

extern "C" void video_encode_example(const char *filename, AVCodecID codec_id)
{
	AVCodec *codec;
	AVCodecContext *c = NULL;
	int i, ret, x, y, got_output = 1;
	FILE *f;
	AVFrame *frame;
	AVPacket pkt;
	uint8_t endcode[] = { 0, 0, 1, 0xb7 };

	printf("Encode video file %s\n", filename);

	auto hAVCodec = LoadLibrary(TEXT("avcodec-57.dll"));
	auto hAVFormat = LoadLibrary(TEXT("avformat-57.dll"));
	auto my_register_all = (lib_av_register_all)GetProcAddress(hAVFormat, TEXT("av_register_all"));
	auto my_avcodec_find_encoder = (lib_avcodec_find_encoder)GetProcAddress(hAVCodec, TEXT("avcodec_find_encoder"));
	my_register_all();

	/* find the video encoder */
	codec = my_avcodec_find_encoder(codec_id);
	if (!codec)
	{
		fprintf(stderr, "Codec not found\n");
		exit(1);
	}
	c = avcodec_alloc_context3(codec);
	if (!c)
	{
		fprintf(stderr, "Could not allocate video codec context\n");
		exit(1);
	}
	/* put sample parameters */
	c->bit_rate = 400000;
	/* resolution must be a multiple of two */
	c->width = 352;
	c->height = 288;
	/* frames per second */
	c->time_base = { 1, 25 };
	/* emit one intra frame every ten frames
	* check frame pict_type before passing frame
	* to encoder, if frame->pict_type is AV_PICTURE_TYPE_I
	* then gop_size is ignored and the output of encoder
	* will always be I frame irrespective to gop_size
	*/
	c->gop_size = 10;
	c->max_b_frames = 1;
	c->pix_fmt = AV_PIX_FMT_YUV420P;
	if (codec_id == AV_CODEC_ID_H264) { av_opt_set(c->priv_data, "preset", "slow", 0); }

	/* open it */
	if (avcodec_open2(c, codec, NULL) < 0)
	{
		fprintf(stderr, "Could not open codec\n");
		exit(1);
	}
	//f = fopen(filename, "wb");
	fopen_s(&f, filename, "wb");
	if (!f)
	{
		fprintf(stderr, "Could not open %s\n", filename);
		exit(1);
	}
	frame = av_frame_alloc();
	if (!frame)
	{
		fprintf(stderr, "Could not allocate video frame\n");
		exit(1);
	}
	frame->format = c->pix_fmt;
	frame->width = c->width;
	frame->height = c->height;
	/* the image can be allocated by any means and av_image_alloc() is
	* just the most convenient way if av_malloc() is to be used */
	ret = av_image_alloc(frame->data, frame->linesize, c->width, c->height,
		c->pix_fmt, 32);
	if (ret < 0)
	{
		fprintf(stderr, "Could not allocate raw picture buffer\n");
		exit(1);
	}
	/* encode 1 second of video */
	for (i = 0; i < 20; i++)
	{
		av_init_packet(&pkt);
		pkt.data = NULL;    // packet data will be allocated by the encoder
		pkt.size = 0;
		fflush(stdout);
		/* prepare a dummy image */
		/* Y */
		for (y = 0; y < c->height; y++)
		{
			for (x = 0; x < c->width; x++)
			{
				frame->data[0][y * frame->linesize[0] + x] = x + y + i * 3;
			}
		}
		/* Cb and Cr */
		for (y = 0; y < c->height / 2; y++)
		{
			for (x = 0; x < c->width / 2; x++)
			{
				frame->data[1][y * frame->linesize[1] + x] = 128 + y + i * 2;
				frame->data[2][y * frame->linesize[2] + x] = 64 + x + i * 5;
			}
		}
		frame->pts = i;
		/* encode the image */
		//ret = avcodec_encode_video2(c, &pkt, frame, &got_output);
		ret = avcodec_send_frame(c, frame);
		if (ret < 0)
		{
			fprintf(stderr, "Error encoding frame\n");
			exit(1);
		}
		if (got_output)
		{
			pkt.data = frame->data[0]; pkt.size = sizeof(frame->data[0]);
			printf("Write frame %3d (size=%5d)\n", i, pkt.size);
			fwrite(pkt.data, 1, pkt.size, f);
			av_packet_unref(&pkt);
		}
	}
	/* get the delayed frames */
	got_output = 1;
	//for (got_output = 1; got_output; i++)
	{
		fflush(stdout);
		//ret = avcodec_encode_video2(c, &pkt, NULL, &got_output);
		ret = avcodec_send_frame(c, NULL);
		if (ret < 0)
		{
			fprintf(stderr, "Error encoding frame\n");
			exit(1);
		}
		if (got_output)
		{
			printf("Write frame %3d (size=%5d)\n", i, pkt.size);
			fwrite(pkt.data, 1, pkt.size, f);
			av_packet_unref(&pkt);
		}
	}
	/* add sequence end code to have a real MPEG file */
	fwrite(endcode, 1, sizeof(endcode), f);
	fclose(f);
	avcodec_close(c);
	av_free(c);
	av_freep(&frame->data[0]);
	av_frame_free(&frame);
	printf("\n");
}



void TestVideo()
{
	video_encode_example("test.mpg", AV_CODEC_ID_H264);

}



