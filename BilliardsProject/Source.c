#include <stdio.h>
#include <GL\freeglut.h>
#include "Display.h"
#include "BilliardsMenu.h"
#include "GameInput.h"

#define TIMER 15

int main(int argc, char**argv)
{	
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
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
	glutMotionFunc(cueDisplay);
	//glutIdleFunc(animate);

	glutTimerFunc(TIMER, animate, 0);

	glutMainLoop();

	return 0;
}