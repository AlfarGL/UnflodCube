#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <fstream>
#include "cube.h"

using namespace std;

CCube g_cube("C:\\Users\\yangq\\Desktop\\test.txt", "C:\\Users\\yangq\\Desktop\\test2.txt");

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	g_cube.Display();
	
	glutSwapBuffers();
}

void Keyboard(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 27:
		glutLeaveMainLoop();
		break;
	case 'w':
		g_cube.Set_size_font_up();
		Render();
		break;
	default:
		g_cube.Check(c);
		Render();
		break;
	}

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	//glutInitWindowSize(1600,900);
	glutCreateWindow("Cube Unfold");
	glutFullScreen();
	
	glutDisplayFunc(Render);
	glutKeyboardFunc(Keyboard);

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		cout << "GLEW ERROR" << endl;
		return 1;
	}

	glutMainLoop();
	return 0;
}