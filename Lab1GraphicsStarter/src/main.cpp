// Standard Library
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <time.h>

// Libraries
#pragma comment(lib, "TTK.lib")
#include "TTK/TTK.h"
#include "GLUT/glut.h"

// Project specific
#include "CubeData.h"
#include "VertexBufferObject.h"

#define FRAMES_PER_SECOND 60
const int FRAME_DELAY_SPRITE = 1000 / FRAMES_PER_SECOND;

int windowWidth = 800;
int windowHeight = 600;

TTK::Vector3 mousePosition;
TTK::Vector3 position;

float deltaTime = 0.0f;

float t = 0.0f; // interpolation param
float multiplier = 1.0f;

TTK::Camera camera(TTK::Camera::PERSPECTIVE, windowWidth, windowHeight, 2.f, TTK::Vector3(10.0f));
TTK::ShaderProgram shaderProgram;

TTK::Texture2D texture;

float movementSpeed = 5000;

VertexBufferObject vbo;

void InitializeCube()
{
	// Create Cube

	AttributeDescriptor attribPositions;
	attribPositions.attributeLocation = AttributeLocations::VERTEX;
	attribPositions.attributeName = "vertices";
	attribPositions.data = (void*)vertexSorted;
	attribPositions.elementSize = sizeof(float);
	attribPositions.elementType = GL_FLOAT;
	attribPositions.numElements = sizeof(vertexSorted) / sizeof(float);
	attribPositions.numElementsPerAttrib = 3;

	vbo.addAttributeArray(attribPositions);

	// Repeat the above for the texture coords and normals

	AttributeDescriptor attribNormals;
	attribNormals.attributeLocation = AttributeLocations::NORMAL;
	attribNormals.attributeName = "normals";
	attribNormals.data = (void*)normal;
	attribNormals.elementSize = sizeof(float);
	attribNormals.elementType = GL_FLOAT;
	attribNormals.numElements = sizeof(normal) / sizeof(float);
	attribNormals.numElementsPerAttrib = 3;

	vbo.addAttributeArray(attribNormals);

	/*AttributeDescriptor attribTexcoords;
	attribTexcoords.attributeLocation = AttributeLocations::TEX_COORD;
	attribTexcoords.attributeName = "texcoords";
	attribTexcoords.data = (void*)texcoord;
	attribTexcoords.elementSize = sizeof(float);
	attribTexcoords.elementType = GL_FLOAT;
	attribTexcoords.numElements = sizeof(texcoord) / sizeof(float);
	attribTexcoords.numElementsPerAttrib = 2;

	vbo.addAttributeArray(attribTexcoords);*/

	vbo.createVBO(false);
}

/* function DisplayCallbackFunction(void)
* Description:
*  - this is the openGL display routine
*  - this draws the sprites appropriately
*/
void DisplayCallbackFunction(void)
{
	TTK::Graphics::SetBackgroundColour(0.5f, 0.5f, 0.5f);
	TTK::Graphics::ClearScreen();

	// Update Camera
	camera.updateView();
	camera.updateProjection();

	// Tell OGL to use our shader program
	shaderProgram.bind();

	// Make the model matrix
	TTK::Matrix4x4 modelMatrix = TTK::Matrix4x4(TTK::Matrix3x3(), TTK::Vector3(), 10.0f);

	// Send the mvp transform to the shader
	shaderProgram.sendUniformMat4("u_mvp", camera.getViewProjMat() * modelMatrix);

	// Bind texture and set the sampler
	texture.bind();
	shaderProgram.sendUniformInt("u_tex", 0);

	// draw the VBO
	vbo.draw();

	shaderProgram.unbind();

	glutSwapBuffers();
}

/* function void KeyboardCallbackFunction(unsigned char, int,int)
* Description:
*   - this handles keyboard input when a button is pressed
*/
void KeyboardCallbackFunction(unsigned char key, int x, int y)
{
	switch (key)
	{
		// Camera
	case 'a':
	case 'A':
		camera.moveLeft();
		break;
	case 'd':
	case 'D':
		camera.moveRight();
		break;
	case 'w':
	case 'W':
		camera.moveForward();
		break;
	case 's':
	case 'S':
		camera.moveBackward();
		break;
	case 'q':
	case 'Q':
		camera.moveUp();
		break;
	case 'e':
	case 'E':
		camera.moveDown();
		break;
	default:
		break;
	}
}
/* function void KeyboardUpCallbackFunction(unsigned char, int,int)
* Description:
*   - this handles keyboard input when a button is lifted
*/
void KeyboardUpCallbackFunction(unsigned char key, int x, int y)
{
	switch (key)
	{
	default:
		break;
	}
}

void SpecialInputCallbackFunction(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		position.z += movementSpeed * deltaTime;
		break;
	case GLUT_KEY_DOWN:
		position.z -= movementSpeed * deltaTime;
		break;
	case GLUT_KEY_LEFT:
		position.x += movementSpeed * deltaTime;
		break;
	case GLUT_KEY_RIGHT:
		position.x -= movementSpeed * deltaTime;
		break;
	}
}
/* function TimerCallbackFunction(int value)
* Description:
*  - this is called many times per second
*  - this enables you to animate things
*  - no drawing, just changing the state
*  - changes the frame number and calls for a redisplay
*  - FRAME_DELAY_SPRITE is the number of milliseconds to wait before calling the timer again
*/
void TimerCallbackFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(FRAME_DELAY_SPRITE, TimerCallbackFunction, 0);

	// Calculate new deltaT for potential updates and physics calculations
	static int elapsedTimeAtLastTick = 0;
	int totalElapsedTime = glutGet(GLUT_ELAPSED_TIME);

	deltaTime = totalElapsedTime - elapsedTimeAtLastTick;
	deltaTime /= 1000.0f;
	elapsedTimeAtLastTick = totalElapsedTime;
}

/* function WindowReshapeCallbackFunction()
* Description:
*  - this is called whenever the window is resized
*  - and sets up the projection matrix properly
*  - currently set up for an orthographic view (2D only)
*/
void WindowReshapeCallbackFunction(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
	// TTK::Graphics::SetCameraMode2D(w, h); rip
	camera.setViewPortSize(windowWidth, windowHeight);
	camera.updateAspectRatio(windowWidth, windowHeight);
	camera.updateProjection();

	glViewport(0, 0, windowWidth, windowHeight);
}

void MouseClickCallbackFunction(int button, int state, int x, int y)
{
	mousePosition.x = x;
	mousePosition.y = y;

	camera.setMousePosition(mousePosition);

	switch (state)
	{
	case GLUT_DOWN:
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
		{
		}
		break;
		default:
			break;
		}
		break;

	case GLUT_UP:
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}
}


/* function MouseMotionCallbackFunction()
* Description:
*   - this is called when the mouse is clicked and moves
*/
void MouseMotionCallbackFunction(int x, int y)
{
	mousePosition.x = x;
	mousePosition.y = y;

	camera.rotateXY(x, y);
}

/* function MousePassiveMotionCallbackFunction()
* Description:
*   - this is called when the mouse is moved in the window
*/
void MousePassiveMotionCallbackFunction(int x, int y)
{

}

/* function main()
* Description:
*  - this is the main function
*  - does initialization and then calls glutMainLoop() to start the event handler
*/
int main(int argc, char **argv)
{
	/* initialize the window and OpenGL properly */
	glutInit(&argc, argv);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Graphics Tutorials");

	/* set up our function callbacks */
	glutDisplayFunc(DisplayCallbackFunction);
	glutKeyboardFunc(KeyboardCallbackFunction);
	glutKeyboardUpFunc(KeyboardUpCallbackFunction);
	glutReshapeFunc(WindowReshapeCallbackFunction);
	glutMouseFunc(MouseClickCallbackFunction);
	glutMotionFunc(MouseMotionCallbackFunction);
	glutPassiveMotionFunc(MousePassiveMotionCallbackFunction);
	glutSpecialFunc(SpecialInputCallbackFunction);
	glutTimerFunc(1, TimerCallbackFunction, 0);

	TTK::Graphics::SetBackgroundColour(0.5f, 0.5f, 0.5f);
	TTK::Graphics::ClearScreen();

	/* initialize TTK */
	TTK::InitializeTTK();


	// Must initialize glew before calling any modern GL functions
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "TTK::InitializeTTK Error: GLEW failed to init" << std::endl;
	}
	printf("OpenGL version: %s, GLSL version: %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

	// Load a texture
	texture.loadTexture("../Assets/Textures/dkong2.png");

	TTK::Shader vShader;
	vShader.loadShaderFromFile("../Assets/Shaders/passthru_v.glsl", GL_VERTEX_SHADER);

	TTK::Shader fShader;
	fShader.loadShaderFromFile("../Assets/Shaders/red_f.glsl", GL_FRAGMENT_SHADER);

	shaderProgram.attachShader(vShader);
	shaderProgram.attachShader(fShader);
	shaderProgram.linkProgram();

	InitializeCube();

	/* start the event handler */
	glutMainLoop();
	return 0;
}