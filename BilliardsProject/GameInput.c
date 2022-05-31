#include "GameInput.h"
#include "VectorMath.h"


void initGameInput(Object* n_CueBall)
{
	isHittable = 0;
	cueAngle = 4.71239;//270DEG
	cueForce = 30;//wierd default?
	cueBall = &n_CueBall->body;
}

float currTime;
float deltaTime;
float prevTime;
float timeScale = 10000;

int inGame = 0;
int ballClick = 0;
Vec3 mouseDown; 
Vec3 mouseUp;
Vec3 origin = { 0,0,0 };
void shotInputSpecialKeyBoard(unsigned char key, int x, int y)
{
	currTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currTime - prevTime) / timeScale;
	printf("DeltaTime %f\n",deltaTime);

	switch (key)
	{
	case GLUT_KEY_UP:
		//increase output velocity
		cueForce += INPUT_SENSITIVITY*20;
		break;
	case GLUT_KEY_DOWN:
		//decrease output velocity
		cueForce -= INPUT_SENSITIVITY*20;
		break;
	case GLUT_KEY_LEFT:
		//change angle
		cueAngle += INPUT_SENSITIVITY;
		break;
	case GLUT_KEY_RIGHT:
		//change angle
		cueAngle -= INPUT_SENSITIVITY;
		break;
	case GLUT_KEY_F1:
	
		if (inGame == 0) {
			inGame = 1;
			glutMouseFunc(clickInput);
		}
		else if(inGame ==1) {
			glutMouseFunc(handleMenuInput);
			inGame = 0;
		}
	default:
		break;
	}
	prevTime = currTime;
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
			cueAngle += 0.01;
			break;
		case 'd':
		case 'D':
			//change angle
			cueAngle -= 0.01;
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
		

		float maxRed = 170;//power the indicator reches max redness
		float lengthMod = 0.3;//how long the indicator is relative to power
		float redness = cueForce / maxRed;
		if (cueForce > maxRed) {
			redness = 1;
		}
		
		glLineWidth(redness * 5);

		//calc line output end
		Vec3 outEnd = calcEndPoint(lengthMod);

		//draw output line
		glBegin(GL_LINES);
		glColor3f(0, 0.5, 0.5);
		glVertex3fv(ballPos);
		glColor3f(redness, 1 - redness, 1 - redness);
		glVertex3f(outEnd.x, outEnd.y, outEnd.z);
		glEnd();

		glPushMatrix();
		
		glTranslatef(ballPos[0], ballPos[1], ballPos[2]);
		glRotatef(cueAngle * 57.2958, 0, 1, 0);
		glTranslatef(0,0,cueForce * lengthMod);
		glutSolidCone(1, cueForce/12, 5, 10);
		glPopMatrix();

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

Vec3 calcEndPoint(float lengthMod) 
{
	GLfloat ballPos[3] = { cueBall->position.x,cueBall->position.y,cueBall->position.z };

	GLfloat endPoint[3] = { ballPos[0],ballPos[1],ballPos[2] };
	endPoint[0] = sin(cueAngle) * cueForce * lengthMod + ballPos[0];
	endPoint[2] = cos(cueAngle) * cueForce * lengthMod + ballPos[2];

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
#define PI 3.14159265
void clickInput(int Button, int state, int x, int y)
{
	float xang, xangr, yang, yangr, xvar, zvar;

	xang = (((float)x - 600) / 1200) * 60; //degrees x left/right
	yang = (((400 - (float)y) / 800) * 45) - 37.59627 + 90; //degrees y up/down
	//adjust into rads and then into ratio

	xangr = xang * PI / 180; //radoan conversions
	yangr = yang * PI / 180;

	xvar = 77 * tan(xangr); //intermediary calcs
	zvar = 77 * tan(yangr) - 100;
	Vec3 location = { 0,3,0 };
	location.z = zvar * cos(xangr);
	location.x = -(100 - location.z) * sin(xangr);

	printf("\nangles at vals: x %f, y %f", xang, yang); //output angles
	printf("\nattempt at vals: x %f, y %f, z %f", location.x, location.y, location.z); //output location
	if (state == GLUT_DOWN)
	{

		float jam = length(minus(minus(location, origin), cueBall->position));
		printf("\nJam is %f, Cue Ball x: %f, y: %f, z: %f", jam, cueBall->position.x, cueBall->position.y, cueBall->position.z );
		if (jam < 30) 
		{
			mouseDown.x = location.x;
			mouseDown.y = location.y;
			mouseDown.z = location.z;
			ballClick = 1;
		}
	}

	if (state == GLUT_UP && ballClick == 1)
	{
		mouseUp.x = location.x;
		mouseUp.y = location.y;
		mouseUp.z = location.z;
		ballClick = 0;
		cueBall->velocity = minus(mouseDown, mouseUp);
	}
}