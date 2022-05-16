#include <stdio.h>
#include <GL\freeglut.h>
#include "Display.h"
#include "BilliardsMenu.h"

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
	initGUI();
	InitBilliardUI();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(handleMenuInput);

	//glutIdleFunc(animate);

	glutTimerFunc(TIMER, animate, 0);

	glutMainLoop();

	return 0;
}