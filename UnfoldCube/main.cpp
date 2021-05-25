#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <fstream>
#include "cube.h"
#include "cube3d.h"

using namespace std;

CCube g_cube;
CCube3d g_cube3d;

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	g_cube.Display();
	//g_cube3d.p(&g_cube3d);
	
	glutSwapBuffers();
}

void Keyboard(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 27:
		glutLeaveMainLoop();
		break;
	case 'a':
		g_cube.Select_problem(false);
		Render();
		break;
	case 'd':
		g_cube.Select_problem(true);
		Render();
		break;
	case 'w':
		g_cube.Set_size_font(1);
		Render();
		break;
	case 's':
		g_cube.Set_size_font(-1);
		Render();
		break;
	case 'e':
		g_cube.easy();
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
	glutCreateWindow("Cube Unfold");
	glutFullScreen();
	
	//glutDisplayFunc(g_cube3d.display);
	//void (*p)();
	
	glutDisplayFunc(Render);
	glutKeyboardFunc(Keyboard);

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		cout << "GLEW ERROR" << endl;
		return 1;
	}
	if (g_cube.flag) {
		return 1;
	}


	glutMainLoop();
	return 0;
}