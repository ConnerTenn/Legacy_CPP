
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
#include <Windows.h>
#include <fstream>
#include <vector>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

// Other includes
#include "Shader.h"


#define PI 3.14159265358979323
#define TAU (2.0*PI)
#define WIDTH 800
#define HEIGHT 450
#define ASPECT_RATIO (float(WIDTH) / float(HEIGHT))
#define IMAGE_WIDTH (4000*2)//4000
#define IMAGE_HEIGHT (2250*2)//2250
#define IMAGE_ASPECT_RATIO (float(IMAGE_WIDTH) / float(IMAGE_HEIGHT))

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);

bool keys[349];
GLuint VAO, VBO, EBO, FBO, renderedTexture, UBO;

double XPos = -0.5;
double YPos = 0;
double Scale = 1;
float PathIndex = 0;
int ImageCount = 0;

struct ShaderData
{
	//					//base alignment	//aligned offset
	double Pos[2];		//16				//0->15
	double Scale;		//8					//16->23
	double Constant;	//8					//24->31
	int MaxCount;		//4					//32->35
	int Power;			//4					//36->39
	float AspectRatio;	//4					//40->43
};

struct Point
{
	double X;
	double Y;
};

struct Vector;

struct Node : Point
{
	Vector *Child1 = 0;
	Vector *Child2 = 0;
	Node(double x, double y)
	{
		X = x; Y = y;
	}
};

struct Vector : Point
{
	Node *Parent = 0;
	Vector(double x, double y)
	{
		X = x; Y = y;
	}
};

Point ClickPos{ 0,0 }, OrigPos[3] = { { 0,0 }, { 0,0 }, { 0,0 } };
Point *ActivePoint = 0; bool ActiveType = 0;
std::vector<Point *> PointList;
std::vector<Node *> NodeList;

Point Interpolate(Node *node1, Node *node2, double t)
{
	return
	{
		pow(1.0 - t, 3)*node1->X + 3.0*pow(1.0 - t, 2)*t*node1->Child2->X + 3 * (1 - t)*pow(t, 2)*node2->Child1->X + pow(t, 3)*node2->X,
		pow(1.0 - t, 3)*node1->Y + 3.0*pow(1.0 - t, 2)*t*node1->Child2->Y + 3 * (1 - t)*pow(t, 2)*node2->Child1->Y + pow(t, 3)*node2->Y
	};
}

// The MAIN function, from here we start the application and run the game loop
void main()
{
	{
		Node *node; Vector *vector1 = 0, *vector2 = 0;

		node = new Node(-0.5, 0.0); vector1 = 0; vector2 = new Vector(-0.5, 0.5);
		node->Child2 = vector2; vector2->Parent = node;
		PointList.push_back(node); PointList.push_back(vector2); NodeList.push_back(node);

		node = new Node(0, 0.2); vector1 = new Vector(-0.2, -0.5);  vector2 = new Vector(0.2, 0.5);
		node->Child1 = vector1; node->Child2 = vector2; vector1->Parent = node; vector2->Parent = node;
		PointList.push_back(node); PointList.push_back(vector1); PointList.push_back(vector2); NodeList.push_back(node);

		node = new Node(0.5, -0.5); vector1 = new Vector(0.3, -0.5); vector2 = 0;
		node->Child1 = vector1; vector1->Parent = node;
		PointList.push_back(node); PointList.push_back(vector1); NodeList.push_back(node);
	}
	//PointList = { {-0.5,0.0}, {-0.5, 0.5}, {0.5, } };

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
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetCursorPosCallback(window, CursorPosCallback);

	//glfwSetCursorPosCallback();

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	// Build and compile our shader program
	Shader Shader("vertex.shader", "fragment.shader");

	glLineWidth(3);
	glEnable(GL_LINE_SMOOTH);
	glPointSize(7);
	glEnable(GL_POINT_SMOOTH);
	
	{/*Vertex Array Setup*/ }
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		
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
		//glUniformBlockBinding(Shader.Program, glGetUniformBlockIndex(Shader.Program, "uBlock"), bindingPoint);

		//Create Uniform Buffer Object
		glGenBuffers(1, &UBO);
		glBindBuffer(GL_UNIFORM_BUFFER, UBO);
		//Bind UBO to binding point 1
		glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, UBO);
	}

	while (!glfwWindowShouldClose(window))
	{
		//glViewport(0, 0, WIDTH, HEIGHT);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		{/*Keyboard*/ }
		{
			/*if (GetAsyncKeyState('W')) { YPos += 0.005 * Scale; }
			if (GetAsyncKeyState('S')) { YPos -= 0.005 * Scale; }
			if (GetAsyncKeyState('A')) { XPos -= 0.005 * Scale; }
			if (GetAsyncKeyState('D')) { XPos += 0.005 * Scale; }
			if (GetAsyncKeyState('Q')) { Scale *= 1.01; }
			if (GetAsyncKeyState('E')) { Scale /= 1.01; }*/
		}

		{/*Uniforms*/ }
		{
			/*
			ShaderData data =
			{
				{XPos, YPos},
				Scale,
				1,
				1,
				1,
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
			*/
		}
		{/*Render*/ }
		{

			Shader.Use();
			// Clear the colorbuffer
			glClear(GL_COLOR_BUFFER_BIT);

			{/*Vector Segments*/ }
			{
				glLineWidth(1);
				GLdouble *vertices = new GLdouble[(NodeList.size() * 4 - 4) * 6];
				GLuint *indices = new GLuint[(NodeList.size() * 4 - 4)];
				for (int i = 1; i < NodeList.size() - 1; i++)
				{
					vertices[(i * 4 - 2) * 6 + 0] = NodeList[i]->X;
					vertices[(i * 4 - 2) * 6 + 1] = NodeList[i]->Y;
					vertices[(i * 4 - 2) * 6 + 2] = 0;

					vertices[(i * 4 - 2) * 6 + 3] = 0.5;
					vertices[(i * 4 - 2) * 6 + 4] = 0.7;
					vertices[(i * 4 - 2) * 6 + 5] = 1.0;

					indices[i * 4 - 2 + 0] = i * 4 - 2 + 0;

					vertices[(i * 4 - 2) * 6 + 6] = NodeList[i]->Child1->X;
					vertices[(i * 4 - 2) * 6 + 7] = NodeList[i]->Child1->Y;
					vertices[(i * 4 - 2) * 6 + 8] = 0;

					vertices[(i * 4 - 2) * 6 + 9] = 0.5;
					vertices[(i * 4 - 2) * 6 + 10] = 0.7;
					vertices[(i * 4 - 2) * 6 + 11] = 1.0;

					indices[i * 4 - 2 + 1] = i * 4 - 2 + 1;

					vertices[(i * 4 - 2) * 6 + 12] = NodeList[i]->X;
					vertices[(i * 4 - 2) * 6 + 13] = NodeList[i]->Y;
					vertices[(i * 4 - 2) * 6 + 14] = 0;

					vertices[(i * 4 - 2) * 6 + 15] = 0.5;
					vertices[(i * 4 - 2) * 6 + 16] = 0.7;
					vertices[(i * 4 - 2) * 6 + 17] = 1.0;

					indices[i * 4 - 2 + 2] = i * 4 - 2 + 2;

					vertices[(i * 4 - 2) * 6 + 18] = NodeList[i]->Child2->X;
					vertices[(i * 4 - 2) * 6 + 19] = NodeList[i]->Child2->Y;
					vertices[(i * 4 - 2) * 6 + 20] = 0;

					vertices[(i * 4 - 2) * 6 + 21] = 0.5;
					vertices[(i * 4 - 2) * 6 + 22] = 0.7;
					vertices[(i * 4 - 2) * 6 + 23] = 1.0;

					indices[i * 4 - 2 + 3] = i * 4 - 2 + 3;
				}

				{
					vertices[0] = NodeList[0]->X;
					vertices[1] = NodeList[0]->Y;
					vertices[2] = 0;

					vertices[3] = 0.5;
					vertices[4] = 0.7;
					vertices[5] = 1.0;

					indices[0] = 0;

					vertices[6] = NodeList[0]->Child2->X;
					vertices[7] = NodeList[0]->Child2->Y;
					vertices[8] = 0;

					vertices[9] = 0.5;
					vertices[10] = 0.7;
					vertices[11] = 1.0;

					indices[1] = 1;


					vertices[((NodeList.size() - 1) * 4 - 2) * 6 + 0] = NodeList[NodeList.size() - 1]->X;
					vertices[((NodeList.size() - 1) * 4 - 2) * 6 + 1] = NodeList[NodeList.size() - 1]->Y;
					vertices[((NodeList.size() - 1) * 4 - 2) * 6 + 2] = 0;

					vertices[((NodeList.size() - 1) * 4 - 2) * 6 + 3] = 0.5;
					vertices[((NodeList.size() - 1) * 4 - 2) * 6 + 4] = 0.7;
					vertices[((NodeList.size() - 1) * 4 - 2) * 6 + 5] = 1.0;

					indices[(NodeList.size() - 1) * 4 - 2 + 0] = ((int)NodeList.size() - 1) * 4 - 2 + 0;

					vertices[((NodeList.size() - 1) * 4 - 2) * 6 + 6] = NodeList[NodeList.size() - 1]->Child1->X;
					vertices[((NodeList.size() - 1) * 4 - 2) * 6 + 7] = NodeList[NodeList.size() - 1]->Child1->Y;
					vertices[((NodeList.size() - 1) * 4 - 2) * 6 + 8] = 0;

					vertices[((NodeList.size() - 1) * 4 - 2) * 6 + 9] = 0.5;
					vertices[((NodeList.size() - 1) * 4 - 2) * 6 + 10] = 0.7;
					vertices[((NodeList.size() - 1) * 4 - 2) * 6 + 11] = 1.0;

					indices[(NodeList.size() - 1) * 4 - 2 + 1] = ((int)NodeList.size() - 1) * 4 - 2 + 1;
				}

				glBufferData(GL_ARRAY_BUFFER, sizeof(GLdouble) * (NodeList.size() * 4 - 4) * 6, vertices, GL_STATIC_DRAW);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (NodeList.size() * 4 - 4), indices, GL_STATIC_DRAW);
				glVertexAttribLPointer(0, 3, GL_DOUBLE, 6 * sizeof(GLdouble), (GLvoid*)(0 * sizeof(GLdouble))); glEnableVertexAttribArray(0);
				glVertexAttribLPointer(1, 3, GL_DOUBLE, 6 * sizeof(GLdouble), (GLvoid*)(3 * sizeof(GLdouble))); glEnableVertexAttribArray(1);



				glDrawElements(GL_LINES, ((int)NodeList.size() * 4 - 4), GL_UNSIGNED_INT, 0);
				delete[] vertices;
				delete[] indices;
				glLineWidth(3);
			}

			{/*Curve*/ }
			{
				//static float q = 0;
				int count = 1000;
				static float rainbowOffset = 0; rainbowOffset += 0.02f; rainbowOffset >= TAU ? rainbowOffset = 0 : 0;
				GLdouble *vertices = new GLdouble[(count+1) * ((int)NodeList.size()-1) * 6];
				GLuint *indices = new GLuint[(count+1) * ((int)NodeList.size()-1)];
				for (int i = 0; i < NodeList.size()-1; i+=1)
				{
					for (int j = 0; j <= count; j++)
					{
						double t = (double)j/(double)count;
						Point pos = Interpolate(NodeList[i], NodeList[i + 1], t);
						vertices[(i*(count + 1) + j) * 6 + 0] = pos.X;
						vertices[(i*(count + 1) + j) * 6 + 1] = pos.Y;
						vertices[(i*(count + 1) + j) * 6 + 2] = 0;

						//vertices[(i*(count + 1) + j) * 6 + 3] = 0.2;
						//vertices[(i*(count + 1) + j) * 6 + 4] = 0.5;
						//vertices[(i*(count + 1) + j) * 6 + 5] = 1.0;
						vertices[(i*(count + 1) + j) * 6 + 3] = (cos((2.0 / count) * (i*(count + 1) + j) * TAU + TAU * (0.0 / 3.0) - rainbowOffset) + 1.0) / 3.0;
						vertices[(i*(count + 1) + j) * 6 + 4] = (cos((2.0 / count) * (i*(count + 1) + j) * TAU + TAU * (1.0 / 3.0) - rainbowOffset) + 1.0) / 3.0;
						vertices[(i*(count + 1) + j) * 6 + 5] = (cos((2.0 / count) * (i*(count + 1) + j) * TAU + TAU * (2.0 / 3.0) - rainbowOffset) + 1.0) / 3.0;

						indices[i*(count + 1) + j] = i * (count + 1) + j;
					}
				}

				glBufferData(GL_ARRAY_BUFFER, sizeof(GLdouble) * (count + 1) * ((int)NodeList.size()-1) * 6, vertices, GL_STATIC_DRAW);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (count + 1) * ((int)NodeList.size()-1), indices, GL_STATIC_DRAW);
				glVertexAttribLPointer(0, 3, GL_DOUBLE, 6 * sizeof(GLdouble), (GLvoid*)(0 * sizeof(GLdouble))); glEnableVertexAttribArray(0);
				glVertexAttribLPointer(1, 3, GL_DOUBLE, 6 * sizeof(GLdouble), (GLvoid*)(3 * sizeof(GLdouble))); glEnableVertexAttribArray(1);


				glDrawElements(GL_LINE_STRIP, (count + 1) * ((int)NodeList.size() - 1), GL_UNSIGNED_INT, 0);
				delete[] vertices;
				delete[] indices;
			}

			{/*Points*/ }
			{
				GLdouble *vertices = new GLdouble[PointList.size() * 6];
				GLuint *indices = new GLuint[PointList.size()];
				for (int i = 0; i <= PointList.size() - 1; i++)
				{
					vertices[i * 6] = PointList[i]->X;
					vertices[i * 6 + 1] = PointList[i]->Y;
					vertices[i * 6 + 2] = 0;

					vertices[i * 6 + 3] = 0.2;
					vertices[i * 6 + 4] = 0.5;
					vertices[i * 6 + 5] = 1.0;

					indices[i] = i;
				}

				glBufferData(GL_ARRAY_BUFFER, sizeof(GLdouble) * PointList.size() * 6, vertices, GL_STATIC_DRAW);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * PointList.size(), indices, GL_STATIC_DRAW);
				glVertexAttribLPointer(0, 3, GL_DOUBLE, 6 * sizeof(GLdouble), (GLvoid*)(0 * sizeof(GLdouble))); glEnableVertexAttribArray(0);
				glVertexAttribLPointer(1, 3, GL_DOUBLE, 6 * sizeof(GLdouble), (GLvoid*)(3 * sizeof(GLdouble))); glEnableVertexAttribArray(1);
				


				glDrawElements(GL_POINTS, (int)PointList.size(), GL_UNSIGNED_INT, 0);
				delete[] vertices;
				delete[] indices;
			}

			
			


			// Swap the screen buffers
			glfwSwapBuffers(window);

		}
		
	}

	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	//glDeleteTextures(1, &renderedTexture);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();

	{
		for (int i = 0; i < PointList.size(); i++)
		{
			delete PointList[i];
		}
	}
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { glfwSetWindowShouldClose(window, GL_TRUE); }
	//keys[key] = bool(action);
}

double dist(Point point1, Point point2)
{
	return sqrt(pow(point2.X - point1.X, 2) + pow(point2.Y - point1.Y, 2));
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		xPos = (xPos / (double)WIDTH) * 2.0 - 1.0;
		yPos = -((yPos / (double)HEIGHT) * 2.0 - 1.0);

		std::cout << "Click: " << xPos << " " << yPos << "\n";

		/*for (int i = 0; i < PointList.size(); i++)
		{
			if (dist(*PointList[i], { xPos, yPos }) < (double)10/(double)WIDTH)
			{
				std::cout << "Dist: " << dist(*PointList[i], { xPos, yPos }) << "\n";
				ActivePoint = PointList[i];
			}
		}*/

		for (int i = 0; i < NodeList.size(); i++)
		{
			Node *node = NodeList[i];
			if (dist(*node, { xPos, yPos }) < (double)12 / (double)WIDTH)
			{
				ActivePoint = node; ActiveType = 0;
				OrigPos[0] = { node->X, node->Y };
				if (node->Child1) { OrigPos[1] = { node->Child1->X, node->Child1->Y }; }
				if (node->Child2) { OrigPos[2] = { node->Child2->X, node->Child2->Y }; }
				ClickPos = { xPos, yPos }; //std::cout << "Click Node\n";
			}
			if (node->Child1 && dist(*node->Child1, { xPos, yPos }) < (double)12 / (double)WIDTH)
			{
				ActivePoint = node->Child1; ActiveType = 1;
				OrigPos[0] = { node->Child1->X, node->Child1->Y };
				ClickPos = { xPos, yPos };
			}
			if (node->Child2 && dist(*node->Child2, { xPos, yPos }) < (double)12 / (double)WIDTH)
			{
				ActivePoint = node->Child2; ActiveType = 1;
				OrigPos[0] = { node->Child2->X, node->Child2->Y };
				ClickPos = { xPos, yPos };
			}
		}
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		ActivePoint = 0;
	}
}

void CursorPosCallback(GLFWwindow* window, double xPos, double yPos)
{
	xPos = (xPos / (double)WIDTH) * 2.0 - 1.0;
	yPos = -((yPos / (double)HEIGHT) * 2.0 - 1.0);
	if (ActivePoint)
	{
		ActivePoint->X = OrigPos[0].X + (xPos - ClickPos.X);
		ActivePoint->Y = OrigPos[0].Y + (yPos - ClickPos.Y);

		if (!ActiveType)
		{
			if (((Node *)ActivePoint)->Child1)
			{
				((Node *)ActivePoint)->Child1->X = OrigPos[1].X + (xPos - ClickPos.X);
				((Node *)ActivePoint)->Child1->Y = OrigPos[1].Y + (yPos - ClickPos.Y);
			}
			if (((Node *)ActivePoint)->Child2)
			{
				((Node *)ActivePoint)->Child2->X = OrigPos[2].X + (xPos - ClickPos.X);
				((Node *)ActivePoint)->Child2->Y = OrigPos[2].Y + (yPos - ClickPos.Y);
			}
		}
	}
}

