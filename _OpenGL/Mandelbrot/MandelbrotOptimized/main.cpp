
#include <iostream>
#include <Windows.h>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other includes
#include "Shader.h"
#include "SaveToFile.h"


// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 800;
double XPos = -0.5, YPos = 0, Scale = 1, Constant = 0, Power = 1, MaxCount = 100;
bool Save = false;

struct ShaderData
{
	//XPos,YPos,Scale,	MaxCount, Constant, Power,
	double Pos[2];
	double Scale;
	int MaxCount;
	double Constant;
	int Power;
};

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
	Shader ourShader("vertex.shader", "fragment.shader");

	// Game loop

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	

	GLint blockIndex = glGetUniformBlockIndex(ourShader.Program, "ShaderData");
	glUniformBlockBinding(ourShader.Program, blockIndex, 0);

	GLuint ubo = 0;
	glGenBuffers(1, &ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ShaderData), NULL, GL_STATIC_DRAW);
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);

	//glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, sizeof(ShaderData));
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo);

	//GLuint renderedTexture;
	//glGenTextures(1, &renderedTexture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	//glBindTexture(GL_TEXTURE_2D, renderedTexture);

	// Give an empty image to OpenGL ( the last "0" )
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_BGR, 2 * WIDTH, 2 * HEIGHT, 0, GL_BGR, GL_UNSIGNED_BYTE, 0);

	// Poor filtering. Needed !
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Set "renderedTexture" as our colour attachement #0
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);
	// Set the list of draw buffers.
	//GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	//glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	while (!glfwWindowShouldClose(window))
	{
		//glViewport(0, 0, WIDTH, HEIGHT);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		{/*Keyboard*/ }
		{
			if (GetAsyncKeyState('Z')) { YPos = 0; XPos = -0.5; Scale = 1; Constant = 0; }
			if (GetAsyncKeyState('W')) { YPos += 0.005 * Scale; }
			if (GetAsyncKeyState('S')) { YPos -= 0.005 * Scale; }
			if (GetAsyncKeyState('A')) { XPos -= 0.005 * Scale; }
			if (GetAsyncKeyState('D')) { XPos += 0.005 * Scale; }
			if (GetAsyncKeyState('Q')) { Scale *= 1.01; }
			if (GetAsyncKeyState('E')) { Scale /= 1.01; }
			if (GetAsyncKeyState('R')) { Constant += 0.001; }
			if (GetAsyncKeyState('F')) { Constant -= 0.001; }
			if (GetAsyncKeyState('Y')) { MaxCount += 0.5; }
			if (GetAsyncKeyState('H')) { MaxCount -= 0.5; }
			static bool keyT = 0; if (GetAsyncKeyState('T')) { if (keyT == 0) { keyT = 1; Power++; } } else { keyT = 0; }
			static bool keyG = 0; if (GetAsyncKeyState('G')) { if (keyG == 0) { keyG = 1; Power--; } } else { keyG = 0; }
			if (GetAsyncKeyState('P')) { std::cout << "X:" << XPos << "\tY:" << YPos << "\tScale:" << Scale << "\tMaxCount" << int(MaxCount) << "\n"; }
			static bool keyO = 0; if (GetAsyncKeyState('O')) { if (keyO == 0) { keyO = 1; Save = true; } } else { keyO = 0; }
		}

		//if (Save) 
		//{
		//	glViewport(0, 0, 2 * WIDTH, 2 * HEIGHT); 
		//}

		//MaxCount = 100 + int(pow(-log2(float(Scale)) - 1.0, 2.0));
		// Set up vertex data (and buffer(s)) and attribute pointers
		GLdouble vertices[] = 
		{
			// Positions         // Colors
			//0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // Bottom Right
			//-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // Bottom Left
			//0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f   // Top 
			1, -1, 0,		XPos,YPos,Scale,	MaxCount, Constant, Power,
			-1, -1, 0,		XPos,YPos,Scale,	MaxCount, Constant, Power,
			-1,  1, 0,		XPos,YPos,Scale,	MaxCount, Constant, Power,
		
			-1,  1, 0,		XPos,YPos,Scale,	MaxCount, Constant, Power,
			1,  1, 0,		XPos,YPos,Scale,	MaxCount, Constant, Power,
			1, -1, 0,		XPos,YPos,Scale,	MaxCount, Constant, Power,
		};
		/*GLdouble vertices[] = {
			-1, -1, 0,		XPos,YPos,Scale,Constant,//top left
			1,  -1, 0,		XPos,YPos,Scale,Constant,//top right

			1,  1, 0,		XPos,YPos,Scale,Constant,//bottom right
			-1,  1, 0,		XPos,YPos,Scale,Constant,//bottom left
		};*/

		ShaderData data =
		{
			{ XPos, YPos },
			Scale,
			int(MaxCount),
			Constant,
			int(Power)
		};

		//std::cout << glGetError() << "\n";

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

		// Position attribute
		glVertexAttribLPointer(0, 3, GL_DOUBLE, 9 * sizeof(GLdouble), (GLvoid*)0); glEnableVertexAttribArray(0);
		glVertexAttribLPointer(1, 3, GL_DOUBLE, 9 * sizeof(GLdouble), (GLvoid*)(3 * sizeof(GLdouble))); glEnableVertexAttribArray(1);
		glVertexAttribLPointer(2, 3, GL_DOUBLE, 9 * sizeof(GLdouble), (GLvoid*)(6 * sizeof(GLdouble))); glEnableVertexAttribArray(2);

		glBindVertexArray(0); // Unbind VAO


		//glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo);

		glBindBuffer(GL_UNIFORM_BUFFER, ubo);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(ShaderData), &data);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);



		// Render
		// Clear the colorbuffer
		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, renderedTexture);
		// Set our "renderedTexture" sampler to user Texture Unit 0
		//glUniform1i(texID, 0);
		// Draw the triangle
		ourShader.Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);

		if (Save) 
		{
			//SaveImage(2 * WIDTH, 2 * HEIGHT, "file.bmp", renderedTexture); 
			Save = false; 
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
}
