#include "GameInput.h"
#include "VectorMath.h"

#define CAM_LIFT 5
#define CAM_ROTATION 0.1

static float camRotAngle = 0;

void initGameInput(Object* n_CueBall)
{
	isHittable = 0;
	cueAngle = 4.71239;//270DEG
	cueForce = 200;//wierd default?
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
	//printf("DeltaTime %f\n",deltaTime);

	if (activeMenu != 3) return;

	switch (key)
	{
	case GLUT_KEY_UP:
		// lift up camera
		getCam()->pos.y += CAM_LIFT;
		break;
	case GLUT_KEY_DOWN:
		// lift down camera
		getCam()->pos.y -= CAM_LIFT;
		break;
	case GLUT_KEY_LEFT:
		// rotate camera left
		camRotAngle -= CAM_ROTATION;
		getCam()->pos.x = sin(camRotAngle) * 100; // * 100 is for distance
		getCam()->pos.z = cos(camRotAngle) * 100;
		break;
	case GLUT_KEY_RIGHT:
		// rotate camera right
		camRotAngle += CAM_ROTATION;
		getCam()->pos.x = sin(camRotAngle) * 100;
		getCam()->pos.z = cos(camRotAngle) * 100;
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

	updateCamera();
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
	yang = -((((400 - (float)y) / 800) * 45) - 37.59627); //degrees y up/down
	//adjust into rads and then into ratio

	xangr = xang * PI / 180; //radian conversions
	yangr = yang * PI / 180;

	
	zvar = -(77 / tan(yangr) - 100) * 1.5;
	xvar = sqrt(77*77+(100-zvar)*(100 - zvar))*(cos(PI/2 - xangr)); //intermediary calcs
	Vec3 location = { 0,3,0 };
	location.z = zvar+1.5;
	location.x = xvar*1.70;

	printf("\nangles at vals: x %f, y %f", xang, yang); //output angles
	printf("\nattempt at vals: x %f, y %f, z %f", location.x, location.y, location.z); //output location
	if (state == GLUT_DOWN)
	{

		float tolerance = length(minus(location, cueBall->position));
		printf("\nJam is %f, Cue Ball x: %f, y: %f, z: %f", jam, cueBall->position.x, cueBall->position.y, cueBall->position.z );
		if (tolerance < 20) 
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
		cueBall->velocity = minus(mouseUp, mouseDown);
	}
}

void cueDisplay(int x, int y)
{
	if (ballClick == 1)
	{
		float xang, xangr, yang, yangr, xvar, zvar;

		xang = (((float)x - 600) / 1200) * 60; //degrees x left/right
		yang = -((((400 - (float)y) / 800) * 45) - 37.59627); //degrees y up/down
		//adjust into rads and then into ratio

		xangr = xang * PI / 180; //radian conversions
		yangr = yang * PI / 180;


		zvar = -(77 / tan(yangr) - 100) * 1.5;
		xvar = sqrt(77 * 77 + (100 - zvar) * (100 - zvar)) * (cos(PI / 2 - xangr)); //intermediary calcs
		Vec3 location = { 0,3,0 };
		location.z = zvar + 1.5;
		location.x = xvar * 1.70;
		printf("Right now I am attempting to run the cuedisplay function");
		glShadeModel(
		glColor3f(1, 0, 0);
		glDisable(GL_LIGHTING);
		glBegin(GL_LINES);
		glLineWidth(3.0);
		glVertex3f(cueBall->position.x, cueBall->position.y, cueBall->position.z);
		glVertex3f(x, cueBall->position.y, y);
		glEnd();
		glEnable(GL_LIGHTING);

	}


}

void setCamRotAngle(GLfloat a)
{
	camRotAngle = a;
}
