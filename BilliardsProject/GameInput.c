#include "GameInput.h"
#include "VectorMath.h"


void initGameInput(Object* n_CueBall)
{
	isHittable = 0;
	cueAngle = 4.71239;//270DEG
	cueForce = 30;//wierd default?
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
		cueAngle -= AIM_SENSIVITY;
		break;
	case GLUT_KEY_RIGHT:
		//change angle
		cueAngle += AIM_SENSIVITY;
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
			cueForce -= 1;
			break;
		case 'a':
		case 'A':
			//change angle
			cueAngle -= AIM_SENSIVITY;
			break;
		case 'd':
		case 'D':
			//change angle
			cueAngle += AIM_SENSIVITY;
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
		glDisable(GL_LIGHTING);
		GLfloat ballPos[3] = { cueBall->position.x,cueBall->position.y,cueBall->position.z };
		GLfloat zwo[3] = { 0,0,0 };

		glLineWidth(3.0);
		glColor3f(0.0, 0.5, 1.0);

		//calc line output end
		Vec3 outEnd = calcEndPoint();

		//draw output line
		glBegin(GL_LINES);
		glVertex3fv(ballPos);
		glVertex3f(outEnd.x, outEnd.y, outEnd.z);
		glEnd();
		glEnable(GL_LIGHTING);
	}
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