#include "Object.h"

#define FRICTION 0.996

void updateObject(Object* obj, float deltaTime)
{
	if (obj->isActive == 0)
	{
		printf("ball inactive");
		return;
	}

	//scuff clamping, 1 seems like a reasonable for now
	if (length(obj->body.velocity) < 1) {
		obj->body.velocity.x = 0;
		obj->body.velocity.y = 0;
		obj->body.velocity.z = 0;
		obj->body.isMoving = 0;
	}
	else 
	{
		obj->body.position = add(obj->body.position, multiply(obj->body.velocity, deltaTime));
		obj->body.isMoving = 1;
		//friction
		obj->body.velocity.x *= FRICTION;
		obj->body.velocity.y *= FRICTION;
		obj->body.velocity.z *= FRICTION;
	}

	/*
	obj->body.velocity = add(
		obj->body.velocity,
		multiply(
			obj->body.acceleration,
			deltaTime
		)
	); // prevVel + prevAccel*deltatime

	obj->body.acceleration = multiply(obj->body.acceleration, deltaTime); // update acceleration
	*/
}

Vec3 centerOfMass(OffModel* cModel)
{
	Vec3 centre = { 0, 0, 0 };

	for (int i = 0; i < cModel->nVert; i++)
	{
		centre.x += cModel->vertice[i].x;
		centre.y += cModel->vertice[i].y;
		centre.z += cModel->vertice[i].z;
	}

	centre.x /= cModel->nVert;
	centre.y /= cModel->nVert;
	centre.z /= cModel->nVert;

	return centre;
}

GLfloat radiusOfBoundingSphere(OffModel* cModel)
{
	GLfloat r = 0;

	for (int i = 0; i < cModel->nVert; i++)
	{
		Vec3 v = minus(cModel->vertice[i], centerOfMass(cModel));
		float d = length(v);

		if (d > r)
			r = d;
	}

	return r;
}

void normalizeOffModel(OffModel* cModel)
{
	int i = 0;
	Vec3 c = centerOfMass(cModel);
	float r = radiusOfBoundingSphere(cModel);

	for (i = 0; i < cModel->nVert; i++)
	{
		cModel->vertice[i].x -= c.x;
		cModel->vertice[i].y -= c.y;
		cModel->vertice[i].z -= c.z;
	}

	for (i = 0; i < cModel->nVert; i++)
	{
		cModel->vertice[i].x /= r;
		cModel->vertice[i].y /= r;
		cModel->vertice[i].z /= r;
	}
}

void loadOffObject(char* filename, Object* obj)
{
    readOffFile(filename, obj);
	normalizeOffModel(&obj->off);
}

void drawComplexObject(Object* obj)
{
    for (int i = 0; i < obj->off.nFace; i++)
    {
		glColor3fv(obj->off.faces[i].colour);
		

		glPushMatrix();
		glTranslatef(obj->body.position.x, obj->body.position.y, obj->body.position.z);
		glScalef(obj->body.scale.x, obj->body.scale.y, obj->body.scale.z);
		glRotatef(obj->body.rotAngle, obj->body.rotation.x, obj->body.rotation.y, obj->body.rotation.z);

        glBegin(GL_POLYGON);
			glVertex3f(obj->off.faces[i].p1->x, obj->off.faces[i].p1->y, obj->off.faces[i].p1->z);
			glVertex3f(obj->off.faces[i].p2->x, obj->off.faces[i].p2->y, obj->off.faces[i].p2->z);
			glVertex3f(obj->off.faces[i].p3->x, obj->off.faces[i].p3->y, obj->off.faces[i].p3->z);
        glEnd();
		glPopMatrix();
    }
}

//RTX enabled baby(not really)
static float pi = 3.1415926536;
void drawSphereShadow(float resolution,float radius, float x, float y, float z)
{		
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 0.0, 0.0);//black shadow

	float angleStep = pi * 2 / resolution; //space beween each point
	float angleCur = 0; //current angle

	glBegin(GL_POLYGON);
	for (size_t i = 0; i < resolution; i++)
	{
		glVertex3f(x + radius * cos(angleCur), y, z + radius * sin(angleCur));
		angleCur += angleStep;
	}
	glEnd();
	glEnable(GL_LIGHTING);
}

void drawSphereObject(Object* obj)
{
	//glColor3f(0.0, 0.0, 1.0);
	setMaterial(&obj->material);
	glLineWidth(0.5);
	glPushMatrix();
	
	glTranslatef(obj->body.position.x, obj->body.position.y, obj->body.position.z);

	drawSphereShadow(20, 2, 0, -2.2,0);

	glRotatef(obj->body.rotAngle, obj->body.rotation.z, obj->body.rotation.y, obj->body.rotation.x);
	glScalef(obj->body.scale.x, obj->body.scale.y, obj->body.scale.z);

	if (ballMode == 0)
	{
		glutSolidSphere(1, 20, 20);
	}
	else if (ballMode == 1) {
		glutSolidCube(2);
	}
	else {
		glutSolidTeapot(1);
	}
	
	//glutSolidTeapot(1);
	//glutWireSphere(1, 10, 8);
	glPopMatrix();
}
