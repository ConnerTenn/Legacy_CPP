
/*
##################
# FUTURE CHANGES #
##################

Spline Graph for all values
	- separate window
	- extrapolation

Move all Transform values to struct
improve Spline Implementation

*/



#include <iostream>
//#include <Windows.h>
#include <fstream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

// Other includes
#include <spline.h>
#include <math.h>
#include "Shader.h"
#include "FileIO.h"


#define WIDTH 800
#define HEIGHT 450
#define ASPECT_RATIO (float(WIDTH) / float(HEIGHT))
#define IMAGE_WIDTH (4000*1.3)//4000
#define IMAGE_HEIGHT (2250*1.4)//2250
#define IMAGE_ASPECT_RATIO (float(IMAGE_WIDTH) / float(IMAGE_HEIGHT))

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

bool keys[349];
GLuint VAO, VBO, EBO, FBO, renderedTexture, UBO;

double XPos = -0.5;
double YPos = 0;
double Scale = 1;
double Constant = 0;
int Power = 1;
double MaxCount = 100;

bool Save = false;
bool SaveEnable = true;
std::vector<ShaderData> PathData;
bool RenderPath = false;
bool InterpolationPrieview = false;

float PathIndex = 0;
int ImageCount = 0;

tk::spline XPosSpline;
tk::spline YPosSpline;
tk::spline ScaleSpline;
tk::spline ConstantSpline;
tk::spline PowerSpline;
tk::spline MaxCountSpline;

#define STEP 0.1

void ParseToSpline()
{
	std::vector<double> posList;
	std::vector<double> xPosList;
	std::vector<double> yPosList;
	std::vector<double> scaleList;
	std::vector<double> constantList;
	std::vector<double> powerList;
	std::vector<double> maxCountList;
	for (int i = 0; i < PathData.size(); i++)
	{
		posList.push_back(double(i));
		xPosList.push_back(PathData[i].Pos[0]);
		yPosList.push_back(PathData[i].Pos[1]);
		scaleList.push_back(log(PathData[i].Scale)/log(1.01));//apply log of base 1.01 to transform to linear
		constantList.push_back(PathData[i].Constant);
		powerList.push_back(double(PathData[i].Power));
		maxCountList.push_back(double(PathData[i].MaxCount));
	}
	XPosSpline.set_points(posList, xPosList);
	YPosSpline.set_points(posList, yPosList);
	ScaleSpline.set_points(posList, scaleList);
	ConstantSpline.set_points(posList, constantList);
	PowerSpline.set_points(posList, powerList);
	MaxCountSpline.set_points(posList, maxCountList);
}

void Interpolate(double pos)
{
	XPos = XPosSpline(pos);
	YPos = YPosSpline(pos);
	Scale = pow(1.01,ScaleSpline(pos));//transform back to exponential
	Constant = ConstantSpline(pos);
	MaxCount = MaxCountSpline(pos);
	Power = int(PowerSpline(pos));
}

// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	// Build and compile our shader program
	Shader fractalShader("vertex.shader", "fragment.shader");
	Shader solidShader("vertex.shader", "fragment2.shader");

	{/*Vertex Array Setup*/ }
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		GLdouble vertices[] = {
			-1, -1, 0,
			1, -1, 0,
			1,  1, 0,
			-1,  1, 0
		};
		GLuint indices[] = {
			0, 1, 3,
			2, 3, 1
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribLPointer(0, 3, GL_DOUBLE, 3 * sizeof(GLdouble), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	}
	{/*Capture Framebuffer Setup*/ }
	{
		glGenFramebuffers(1, &FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);

		glGenTextures(1, &renderedTexture);
		glBindTexture(GL_TEXTURE_2D, renderedTexture);

		// Give an empty image to OpenGL ( the last "0" )
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_WIDTH, IMAGE_HEIGHT, 0, GL_BGR, GL_UNSIGNED_BYTE, 0);
		// Poor filtering. Needed !
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		// Set "renderedTexture" as our colour attachement #0
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	{/*Uniform Buffer Setup*/ }
	{
		GLuint bindingPoint = 1;
		//Only needed if binding not specified within shader
		//glUniformBlockBinding(fractalShader.Program, glGetUniformBlockIndex(fractalShader.Program, "uBlock"), bindingPoint);

		//Create Uniform Buffer Object
		glGenBuffers(1, &UBO);
		glBindBuffer(GL_UNIFORM_BUFFER, UBO);
		//Bind UBO to binding point 1
		glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, UBO);
	}
	
	std::cout << "Begin Rendering Path\n"; PathData = ReadPathFile(); RenderPath = true; PathIndex = 0; ImageCount = 0; ParseToSpline();
	
	while (!glfwWindowShouldClose(window) && RenderPath)
	{
		//glViewport(0, 0, WIDTH, HEIGHT);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		{/*Keyboard*/ }
		{
			//if (GetAsyncKeyState('Z')) { YPos = 0; XPos =  -0.5; Scale = 1; Constant = 0; }
			//if (GetAsyncKeyState('W')) { YPos += 0.005 * Scale; }
			//if (GetAsyncKeyState('S')) { YPos -= 0.005 * Scale; }
			//if (GetAsyncKeyState('A')) { XPos -= 0.005 * Scale; }
			//if (GetAsyncKeyState('D')) { XPos += 0.005 * Scale; }
			//if (GetAsyncKeyState('Q')) { Scale *= 1.01; }
			//if (GetAsyncKeyState('E')) { Scale /= 1.01; }
			//if (GetAsyncKeyState('R')) { Constant += 0.001; }
			//if (GetAsyncKeyState('F')) { Constant -= 0.001; }
			//if (GetAsyncKeyState('Y')) { MaxCount += 0.5; }
			//if (GetAsyncKeyState('H')) { MaxCount -= 0.5; }
			//static bool keyT = 0; if (GetAsyncKeyState('T')) { if (keyT == 0) { keyT = 1; Power++; } } else { keyT = 0; }
			//static bool keyG = 0; if (GetAsyncKeyState('G')) { if (keyG == 0) { keyG = 1; Power--; } } else { keyG = 0; }
			//if (GetAsyncKeyState('P')) { std::cout << "X:" << XPos << "\tY:" << YPos << "\tScale:" << Scale << "\tMaxCount:" << int(MaxCount) << "\tConstant:" << Constant << "\tPower:" << Power << "\n"; }
			//static bool keyO = 0; if (GetAsyncKeyState('O')) { if (keyO == 0) { keyO = 1; Save = true; } } else { keyO = 0; }

			//record frame
			//static bool keyB = 0; if (GetAsyncKeyState('B')) { if (keyB == 0) { keyB = 1;  PathData.push_back({ { XPos, YPos }, Scale, Constant, int(MaxCount), Power, 0}); if (PathData.size() > 2) { ParseToSpline(); Interpolate(double(PathData.size())); } } } else { keyB = 0; }
			//save frames
			//static bool keyN = 0; if (GetAsyncKeyState('N')) { if (keyN == 0) { keyN = 1;  WritePathFile(PathData); } } else { keyN = 0; }
			//render path
			/*static bool keyM = 0; if (GetAsyncKeyState('M')) { if (keyM == 0) { keyM = 1; 
				if (!RenderPath)
				{
					std::cout << "Begin Rendering Path\n";  PathData = ReadPathFile(); RenderPath = true; PathIndex = 0; ImageCount = 0; ParseToSpline();
				}
				else
				{
					std::cout << "Cancelling Rendering Path\n"; RenderPath = false; PathIndex = 0; ImageCount = 0;
				}
				} } else { keyM = 0; }*/
			//interpolation view enable
			//static bool keyV = 0; if (GetAsyncKeyState('V')) { if (keyV == 0) { keyV = 1; InterpolationPrieview = !InterpolationPrieview; } } else { keyV = 0; }
			//static bool keyK = 0; if (GetAsyncKeyState('K')) { if (keyK == 0) { keyK = 1; SaveEnable = !SaveEnable; std::cout << "SaveEnable:" << SaveEnable << "\n"; } } else { keyK = 0; }
		}

		{/*RenderPath Calculations*/}
		{
			if (RenderPath)
			{
				Save = true;
				/*XPos = XPosSpline(PathIndex);//PathData[PathIndex].Pos[0];
				YPos = YPosSpline(PathIndex);//PathData[PathIndex].Pos[1];
				Scale = ScaleSpline(PathIndex);//PathData[PathIndex].Scale;
				Constant = ConstantSpline(PathIndex);//PathData[PathIndex].Constant;
				MaxCount = MaxCountSpline(PathIndex);//PathData[PathIndex].MaxCount;
				Power = PowerSpline(PathIndex);//PathData[PathIndex].Power;*/
				Interpolate(PathIndex);
				PathIndex += float(STEP);
				if (PathIndex >= PathData.size()) { PathIndex = 0; RenderPath = false; Save = 0; std::cout << "Done Rendering Path\n"; }
			}
		}

		{/*Uniforms*/ }
		{
			ShaderData data =
			{
				{XPos, YPos},
				Scale,
				Constant,
				int(MaxCount),
				Power,
				ASPECT_RATIO
			};

			//Uniform data with proper alignment
			//GLdouble uniformData[] = { XPos,YPos,Scale, 0.0, MaxCount, Constant, Power };
			//glBufferData(GL_UNIFORM_BUFFER, sizeof(uniformData), uniformData, GL_DYNAMIC_DRAW);
			//glBufferData(GL_UNIFORM_BUFFER, sizeof(uniformData), 0, GL_DYNAMIC_DRAW);
			glBufferData(GL_UNIFORM_BUFFER, sizeof(ShaderData), &data, GL_DYNAMIC_DRAW);

			//GLdouble transformData[] = { XPos, YPos, Scale };
			//GLdouble constData[] = { MaxCount, Constant, Power };
			//glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(transformData), transformData);
			//Aligment (there is a 8 byte gap between the two dvec3s)
			//glBufferSubData(GL_UNIFORM_BUFFER, 4*8, sizeof(constData), constData);
		}
		{/*Render*/ }
		{
			GLdouble vertices[] = {
				-1, -1, 0,
				1, -1, 0,
				1,  1, 0,
				-1,  1, 0
			};
			GLuint indices[] = {
				0, 1, 3,
				2, 3, 1
			};
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
			glVertexAttribLPointer(0, 3, GL_DOUBLE, 3 * sizeof(GLdouble), (GLvoid*)0);
			glEnableVertexAttribArray(0);

			fractalShader.Use();
			// Clear the colorbuffer
			glClear(GL_COLOR_BUFFER_BIT);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			if (InterpolationPrieview && PathData.size() > 1)
			{
				//calculate spline including current pos
				std::vector<double> posList;
				std::vector<double> xPosList;
				std::vector<double> yPosList;
				std::vector<double> scaleList;
				for (int i = 0; i < PathData.size(); i++)
				{
					posList.push_back(double(i));
					xPosList.push_back(PathData[i].Pos[0]);
					yPosList.push_back(PathData[i].Pos[1]);
					scaleList.push_back(log(PathData[i].Scale) / log(1.01));
				}
				posList.push_back(int(PathData.size()));
				xPosList.push_back(XPos);
				yPosList.push_back(YPos);
				scaleList.push_back(log(Scale) / log(1.01));

				XPosSpline.set_points(posList, xPosList);
				YPosSpline.set_points(posList, yPosList);
				ScaleSpline.set_points(posList, scaleList);

				//get new position by extrapolation
				double newXPos = XPosSpline(double(PathData.size() + 1));
				double newYPos = YPosSpline(double(PathData.size() + 1));
				double newScale = pow(1.01, ScaleSpline(double(PathData.size() + 1)));
				GLdouble vertices[] = {//transforms to render the rectangle in the correct position
					(1.0 / Scale * newScale) * -1 + ((newXPos - XPos) * (1.0 / Scale)) / ASPECT_RATIO, (1.0 / Scale * newScale) * -1 + (newYPos - YPos) * (1.0 / Scale), 0,
					(1.0 / Scale * newScale) * 1 + ((newXPos - XPos) * (1.0 / Scale)) / ASPECT_RATIO, (1.0 / Scale * newScale) * -1 + (newYPos - YPos) * (1.0 / Scale), 0,
					(1.0 / Scale * newScale) * 1 + ((newXPos - XPos) * (1.0 / Scale)) / ASPECT_RATIO, (1.0 / Scale * newScale) * 1 + (newYPos - YPos) * (1.0 / Scale), 0,
					(1.0 / Scale * newScale) * -1 + ((newXPos - XPos) * (1.0 / Scale)) / ASPECT_RATIO, (1.0 / Scale * newScale) * 1 + (newYPos - YPos) * (1.0 / Scale), 0
				};
				GLuint indices[] = {
					0, 1, 2, 3,
				};
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
				glVertexAttribLPointer(0, 3, GL_DOUBLE, 3 * sizeof(GLdouble), (GLvoid*)0);
				glEnableVertexAttribArray(0);

				solidShader.Use();
				glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, 0);
				fractalShader.Use();
			}

			// Swap the screen buffers
			glfwSwapBuffers(window);
		}
		if (Save && SaveEnable)
		{
			std::cout << "Rendering Image " << ImageCount << "\n";
			{/*Uniforms*/ }
			{
				ShaderData data =
				{
					{ XPos, YPos },
					Scale,
					Constant,
					int(MaxCount),
					Power,
					IMAGE_ASPECT_RATIO
				};
				glBufferData(GL_UNIFORM_BUFFER, sizeof(ShaderData), &data, GL_DYNAMIC_DRAW);
			}

			glViewport(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);
			glBindFramebuffer(GL_FRAMEBUFFER, FBO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			SaveImage(IMAGE_WIDTH, IMAGE_HEIGHT, std::string(std::string(RenderPath ? "Frames/" : "") + "file" + std::to_string(ImageCount) + ".bmp").c_str(), renderedTexture); Save = false; if (RenderPath) { ImageCount++; }
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, WIDTH, HEIGHT);
			std::cout << "Done Rendering Image " << ImageCount << "\n";
		}
	}

	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	//glDeleteTextures(1, &renderedTexture);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();

	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { glfwSetWindowShouldClose(window, GL_TRUE); }
	//keys[key] = bool(action);
}
