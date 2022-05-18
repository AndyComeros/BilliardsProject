#include <stdio.h>
#include <GL\freeglut.h>
#include "Display.h"
#include "BilliardsMenu.h"
#include "GameInput.h"

#define TIMER 15

int main(int argc, char**argv)
{
	loadComplexObj(); // within display.c
	
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	//maybe make seperate functions to aggregate all input functions, this will do for now
	glutKeyboardFunc(shotInputKeyBoard);
	glutSpecialFunc(shotInputSpecialKeyBoard);

	glutMouseFunc(handleMenuInput);

	//glutIdleFunc(animate);

	glutTimerFunc(TIMER, animate, 0);

	glutMainLoop();

	return 0;
}