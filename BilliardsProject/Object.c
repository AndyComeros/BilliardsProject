#include "Object.h"

#define FRICTION 0.996

void updateObject(Object* obj, float deltaTime)
{

	//scuff clamping, 1 seems like a reasonable for now
	if (length(obj->body.velocity) < 1) {
		obj->body.velocity.x = 0;
		obj->body.velocity.y = 0;
		obj->body.velocity.z = 0;
		obj->isAvtive = 0;
	}
	else {
		obj->body.position = add(obj->body.position, multiply(obj->body.velocity, deltaTime));
		obj->isAvtive = 1;
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

void drawSphereObject(Object* obj)
{
	glColor3f(0.0, 0.0, 1.0);

	glLineWidth(0.5);
	glPushMatrix();
	
	glTranslatef(obj->body.position.x, obj->body.position.y, obj->body.position.z);

	//dont know why but when velocity is 0 and a rotation is made the ball dissapears. so this check is here i guess...
	if (length(obj->body.velocity) > 0) {
		glRotatef(obj->body.rotAngle, obj->body.rotation.z, obj->body.rotation.y, obj->body.rotation.x);
	}
	
	glScalef(obj->body.scale.x, obj->body.scale.y, obj->body.scale.z);
	
	glutWireSphere(1, 10, 8);
	glPopMatrix();
}
