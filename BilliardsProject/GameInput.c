#include "GameInput.h"
#include "VectorMath.h"

void initGameInput(Object* n_CueBall)
{
	cueAngle = 0;
	cueForce = 10;//wierd default?
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
		cueAngle += 0.1;
		break;
	case GLUT_KEY_RIGHT:
		//change angle
		cueAngle -= 0.1;
		break;
	case GLUT_KEY_F2://reset poition for testing
		cueBall->position.x = 0;
		cueBall->position.y = 5;
		cueBall->position.z = 0;
		cueBall->velocity.x = 0;
		cueBall->velocity.z = 0;
		break;
	default:
		break;
	}
}


void shotInputKeyBoard(unsigned char key, int x, int y)
{	
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
		cueAngle += 0.1;
		break;
	case 'd':
	case 'D':
		//change angle
		cueAngle -= 0.1;
		break;
	case 32://SPACEBAR
		cueBall->velocity = calcForceVector();
		break;
	default:
		break;
	}
}

void RenderShotIndicator() 
{

	GLfloat ballPos[3] = { cueBall->position.x,cueBall->position.y,cueBall->position.z};
	GLfloat zwo[3] = { 0,0,0 };
	

	glColor3f(1.0,1.0,1.0);

	//draw line pointing to used object for testing
	glBegin(GL_LINES);
	glVertex3fv(ballPos);
	glVertex3fv(zwo);
	glEnd();

	//calc line output end
	Vec3 outEnd = calcEndPoint();

	//draw output line
	glBegin(GL_LINES);
	glVertex3fv(ballPos);
	glVertex3f(outEnd.x,outEnd.y,outEnd.z);
	glEnd();

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
	endPoint[0] = sin(cueAngle) * cueForce + ballPos[0];
	endPoint[2] = cos(cueAngle) * cueForce + ballPos[2];

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