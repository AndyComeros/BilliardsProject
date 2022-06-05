#include <stdio.h>
#include <GL\freeglut.h>
#include "Display.h"
#include "BilliardsMenu.h"
#include "GameInput.h"
#include "Texture.h"

#define TIMER 15
#define WINDOW_W 1920
#define WINDOW_H 1080



int main(int argc, char**argv)
{	

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(WINDOW_W, WINDOW_H);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("AAAA Pool");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	//maybe make seperate functions to aggregate all input functions, this will do for now
	glutKeyboardFunc(shotInputKeyBoard);
	glutSpecialFunc(shotInputSpecialKeyBoard);

	glutMouseFunc(handleMenuInput);
	glutMotionFunc(cueMovement);
	//glutIdleFunc(animate);

	glutTimerFunc(TIMER, animate, 0);

	//glutCloseFunc(displayGroupPictures);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutMainLoop();
	

	
	return 0;
}