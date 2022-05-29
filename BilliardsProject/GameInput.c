#include "GameInput.h"
#include "VectorMath.h"


void initGameInput(Object* n_CueBall)
{
	isHittable = 0;
	cueAngle = -1.5f;
	cueForce = 200;//wierd default?
	cueBall = &n_CueBall->body;
}

void shotInputSpecialKeyBoard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		//increase output velocity
		cueForce += 1;
		break;
	case GLUT_KEY_DOWN:
		//decrease output velocity
		cueForce -= 1;
		break;
	case GLUT_KEY_LEFT:
		//change angle
		cueAngle += 0.05;
		break;
	case GLUT_KEY_RIGHT:
		//change angle
		cueAngle -= 0.05;
		break;
	default:
		break;
	}
}


void shotInputKeyBoard(unsigned char key, int x, int y)
{	
	if(isHittable == 1){
		switch (key)
		{
		case 'w':
		case 'W':
			//increase output velocity
			cueForce += 1;
			break;
		case 's':
		case 'S':
			//decrease output velocity
			cueForce -= 1.0;
			break;
		case 'a':
		case 'A':
			//change angle
			cueAngle += 0.05;
			break;
		case 'd':
		case 'D':
			//change angle
			cueAngle -= 0.05;
			break;
		case 32://SPACEBAR
			cueBall->velocity = calcForceVector();
			isHittable = 0;
			break;
		default:
			break;
		}
	}

}

void RenderShotIndicator()
{
	//modify ui element
	char cueForceChar[255];
	sprintf(cueForceChar, "Force: %d", (int)cueForce);
	strcpy(GetUI(3)->element[1].Text, cueForceChar);

	if (isHittable == 1) {
	

		//render line
		GLfloat ballPos[3] = { cueBall->position.x,cueBall->position.y,cueBall->position.z };
		GLfloat zwo[3] = { 0,0,0 };

		glDisable(GL_LIGHTING);
		glLineWidth(3.0);
		glColor3f(0.0, 0.5, 1.0);

		//draw line pointing to used object for testing
		/*
		glBegin(GL_LINES);
		glVertex3fv(ballPos);
		glVertex3fv(zwo);
		glEnd();
		*/

		//calc line output end
		Vec3 outEnd = calcEndPoint();

		//draw output line
		glBegin(GL_LINES);
		glVertex3fv(ballPos);
		glVertex3f(outEnd.x, outEnd.y, outEnd.z);
		glEnd();
		glEnable(GL_LIGHTING);
	}
	/*temp follow ball
	glLoadIdentity();
	gluLookAt(
		cueBall->position.x + 5, cueBall->position.y + 1, cueBall->position.z + 5,
		cueBall->position.x, cueBall->position.y, cueBall->position.z,
		0, 1, 0);
	*/
}

Vec3 calcEndPoint() 
{
	GLfloat ballPos[3] = { cueBall->position.x,cueBall->position.y,cueBall->position.z };

	GLfloat endPoint[3] = { ballPos[0],ballPos[1],ballPos[2] };
	endPoint[0] = sin(cueAngle) * cueForce/2 + ballPos[0];
	endPoint[2] = cos(cueAngle) * cueForce/2 + ballPos[2];

	Vec3 v = { endPoint[0], endPoint[1], endPoint[2] };

	return v;
}

Vec3 calcForceVector()
{
	GLfloat fv[3] = { 0,0,0};
	fv[0] = sin(cueAngle) * cueForce;
	fv[2] = cos(cueAngle) * cueForce;

	Vec3 retv = { fv[0], fv[1], fv[2] };

	return retv;

}